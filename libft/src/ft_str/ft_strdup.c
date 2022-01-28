/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfeng <zfeng@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 16:07:10 by zfeng             #+#    #+#             */
/*   Updated: 2018/03/05 20:01:37 by zfeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_strdup(const char *s1)
{
	char	*sdup;

	sdup = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!sdup)
		return (NULL);
	ft_strcpy(sdup, s1);
	return (sdup);
}
