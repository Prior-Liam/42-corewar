/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_perc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfeng <zfeng@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/29 17:04:22 by zfeng             #+#    #+#             */
/*   Updated: 2018/05/01 14:46:57 by zfeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

int		handle_perc(t_fields *fds, va_list ap)
{
	int		w;

	(void)ap;
	w = fds->width;
	if (fds->minus)
	{
		ft_putchar('%');
		padding(w - 1, ' ');
		return (is_greater(w, 1) ? w : 1);
	}
	else if (fds->zero)
	{
		ft_putchar('%');
		padding(w - 1, '0');
		return (is_greater(w, 1) ? w : 1);
	}
	else
	{
		padding(w - 1, ' ');
		ft_putchar('%');
		return (is_greater(w, 1) ? w : 1);
	}
	return (0);
}
