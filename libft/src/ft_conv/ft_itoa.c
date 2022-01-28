/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfeng <zfeng@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 16:11:42 by zfeng             #+#    #+#             */
/*   Updated: 2018/05/03 14:13:27 by zfeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static int		digit_len(int n)
{
	int		dlen;

	if (n == -2147483648)
		return (11);
	dlen = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		dlen++;
		n = -n;
	}
	while (n > 0)
	{
		dlen++;
		n = n / 10;
	}
	return (dlen);
}

char			*ft_itoa(int n)
{
	char	*res;
	int		dlen;

	dlen = digit_len(n);
	res = ft_strnew(dlen);
	if (!res)
		return (NULL);
	if (n < 0)
		res[0] = '-';
	else
		n = -n;
	while (dlen > 0)
	{
		dlen--;
		if (res[dlen] == '-')
			return (res);
		res[dlen] = ABS(n % 10) + '0';
		n = n / 10;
	}
	return (res);
}
