/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_read_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liamprior <liamprior@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 11:34:39 by lprior            #+#    #+#             */
/*   Updated: 2022/01/27 12:40:20 by liamprior        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** this function read the whole file, and stored into the tasm->file
*/

int		asm_read_file(char *file, t_asm *tasm)
{
	int		fd;
	size_t	file_size;

	if ((fd = open(file, O_RDONLY, 0)) < 0)
	{
		ft_printf("Failed on open %s", file);
		free(tasm);
		return (0);
	}
	if ((file_size = lseek(fd, 0, SEEK_END)) < 1)
	{
		ft_printf("%s is an empty file", file);
		free(tasm);
		return (0);
	}
	if (!(tasm->file = ft_memalloc(sizeof(char) * (file_size + 1))))
	{
		ft_printf("Failed on alloc the file %s", file);
		free(tasm);
		return (0);
	}
	lseek(fd, 0, SEEK_SET);
	read(fd, tasm->file, file_size);
	close(fd);
	return (1);
}
