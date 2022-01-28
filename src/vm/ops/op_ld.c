/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liamprior <liamprior@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 11:51:35 by lprior            #+#    #+#             */
/*   Updated: 2022/01/27 12:42:58 by liamprior        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**[1]:If the coding byte's bits show the argument is direct,
**    then direct value of
**   :it is stored in the registery given;
**[2]:If the coding byte's bits show the argument is indirect, then the arg
**   :value is interpreted as a memory address (PC+(arg%512));
*/

void	load_indir(t_vm *vm, t_process *process, unsigned char *hex)
{
	int				i;
	int				offset;
	unsigned char	value[2];

	offset = 0;
	i = hex[4];
	hex += 2;
	offset = bigendianconv(hex, 2);
	offset += ((cir_mem(offset) % IDX_MOD) + process->pc) % MEM_SIZE;
	get_hex(vm, offset, value, 2);
	if (!(process->reg[(i - 1) % REG_NUMBER] = bigendianconv(value, 4)))
		process->carry = 1;
	process->pc = (process->pc + 5) % MEM_SIZE;
}

void	load_dir(t_process *process, unsigned char *hex)
{
	int				i;

	i = hex[6];
	hex += 2;
	if (!(process->reg[(i - 1) % REG_NUMBER] = bigendianconv(hex, 4)))
		process->carry = 1;
	process->pc = (process->pc + 7) % MEM_SIZE;
}

/*
**May need to be more carful when deciding dir or in dir for carry. Below.
*/

void	ft_op_ld(t_vm *vm, t_process *process)
{
	unsigned char	hex[7];
	int				type[4];

	process->carry = 0;
	get_hex(vm, process->pc, hex, 7);
	get_type(hex[1], type);
	if (type[0] == DIR_CODE)
		load_dir(process, hex);
	else if (type[0] == IND_CODE)
		load_indir(vm, process, hex);
	else if (type[0] == REG_SIZE)
		process->carry = 1;
}
