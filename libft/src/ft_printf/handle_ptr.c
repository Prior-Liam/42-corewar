/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ptr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfeng <zfeng@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/29 22:16:54 by zfeng             #+#    #+#             */
/*   Updated: 2018/04/29 22:17:11 by zfeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

void		pre_pflags(t_fields *fds, uintmax_t p)
{
	char	*tmp;

	tmp = ft_itoa_base(p, 16, 'x');
	fds->len = ft_strlen(tmp);
	ft_strdel(&tmp);
	fds->plus = 0;
	fds->space = 0;
	fds->zero = 0;
}

void		p_flags(int pd, char *s, t_fields *fds)
{
	if (fds->minus)
	{
		ft_putstr("0x");
		uflag_minus(pd, s, fds);
	}
	else
	{
		padding(pd, ' ');
		ft_putstr("0x");
		ft_putstr(s);
	}
}

int			handle_ptr(t_fields *fds, va_list ap)
{
	uintmax_t	p;

	NUM_HANDLER_VARS;
	p = (uintmax_t)va_arg(ap, void*);
	s = ft_itoa_base(p, 16, 'x');
	pre_pflags(fds, p);
	w = is_greater(fds->len, fds->width) ? fds->len : fds->width;
	l = fds->len;
	pd = w - l;
	p_flags(pd, s, fds);
	ft_strdel(&s);
	return (is_greater(l + 2, w) ? l + 2 : w);
}
