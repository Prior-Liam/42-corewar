/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfeng <zfeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 16:14:27 by zfeng             #+#    #+#             */
/*   Updated: 2018/03/13 10:15:43 by zfeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static int		skip_char(char const *s, char c, int i)
{
	while (s[i] == c)
		i++;
	return (i);
}

static int		word_count(char const *s, char c)
{
	int		wc;
	int		start;
	int		end;

	if (!*s)
		return (0);
	wc = 0;
	start = skip_char(s, c, 0);
	end = ft_strlen(s) - 1;
	while (s[end] == c)
		end--;
	if (start > end)
		return (0);
	while (start < end)
	{
		if (s[start] == c)
		{
			wc++;
			start = skip_char(s, c, start);
		}
		else
			start++;
	}
	return (wc + 1);
}

static char		**fill_array(char const *s, char c, int wc, char **res)
{
	int		wlen;
	int		i;
	int		j;

	wlen = 0;
	i = skip_char(s, c, 0);
	j = 0;
	while (j < wc)
	{
		while (s[i] && s[i] != c)
		{
			wlen++;
			i++;
		}
		if (!s[i] || s[i] == c)
		{
			res[j] = ft_strsub(s, i - wlen, wlen);
			j++;
			wlen = 0;
			i = skip_char(s, c, i);
		}
	}
	res[j] = 0;
	return (res);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**res;
	int		wc;

	if (!s)
		return (NULL);
	wc = word_count(s, c);
	res = (char **)ft_memalloc(sizeof(char *) * (wc + 1));
	if (!res)
		return (NULL);
	res = fill_array(s, c, wc, res);
	return (res);
}
