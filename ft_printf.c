/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 10:33:14 by orobert           #+#    #+#             */
/*   Updated: 2025/11/05 10:33:16 by orobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	dispatch(t_format *f, va_list *params, int *total)
{
	int	w;

	if (f->conv == 'c')
		w = pf_conv_char(f, va_arg(*params, int));
	else if (f->conv == 's')
		w = pf_conv_str(f, va_arg(*params, const char *));
	else if (f->conv == 'p')
		w = pf_conv_ptr(f, va_arg(*params, void *));
	else if (f->conv == 'd' || f->conv == 'i')
		w = pf_conv_int(f, va_arg(*params, int));
	else if (f->conv == 'u')
		w = pf_conv_unsint(f, va_arg(*params, unsigned int));
	else if (f->conv == 'x' || f->conv == 'X')
		w = pf_conv_hex(f, va_arg(*params, unsigned int));
	else if (f->conv == '%')
		w = pf_conv_percent(f);
	else
		return (-1);
	*total = *total + w;
	return (0);
}

static int	justtext(const char *format, int *total)
{
	if (pf_write(format, 1) < 0)
		return (-1);
	*total = *total + 1;
	return (0);
}

static int	loop(const char *format, t_format *f, va_list *params, int *total)
{
	while (*format)
	{
		if (*format == '%')
		{
			format = pf_parse(format + 1, f, params);
			if (!f->conv)
			{
				if (pf_write("%", 1) < 0)
					return (-1);
				*total = *total + 1;
				continue ;
			}
			if (dispatch(f, params, total) < 0)
				return (-1);
		}
		else
		{
			if (justtext(format, total) < 0)
				return (-1);
			format++;
		}
	}
	return (*total);
}

int	ft_printf(const char *format, ...)
{
	va_list		params;
	t_format	f;
	int			total;

	if (!format)
		return (-1);
	va_start(params, format);
	total = 0;
	total = loop(format, &f, &params, &total);
	va_end(params);
	if (total < 0)
		return (-1);
	return (total);
}
