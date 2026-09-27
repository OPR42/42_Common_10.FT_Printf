/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 10:33:14 by orobert           #+#    #+#             */
/*   Updated: 2025/11/05 10:33:16 by orobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	find_offset(const char *core)
{
	int	offset;

	offset = 0;
	if (core[1] == 'x' || core[1] == 'X')
		offset = 2;
	else if (core[0] == '-')
		offset = 1;
	else if (core[0] == ' ')
		while (core[offset] == ' ')
			offset++;
	return (offset);
}

size_t	pf_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*pf_strdup(const char *s)
{
	size_t	len;
	size_t	i;
	char	*dup;

	len = pf_strlen(s);
	dup = (char *)malloc(len + 1);
	i = 0;
	if (!dup)
		return (NULL);
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*pf_utoa_base(unsigned long long n, int base, int up, t_format *f)
{
	char	buf[65];
	char	*digits_u;
	char	*digits_l;
	int		i;

	digits_u = "0123456789ABCDEF";
	digits_l = "0123456789abcdef";
	i = 64;
	buf[i] = '\0';
	if (n == 0 && (f->isprecision != 1 || f->precision != 0))
		buf[--i] = '0';
	while (n > 0)
	{
		if (up == 1)
			buf[--i] = digits_u[n % base];
		else
			buf[--i] = digits_l[n % base];
		n /= base;
	}
	return (pf_strdup(&buf[i]));
}

char	*pf_pad_left_zeros(char *digits, int needed)
{
	size_t	len;
	char	*out;
	int		i;
	size_t	j;

	len = pf_strlen(digits);
	if (needed <= 0)
		return (pf_strdup(digits));
	out = (char *)malloc((size_t)needed + len + 1);
	if (!out)
		return (NULL);
	i = 0;
	while (i < needed)
	{
		out[i] = '0';
		i++;
	}
	j = 0;
	while (j < len)
	{
		out[needed + (int)j] = digits[j];
		j++;
	}
	out[needed + (int)len] = '\0';
	return (out);
}
