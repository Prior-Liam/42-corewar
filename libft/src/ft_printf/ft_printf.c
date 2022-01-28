/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfeng <zfeng@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 14:32:55 by zfeng             #+#    #+#             */
/*   Updated: 2018/04/29 16:25:54 by zfeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

t_handler	g_conv_table[] =
{
	{'c', &handle_char},
	{'C', &handle_wchar},
	{'s', &handle_str},
	{'S', &handle_wstr},
	{'d', &handle_dec},
	{'D', &handle_dec},
	{'i', &handle_dec},
	{'u', &handle_unsigned},
	{'U', &handle_unsigned},
	{'o', &handle_oct},
	{'O', &handle_oct},
	{'x', &handle_hex},
	{'X', &handle_hex},
	{'p', &handle_ptr},
	{'%', &handle_perc}
};

int		parse_format(const char *format, va_list ap, t_fields *fds)
{
	int			i;

	i = 0;
	while (format[i])
	{
		if (is_conversion(format[i]))
		{
			fds->prec_fill = -1;
			fds->neg = 0;
			set_flags(format, fds);
			set_width(format, ap, fds);
			set_precision(format, fds);
			set_modifier(format, fds);
			set_conversion(format, fds);
			if (fds->zero == 1 && fds->minus == 1)
				fds->zero = 0;
			if (fds->space == 1 && fds->plus == 1)
				fds->space = 0;
			return (1);
		}
		i++;
	}
	return (0);
}

int		print_content(const char *format, va_list ap)
{
	int			i;
	int			count;
	t_fields	fds;

	i = 0;
	count = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			if (parse_format(&format[++i], ap, &fds))
				count += g_conv_table[fn_idx(fds.conv)].func(&fds, ap);
			while (format[i] && !is_conversion(format[i]))
				i++;
		}
		else
		{
			ft_putchar(format[i]);
			count++;
		}
		i++;
	}
	return (count);
}

int		ft_printf(const char *format, ...)
{
	va_list		list;
	int			result;
	t_fields	fields;

	va_start(list, format);
	parse_format(format, list, &fields);
	result = print_content(format, list);
	va_end(list);
	return (result);
}
