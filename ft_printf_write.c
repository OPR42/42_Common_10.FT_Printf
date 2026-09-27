/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_write.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 10:33:14 by orobert           #+#    #+#             */
/*   Updated: 2025/11/05 10:33:16 by orobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int	pf_write(const char *s, int len)
{
	int	w;
	int	r;

	w = 0;
	if (len <= 0)
		return (0);
	while (w < len)
	{
		r = (int)write(1, s + w, (size_t)(len - w));
		if (r < 0)
			return (-1);
		w += r;
	}
	return (w);
}

int	pf_write_nchar(char c, int n)
{
	int	w;
	int	r;

	w = 0;
	while (n-- > 0)
	{
		r = (int)write(1, &c, 1);
		if (r < 0)
			return (-1);
		w += r;
	}
	return (w);
}

static int	outpad_l(const char *prefix, const char *core, int width)
{
	int	plen;
	int	clen;
	int	pad;
	int	tmp;
	int	w;

	plen = (int)pf_strlen(prefix);
	clen = (int)pf_strlen(core);
	pad = 0;
	if (width > (plen + clen))
		pad = width - (plen + clen);
	w = 0;
	tmp = pf_write(prefix, plen);
	if (tmp < 0)
		return (-1);
	w += tmp;
	tmp = pf_write(core, clen);
	if (tmp < 0)
		return (-1);
	w += tmp;
	tmp = pf_write_nchar(' ', pad);
	if (tmp < 0)
		return (-1);
	w += tmp;
	return (w);
}

static int	outpad_r(const char *prefix, const char *core, int width, int la_zp)
{
	int	pad;
	int	tmp;
	int	w;

	pad = 0;
	if (width > ((int)pf_strlen(prefix) + (int)pf_strlen(core)))
		pad = width - ((int)pf_strlen(prefix) + (int)pf_strlen(core));
	w = 0;
	if (la_zp % 10 == 1)
		tmp = pf_write_nchar('0', pad);
	else
		tmp = pf_write_nchar(' ', pad);
	if (tmp < 0)
		return (-1);
	w += tmp;
	tmp = pf_write(prefix, (int)pf_strlen(prefix));
	if (tmp < 0)
		return (-1);
	w += tmp;
	tmp = pf_write(core, (int)pf_strlen(core));
	if (tmp < 0)
		return (-1);
	w += tmp;
	return (w);
}

int	outpad(const char *prefix, const char *core, int width, int la_zp)
{
	int	w;
	int	tmp;
	int	offset;

	if (la_zp >= 10)
		w = outpad_l(prefix, core, width);
	else
	{
		w = 0;
		offset = 0;
		if (la_zp % 10 == 1)
			offset = find_offset(core);
		tmp = pf_write(core, offset);
		if (tmp < 0)
			return (-1);
		w += tmp;
		tmp = outpad_r(prefix, core + offset, width - offset, la_zp);
		if (tmp < 0)
			return (-1);
		w += tmp;
	}
	return (w);
}
