/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfeng <zfeng@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/29 20:30:31 by zfeng             #+#    #+#             */
/*   Updated: 2018/04/29 20:30:54 by zfeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_itoa_base(uintmax_t nb, uintmax_t base_nb, char c)
{
	char	*result;
	char	*base;
	int		i;

	i = 0;
	if (c == 'x')
		base = "0123456789abcdef";
	else if (c == 'X')
		base = "0123456789ABCDEF";
	else
		base = "0123456789";
	if (base_nb < 2 || 16 < base_nb)
		return (NULL);
	result = ft_memalloc(sizeof(char) * 35);
	while (base_nb <= nb)
	{
		result[i++] = base[nb % base_nb];
		nb = nb / base_nb;
	}
	if (base_nb > nb)
		result[i++] = base[nb];
	result[i] = '\0';
	ft_strrev(result);
	return (result);
}
