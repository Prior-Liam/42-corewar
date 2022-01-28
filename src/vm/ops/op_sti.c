/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liamprior <liamprior@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/27 16:37:42 by lprior            #+#    #+#             */
/*   Updated: 2022/01/27 12:43:34 by liamprior        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**May have a problem... if its indir indir i do (arg1 + pc) + (arg2 + pc)...
**epitech pdf says to do it this way but 42 might be implying (arg1 + arg2) + pc
*/

void	ft_move_types(int *types)
{
	types[0] = types[1];
	types[1] = types[2];
	types[2] = 0;
}

void	ft_op_sti(t_vm *vm, t_process *process)
{
	unsigned char	hex[7];
	int				args[6];
	int				reg_num;
	int				addr;
	int				index;

	index = 1;
	args[5] = 69;
	process->carry = 1;
	get_hex(vm, process->pc, hex, 7);
	get_type(hex[1], args);
	ft_move_types(args);
	reg_num = (int)hex[2];
	check_first_arg(&(hex[3]), args, &(args[3]), &index);
	check_second_arg(&(hex[index]), args, &(args[4]), &index);
	convert_arg(vm, process, args[0], &(args[3]));
	convert_arg(vm, process, args[1], &(args[4]));
	addr = cir_mem((((args[3] + args[4])% IDX_MOD) + process->pc) % MEM_SIZE);
	int_to_hex(process->reg[(reg_num - 1) % REG_NUMBER], hex);

	int size = 0;


	while (size < 4)
		vm->membox[(addr++) % MEM_SIZE].value = hex[size++];
	process->pc = (process->pc + index) % MEM_SIZE;
}
