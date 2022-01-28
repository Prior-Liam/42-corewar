/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfeng <zfeng@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 11:44:52 by zfeng             #+#    #+#             */
/*   Updated: 2018/03/07 14:20:38 by zfeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_strtrim(char const *s)
{
	char	*trim;
	int		start;
	int		end;
	int		i;

	if (!s)
		return (NULL);
	start = 0;
	end = ft_strlen(s) - 1;
	while (ft_isspace(s[start]))
		start++;
	while (ft_isspace(s[end]))
		end--;
	if (start > end)
		return (ft_strnew(0));
	trim = ft_strnew(end - start + 1);
	if (!trim)
		return (NULL);
	i = start;
	while (i <= end)
	{
		trim[i - start] = s[i];
		i++;
	}
	return (trim);
}
