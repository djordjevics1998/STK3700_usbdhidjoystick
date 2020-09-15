/***************************************************************************//**
 * @file
 * @brief LCD controller demo for EFM32GG_STK3700 development kit
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

#include <stdint.h>
#include <stdbool.h>
#include "em_device.h"
#include "em_chip.h"
#include "em_cmu.h"

#include "bsp.h"
#include "segmentlcd.h"
#include "bsp_trace.h"
#include <em_adc.h>
#include "OLED_I2C.h"
#include "em_timer.h"
#include "em_emu.h"
#include "em_gpio.h"
#include "em_prs.h"
#include "em_system.h"
#include "em_chip.h"
#include <stdio.h>
#include <string.h>

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
void Delay1(uint32_t dlyTicks);

/***************************************************************************//**
 * @brief SysTick_Handler
 *   Interrupt Service Routine for system tick counter
 * @note
 *   No wrap around protection
 ******************************************************************************/
void SysTick_Handler1(void)
{
  msTicks++;       /* increment counter necessary in Delay()*/
}

/***************************************************************************//**
 * @brief Delays number of msTick Systicks (typically 1 ms)
 * @param dlyTicks Number of ticks to delay
 ******************************************************************************/
void Delay1(uint32_t dlyTicks)
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
uint16_t adcSingle1(ADC_SingleInput_TypeDef ch)
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
void TIMER3_IRQHandler1(void)
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

float readCoordinate1(ADC_SingleInput_TypeDef ch, comp compensation) {
	uint32_t sum = 0;
	for(int i = 0; i < SAMPLE_AVG_LEN; i++) sum += adcSingle(ch);
	return sum / (float) SAMPLE_AVG_LEN + compensation;
}

/***************************************************************************//**
 * @brief  Main function
 ******************************************************************************/
int main1(void) {
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

	  /* Enable LCD without voltage boost */
	  SegmentLCD_Init(false);
	  SegmentLCD_Write("potat");

	  float vx, vy, vz;
	  char* dirx, diry, dirz;
	  float treshold = 0;
	  /* Infinite loop with test pattern. */
	  while (1) {
		  vx = readCoordinate(adcSingleInpCh0, COMP_X);
		  vy = readCoordinate(adcSingleInpCh1, COMP_Y);
		  vz = readCoordinate(adcSingleInpCh2, COMP_Z);
		  if(vx>= treshold) dirx = "A";
		  else if(vx<treshold) dirx = "D";

		  if(vz>= treshold) dirz = "W";
		  else if(vz<treshold) dirz = "S";

		  SegmentLCD_Number(vx);
		  Delay(500);
	  }
}
