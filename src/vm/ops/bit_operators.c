/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bit_operators.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liamprior <liamprior@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 15:34:24 by lprior            #+#    #+#             */
/*   Updated: 2022/01/27 12:42:21 by liamprior        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void    int_to_hex(int val, unsigned char *dest)
{
    dest[0] = (val & 0xff000000) >> 24;
    dest[1] = (val & 0x00ff0000) >> 16;
    dest[2] = (val & 0x0000ff00) >>  8;
    dest[3] = (val & 0x000000ff);
}

/*
**Takes in coding byte, compares bits to 3, and determines
**the types the args given are;
*/

void			get_type(unsigned char byte, int *ret)
{
	unsigned char	code;
	int				i;

	i = MAX_ARGS_NUMBER - 1;
	ft_bzero(ret, 4);
	while (i >= 0)
	{
		code = byte & 3;
		if ((code & 3) == 0)
			ret[i] = 0;
		else if ((code & 3) == REG_CODE)
			ret[i] = REG_CODE;
		else if ((code & 3) == DIR_CODE)
			ret[i] = DIR_CODE;
		else if ((code & 3) == IND_CODE)
			ret[i] = IND_CODE;
		byte >>= 2;
		i--;
	}
}

/*
**Converts 4 unsgined char bytes into signal 4 byte int though bit altercation.
*/

int				bigendianconv(unsigned char *hex, size_t size)
{
	int				res;
	size_t			i;

	res = 0;
	i = -1;
	while (++i < size)
	{
		res <<= 8 & 0xff;
		res |= (int)(hex[i]);
	}
	return (res);
}

/*
**Never tested this or really looked at it but might need it.
*/

unsigned char	*flip_endian(unsigned char *bytes, size_t size)
{
	unsigned char	tmp;
	int				i;

	i = -1;
	while ((size_t)++i < size)
	{
		tmp = bytes[i];
		bytes[i] = bytes[size];
		bytes[size] = tmp;
		size--;
	}
	return (bytes);
}
