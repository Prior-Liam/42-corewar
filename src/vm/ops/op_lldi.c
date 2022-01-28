/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lldi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liamprior <liamprior@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 01:55:13 by lprior            #+#    #+#             */
/*   Updated: 2022/01/27 12:43:26 by liamprior        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**May have a problem... if its indir indir i do (arg1 + pc) + (arg2 + pc)...
**epitech pdf says to do it this way but 42 might be implying (arg1 + arg2) + pc
*/

void	ft_op_lldi(t_vm *vm, t_process *process)
{
	unsigned char	hex[7];
	int				args[9];

	args[5] = 69;
	process->carry = 0;
	get_hex(vm, process->pc, hex, 7);
	get_type(hex[1], args);
	if (args[2] == REG_CODE)
	{
		if (!check_first_arg(&(hex[2]), args, &(args[3]), &(args[7])))
			process->carry = 1;
		if (!check_second_arg(&(hex[args[7]]), args, &(args[4]), &args[7]))
			process->carry = 1;
		args[8] = hex[args[7]];
		convert_arg(vm, process, args[0], &(args[3]));
		convert_arg(vm, process, args[1], &(args[4]));
		get_hex(vm, cir_mem((args[3] + args[4]) % MEM_SIZE), &(hex[0]), 2);
		if (!(process->reg[(args[8] - 1) % REG_NUMBER]
			= bigendianconv(&(hex[0]), 2)))
			process->carry = 1;
	}
	else
		process->carry = 1;
	process->pc = (process->pc + args[7]) % MEM_SIZE;
}
