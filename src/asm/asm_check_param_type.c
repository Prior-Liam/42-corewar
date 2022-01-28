/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_check_param_type.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liamprior <liamprior@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 19:19:04 by lprior            #+#    #+#             */
/*   Updated: 2022/01/27 12:38:27 by liamprior        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** all the function below is to check whether the arg type is correct
*/

// label cannot have {, }, \, [, ],(,), :
int		asm_check_REG(char *str)
{
	int	i;

	i = 0;
	if ((str[i] == 'r' || str[i] == 'R') && str[++i])
	{
		while (str[i])
		{
			if (!ft_isdigit(str[i]))
				return (0);
			i++;
		}
	}
	else
		return (0);
	return (1);
}

int		asm_check_DIR(char *str)
{
	if (str[0] == '%' && str[1])
	{
		if (asm_check_label(str + 1, 0))
			return (1);
		else
			return (0);
	}
	else
		return (0);
}

int		asm_check_label(char *str, int colon)
{
	int i;
	int j;

	i = 0;
	j = ft_strlen(str);
	if (colon == 1)
	{
		if ((str[j - 1]) != LABEL_CHAR)
			return (0);
		while (str[i] && i < j - 1)
		{
			if (!ft_strchr(LABEL_CHARS, str[i++]))
				return(0);
		}
	}
	else
	{
		while (str[i])
		{
			if (!ft_strchr(LABEL_CHARS, str[i++]))
				return(0);
		}
	}
	return (1);
}

int		asm_check_IND(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}