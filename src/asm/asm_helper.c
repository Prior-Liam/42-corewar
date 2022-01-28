/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liamprior <liamprior@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 21:30:41 by lprior            #+#    #+#             */
/*   Updated: 2022/01/27 12:38:44 by liamprior        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/* this is the idea to check if the argument is the right type, use
** if (g_op_tab[i].params_type[0] & T_DIR (current arg))
** 		this is the right T_DIR
** else
** 		this is wrong format, perror("wrong instruction argument"), free()
*/
/*
T_REG	1 =  01
T_DIR	2 =  10
T_IND	4 = 101

T_DIR | T_IND = 6			110		&
T_IND | T_REG = 5			101		&
T_REG | T_DIR | T_IND = 7	111		&
T_DIR | T_REG = 3			011		^

ld {T_DIR | T_IND, T_REG} params_type[0] = 6 params_type[1] = 1

ld T_DIR, T_REG

if (T_DIR & params_type[0])
	//correct format
if (T_REG & params_type[0])
	//wrong format

*/

int		ft_strlen_til(char *str, char c)
{
		int	i;

		i = 0;
		while (str[i] && str[i] != c)
			i++;
		return (i);
}

int		asm_get_nb_array(char **instruction)
{
	int	i;

	i = 0;
	while (instruction[i])
		i++;
	return (i);
}

int		get_line_len(char **line)
{
	int len;

	len = 0;
	if (!line)
		return (0);
	while (line[len])
		len++;
	return (len + 1);
}

int		ft_check_char_til(char *str, char c, int i)
{
	int	j;

	j = 0;
	while (str[j] && j < i)
	{
		if (str[j] == c)
			return (1);
		j++;
	}
	return (0);
}
