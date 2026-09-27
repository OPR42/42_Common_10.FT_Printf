/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_convert2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 10:33:14 by orobert           #+#    #+#             */
/*   Updated: 2025/11/05 10:33:16 by orobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	pf_conv_int(t_format *f, int n)
{
	long				ln;
	unsigned long long	un;
	int					negative;
	char				*digits;
	int					w;

	ln = (long)n;
	negative = 0;
	if (ln < 0)
	{
		negative = 1;
		un = (unsigned long long)(-ln);
	}
	else
		un = (unsigned long long)ln;
	digits = pf_utoa_base(un, 10, 0, f);
	if (!digits)
		return (-1);
	w = pf_prtnb(f, digits, 10 + negative, NULL);
	free(digits);
	return (w);
}

int	pf_conv_unsint(t_format *f, unsigned int n)
{
	char	*digits;
	int		w;

	digits = pf_utoa_base((unsigned long long)n, 10, 0, f);
	if (!digits)
		return (-1);
	w = pf_prtnb(f, digits, 0, NULL);
	free(digits);
	return (w);
}

int	pf_conv_hex(t_format *f, unsigned int n)
{
	char		*digits;
	const char	*alt;
	int			w;
	int			upper;

	upper = 0;
	if (f->conv == 'X')
		upper = 1;
	digits = pf_utoa_base((unsigned long long)n, 16, upper, f);
	alt = NULL;
	if (!digits)
		return (-1);
	if (f->flag_hash && !(pf_strlen(digits) == 1 && digits[0] == '0') && n != 0)
	{
		alt = "0x";
		if (upper == 1)
			alt = "0X";
	}
	w = pf_prtnb(f, digits, 0, alt);
	free(digits);
	return (w);
}

static int	pf_conv_ptr_findpad(int width, int len)
{
	if (width > len)
		return (width - len);
	return (0);
}

int	pf_conv_ptr(t_format *f, void *p)
{
	char				*digits;
	int					w;
	int					len;
	int					width;
	int					pad;

	if (!p)
	{
		len = (int)pf_strlen("(nil)");
		width = 0;
		if (f->width >= 0)
			width = f->width;
		pad = pf_conv_ptr_findpad(width, len);
		if (f->flag_minus)
			return (pf_write("(nil)", len) + pf_write_nchar(' ', pad));
		else
			return (pf_write_nchar(' ', pad) + pf_write("(nil)", len));
	}
	digits = pf_utoa_base((unsigned long long)(unsigned long)p, 16, 0, f);
	if (!digits)
		return (-1);
	w = pf_prtnb(f, digits, 0, "0x");
	free(digits);
	return (w);
}
