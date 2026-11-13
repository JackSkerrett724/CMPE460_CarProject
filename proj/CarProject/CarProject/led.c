/**
 * ******************************************************************************
 * @file    : leds.c
 * @brief   : LEDs file
 * @details : LED initialization and interaction
 * 
 * @author Wil Salus
 * @date 8/26/2026
 * ******************************************************************************
*/
#include <stdint.h>
#include <ti/devices/msp/msp.h>
#include "lab1/leds.h" // OR #include "leds.h"

#define LED_1_OFF                (0) 
#define LED_1_ON                 (1) 
#define LED_1_TOG                (2) 

#define LED_2_OFF                (0) 
#define LED_2_RED                (1) 
#define LED_2_GREEN              (2) 
#define LED_2_BLUE               (3) 
#define LED_2_CYAN               (4) 
#define LED_2_MAGENTA            (5) 
#define LED_2_YELLOW             (6) 
#define LED_2_WHITE              (7) 


/**
 * @brief Initialze LED1
 * @hint You might want to check out the schematics in the MSP User Guide
 *       The IOMUX has a hardware inversion bit
*/

void LED1_init(void){
	//Peripheral enable
	if (!(GPIOA->GPRCM.PWREN & GPIO_PWREN_ENABLE_MASK)){
		//Peripheral reset control
		GPIOA->GPRCM.RSTCTL |= (GPIO_RSTCTL_KEY_UNLOCK_W | GPIO_RSTCTL_RESETASSERT_ASSERT | GPIO_RSTCTL_RESETSTKYCLR_CLR);
		GPIOA->GPRCM.PWREN |= (GPIO_PWREN_ENABLE_ENABLE | GPIO_PWREN_KEY_UNLOCK_W);
	}
	
	//Configure the IOMUX register for peripheral
	IOMUX -> SECCFG.PINCM[IOMUX_PINCM1] |= (IOMUX_PINCM1_PF_GPIOA_DIO00 | IOMUX_PINCM_PC_CONNECTED);
	IOMUX -> SECCFG.PINCM[IOMUX_PINCM1] |= IOMUX_PINCM_DRV_DRVVAL1;
	IOMUX -> SECCFG.PINCM[IOMUX_PINCM1] |= IOMUX_PINCM_INV_ENABLE;
	
	//Enable GPIO ouput
	GPIOA -> DOESET31_0 |= GPIO_DOESET31_0_DIO0_SET;
	
	//Init the pin to off
	GPIOA -> DOUTCLR31_0 |= GPIO_DOUTCLR31_0_DIO0_CLR;
}
/**
 * @brief Initialize LED2
 * @note You must account for each LED color
*/
void LED2_init(void){
	//Peripheral enable
	if (!(GPIOB->GPRCM.PWREN & GPIO_PWREN_ENABLE_MASK)){
		//Peripheral reset control
		GPIOB->GPRCM.RSTCTL |= (GPIO_RSTCTL_KEY_UNLOCK_W | GPIO_RSTCTL_RESETASSERT_ASSERT | GPIO_RSTCTL_RESETSTKYCLR_CLR);
		GPIOB->GPRCM.PWREN |= (GPIO_PWREN_ENABLE_ENABLE | GPIO_PWREN_KEY_UNLOCK_W);
	}
	
	//RED LED
	//Configure the IOMUX register for peripheral (RED LED)
	IOMUX -> SECCFG.PINCM[IOMUX_PINCM57] |= (IOMUX_PINCM57_PF_GPIOB_DIO26 | IOMUX_PINCM_PC_CONNECTED);
	IOMUX -> SECCFG.PINCM[IOMUX_PINCM57] |= IOMUX_PINCM_DRV_DRVVAL1;
	//Enable GPIO ouput
	GPIOB -> DOESET31_0 |= GPIO_DOESET31_0_DIO26_SET;
	//Init the pin to off
	GPIOB -> DOUTCLR31_0 |= GPIO_DOUTCLR31_0_DIO26_CLR;
	
	
	//GREEN LED
	//Configure the IOMUX register for peripheral (GREEN LED)
	IOMUX -> SECCFG.PINCM[IOMUX_PINCM58] |= (IOMUX_PINCM58_PF_GPIOB_DIO27 | IOMUX_PINCM_PC_CONNECTED);
	IOMUX -> SECCFG.PINCM[IOMUX_PINCM58] |= IOMUX_PINCM_DRV_DRVVAL1;
	//Enable GPIO ouput
	GPIOB -> DOESET31_0 |= GPIO_DOESET31_0_DIO27_SET;
	//Init the pin to off
	GPIOB -> DOUTCLR31_0 |= GPIO_DOUTCLR31_0_DIO27_CLR;
	
	//BLUE LED
	//Configure the IOMUX register for peripheral (BLUE LED)
	IOMUX -> SECCFG.PINCM[IOMUX_PINCM50] |= (IOMUX_PINCM50_PF_GPIOB_DIO22 | IOMUX_PINCM_PC_CONNECTED);
	IOMUX -> SECCFG.PINCM[IOMUX_PINCM50] |= IOMUX_PINCM_DRV_DRVVAL1;
	//Enable GPIO ouput
	GPIOB -> DOESET31_0 |= GPIO_DOESET31_0_DIO22_SET;
	//Init the pin to off
	GPIOB -> DOUTCLR31_0 |= GPIO_DOUTCLR31_0_DIO22_CLR;
	
}
/**
 * @brief Set LED1 output state
 * @note ON, OFF, TOGGLE
*/
void LED1_set(uint16_t set_state){
	switch (set_state){
		case LED_1_OFF:
			GPIOA -> DOUTSET31_0 |= GPIO_DOUTCLR31_0_DIO0_CLR;
			break;
		case LED_1_ON:
			GPIOA -> DOUTCLR31_0 |= GPIO_DOUTSET31_0_DIO0_SET;
			break;
		case LED_1_TOG:
			GPIOA -> DOUTTGL31_0 |= GPIO_DOUTTGL31_0_DIO0_TOGGLE;
			break;
		default:
			GPIOA -> DOUTSET31_0 |= GPIO_DOUTCLR31_0_DIO0_CLR;
			//Nothing
	}
}


/**
 * @brief Set LED2 output state
 * @note RED, GREEN, BLUE, CYAN, MAGENTA, YELLOW, WHITE, OFF
*/
void LED2_set(uint16_t set_state){
	switch (set_state){
		case LED_2_OFF:
			GPIOB -> DOUTCLR31_0 |= GPIO_DOUTCLR31_0_DIO26_CLR; //R
			GPIOB -> DOUTCLR31_0 |= GPIO_DOUTCLR31_0_DIO27_CLR; //G
			GPIOB -> DOUTCLR31_0 |= GPIO_DOUTCLR31_0_DIO22_CLR; //B
			break;
		case LED_2_RED:
			GPIOB -> DOUTSET31_0 |= GPIO_DOUTSET31_0_DIO26_SET; //R
			GPIOB -> DOUTCLR31_0 |= GPIO_DOUTCLR31_0_DIO27_CLR; //G
			GPIOB -> DOUTCLR31_0 |= GPIO_DOUTCLR31_0_DIO22_CLR; //B
			break;
		case LED_2_GREEN:
			GPIOB -> DOUTCLR31_0 |= GPIO_DOUTCLR31_0_DIO26_CLR; //R
			GPIOB -> DOUTSET31_0 |= GPIO_DOUTSET31_0_DIO27_SET; //G
			GPIOB -> DOUTCLR31_0 |= GPIO_DOUTCLR31_0_DIO22_CLR; //B
			break;
		case LED_2_BLUE:
			GPIOB -> DOUTCLR31_0 |= GPIO_DOUTCLR31_0_DIO26_CLR; //R
			GPIOB -> DOUTCLR31_0 |= GPIO_DOUTCLR31_0_DIO27_CLR; //G
			GPIOB -> DOUTSET31_0 |= GPIO_DOUTSET31_0_DIO22_SET; //B
			break;
		case LED_2_CYAN:
			GPIOB -> DOUTCLR31_0 |= GPIO_DOUTCLR31_0_DIO26_CLR; //R
			GPIOB -> DOUTSET31_0 |= GPIO_DOUTSET31_0_DIO27_SET; //G
			GPIOB -> DOUTSET31_0 |= GPIO_DOUTSET31_0_DIO22_SET; //B
			break;
		case LED_2_MAGENTA:
			GPIOB -> DOUTSET31_0 |= GPIO_DOUTSET31_0_DIO26_SET; //R
			GPIOB -> DOUTCLR31_0 |= GPIO_DOUTCLR31_0_DIO27_CLR; //G
			GPIOB -> DOUTSET31_0 |= GPIO_DOUTSET31_0_DIO22_SET; //B
			break;
		case LED_2_YELLOW:
			GPIOB -> DOUTSET31_0 |= GPIO_DOUTSET31_0_DIO26_SET; //R
			GPIOB -> DOUTSET31_0 |= GPIO_DOUTSET31_0_DIO27_SET; //G
			GPIOB -> DOUTCLR31_0 |= GPIO_DOUTCLR31_0_DIO22_CLR; //B
			break;
		case LED_2_WHITE:
			GPIOB -> DOUTSET31_0 |= GPIO_DOUTSET31_0_DIO26_SET; //R
			GPIOB -> DOUTSET31_0 |= GPIO_DOUTSET31_0_DIO27_SET; //G
			GPIOB -> DOUTSET31_0 |= GPIO_DOUTSET31_0_DIO22_SET; //B
			break;

		default:
			GPIOB -> DOUTCLR31_0 |= GPIO_DOUTCLR31_0_DIO26_CLR; //R
			GPIOB -> DOUTCLR31_0 |= GPIO_DOUTCLR31_0_DIO27_CLR; //G
			GPIOB -> DOUTCLR31_0 |= GPIO_DOUTCLR31_0_DIO22_CLR; //B
	}
}

void loop_timer(void){
	long int timer = 0;
	do {
		timer++;
	} while (timer < 2000000);
}