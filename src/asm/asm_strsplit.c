/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_strsplit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liamprior <liamprior@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/27 17:53:23 by lprior            #+#    #+#             */
/*   Updated: 2022/01/27 12:40:28 by liamprior        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** you can strsplit with multiple char
** asm_strsplit(file, " \t\n,")
*/

int		is_delim(char c, char *delims)
{
	while (*delims && c)
	{
		if (c == *delims)
			return (1);
		++delims;
	}
	return (0);
}

int		asm_count_words(char const *str, char *delims)
{
	int	count;

	count = 0;
	while (*str != '\0')
	{
		while (*str && is_delim(*str, delims))
			str++;
		if (*str && !is_delim(*str, delims))
		{
			count++;
			while (*str && !is_delim(*str, delims))
				str++;
		}
	}
	return (count);
}

char	*asm_malloc_word(char const *str, char *delims)
{
	char	*word;
	int		i;

	i = 0;
	while (str[i] && !is_delim(str[i], delims))
		i++;
	word = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (str[i] && !is_delim(str[i], delims))
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**asm_strsplit(char const *s, char *delims)
{
	int		words;
	char	**tab;
	int		i;

	if (!s)
		return (NULL);
	words = asm_count_words(s, delims);
	tab = (char **)malloc(sizeof(char*) * (words + 1));
	i = 0;
	while (*s)
	{
		while (*s && is_delim(*s, delims))
			s++;
		if (*s && !is_delim(*s, delims))
		{
			tab[i] = asm_malloc_word(s, delims);
			i++;
			while (*s && !is_delim(*s, delims))
				s++;
		}
	}
	tab[i] = 0;
	return (tab);
}
