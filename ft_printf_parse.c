/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 10:33:14 by orobert           #+#    #+#             */
/*   Updated: 2025/11/05 10:33:16 by orobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static const char	*parse_flags(const char *s, t_format *f)
{
	while (*s == '-' || *s == '0' || *s == '#' || *s == ' ' || *s == '+')
	{
		if (*s == '-')
			f->flag_minus = 1;
		else if (*s == '0')
			f->flag_zero = 1;
		else if (*s == '#')
			f->flag_hash = 1;
		else if (*s == ' ')
			f->flag_space = 1;
		else if (*s == '+')
			f->flag_plus = 1;
		s++;
	}
	return (s);
}

static const char	*parse_width(const char *s, t_format *f, va_list *params)
{
	(void)params;
	if (*s < '0' || *s > '9')
		return (s);
	f->width = 0;
	while (*s >= '0' && *s <= '9')
	{
		f->width = f->width * 10 + (*s - '0');
		s++;
	}
	return (s);
}

static const char	*parse_prec(const char *s, t_format *f, va_list *params)
{
	(void)params;
	if (*s != '.')
		return (s);
	f->isprecision = 1;
	s++;
	f->precision = 0;
	if (*s < '0' || *s > '9')
		return (s);
	while (*s >= '0' && *s <= '9')
	{
		f->precision = f->precision * 10 + (*s - '0');
		s++;
	}
	return (s);
}

const char	*pf_parse(const char *s, t_format *f, va_list *params)
{
	f->flag_minus = 0;
	f->flag_zero = 0;
	f->flag_hash = 0;
	f->flag_space = 0;
	f->flag_plus = 0;
	f->width = -1;
	f->precision = 0;
	f->isprecision = 0;
	f->conv = '\0';
	s = parse_flags(s, f);
	s = parse_width(s, f, params);
	s = parse_prec(s, f, params);
	if (*s == 'c' || *s == 's' || *s == 'p' || *s == 'd' || *s == 'i')
	{
		f->conv = *s;
		return (s + 1);
	}
	else if (*s == 'u' || *s == 'x' || *s == 'X' || *s == '%')
	{
		f->conv = *s;
		return (s + 1);
	}
	return (s);
}
