/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfeng <zfeng@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/29 14:02:52 by zfeng             #+#    #+#             */
/*   Updated: 2018/04/29 14:56:57 by zfeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

int		handle_char(t_fields *fds, va_list ap)
{
	char	c;
	int		w;
	int		pd;

	if (fds->modifier == l)
		return (handle_wchar(fds, ap));
	c = va_arg(ap, int);
	w = fds->width;
	pd = w - 1;
	if (fds->minus)
	{
		ft_putchar(c);
		padding(pd, ' ');
	}
	else
	{
		padding(pd, ' ');
		ft_putchar(c);
	}
	return (is_greater(w, 1) ? w : 1);
}
