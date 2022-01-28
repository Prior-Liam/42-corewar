/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfeng <zfeng@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/29 14:58:35 by zfeng             #+#    #+#             */
/*   Updated: 2018/04/29 16:18:02 by zfeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

void		pre_dflags(t_fields *fds, intmax_t d)
{
	char	*tmp;

	tmp = ft_itoa_base(ABS(d), 10, fds->conv);
	fds->len = ft_strlen(tmp);
	ft_strdel(&tmp);
	if (d == -2147483648)
		fds->len = 10;
	if (is_greater(fds->prec, 0))
	{
		fds->zero = 0;
		fds->prec_fill = fds->prec - fds->len;
		fds->len = is_greater(fds->len, fds->prec) ? fds->len : fds->prec;
	}
	if (d < 0)
	{
		fds->space = 0;
		fds->plus = 0;
		fds->neg = 1;
		fds->len++;
	}
	else
	{
		if (fds->plus || fds->space)
			fds->len++;
	}
}

void		d_flags(int pd, char *s, t_fields *fds)
{
	if (*s == '-')
		s++;
	if (fds->minus)
		dflag_minus(pd, s, fds);
	else if (fds->zero)
		dflag_zero(pd, s, fds);
	else if (fds->plus)
		dflag_plus(pd, s, fds);
	else if (fds->space)
		dflag_space(pd, s, fds);
	else
	{
		padding(pd, ' ');
		if (fds->neg)
			ft_putchar('-');
		padding(fds->prec_fill, '0');
		ft_putstr(s);
	}
}

intmax_t	dmodifier(t_fields *fds, va_list ap)
{
	intmax_t	d;

	d = va_arg(ap, intmax_t);
	if (fds->modifier == h && fds->conv != 'D')
		d = (short int)d;
	else if (fds->modifier == l || fds->conv == 'D')
		d = (long int)d;
	else if (fds->modifier == hh)
		d = (signed char)d;
	else if (fds->modifier == ll)
		d = (long long int)d;
	else if (fds->modifier == j)
		d = (intmax_t)d;
	else if (fds->modifier == z)
		d = (size_t)d;
	else
		d = (int)d;
	return (d);
}

int			handle_dec(t_fields *fds, va_list ap)
{
	intmax_t	d;

	NUM_HANDLER_VARS;
	d = dmodifier(fds, ap);
	if (d == 0 && fds->prec == 0)
	{
		if (is_greater(fds->width, 0))
		{
			padding(fds->width, ' ');
			return (fds->width);
		}
		return (0);
	}
	s = ft_itoa_base(ABS(d), 10, fds->conv);
	pre_dflags(fds, d);
	w = is_greater(fds->len, fds->width) ? fds->len : fds->width;
	l = fds->len;
	pd = w - l;
	d_flags(pd, s, fds);
	ft_strdel(&s);
	return (is_greater(l, w) ? l : w);
}
