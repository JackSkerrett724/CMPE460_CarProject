/**
 * ******************************************************************************
 * @file    : switches.c
 * @brief   : Switches module c file
 * @details : Switches initialization and interaction
 * 
 * @author Jack Skerrett
 * @date 8-31-2026 
 * ******************************************************************************
*/

#include "lab1/switches.h"
#include <ti/devices/msp/msp.h>

void S1_init(void)
{
	
	if(!(GPIOA->GPRCM.PWREN & GPIO_PWREN_ENABLE_MASK))
	{
		GPIOA->GPRCM.RSTCTL |= GPIO_RSTCTL_KEY_UNLOCK_W;
		GPIOA->GPRCM.RSTCTL |= GPIO_RSTCTL_RESETASSERT_ASSERT;
		GPIOA->GPRCM.RSTCTL |= GPIO_RSTCTL_RESETSTKYCLR_CLR;
		
		GPIOA->GPRCM.PWREN |= GPIO_PWREN_ENABLE_ENABLE;
		GPIOA->GPRCM.PWREN |= GPIO_PWREN_KEY_UNLOCK_W;
	}
	
	
  // Select PINCM40 for use as GPIO, set to high drive, and set as input
    IOMUX->SECCFG.PINCM[IOMUX_PINCM40] |= (0x80 | 0x01);
	IOMUX->SECCFG.PINCM[IOMUX_PINCM40] |= IOMUX_PINCM_DRV_DRVVAL1;
	IOMUX->SECCFG.PINCM[IOMUX_PINCM40] |= IOMUX_PINCM_INENA_ENABLE;
	
	GPIOA->DOESET31_0 |= GPIO_DOESET31_0_DIO18_SET;

  GPIOA->DOECLR31_0 |= GPIO_DOECLR31_0_DIO18_CLR;
}




void S2_init(void)
{
		if(!(GPIOB->GPRCM.PWREN & GPIO_PWREN_ENABLE_MASK))
	{
		GPIOB->GPRCM.RSTCTL |= GPIO_RSTCTL_KEY_UNLOCK_W |
													 GPIO_RSTCTL_RESETASSERT_ASSERT |
													 GPIO_RSTCTL_RESETSTKYCLR_CLR;
		
		GPIOB->GPRCM.PWREN |= GPIO_PWREN_ENABLE_ENABLE |
												  GPIO_PWREN_KEY_UNLOCK_W;
	}
	
	
	// Select PINCM49 for use as GPIO, set to high drive, set as input, and invert to be active high
  IOMUX->SECCFG.PINCM[IOMUX_PINCM49] |= (0x80 | 0x01);
	IOMUX->SECCFG.PINCM[IOMUX_PINCM49] |= IOMUX_PINCM_INV_ENABLE;
	IOMUX->SECCFG.PINCM[IOMUX_PINCM49] |= IOMUX_PINCM_DRV_DRVVAL1;
	IOMUX->SECCFG.PINCM[IOMUX_PINCM49] |= IOMUX_PINCM_INENA_ENABLE;
	
	GPIOB->DOESET31_0 |= GPIO_DOESET31_0_DIO21_SET;
	
	IOMUX->SECCFG.PINCM[IOMUX_PINCM49] |= IOMUX_PINCM_PIPU_ENABLE;


  GPIOB->DOECLR31_0 |= GPIO_DOECLR31_0_DIO21_CLR;
	
}


int S1_pressed(void)
{
	if (GPIOA->DIN31_0 & GPIO_DIN31_0_DIO18_MASK) return 1;
	else return 0;
}


int S2_pressed(void)
{
	if (GPIOB->DIN31_0 & GPIO_DIN31_0_DIO21_MASK) return 1;
	else return 0;
}


