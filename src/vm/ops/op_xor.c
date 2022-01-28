/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_xor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liamprior <liamprior@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 15:41:27 by lprior            #+#    #+#             */
/*   Updated: 2022/01/27 12:43:39 by liamprior        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_op_xor(t_vm *vm, t_process *process)
{
	unsigned char	hex[11];
	int				args[7];
	int				index;

	index = 0;
	args[6] = 420;
	process->carry = 0;
	get_hex(vm, process->pc, hex, 11);
	get_type(hex[1], args);
	if (args[2] == REG_CODE)
	{
		if (!check_first_arg(&(hex[2]), args, &args[3], &index))
			process->carry = 1;
		if (!check_second_arg(&(hex[index]), args, &args[4], &index))
			process->carry = 1;
		if (!convert_arg(vm, process, args[0], &(args[3])))
			process->carry = 1;
		if (!convert_arg(vm, process, args[1], &(args[4])))
			process->carry = 1;
		if (!(process->reg[(hex[index] - 1) % REG_NUMBER] = (args[3] ^ args[4])))
			process->carry = 1;
	}
	else
		process->carry = 1;
	process->pc = (process->pc + index + 1) % MEM_SIZE;
}
