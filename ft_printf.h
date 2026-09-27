/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 15:06:59 by orobert           #+#    #+#             */
/*   Updated: 2025/11/05 15:07:01 by orobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_format
{
	int		flag_minus;
	int		flag_zero;
	int		flag_hash;
	int		flag_space;
	int		flag_plus;
	int		width;
	int		precision;
	int		isprecision;
	char	conv;
}	t_format;

typedef struct s_prtnb
{
	int			dlen;
	int			clen;
	int			prec_zeros;
	int			width;
	int			zero_pad_field;
	int			prefix_len;
	int			is_signed;
	int			is_negative;
	int			i;
	int			k;
	int			w;
	int			tmp;
	const char	*sign;
	const char	*ap;
	const char	*digits;
	const char	*alt;
	char		signbuf[2];
	char		*padded;
	char		*core;
	char		prefix[6];
}	t_prtnb;

int			ft_printf(const char *format, ...);
size_t		pf_strlen(const char *s);
char		*pf_strdup(const char *s);
char		*pf_utoa_base(unsigned long long n, int base, int up, t_format *f);
char		*pf_pad_left_zeros(char *digits, int needed);
int			find_offset(const char *core);
const char	*pf_parse(const char *s, t_format *f, va_list *ap);
int			pf_write(const char *s, int len);
int			pf_write_nchar(char c, int n);
int			outpad(const char *prefix, const char *core, int width, int la_zp);
int			pf_prtnb(t_format *f, const char *dgs, int sg_ng, const char *alt);
int			pf_conv_char(t_format *f, int c);
int			pf_conv_char_zero(int width);
int			pf_conv_percent(t_format *f);
int			pf_conv_str(t_format *f, const char *s);
int			pf_conv_int(t_format *f, int n);
int			pf_conv_unsint(t_format *f, unsigned int n);
int			pf_conv_hex(t_format *f, unsigned int n);
int			pf_conv_ptr(t_format *f, void *p);

#endif
