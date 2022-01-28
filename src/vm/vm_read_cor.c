/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_read_cor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liamprior <liamprior@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 16:54:54 by lprior            #+#    #+#             */
/*   Updated: 2022/01/27 12:44:57 by liamprior        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/vm.h"

/*
** Safely open the file.
*/

int		open_file(char *file_name)
{
	int		fd;

	if ((fd = open(file_name, O_RDONLY)) == -1)
	{
		ft_putstr_fd("File Error!", 2);
		exit(0);
	}
	return (fd);
}

/*
** Get the next player id.
*/

int		get_next_player(t_vm *vm)
{
	if (vm->player_count >= 4)
		return (ft_puterror(-1, "Too many players."));
	vm->curr_player += 1;
	vm->players[vm->curr_player].num = vm->curr_player + 1;
	vm->player_count += 1;
	return (1);
}

/*
** Check whether the extension is a .cor and open and load the file.
*/

int		handle_file(char *file_name, t_vm *vm)
{
	int		fd;
	int		len;
	int		valid;

	len = ft_strlen(file_name);
	while (*file_name && *(file_name + len) != '.')
		len--;
	valid = (ft_strequ((file_name + len), ".cor") == 1);
	if (valid == 1)
	{
		fd = open_file(file_name);
		if (get_next_player(vm) == -1)
			return (-1);
		if (valid == 0)
			return (-1);
		if (read_file_header(fd, &(vm->players[vm->curr_player].header)) == -1)
			return (-1);
		if (read_file_program(fd, &(vm->players[vm->curr_player])) == -1)
			return (-1);
		return (1);
	}
	return (-1);
}

/*
** Read the file header.
** 1) 4 bytes for the .cor magic number
** 2) PROG_NAME_LENGTH bytes for the program name
** 3) 4 bytes for 0 buffer
** 4) 4 bytes for program size
** 5) COMMENT_LENGTH bytes for the comment
** 6) 4 bytes for 0 buffer
*/

int		read_file_header(int fd, t_header *header)
{
	unsigned char buff[4];

	if (!(read(fd, buff, 4) == 4 &&
		ft_memcmp(buff, COREWAR_EXEC_MAGIC, 4) == 0))
		return (ft_puterror(-1, "Invalid Magic Number."));
	read(fd, header->prog_name, PROG_NAME_LENGTH);
	if (!(read(fd, buff, 4) == 4 &&
		ft_memcmp(buff, "\0\0\0\0", 4) == 0))
		return (ft_puterror(-1, "Incorrect buffer"));
	if (!(read(fd, buff, 4) == 4))
		return (ft_puterror(-1, "Incorrect program size."));
	header->prog_size = (unsigned int)buff[3] | ((unsigned int)buff[2] << 8) |
		((unsigned int)buff[1] << 16) | ((unsigned int)buff[0] << 24);
	if (header->prog_size <= 0 || header->prog_size > CHAMP_MAX_SIZE)
		return (ft_puterror(-1, "Invalid program size."));
	if (!(read(fd, header->comment, COMMENT_LENGTH) == COMMENT_LENGTH))
		return (ft_puterror(-1, "Invalid comment."));
	if (!(read(fd, buff, 4) == 4 &&
		ft_memcmp(buff, "\0\0\0\0", 4) == 0))
		return (ft_puterror(-1, "Invalid buffer between comment and program."));
	return (1);
}

/*
** Read the next PROG_SIZE bytes
*/

int		read_file_program(int fd, t_player *player)
{
	player->program = ft_memalloc(sizeof(unsigned char *) *
					player->header.prog_size);
	if (read(fd, player->program, player->header.prog_size) !=
				player->header.prog_size)
		return (ft_puterror(-1, "Invalid program."));
	return (1);
}
