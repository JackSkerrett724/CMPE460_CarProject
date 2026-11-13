/**
 * ******************************************************************************
 * @file    : uart.c
 * @brief   : UART module c file
 * @details : UART initialization and interaction
 * 
 * @author 
 * @date 
 * ******************************************************************************
*/
#include <ti/devices/msp/msp.h>
#include "sysctl.h"
#include "lab2/uart.h"
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#define BAUD_RATE 9600
#define OVS 16

void UART0_init(void)
{
	
	if(!(UART0->GPRCM.PWREN & UART_PWREN_ENABLE_MASK))
	{
		UART0->GPRCM.RSTCTL |= (UART_RSTCTL_KEY_UNLOCK_W | 
														UART_RSTCTL_RESETASSERT_ASSERT | 
														UART_RSTCTL_RESETSTKYCLR_CLR);
		
		UART0->GPRCM.PWREN |=  (UART_PWREN_ENABLE_ENABLE | 
														UART_PWREN_KEY_UNLOCK_W);
	}
	
	
	//Rx IOMUX
	IOMUX->SECCFG.PINCM[IOMUX_PINCM22] |= (IOMUX_PINCM22_PF_UART0_RX | 
																				 IOMUX_PINCM_PC_CONNECTED  |
	                                       IOMUX_PINCM_INENA_ENABLE);
	
	
	//Tx IOMUX
	IOMUX->SECCFG.PINCM[IOMUX_PINCM21] |= (IOMUX_PINCM21_PF_UART0_TX | 
																				 IOMUX_PINCM_PC_CONNECTED);
	
	//Clock Select
	UART0->CLKSEL |= UART_CLKSEL_BUSCLK_SEL_ENABLE;
	
	//Clock Division
	UART0->CLKDIV |= UART_CLKDIV_RATIO_DIV_BY_1;
	
	//Disable the UART
	UART0->CTL0 |= UART_CTL0_ENABLE_DISABLE;
	
	UART0->CTL0 |= (UART_CTL0_HSE_OVS16 |	//Oversampling rate
								 UART_CTL0_FEN_ENABLE |
								 UART_CTL0_TXE_ENABLE | //TX Enable
								 UART_CTL0_RXE_ENABLE);//RX Enable
	

	

	
	//Baud Calc
	uint32_t UARTclk;
	float BRD;
	uint32_t FBRD, IBRD;

	UARTclk = SYSCTL_SYSCLK_getULPCLK();   
	
	BRD = (float)UARTclk / (OVS * BAUD_RATE);
	
	IBRD = (uint32_t)BRD;
	FBRD = (uint32_t)((BRD - IBRD) * 64);
	
	UART0->IBRD = IBRD; //Integer portion
	UART0->FBRD = FBRD; //Floating point portion

	
	//Line Control Register
	UART0->LCRH |= (UART_LCRH_WLEN_DATABIT8 | //8 Data bit
								 UART_LCRH_STP2_DISABLE  |  //1 Stop bit
								 UART_LCRH_PEN_DISABLE);    //0 parity bit
								 
								 
	//Re-Enable the UART
	UART0->CTL0 |= UART_CTL0_ENABLE_ENABLE;
	

	
	
}



void UART0_putchar(char ch)
{

	// Wait until the Tx queue is not full
	while ((UART0->STAT & UART_STAT_TXFF_MASK) == UART_STAT_TXFF_SET)
	{
	}

	
	// Transmit the character
	UART0->TXDATA = (uint32_t) ch;
}




char UART0_getchar(void)
{
    while (UART0->STAT & UART_STAT_RXFE_MASK)
    {
    }

    return (char)(UART0->RXDATA & 0xFFU);
}



void UART0_put(char *ptr_str)
{
		size_t size = strlen(ptr_str);
	  for(int i = 0; i < size; i++)
		{
			UART0_putchar(ptr_str[i]);
		}
}


bool UART0_dataAvailable(void)
{
    bool go = false;

    if (!(UART0->STAT & UART_STAT_RXFE_MASK))
        go = true;

    return go;
}









//********************************
//*******UART1********************
//********************************



void UART1_init(void)
{
    // Enable UART1 power and reset
    if (!(UART1->GPRCM.PWREN & UART_PWREN_ENABLE_MASK))
    {
        UART1->GPRCM.RSTCTL |= (UART_RSTCTL_KEY_UNLOCK_W |
                                UART_RSTCTL_RESETASSERT_ASSERT |
                                UART_RSTCTL_RESETSTKYCLR_CLR);

        UART1->GPRCM.PWREN |= (UART_PWREN_ENABLE_ENABLE |
                               UART_PWREN_KEY_UNLOCK_W);
    }


		//Rx IOMUX
		IOMUX->SECCFG.PINCM[IOMUX_PINCM20] |= (IOMUX_PINCM20_PF_UART1_RX | 
																					 IOMUX_PINCM_PC_CONNECTED  |
																					 IOMUX_PINCM_INENA_ENABLE);
		
		
		//Tx IOMUX
		IOMUX->SECCFG.PINCM[IOMUX_PINCM19] |= (IOMUX_PINCM19_PF_UART1_TX | 
																					 IOMUX_PINCM_PC_CONNECTED);

    // Clock Select
    UART1->CLKSEL |= UART_CLKSEL_BUSCLK_SEL_ENABLE;

    // Clock Division
    UART1->CLKDIV |= UART_CLKDIV_RATIO_DIV_BY_1;

    // Disable the UART
    UART1->CTL0 |= UART_CTL0_ENABLE_DISABLE;

    // UART configuration
    UART1->CTL0 |= (UART_CTL0_HSE_OVS16 |   // Oversampling rate
                    UART_CTL0_FEN_ENABLE |
                    UART_CTL0_TXE_ENABLE |   // TX Enable
                    UART_CTL0_RXE_ENABLE);   // RX Enable


    // -------------------------------------------------------------------------
    // Baud Rate Calculation
    // -------------------------------------------------------------------------
    uint32_t UARTclk;
    float BRD;
    uint32_t FBRD, IBRD;

    UARTclk = SYSCTL_SYSCLK_getULPCLK();

    BRD = (float)UARTclk / (OVS * BAUD_RATE);

    IBRD = (uint32_t)BRD;
    FBRD = (uint32_t)((BRD - IBRD) * 64);

    UART1->IBRD = IBRD;       // Integer portion
    UART1->FBRD = FBRD;       // Fractional portion


    // -------------------------------------------------------------------------
    // Line Control Register
    // -------------------------------------------------------------------------
    UART1->LCRH |= (UART_LCRH_WLEN_DATABIT8 |   // 8 Data bits
                    UART_LCRH_STP2_DISABLE |    // 1 Stop bit
                    UART_LCRH_PEN_DISABLE);      // No parity


    // Re-enable UART
    UART1->CTL0 |= UART_CTL0_ENABLE_ENABLE;
}



void UART1_putchar(char ch)
{
    // Wait until the TX FIFO is not full
    while ((UART1->STAT & UART_STAT_TXFF_MASK) == UART_STAT_TXFF_SET)
    {
    }

    // Transmit character
    UART1->TXDATA = (uint32_t)ch;
}



char UART1_getchar(void)
{
    // Wait until RX FIFO is not empty
    while (UART1->STAT & UART_STAT_RXFE_MASK)
    {
    }

    return (char)(UART1->RXDATA & 0xFFU);
}



void UART1_put(char *ptr_str)
{
    size_t size = strlen(ptr_str);

    for (int i = 0; i < size; i++)
    {
        UART1_putchar(ptr_str[i]);
    }
}


bool UART1_dataAvailable(void)
{
    bool go = false;

    if (!(UART1->STAT & UART_STAT_RXFE_MASK))
        go = true;

    return go;
}

