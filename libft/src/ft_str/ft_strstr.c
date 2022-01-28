/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfeng <zfeng@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 16:50:22 by zfeng             #+#    #+#             */
/*   Updated: 2018/03/07 11:55:14 by zfeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int		i;
	int		nlen;

	if (!*needle)
		return ((char *)haystack);
	i = 0;
	nlen = ft_strlen(needle);
	while (haystack[i])
	{
		if (ft_strncmp(&haystack[i], needle, nlen) == 0)
			return (&((char *)haystack)[i]);
		i++;
	}
	return (NULL);
}
