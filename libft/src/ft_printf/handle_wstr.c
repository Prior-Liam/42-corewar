/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_wstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfeng <zfeng@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/29 14:57:43 by zfeng             #+#    #+#             */
/*   Updated: 2018/04/29 16:16:06 by zfeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

int		handle_wstr(t_fields *fds, va_list ap)
{
	CHAR_HANDLER_VARS;
	(void)s;
	ws = va_arg(ap, wchar_t*);
	w = fds->width;
	pr = fds->prec;
	l = (pr > 0 && pr < (int)ft_wstrlen(ws)) ? pr : (int)ft_wstrlen(ws);
	pd = w < l ? 0 : w - l;
	if (fds->minus)
	{
		ft_putnwstr(ws, l);
		padding(pd, ' ');
	}
	else
	{
		padding(pd, ' ');
		ft_putnwstr(ws, l);
	}
	return (w > l ? w : l);
}
