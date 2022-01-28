/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fields.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfeng <zfeng@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/29 15:01:14 by zfeng             #+#    #+#             */
/*   Updated: 2018/04/29 16:14:23 by zfeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

void	set_flags(const char *format, t_fields *fds)
{
	int		i;

	fds->hash = 0;
	fds->zero = 0;
	fds->minus = 0;
	fds->space = 0;
	fds->plus = 0;
	i = 0;
	while (format[i] && is_flag(format[i]))
	{
		if (format[i] == '#')
			fds->hash = 1;
		else if (format[i] == '0')
			fds->zero = 1;
		else if (format[i] == '-')
			fds->minus = 1;
		else if (format[i] == ' ')
			fds->space = 1;
		else if (format[i] == '+')
			fds->plus = 1;
		i++;
	}
}

void	set_width(const char *format, va_list ap, t_fields *fds)
{
	int		i;
	int		w;

	fds->width = -1;
	i = 0;
	while (format[i] && is_flag(format[i]))
		i++;
	if ((w = ft_atoi(&format[i])) > 0)
		fds->width = w;
	else
	{
		while (!is_conversion(format[i]))
		{
			if (format[i] == '*')
				fds->width = va_arg(ap, int);
			i++;
		}
	}
}

void	set_precision(const char *format, t_fields *fds)
{
	int		i;

	fds->prec = -1;
	i = 0;
	while (format[i] && !is_conversion(format[i]))
	{
		if (format[i] == '.')
		{
			i++;
			fds->prec = ft_atoi(&format[i]);
			return ;
		}
		i++;
	}
}

void	set_modifier(const char *format, t_fields *fds)
{
	int		i;

	fds->modifier = null;
	i = 0;
	while (format[i] && !is_conversion(format[i]))
		i++;
	i--;
	if (format[i] == 'h' && format[i - 1] != 'h')
		fds->modifier = h;
	else if (format[i] == 'h' && format[i - 1] == 'h')
		fds->modifier = hh;
	else if (format[i] == 'l' && format[i - 1] != 'l')
		fds->modifier = l;
	else if (format[i] == 'l' && format[i - 1] == 'l')
		fds->modifier = ll;
	else if (format[i] == 'j')
		fds->modifier = j;
	else if (format[i] == 'z')
		fds->modifier = z;
	if (fds->modifier != null)
		return ;
}

void	set_conversion(const char *format, t_fields *fds)
{
	int		i;

	fds->conv = null;
	i = 0;
	while (format[i] && !is_conversion(format[i]))
		i++;
	if (is_conversion(format[i]))
		fds->conv = format[i];
}
