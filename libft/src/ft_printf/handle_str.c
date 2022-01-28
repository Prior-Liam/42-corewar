/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfeng <zfeng@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/29 14:57:24 by zfeng             #+#    #+#             */
/*   Updated: 2018/04/29 14:57:37 by zfeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

int		handle_str(t_fields *fds, va_list ap)
{
	CHAR_HANDLER_VARS;
	(void)ws;
	if (fds->modifier == 3)
		return (handle_wstr(fds, ap));
	s = va_arg(ap, char*);
	if (!s)
	{
		ft_putstr("(null)");
		return (6);
	}
	w = fds->width;
	pr = fds->prec;
	l = (pr > 0 && pr < (int)ft_strlen(s)) ? pr : (int)ft_strlen(s);
	pd = w < l ? 0 : w - l;
	if (fds->minus)
	{
		ft_putnstr(s, l);
		padding(pd, ' ');
	}
	else
	{
		padding(pd, ' ');
		ft_putnstr(s, l);
	}
	return (w > l ? w : l);
}
