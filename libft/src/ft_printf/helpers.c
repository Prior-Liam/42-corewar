/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfeng <zfeng@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/29 15:02:00 by zfeng             #+#    #+#             */
/*   Updated: 2018/04/29 16:16:17 by zfeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

int		is_flag(char c)
{
	if (c == '#' || c == '0' || c == '-' || c == ' ' || c == '+')
		return (1);
	return (0);
}

int		is_conversion(char c)
{
	if (c == 's' || c == 'S' || c == 'p' || c == 'd' || c == 'D' ||
		c == 'i' || c == 'o' || c == 'O' || c == 'u' || c == 'U' ||
		c == 'x' || c == 'X' || c == 'c' || c == 'C' || c == '%')
		return (1);
	return (0);
}

int		fn_idx(char c)
{
	int		i;

	i = 0;
	while (CONV[i])
	{
		if (CONV[i] == c)
			return (i);
		i++;
	}
	return (0);
}

int		is_greater(int a, int b)
{
	if (a > b)
		return (1);
	else
		return (0);
}

void	padding(int pd, char c)
{
	while (pd-- > 0)
		ft_putchar(c);
}
