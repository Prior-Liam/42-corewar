/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liamprior <liamprior@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 11:33:13 by lprior            #+#    #+#             */
/*   Updated: 2022/01/27 12:40:14 by liamprior        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** parse 1. name, 2. comment 3. instruction
*/
void	asm_parse_file(t_asm *tasm)
{
	tasm->i = 0;
	if (tasm->file[tasm->i] && !tasm->error)
		asm_parse_name(tasm);
	if (tasm->file[tasm->i] && !tasm->error)
		asm_parse_comment(tasm);
	if (tasm->file[tasm->i] && !tasm->error)
		asm_parse_instruction(tasm);
}

/*
** parse the name in the header struct which in the op.h
*/
void	asm_parse_name(t_asm *tasm)
{
	asm_skip_routine(tasm);
	if (!ft_strncmp(tasm->file, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)))
	{
		tasm->i += ft_strlen(NAME_CMD_STRING);
		while (asm_check_space_wonl(tasm->file[tasm->i]))
			tasm->i += 1;
		if (tasm->file[tasm->i++] != '"')
			asm_perror(tasm, "Syntax error at .name"); // doesn't have '"' after .name
		else
		{
			tasm->j = 0;
			while (tasm->file[tasm->i] && tasm->file[tasm->i] != '"')
			{
				if (tasm->j < PROG_NAME_LENGTH)
					tasm->header.prog_name[tasm->j++] = tasm->file[tasm->i++];
				if (tasm->j == PROG_NAME_LENGTH && tasm->file[tasm->i + 1] != '"')
					asm_perror(tasm, "Champion name too long (Max length 128)");
			}
			if (tasm->j <= PROG_NAME_LENGTH && tasm->file[tasm->i++] == '"')
					tasm->part[0] = 1;
 		}
	}
	else
		asm_perror(tasm, "Lexical error"); // no .name when it start
}

/*
** parse the comment in the header struct which in the op.h
*/
void	asm_parse_comment(t_asm *tasm)
{
	asm_skip_routine(tasm);
	if (!ft_strncmp(tasm->file + tasm-> i, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING)))
	{
		tasm->i += ft_strlen(COMMENT_CMD_STRING);
		while (asm_check_space_wonl(tasm->file[tasm->i]))
			tasm->i += 1;
		if (tasm->file[tasm->i++] != '"')
			asm_perror(tasm, "Syntax error at .comment");
		else
		{
			tasm->j = 0;
			while (tasm->file[tasm->i] && tasm->file[tasm->i] != '"')
			{
				if (tasm->j < COMMENT_LENGTH)
					tasm->header.comment[tasm->j++] = tasm->file[tasm->i++];
				if (tasm->j == COMMENT_LENGTH && tasm->file[tasm->i + 1] != '"')
					asm_perror(tasm, "Champion comment too long (MAX len 2048)");
			}
			if (tasm->j <= COMMENT_LENGTH && tasm->file[tasm->i] == '"')
				tasm->part[1] = 1;
			tasm->i += 3;//this pushes us off of " then t0o \n then too \n then lands on the first real line
		}
	}
	else
		asm_perror(tasm, "aLexical error");
}
