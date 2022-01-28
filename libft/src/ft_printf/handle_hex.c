/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfeng <zfeng@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/29 23:09:08 by zfeng             #+#    #+#             */
/*   Updated: 2018/04/29 23:09:10 by zfeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

void		pre_xflags(t_fields *fds, uintmax_t x)
{
	char	*tmp;

	tmp = ft_itoa_base(x, 16, fds->conv);
	fds->len = ft_strlen(tmp);
	ft_strdel(&tmp);
	fds->plus = 0;
	fds->space = 0;
	if (x == 0)
		fds->hash = 0;
	if (is_greater(fds->prec, 0))
	{
		fds->zero = 0;
		fds->prec_fill = fds->prec - fds->len;
		fds->len = is_greater(fds->len, fds->prec) ? fds->len : fds->prec;
	}
}

void		print_sharp(t_fields *fds)
{
	ft_putchar('0');
	ft_putchar(fds->conv);
}

void		x_flags(int pd, char *s, t_fields *fds)
{
	if (fds->minus)
	{
		if (fds->hash)
			print_sharp(fds);
		uflag_minus(pd, s, fds);
	}
	else if (fds->zero)
	{
		if (fds->hash)
			print_sharp(fds);
		padding(pd, '0');
		ft_putstr(s);
	}
	else
	{
		padding(pd, ' ');
		if (fds->hash)
			print_sharp(fds);
		padding(fds->prec_fill, '0');
		ft_putstr(s);
	}
}

int			handle_hex(t_fields *fds, va_list ap)
{
	uintmax_t	x;

	NUM_HANDLER_VARS;
	x = umodifier(fds, ap);
	if (x == 0 && fds->prec == 0)
	{
		if (is_greater(fds->width, 0))
		{
			padding(fds->width, ' ');
			return (fds->width);
		}
		return (0);
	}
	s = ft_itoa_base(x, 16, fds->conv);
	pre_xflags(fds, x);
	w = is_greater(fds->len, fds->width) ? fds->len : fds->width;
	l = fds->len;
	pd = w - l;
	if (fds->hash)
		pd = pd - 2;
	x_flags(pd, s, fds);
	ft_strdel(&s);
	if (fds->hash)
		l = l + 2;
	return (is_greater(l, w) ? l : w);
}
