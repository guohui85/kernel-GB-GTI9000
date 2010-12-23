/* linux/arch/arm/mach-s5pv210/setup-sdhci.c
 *
 * Copyright (c) 2010 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com/
 *
 * Based on mach-s3c64xx/setup-sdhci.c
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/interrupt.h>
#include <linux/platform_device.h>
#include <linux/io.h>
#include <linux/irq.h>

#include <linux/mmc/card.h>
#include <linux/mmc/host.h>

#include <plat/regs-sdhci.h>
#include <plat/sdhci.h>

#include <plat/gpio-cfg.h>
#include <mach/gpio-bank.h>
#include <mach/regs-gpio.h>
#include <mach/gpio.h>

/* clock sources for the mmc bus clock, order as for the ctrl2[5..4] */
char *s5pv210_hsmmc_clksrcs[4] = {
	[0] = NULL,
	[1] = NULL,
	[2] = "sclk_mmc",
	[3] = NULL,
};

void s5pv210_setup_sdhci0_cfg_gpio(struct platform_device *dev, int width)
{
	unsigned int gpio;

	switch (width) {
	/* Channel 0 supports 4 and 8-bit bus width */
	case 8:
		/* Set all the necessary GPIO function and pull up/down */
		for (gpio = S5PV210_GPG1(3); gpio <= S5PV210_GPG1(6); gpio++) {
			s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(3));
			s3c_gpio_setpull(gpio, S3C_GPIO_PULL_NONE);
		}

		gpio = readl(S5PV210_GPG1DRV);
		writel(gpio | 0x2a80, S5PV210_GPG1DRV);

	case 0:
	case 1:
	case 4:
		/* Set all the necessary GPIO function and pull up/down */
		for (gpio = S5PV210_GPG0(0); gpio <= S5PV210_GPG0(6); gpio++) {
			if(gpio != S5PV210_GPG0(2)) {
				s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(2));
				s3c_gpio_setpull(gpio, S3C_GPIO_PULL_NONE);
			}
		}

//		gpio = readl(S5PV210_GPG0DRV);
		writel(0x2aaa, S5PV210_GPG0DRV);

		/* Chip detect pin Pull up -> none*/
		s3c_gpio_setpull(S5PV210_GPG0(2), S3C_GPIO_PULL_NONE);

		break;
	default:
		printk(KERN_ERR "Wrong SD/MMC bus width : %d\n", width);
	}

#if defined (CONFIG_MACH_S5PC110_ARIES)
	s3c_gpio_cfgpin(S5PV210_GPJ2(7), S3C_GPIO_OUTPUT);
	s3c_gpio_setpull(S5PV210_GPJ2(7), S3C_GPIO_PULL_NONE);
	gpio_set_value(S5PV210_GPJ2(7), 1);
#endif
}

void s5pv210_setup_sdhci1_cfg_gpio(struct platform_device *dev, int width)
{
	unsigned int gpio;

	switch (width) {
	/* Channel 1 supports 4-bit bus width */
	case 0:
	case 1:
	case 4:
		/* Set all the necessary GPIO function and pull up/down */
		for (gpio = S5PV210_GPG1(0); gpio <= S5PV210_GPG1(6); gpio++) {
			if(gpio != S5PV210_GPG1(2)) {
				s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(2));
				s3c_gpio_setpull(gpio, S3C_GPIO_PULL_NONE);
			}
		}

//		gpio = readl(S5PV210_GPG1DRV);
		writel(0x2aaa, S5PV210_GPG1DRV);

		/* Chip detect pin Pull up -> none*/
		s3c_gpio_setpull(S5PV210_GPG1(2), S3C_GPIO_PULL_NONE);

		break;
	default:
		printk(KERN_ERR "Wrong SD/MMC bus width : %d\n", width);
	}
}

void s5pv210_setup_sdhci2_cfg_gpio(struct platform_device *dev, int width)
{
	unsigned int gpio;

	switch (width) {
	/* Channel 2 supports 4 and 8-bit bus width */
	case 8:
		/* Set all the necessary GPIO function and pull up/down */
		for (gpio = S5PV210_GPG3(3); gpio <= S5PV210_GPG3(6); gpio++) {
			s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(3));
			s3c_gpio_setpull(gpio, S3C_GPIO_PULL_NONE);
		}

		gpio = readl(S5PV210_GPG3DRV);
		writel(gpio | 0x2a80, S5PV210_GPG3DRV);
	case 0:
	case 1:
	case 4:
		/* Set all the necessary GPIO function and pull up/down */
		for (gpio = S5PV210_GPG2(0); gpio <= S5PV210_GPG2(6); gpio++) {
			if(gpio != S5PV210_GPG2(2)) {
				s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(2));
				s3c_gpio_setpull(gpio, S3C_GPIO_PULL_NONE);
			}
		}

		writel(0x2aaa, S5PV210_GPG2DRV);

		/* Chip detect pin Pull up -> none*/
		s3c_gpio_setpull(S5PV210_GPG2(2), S3C_GPIO_PULL_NONE);

		break;
	default:
		printk(KERN_ERR "Wrong SD/MMC bus width : %d\n", width);
	}
}

void s5pv210_setup_sdhci3_cfg_gpio(struct platform_device *dev, int width)
{
	unsigned int gpio;

	switch (width) {
	/* Channel 3 supports 4-bit bus width */
	case 0:
	case 1:
	case 4:
		/* Set all the necessary GPIO function and pull up/down */
		for (gpio = S5PV210_GPG3(0); gpio <= S5PV210_GPG3(6); gpio++) {
			s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(2));
			s3c_gpio_setpull(gpio, S3C_GPIO_PULL_UP);
		}

		writel(0x2aaa, S5PV210_GPG3DRV);

		/* Chip detect pin Pull up*/
		s3c_gpio_setpull(S5PV210_GPG3(2), S3C_GPIO_PULL_UP);

		break;
	default:
		printk(KERN_ERR "Wrong SD/MMC bus width : %d\n", width);
	}
}

#define S3C_SDHCI_CTRL3_FCSELTX_INVERT  (0)
#define S3C_SDHCI_CTRL3_FCSELTX_BASIC   (S3C_SDHCI_CTRL3_FCSEL3 | S3C_SDHCI_CTRL3_FCSEL2)
#define S3C_SDHCI_CTRL3_FCSELRX_INVERT  (0)
#define S3C_SDHCI_CTRL3_FCSELRX_BASIC   (S3C_SDHCI_CTRL3_FCSEL1 | S3C_SDHCI_CTRL3_FCSEL0)

void s5pv210_setup_sdhci_cfg_card(struct platform_device *dev,
				    void __iomem *r,
				    struct mmc_ios *ios,
				    struct mmc_card *card)
{
	u32 ctrl2;
	u32 ctrl3;

	ctrl2 = readl(r + S3C_SDHCI_CONTROL2);
	ctrl2 &= S3C_SDHCI_CTRL2_SELBASECLK_MASK;
	ctrl2 |= (S3C64XX_SDHCI_CTRL2_ENSTAASYNCCLR |
		  S3C64XX_SDHCI_CTRL2_ENCMDCNFMSK |
		  S3C_SDHCI_CTRL2_DFCNT_NONE |
		  S3C_SDHCI_CTRL2_ENCLKOUTHOLD);

	if (ios->clock <= (400 * 1000)) {
		ctrl2 &= ~(S3C_SDHCI_CTRL2_ENFBCLKTX | S3C_SDHCI_CTRL2_ENFBCLKRX);
		ctrl3 = 0;
	} else {
		u32 range_start;
		u32 range_end;

		ctrl2 |= S3C_SDHCI_CTRL2_ENFBCLKTX | S3C_SDHCI_CTRL2_ENFBCLKRX;

		if (card->type == MMC_TYPE_MMC)  /* MMC */
			range_start = 20 * 1000 * 1000;
		else    /* SD, SDIO */
			range_start = 25 * 1000 * 1000;

		range_end = 37 * 1000 * 1000;

		if ((ios->clock > range_start) && (ios->clock < range_end))
			ctrl3 = S3C_SDHCI_CTRL3_FCSELTX_BASIC |
				S3C_SDHCI_CTRL3_FCSELRX_BASIC;
		else
			ctrl3 = S3C_SDHCI_CTRL3_FCSELTX_BASIC |
				S3C_SDHCI_CTRL3_FCSELRX_INVERT;
	}

	writel(ctrl2, r + S3C_SDHCI_CONTROL2);
	writel(ctrl3, r + S3C_SDHCI_CONTROL3);
}

void s5pv210_adjust_sdhci_cfg_card(struct s3c_sdhci_platdata *pdata, void __iomem *r, int rw)
{
	u32 ctrl2, ctrl3;

	ctrl2 = readl(r + S3C_SDHCI_CONTROL2);
	ctrl3 = readl(r + S3C_SDHCI_CONTROL3);

	if(rw == 0) {
		pdata->rx_cfg++;
		if(pdata->rx_cfg == 1) {
			ctrl2 |= S3C_SDHCI_CTRL2_ENFBCLKRX;
			ctrl3 |= S3C_SDHCI_CTRL3_FCSELRX_BASIC;
		}
		else if(pdata->rx_cfg == 2) {
			ctrl2 |= S3C_SDHCI_CTRL2_ENFBCLKRX;
			ctrl3 &= ~S3C_SDHCI_CTRL3_FCSELRX_BASIC;
		}
		else if(pdata->rx_cfg == 3) {
			ctrl2 &= ~(S3C_SDHCI_CTRL2_ENFBCLKTX | S3C_SDHCI_CTRL2_ENFBCLKRX);
			pdata->rx_cfg = 0;
		}
	}
	else if(rw == 1) {
		pdata->tx_cfg++;
		if(pdata->tx_cfg == 1) {
			if(ctrl2 & S3C_SDHCI_CTRL2_ENFBCLKRX) {
				ctrl2 |= S3C_SDHCI_CTRL2_ENFBCLKTX;
				ctrl3 |= S3C_SDHCI_CTRL3_FCSELTX_BASIC;
			}
			else
				ctrl2 &= ~S3C_SDHCI_CTRL2_ENFBCLKTX;
		}
		else if(pdata->tx_cfg == 2) {
			ctrl2 &= ~S3C_SDHCI_CTRL2_ENFBCLKTX;
			pdata->tx_cfg = 0;
		}
	}
	else {
		printk(KERN_ERR "%s, unknown value rw:%d\n", __func__, rw);
		return;
	}

	writel(ctrl2, r + S3C_SDHCI_CONTROL2);
	writel(ctrl3, r + S3C_SDHCI_CONTROL3);
}

#if defined(CONFIG_MACH_SMDKV210)
static void setup_sdhci0_gpio_wp(void)
{
	s3c_gpio_cfgpin(S5PV210_GPH0(7), S3C_GPIO_INPUT);
	s3c_gpio_setpull(S5PV210_GPH0(7), S3C_GPIO_PULL_DOWN);
}

static int sdhci0_get_ro(struct mmc_host *mmc)
{
	return !!(readl(S5PV210_GPH0DAT) & 0x80);
}
#endif

#if defined (CONFIG_MACH_S5PC110_ARIES) || defined(CONFIG_MACH_S5PC110_P1)
unsigned int universal_sdhci2_detect_ext_cd(void)
{
	unsigned int card_status = 0;

#ifdef CONFIG_MMC_DEBUG
	printk(" Universal :SD Detect function \n");
	printk("eint conf %x  eint filter conf %x",readl(S5PV210_EINT3CON),
			readl(S5PV210_EINT3FLTCON1));
	printk("eint pend %x  eint mask %x",readl(S5PC11X_EINT3PEND),
			readl(S5PC11X_EINT3MASK));
#endif
#if defined(CONFIG_MACH_S5PC110_P1)
	card_status = (readl(S5PV210_GPH3DAT)) & (1 << 4);
	printk(KERN_DEBUG " Universal : Card status  %d\n",card_status?0:1);
	return card_status ? 0 : 1;

#else
	card_status = (readl(S5PV210_GPH3DAT)) & (1 << 4);
	printk(KERN_DEBUG " Universal : Card status  %d\n",card_status?1:0);

		return card_status ? 0 : 1;
#endif
}

void universal_sdhci2_cfg_ext_cd(void)
{
	printk(" Universal :SD Detect configuration \n");

	s3c_gpio_setpull(GPIO_T_FLASH_DETECT, S3C_GPIO_PULL_NONE);
	set_irq_type(IRQ_T_FLASH_DETECT, IRQ_TYPE_EDGE_BOTH);
}
#endif // CONFIG_MACH_S5PC110_ARIES

static struct s3c_sdhci_platdata hsmmc0_platdata = {
#if defined(CONFIG_S5PV210_SD_CH0_8BIT)
	.max_width	= 8,
	.host_caps	= MMC_CAP_8_BIT_DATA,
#endif
#if defined(CONFIG_MACH_SMDKV210)
	.cfg_wp         = setup_sdhci0_gpio_wp,
	.get_ro         = sdhci0_get_ro,
#endif
};

static struct s3c_sdhci_platdata hsmmc2_platdata = {
#if defined(CONFIG_S5PV210_SD_CH2_8BIT)
	.max_width	= 8,
	.host_caps	= MMC_CAP_8_BIT_DATA,
#endif
#if defined (CONFIG_MACH_S5PC110_ARIES) || defined(CONFIG_MACH_S5PC110_P1)
	.ext_cd = IRQ_T_FLASH_DETECT,
	.cfg_ext_cd =universal_sdhci2_cfg_ext_cd,
	.detect_ext_cd = universal_sdhci2_detect_ext_cd,
#endif
};

void s3c_sdhci_set_platdata(void)
{
#if defined(CONFIG_S3C_DEV_HSMMC)
	s3c_sdhci0_set_platdata(&hsmmc0_platdata);
#endif
#if defined(CONFIG_S3C_DEV_HSMMC2)
	s3c_sdhci2_set_platdata(&hsmmc2_platdata);
#endif
};

