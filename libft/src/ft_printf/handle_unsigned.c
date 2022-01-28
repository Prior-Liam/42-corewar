/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_unsigned.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfeng <zfeng@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/29 20:26:19 by zfeng             #+#    #+#             */
/*   Updated: 2018/04/29 20:26:35 by zfeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

void		pre_uflags(t_fields *fds, uintmax_t u)
{
	char	*tmp;

	tmp = ft_itoa_base(u, 10, fds->conv);
	fds->len = ft_strlen(tmp);
	ft_strdel(&tmp);
	fds->plus = 0;
	fds->space = 0;
	if (is_greater(fds->prec, 0))
	{
		fds->zero = 0;
		fds->prec_fill = fds->prec - fds->len;
		fds->len = is_greater(fds->len, fds->prec) ? fds->len : fds->prec;
	}
}

void		u_flags(int pd, char *s, t_fields *fds)
{
	if (fds->minus)
		uflag_minus(pd, s, fds);
	else if (fds->zero)
		uflag_zero(pd, s, fds);
	else if (fds->plus)
		uflag_plus(pd, s, fds);
	else if (fds->space)
		uflag_space(pd, s, fds);
	else
	{
		padding(pd, ' ');
		padding(fds->prec_fill, '0');
		ft_putstr(s);
	}
}

uintmax_t	umodifier(t_fields *fds, va_list ap)
{
	uintmax_t	u;

	u = va_arg(ap, uintmax_t);
	if (fds->modifier == h && fds->conv != 'U' && fds->conv != 'O')
		u = (unsigned short int)u;
	else if (fds->modifier == l || fds->conv == 'U' || fds->conv == 'O')
		u = (unsigned long int)u;
	else if (fds->modifier == hh)
		u = (unsigned char)u;
	else if (fds->modifier == ll)
		u = (unsigned long long int)u;
	else if (fds->modifier == j)
		u = (uintmax_t)u;
	else if (fds->modifier == z)
		u = (size_t)u;
	else
		u = (unsigned int)u;
	return (u);
}

int			handle_unsigned(t_fields *fds, va_list ap)
{
	uintmax_t	u;

	NUM_HANDLER_VARS;
	u = umodifier(fds, ap);
	s = ft_itoa_base(u, 10, fds->conv);
	pre_uflags(fds, u);
	w = is_greater(fds->len, fds->width) ? fds->len : fds->width;
	l = fds->len;
	pd = w - l;
	u_flags(pd, s, fds);
	ft_strdel(&s);
	return (is_greater(l, w) ? l : w);
}
