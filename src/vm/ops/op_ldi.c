/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ldi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liamprior <liamprior@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 18:32:52 by lprior            #+#    #+#             */
/*   Updated: 2022/01/27 12:43:00 by liamprior        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**args[7] is holding the index of hex.
*/

void	ft_op_ldi(t_vm *vm, t_process *process)
{
	unsigned char	hex[7];
	int				args[9];//index 7 is holding the index of hex. args[8] is holding the the register number

	args[5] = 69;
	args[6] = 420;
	process->carry = 0;
	get_hex(vm, process->pc, hex, 7);
	get_type(hex[1], args);
	if (args[2] == REG_CODE)
	{
		if (!check_first_arg(&(hex[2]), args, &(args[3]), &(args[7])))
			process->carry = 1;
		if (!check_second_arg(&(hex[args[7]]), args, &(args[4]), &(args[7])))
			process->carry = 1;
		args[8] = hex[args[7]];
		convert_arg(vm, process, args[0], &(args[3]));
		convert_arg(vm, process, args[1], &(args[4]));
		get_hex(vm, cir_mem(cir_mem(args[3] + args[4]) % IDX_MOD + process->pc), &(hex[0]), 4);
		if (!(process->reg[(args[8] - 1) % REG_NUMBER] = bigendianconv(hex, 4)))
			process->carry = 1;
		process->reg[(args[8] - 1)] = process->reg[(args[8] - 1)];
	}
	else
		process->carry = 1;
	process->pc = (process->pc + args[7] + 1) % MEM_SIZE;
}
