/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfeng <zfeng@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 14:37:24 by zfeng             #+#    #+#             */
/*   Updated: 2018/04/22 14:39:20 by zfeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft.h"

# define ABS(x) ((x)<0 ? -(x) : (x))
# define CONV "cCsSdDiuUoOxXp%"
# define CHAR_HANDLER_VARS char *s; wchar_t *ws; int w; int l; int pd; int pr;
# define NUM_HANDLER_VARS char *s; int w; int l; int pd;

typedef struct						s_fields
{
	int								hash;
	int								zero;
	int								minus;
	int								space;
	int								plus;
	unsigned int					width;
	unsigned int					prec;
	int								prec_fill;
	enum {null, h, hh, l, ll, j, z} modifier;
	char							conv;
	int								len;
	int								neg;
}									t_fields;

typedef	struct						s_handler
{
	char							name;
	int								(*func)(t_fields *fields, va_list ap);
}									t_handler;

int									is_flag(char c);
int									is_conversion(char c);
int									fn_idx(char c);
int									is_greater(int a, int b);
void								padding(int pd, char c);

void								set_flags(const char *format,
												t_fields *fds);
void								set_width(const char *format, va_list ap,
												t_fields *fds);
void								set_precision(const char *format,
													t_fields *fds);
void								set_modifier(const char *format,
													t_fields *fds);
void								set_conversion(const char *format,
													t_fields *fds);

void								dflag_zero(int pd, char *s, t_fields *fds);
void								dflag_minus(int pd, char *s, t_fields *fds);
void								dflag_plus(int pd, char *s, t_fields *fds);
void								dflag_space(int pd, char *s, t_fields *fds);
intmax_t							dmodifier(t_fields *fds, va_list ap);

void								uflag_zero(int pd, char *s, t_fields *fds);
void								uflag_minus(int pd, char *s, t_fields *fds);
void								uflag_plus(int pd, char *s, t_fields *fds);
void								uflag_space(int pd, char *s, t_fields *fds);
uintmax_t							umodifier(t_fields *fds, va_list ap);

int									handle_char(t_fields *fds, va_list ap);
int									handle_wchar(t_fields *fds, va_list ap);
int									handle_str(t_fields *fds, va_list ap);
int									handle_wstr(t_fields *fds, va_list ap);
int									handle_dec(t_fields *fds, va_list ap);
int									handle_int(t_fields *fds, va_list ap);
int									handle_unsigned(t_fields *fds, va_list ap);
int									handle_oct(t_fields *fds, va_list ap);
int									handle_hex(t_fields *fds, va_list ap);
int									handle_ptr(t_fields *fds, va_list ap);
int									handle_perc(t_fields *fds, va_list ap);

int									parse_format(const char *format, va_list ap,
													t_fields *fds);
int									print_content(const char *format,
													va_list ap);
int									ft_printf(const char *restrict format, ...);

#endif
