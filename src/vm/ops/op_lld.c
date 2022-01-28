/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lld.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liamprior <liamprior@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/27 21:41:38 by lprior            #+#    #+#             */
/*   Updated: 2022/01/27 12:43:19 by liamprior        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_op_lld(t_vm *vm, t_process *process)
{
	unsigned char	hex[7];
	int				args[5];
	int				index;

	index = 0;
	get_hex(vm, process->pc, hex, 7);
	get_type(hex[1], args);
	process->carry = 0;
	if (args[1])
	{
		if (!check_first_arg(&(hex[2]), args, &(args[3]), &index))
			process->carry = 1;
		if (!convert_arg(vm, process, args[0], &(args[3])))
			process->carry = 1;
		if (!(process->reg[(hex[index] - 1) % REG_NUMBER] = args[3]))
			process->carry = 1;
	}
	else
		process->carry = 1;
	process->pc = (process->pc + index) % MEM_SIZE;
}
