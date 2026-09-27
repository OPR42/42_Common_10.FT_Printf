/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_convert1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 10:33:14 by orobert           #+#    #+#             */
/*   Updated: 2025/11/05 10:33:16 by orobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	pf_conv_char(t_format *f, int c)
{
	char	ch;
	char	core[2];
	int		width;
	int		w;

	width = 0;
	if (f->width >= 0)
		width = f->width;
	if (c == 0)
	{
		w = pf_conv_char_zero(width);
		return (w);
	}
	ch = (char)c;
	core[0] = ch;
	core[1] = '\0';
	if (f->flag_minus)
	{
		w = outpad("", core, width, 10);
		return (w);
	}
	w = outpad("", core, width, 0);
	return (w);
}

int	pf_conv_percent(t_format *f)
{
	char	core[2];
	int		width;
	int		zero_pad;

	core[0] = '%';
	core[1] = '\0';
	width = 0;
	if (f->width >= 0)
		width = f->width;
	zero_pad = 0;
	if (!f->flag_minus && f->flag_zero)
		zero_pad = 1;
	return (outpad("", core, width, (f->flag_minus * 10) + zero_pad));
}

static int	pf_conv_str_minus(const char *s, int outlen, int pad)
{
	int	tmp;
	int	w;

	w = 0;
	tmp = pf_write(s, outlen);
	if (tmp < 0)
		return (-1);
	w += tmp;
	tmp = pf_write_nchar(' ', pad);
	if (tmp < 0)
		return (-1);
	w += tmp;
	return (w);
}

static int	pf_conv_str_nominus(const char *s, int outlen, int pad)
{
	int	tmp;
	int	w;

	w = 0;
	tmp = pf_write_nchar(' ', pad);
	if (tmp < 0)
		return (-1);
	w += tmp;
	tmp = pf_write(s, outlen);
	if (tmp < 0)
		return (-1);
	w += tmp;
	return (w);
}

int	pf_conv_str(t_format *f, const char *s)
{
	int			outlen;
	int			width;
	int			pad;
	int			w;

	if (!s)
		s = "(null)";
	if (f->isprecision && f->precision < (int)pf_strlen(s))
		outlen = f->precision;
	else
		outlen = (int)pf_strlen(s);
	width = 0;
	if (f->width >= 0)
		width = f->width;
	pad = 0;
	if (width > outlen)
		pad = width - outlen;
	w = 0;
	if (f->flag_minus)
		w += pf_conv_str_minus(s, outlen, pad);
	else
		w += pf_conv_str_nominus(s, outlen, pad);
	return (w);
}
