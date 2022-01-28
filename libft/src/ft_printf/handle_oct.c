/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_oct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfeng <zfeng@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/29 22:49:26 by zfeng             #+#    #+#             */
/*   Updated: 2018/04/29 22:49:28 by zfeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

void		pre_oflags(t_fields *fds, uintmax_t o)
{
	char	*tmp;

	tmp = ft_itoa_base(o, 8, fds->conv);
	fds->len = ft_strlen(tmp);
	ft_strdel(&tmp);
	fds->plus = 0;
	fds->space = 0;
	if (o == 0)
		fds->hash = 0;
	if (is_greater(fds->prec, 0))
	{
		fds->zero = 0;
		fds->prec_fill = fds->prec - fds->len;
		fds->len = is_greater(fds->len, fds->prec) ? fds->len : fds->prec;
	}
}

void		o_flags(int pd, char *s, t_fields *fds)
{
	if (fds->minus)
	{
		if (fds->hash)
			ft_putstr("0");
		uflag_minus(pd, s, fds);
	}
	else if (fds->zero)
	{
		if (fds->hash)
			ft_putstr("0");
		padding(pd, '0');
		ft_putstr(s);
	}
	else
	{
		padding(pd, ' ');
		if (fds->hash)
			ft_putstr("0");
		padding(fds->prec_fill, '0');
		ft_putstr(s);
	}
}

int			handle_oct(t_fields *fds, va_list ap)
{
	uintmax_t	o;

	NUM_HANDLER_VARS;
	o = umodifier(fds, ap);
	if (o == 0 && fds->prec == 0 && fds->hash == 0)
	{
		if (is_greater(fds->width, 0))
		{
			padding(fds->width, ' ');
			return (fds->width);
		}
		return (0);
	}
	s = ft_itoa_base(o, 8, fds->conv);
	pre_oflags(fds, o);
	w = is_greater(fds->len, fds->width) ? fds->len : fds->width;
	l = fds->len;
	pd = w - l;
	if (fds->hash)
		pd = pd - 1;
	o_flags(pd, s, fds);
	ft_strdel(&s);
	if (fds->hash == 1)
		l = l + 1;
	return (is_greater(l, w) ? l : w);
}
