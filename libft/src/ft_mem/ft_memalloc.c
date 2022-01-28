/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfeng <zfeng@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 10:04:30 by zfeng             #+#    #+#             */
/*   Updated: 2018/03/06 11:04:20 by zfeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	*ft_memalloc(size_t size)
{
	void	*rtn;

	rtn = (void *)malloc(size);
	if (!rtn)
		return (NULL);
	ft_bzero(rtn, size);
	return (rtn);
}
