/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_check_skip.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liamprior <liamprior@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 11:31:03 by lprior            #+#    #+#             */
/*   Updated: 2022/01/27 12:38:37 by liamprior        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** check if it is space, tab, and new_line, and comment char (';', '#')
*/

int		asm_check_comment(char comment)
{
	return ((comment == '#' || comment == ';') ? 1 : 0);
}

int		asm_check_space_wnl(char space)
{
	return ((space == ' ' || space == '\t' || space == '\n') ? 1 : 0);
}

int		asm_check_space_wonl(char space)
{
	return ((space == ' ' || space == '\t') ? 1 : 0);
}

void	asm_skip_space(t_asm *tasm)
{
	while (asm_check_space_wnl(tasm->file[tasm->i]))
		tasm->i += 1;
	if (asm_check_comment(tasm->file[tasm->i]))
	{
		while (tasm->file[tasm->i] != '\n')
			tasm->i += 1;
		tasm->i += 1;
	}
}

void	asm_skip_routine(t_asm *tasm)
{
	while (tasm->file[tasm->i] == ' ' || tasm->file[tasm->i] == '\t' ||
		tasm->file[tasm->i] == '\n' || tasm->file[tasm->i] == '#' ||
		tasm->file[tasm->i] == ';')
		asm_skip_space(tasm);
}
