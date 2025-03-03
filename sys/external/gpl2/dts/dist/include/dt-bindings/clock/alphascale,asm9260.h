/*	$NetBSD: alphascale,asm9260.h,v 1.1.1.1.4.2 2017/07/18 16:08:56 snj Exp $	*/

/*
 * Copyright 2014 Oleksij Rempel <linux@rempel-privat.de>
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef _DT_BINDINGS_CLK_ASM9260_H
#define _DT_BINDINGS_CLK_ASM9260_H

/* ahb gate */
#define CLKID_AHB_ROM		0
#define CLKID_AHB_RAM		1
#define CLKID_AHB_GPIO		2
#define CLKID_AHB_MAC		3
#define CLKID_AHB_EMI		4
#define CLKID_AHB_USB0		5
#define CLKID_AHB_USB1		6
#define CLKID_AHB_DMA0		7
#define CLKID_AHB_DMA1		8
#define CLKID_AHB_UART0		9
#define CLKID_AHB_UART1		10
#define CLKID_AHB_UART2		11
#define CLKID_AHB_UART3		12
#define CLKID_AHB_UART4		13
#define CLKID_AHB_UART5		14
#define CLKID_AHB_UART6		15
#define CLKID_AHB_UART7		16
#define CLKID_AHB_UART8		17
#define CLKID_AHB_UART9		18
#define CLKID_AHB_I2S0		19
#define CLKID_AHB_I2C0		20
#define CLKID_AHB_I2C1		21
#define CLKID_AHB_SSP0		22
#define CLKID_AHB_IOCONFIG	23
#define CLKID_AHB_WDT		24
#define CLKID_AHB_CAN0		25
#define CLKID_AHB_CAN1		26
#define CLKID_AHB_MPWM		27
#define CLKID_AHB_SPI0		28
#define CLKID_AHB_SPI1		29
#define CLKID_AHB_QEI		30
#define CLKID_AHB_QUADSPI0	31
#define CLKID_AHB_CAMIF		32
#define CLKID_AHB_LCDIF		33
#define CLKID_AHB_TIMER0	34
#define CLKID_AHB_TIMER1	35
#define CLKID_AHB_TIMER2	36
#define CLKID_AHB_TIMER3	37
#define CLKID_AHB_IRQ		38
#define CLKID_AHB_RTC		39
#define CLKID_AHB_NAND		40
#define CLKID_AHB_ADC0		41
#define CLKID_AHB_LED		42
#define CLKID_AHB_DAC0		43
#define CLKID_AHB_LCD		44
#define CLKID_AHB_I2S1		45
#define CLKID_AHB_MAC1		46

/* devider */
#define CLKID_SYS_CPU		47
#define CLKID_SYS_AHB		48
#define CLKID_SYS_I2S0M		49
#define CLKID_SYS_I2S0S		50
#define CLKID_SYS_I2S1M		51
#define CLKID_SYS_I2S1S		52
#define CLKID_SYS_UART0		53
#define CLKID_SYS_UART1		54
#define CLKID_SYS_UART2		55
#define CLKID_SYS_UART3		56
#define CLKID_SYS_UART4		56
#define CLKID_SYS_UART5		57
#define CLKID_SYS_UART6		58
#define CLKID_SYS_UART7		59
#define CLKID_SYS_UART8		60
#define CLKID_SYS_UART9		61
#define CLKID_SYS_SPI0		62
#define CLKID_SYS_SPI1		63
#define CLKID_SYS_QUADSPI	64
#define CLKID_SYS_SSP0		65
#define CLKID_SYS_NAND		66
#define CLKID_SYS_TRACE		67
#define CLKID_SYS_CAMM		68
#define CLKID_SYS_WDT		69
#define CLKID_SYS_CLKOUT	70
#define CLKID_SYS_MAC		71
#define CLKID_SYS_LCD		72
#define CLKID_SYS_ADCANA	73

#define MAX_CLKS		74
#endif
