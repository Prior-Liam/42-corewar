/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uflags.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfeng <zfeng@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/29 21:07:58 by zfeng             #+#    #+#             */
/*   Updated: 2018/04/29 21:34:30 by zfeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

void	uflag_zero(int pd, char *s, t_fields *fds)
{
	if (fds->plus)
	{
		ft_putchar('+');
		padding(pd, '0');
		ft_putstr(s);
	}
	else if (fds->space)
	{
		ft_putchar(' ');
		padding(pd, '0');
		ft_putstr(s);
	}
	else
	{
		padding(pd, '0');
		ft_putstr(s);
	}
}

void	uflag_minus(int pd, char *s, t_fields *fds)
{
	if (fds->plus)
	{
		ft_putchar('+');
		padding(fds->prec_fill, '0');
		ft_putstr(s);
		padding(pd, ' ');
	}
	else if (fds->space)
	{
		ft_putchar(' ');
		padding(fds->prec_fill, '0');
		ft_putstr(s);
		padding(pd, ' ');
	}
	else
	{
		padding(fds->prec_fill, '0');
		ft_putstr(s);
		padding(pd, ' ');
	}
}

void	uflag_plus(int pd, char *s, t_fields *fds)
{
	padding(pd, ' ');
	ft_putchar('+');
	padding(fds->prec_fill, '0');
	ft_putstr(s);
}

void	uflag_space(int pd, char *s, t_fields *fds)
{
	padding(pd, ' ');
	ft_putchar(' ');
	padding(fds->prec_fill, '0');
	ft_putstr(s);
}
