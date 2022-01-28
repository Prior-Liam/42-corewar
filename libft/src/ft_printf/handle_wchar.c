/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_wchar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfeng <zfeng@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/29 14:03:18 by zfeng             #+#    #+#             */
/*   Updated: 2018/04/29 16:08:46 by zfeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

int		handle_wchar(t_fields *fds, va_list ap)
{
	wchar_t	c;
	int		w;
	int		pd;

	c = va_arg(ap, wchar_t);
	w = fds->width;
	pd = w - 1;
	if (fds->minus)
	{
		ft_putwchar(c);
		padding(pd, ' ');
	}
	else
	{
		padding(pd, ' ');
		ft_putwchar(c);
	}
	return (is_greater(w, sizeof(wchar_t)) ? w : sizeof(wchar_t));
}
