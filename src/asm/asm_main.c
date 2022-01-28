/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liamprior <liamprior@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 16:04:57 by lprior            #+#    #+#             */
/*   Updated: 2022/01/27 12:39:28 by liamprior        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	asm_usage(void)
{
	ft_printf("%s\n", "Usage: ./tasm <sourcefile.s>");
}

void	asm_perror(t_asm *tasm, char *error_string)
{
	ft_printf("%s\n", error_string);
	tasm->error = 1;
	// i need to free the struct, haven't done this step
	// ft_strdel(tasm->file);
	// free(tasm);
}

/*
** only parse the last argv, if we have time then we can do one every argv
*/

int	main(int argc, char **argv)
{
	t_asm	*tasm;
	size_t	len;

	if (argc > 1)
	{
		len = ft_strlen(argv[argc - 1]);
		if ((argv[argc - 1][len - 1] == 's' || argv[argc - 1][len - 1] == 'S')
			&& argv[argc - 1][len - 2] == '.' )
		{
			if (!(tasm = ft_memalloc(sizeof(t_asm))))
			{
				ft_printf("alloc failed");
				return (-1);
			}
			tasm->error == 0 ? asm_read_file(argv[argc - 1], tasm) : 1; // read the file and parse in the buffer as tasm->file
			tasm->error == 0 ? asm_parse_file(tasm) : 1; // parse name, comment, and instruction
			//tasm->error == 0 ? asm_create_file(argv[argc - 1], tasm) : 1; // create binary code
			tasm->error == 0 ? free(tasm) : 1;

		}
		else
			ft_printf("%s is an invalid filetype", argv[argc - 1]);
	}
	else
		asm_usage();
	return (0);
}
