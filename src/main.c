/***************************************************************************//**
 * @file
 * @brief USB HID keyboard device example.
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/
#include "em_device.h"
#include "em_chip.h"
#include "em_cmu.h"
#include "em_gpio.h"
#include "segmentlcd.h"
#include "bsp_trace.h"

#include "em_usb.h"
#include "descriptors.h"

#include <stdint.h>
#include <stdbool.h>

#include "bsp.h"
#include <em_adc.h>
#include "OLED_I2C.h"
#include "em_timer.h"
#include "em_emu.h"
#include "em_prs.h"
#include "em_system.h"
#include "em_chip.h"
#include <stdio.h>
#include <string.h>
/***************************************************************************//**
 *
 * This example shows how a HID keyboard can be implemented.
 *
 ******************************************************************************/

/*** Typedef's and defines. ***/

#define SCAN_TIMER              1       /* Timer used to scan keyboard. */
#define SCAN_RATE               50

#define ACTIVITY_LED_PORT       gpioPortE   /* LED0. */
#define ACTIVITY_LED_PIN        2
#define BUTTON_PORT             gpioPortB
#define BUTTON_PIN              9

/*** Function prototypes. ***/

static void StateChange(USBD_State_TypeDef oldState,
                        USBD_State_TypeDef newState);

/*** Variables ***/

static int      keySeqNo;           /* Current position in report table. */
static bool     keyPushed;          /* Current pushbutton status. */

static const USBD_Callbacks_TypeDef callbacks =
{
  .usbReset        = NULL,
  .usbStateChange  = StateChange,
  .setupCmd        = HIDKBD_SetupCmd,
  .isSelfPowered   = NULL,
  .sofInt          = NULL
};

static const USBD_Init_TypeDef usbInitStruct =
{
  .deviceDescriptor    = &USBDESC_deviceDesc,
  .configDescriptor    = USBDESC_configDesc,
  .stringDescriptors   = USBDESC_strings,
  .numberOfStrings     = sizeof(USBDESC_strings) / sizeof(void*),
  .callbacks           = &callbacks,
  .bufferingMultiplier = USBDESC_bufferingMultiplier,
  .reserved            = 0
};

int RETARGET_WriteString(char *s);
void RETARGET_SerialInit(void);
void RETARGET_SerialCrLf(int on);
int RETARGET_ReadChar(void);
char bluetooth[128];

#define SAMPLE_AVG_LEN 100

#define LIGHTSENSE_EXCITE_PORT   gpioPortD
#define LIGHTSENSE_EXCITE_PIN    6U
#define LIGHTSENSE_SENSOR_PORT   gpioPortC
#define LIGHTSENSE_SENSOR_PIN    6U

#define OUTPUT_PORT gpioPortE
#define OUTPUT_PIN 2
#define LOCATION TIMER_ROUTE_LOCATION_LOC1
#define PWM_FREQ 10000

#define GYTOP 100
#define GYBOT 0
#define GXTOP 20
#define GXBOT 0
#define GX0  20
#define GY0  55
#define GW   100
#define GH   50
extern uint8_t SmallFont[];

volatile uint32_t msTicks; /* counts 1ms timeTicks */

typedef enum {COMP_X = -1655, COMP_Y = -1653, COMP_Z = -1675} comp;

/* Locatl prototypes */
void Delay(uint32_t dlyTicks);

/***************************************************************************//**
 * @brief SysTick_Handler
 *   Interrupt Service Routine for system tick counter
 * @note
 *   No wrap around protection
 ******************************************************************************/
void SysTick_Handler(void)
{
  msTicks++;       /* increment counter necessary in Delay()*/
}

/***************************************************************************//**
 * @brief Delays number of msTick Systicks (typically 1 ms)
 * @param dlyTicks Number of ticks to delay
 ******************************************************************************/
void Delay(uint32_t dlyTicks)
{
  uint32_t curTicks;

  curTicks = msTicks;
  while ((msTicks - curTicks) < dlyTicks) ;
}

#define ADC_CLOCK               11000000        /* ADC conversion clock */
#define ADC_12BIT_MAX           4096            /* 2^12 */
/***************************************************************************//**
* @brief Configure ADC for single channel.
*******************************************************************************/
uint16_t adcSingle(ADC_SingleInput_TypeDef ch)
{
  uint16_t sampleValue;
  ADC_Init_TypeDef       init       = ADC_INIT_DEFAULT;
  ADC_InitSingle_TypeDef singleInit = ADC_INITSINGLE_DEFAULT;

  /* Init common settings for both single conversion and scan mode */
  init.timebase = ADC_TimebaseCalc(0);
  init.prescale = ADC_PrescaleCalc(ADC_CLOCK, 0);
  ADC_Init(ADC0, &init);

  singleInit.input      = ch;
  /* The datasheet specifies a minimum aquisition time when sampling VDD/3 */
  /* 32 cycles should be safe for all ADC clock frequencies */
  singleInit.reference = adcRefVDD;
  singleInit.acqTime = adcAcqTime32;
  ADC_InitSingle(ADC0, &singleInit);

  ADC_Start(ADC0, adcStartSingle);

  /* Wait while conversion is active */
  while (ADC0->STATUS & ADC_STATUS_SINGLEACT);

  /* Get ADC result */
  sampleValue = ADC_DataSingleGet(ADC0);

  /* Calculate voltage mV */
  sampleValue = (sampleValue * 3330 * 1) / ADC_12BIT_MAX;

  /* Write to LCD */
  //SegmentLCD_Number(sampleValue);
  //ADC_Reset(ADC0);
  return(sampleValue);
}

/**************************************************************************//**
 * @brief TIMER3_IRQHandler
 * Interrupt Service Routine TIMER3 Interrupt Line
 *****************************************************************************/
void TIMER3_IRQHandler(void)
{
  uint32_t compareValue;

  /* Clear flag for TIMER3 overflow interrupt */
  TIMER_IntClear(TIMER3, TIMER_IF_OF);

  compareValue = TIMER_CaptureGet(TIMER3, 2);
  /* increment duty-cycle or reset if reached TOP value */
  if( compareValue == TIMER_TopGet(TIMER3))
    TIMER_CompareBufSet(TIMER3, 2, 0);
  else
    TIMER_CompareBufSet(TIMER3, 2, ++compareValue);
}

float readCoordinate(ADC_SingleInput_TypeDef ch, comp compensation) {
	uint32_t sum = 0;
	for(int i = 0; i < SAMPLE_AVG_LEN; i++) sum += adcSingle(ch);
	return sum / (float) SAMPLE_AVG_LEN + compensation;
}

/***************************************************************************//**
 * @brief main - the entrypoint after reset.
 ******************************************************************************/
int main(void)
{

	HIDKBD_Init_t hidInitStruct;

	/* Chip errata */
	CHIP_Init();

	/* If first word of user data page is non-zero, enable Energy Profiler trace */
	BSP_TraceProfilerSetup();

	// redirect to LEUART0
  	RETARGET_SerialInit();
  	RETARGET_SerialCrLf(0);

  	/* Enable clock for GPIO module */

  	GPIO_PinModeSet(gpioPortD, 0, gpioModeInput, 1);
  	GPIO_PinModeSet(gpioPortD, 1, gpioModeInput, 1);
  	GPIO_PinModeSet(gpioPortD, 2, gpioModeInput, 1);
  	/* Enable ADC clock */
  	CMU_ClockEnable(cmuClock_GPIO, true);
  	CMU_ClockEnable(cmuClock_ADC0, true);

  	/* Setup SysTick Timer for 1 msec interrupts  */
  	if (SysTick_Config(CMU_ClockFreqGet(cmuClock_CORE) / 1000)) {
  		while (1) ;
  	}

  GPIO_PinModeSet(BUTTON_PORT, BUTTON_PIN, gpioModeInputPull, 1);
  GPIO_PinModeSet(ACTIVITY_LED_PORT, ACTIVITY_LED_PIN, gpioModePushPull, 0);
  CMU_ClockSelectSet(cmuClock_HF, cmuSelect_HFXO);
  SegmentLCD_Init(false);
  SegmentLCD_Write("usb kbd");
  SegmentLCD_Symbol(LCD_SYMBOL_GECKO, true);

  /* Initialize HID keyboard driver. */
  hidInitStruct.hidDescriptor = (void*)USBDESC_HidDescriptor;
  hidInitStruct.setReportFunc = NULL;
  HIDKBD_Init(&hidInitStruct);

  /* Initialize and start USB device stack. */
  USBD_Init(&usbInitStruct);

  /*
   * When using a debugger it is practical to uncomment the following three
   * lines to force host to re-enumerate the device.
   */
  /* USBD_Disconnect();      */
  /* USBTIMER_DelayMs(1000); */
  /* USBD_Connect();         */

  /* Enable LCD without voltage boost */
  SegmentLCD_Init(false);
  SegmentLCD_Write("potat");

  float vx, vy, vz;
  float treshold = 0;
  HIDKBD_KeyReport_t report;
  /* Infinite loop with test pattern. */
  while (1) {
	  vx = readCoordinate(adcSingleInpCh0, COMP_X);
	  vy = readCoordinate(adcSingleInpCh1, COMP_Y);
	  vz = readCoordinate(adcSingleInpCh2, COMP_Z);
	  if (vx > 330) vx = 330;
	  else if(vx < -330) vx = -330;
	  if(vy > 330) vy = 330;
	  else if(vy < -330) vy = -330;
	  if(vz > 330) vz = 330;
	  else if(vz < -330) vz = -330;

	  report.X = -vx * 127 / 330;

	  report.Y = vz * 127 / 330;
	  if(vy > 160) {
		  if(vz > 0) report.Buttons = 1;
		  else report.Buttons = 1 << 2;
	  }
	  else if(abs(vx) > 50) report.Buttons = 1 << 1;
	  else report.Buttons = 0;

	  SegmentLCD_Number(report.Y);
	  /*if(vy > 160) report.Buttons = 1 << 14;//report = (void*)&USBDESC_reportTable[15];
	  else if(vy < -160) report.Buttons = 0x02;//report = (void*)&USBDESC_reportTable[18];
	  else {
		  report.Buttons = 0;
		  //report = (void*)&USBDESC_noKeyReport;
	  }*/

	  /* Pass keyboard report on to the HID keyboard driver. */
	  HIDKBD_KeyboardEvent(&report);
  }
}

/***************************************************************************//**
 * @brief
 *   Timeout function for keyboard scan timer.
 *   Scan keyboard to check for key press/release events.
 *   This function is called at a fixed rate.
 ******************************************************************************/
static void ScanTimeout(void)
{
  bool pushed;
  HIDKBD_KeyReport_t *report;

  /* Check pushbutton */
  pushed = GPIO_PinInGet(BUTTON_PORT, BUTTON_PIN) == 0;

  if (!keyPushed) {
    GPIO_PinOutToggle(ACTIVITY_LED_PORT, ACTIVITY_LED_PIN);
  }

  if ( pushed != keyPushed ) { /* Any change in keyboard status ? */
    if ( pushed ) {
      report = (void*)&USBDESC_reportTable[keySeqNo];
    } else {
      report = (void*)&USBDESC_noKeyReport;
    }

    /* Pass keyboard report on to the HID keyboard driver. */
    HIDKBD_KeyboardEvent(report);
  }

  /* Keep track of the new keypush event (if any) */
  if ( pushed && !keyPushed ) {
    /* Advance to next position in report table */
    keySeqNo++;
    if ( keySeqNo == (sizeof(USBDESC_reportTable) / sizeof(HIDKBD_KeyReport_t))) {
      keySeqNo = 0;
    }
    GPIO_PinOutSet(ACTIVITY_LED_PORT, ACTIVITY_LED_PIN);
  }
  keyPushed = pushed;

  /* Restart keyboard scan timer */
  USBTIMER_Start(SCAN_TIMER, SCAN_RATE, ScanTimeout);
}

/***************************************************************************//**
 * @brief
 *   Callback function called each time the USB device state is changed.
 *   Starts keyboard scanning when device has been configured by USB host.
 *
 * @param[in] oldState The device state the device has just left.
 * @param[in] newState The new device state.
 ******************************************************************************/
static void StateChange(USBD_State_TypeDef oldState,
                        USBD_State_TypeDef newState)
{
  /* Call HIDKBD drivers state change event handler. */
  HIDKBD_StateChangeEvent(oldState, newState);

  if ( newState == USBD_STATE_CONFIGURED ) {
    /* We have been configured, start scanning the keyboard ! */
    if ( oldState != USBD_STATE_SUSPENDED ) { /* Resume ?   */
      keySeqNo        = 0;
      keyPushed       = false;
      GPIO_PinOutSet(ACTIVITY_LED_PORT, ACTIVITY_LED_PIN);
    }
    USBTIMER_Start(SCAN_TIMER, SCAN_RATE, ScanTimeout);
  } else if ( (oldState == USBD_STATE_CONFIGURED)
              && (newState != USBD_STATE_SUSPENDED)    ) {
    /* We have been de-configured, stop keyboard scanning. */
    USBTIMER_Stop(SCAN_TIMER);
    GPIO_PinOutClear(ACTIVITY_LED_PORT, ACTIVITY_LED_PIN);
  } else if ( newState == USBD_STATE_SUSPENDED ) {
    /* We have been suspended, stop keyboard scanning. */
    /* Reduce current consumption to below 2.5 mA.     */
    GPIO_PinOutClear(ACTIVITY_LED_PORT, ACTIVITY_LED_PIN);
    USBTIMER_Stop(SCAN_TIMER);
  }
}
