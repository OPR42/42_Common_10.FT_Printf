/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_convert3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 10:33:14 by orobert           #+#    #+#             */
/*   Updated: 2025/11/05 10:33:16 by orobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	pf_prtnb_ep2b(t_format *f, t_prtnb *data)
{
	int	la_zp;

	la_zp = f->flag_minus * 10;
	data->k = 0;
	data->i = 0;
	while (data->sign[data->i])
		data->prefix[data->k++] = data->sign[data->i++];
	if (data->alt)
	{
		data->i = 0;
		while (data->alt[data->i])
			data->prefix[data->k++] = data->alt[data->i++];
	}
	data->prefix[data->k] = '\0';
	data->tmp = outpad(data->prefix, data->padded, data->width, la_zp);
}

static int	pf_prtnb_ep2a(t_format *f, t_prtnb *data)
{
	data->clen = data->prefix_len + (int)pf_strlen(data->padded);
	data->core = (char *)malloc((size_t)data->clen + 1);
	if (!data->core)
	{
		free(data->padded);
		return (-1);
	}
	data->k = 0;
	data->i = 0;
	while (data->sign[data->i])
		data->core[data->k++] = data->sign[data->i++];
	data->i = 0;
	while (data->ap[data->i])
		data->core[data->k++] = data->ap[data->i++];
	data->i = 0;
	while (data->padded[data->i])
		data->core[data->k++] = data->padded[data->i++];
	data->core[data->k] = '\0';
	data->tmp = outpad("", data->core, data->width, (f->flag_minus * 10) + 1);
	free(data->core);
	return (0);
}

static int	pf_prtnb_ep1(t_format *f, t_prtnb *data)
{
	if (data->is_signed)
	{
		if (data->is_negative % 10)
			data->sign = "-";
		else if (f->flag_plus)
			data->sign = "+";
		else if (f->flag_space)
			data->sign = " ";
	}
	if (f->isprecision && f->precision > data->dlen)
		data->prec_zeros = f->precision - data->dlen;
	data->padded = pf_pad_left_zeros((char *)data->digits, data->prec_zeros);
	if (!data->padded && (data->prec_zeros > 0))
		return (-1);
	if (!data->padded)
		data->padded = pf_strdup(data->digits);
	data->ap = "";
	if (data->alt)
		data->ap = data->alt;
	data->prefix_len = (int)pf_strlen(data->sign) + (int)pf_strlen(data->ap);
	data->core = NULL;
	return (0);
}

static void	pf_prtnb_ep0(t_format *f, t_prtnb *data)
{
	data->dlen = (int)pf_strlen(data->digits);
	data->prec_zeros = 0;
	data->width = 0;
	if (f->width >= 0)
		data->width = f->width;
	data->zero_pad_field = 0;
	if (!f->flag_minus && f->flag_zero && !f->isprecision)
		data->zero_pad_field = 1;
	data->signbuf[0] = 0;
	data->signbuf[1] = 0;
	data->sign = "";
	data->padded = NULL;
	data->w = 0;
	if (f->isprecision && f->precision == 0 && data->dlen == 1)
		if (data->digits[0] == '0')
			data->dlen = 0;
}

int	pf_prtnb(t_format *f, const char *dgs, int sg_ng, const char *alt)
{
	t_prtnb	data;
	int		r;

	data.alt = alt;
	data.digits = dgs;
	data.is_signed = sg_ng / 10;
	data.is_negative = sg_ng % 10;
	pf_prtnb_ep0(f, &data);
	r = pf_prtnb_ep1(f, &data);
	if (r < 0)
		return (-1);
	if (data.zero_pad_field)
	{
		r = pf_prtnb_ep2a(f, &data);
		if (r < 0)
			return (-1);
	}
	else
		pf_prtnb_ep2b(f, &data);
	free(data.padded);
	if (data.tmp < 0)
		return (-1);
	data.w += data.tmp;
	return (data.w);
}
