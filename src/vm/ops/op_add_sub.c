/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_add_sub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liamprior <liamprior@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 19:18:33 by lprior            #+#    #+#             */
/*   Updated: 2022/01/27 12:42:24 by liamprior        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_op_sub(t_vm *vm, t_process *process)
{
	unsigned char	hex[5];
	int				type[4];
	int				num1;
	int				num2;

	get_hex(vm, process->pc, hex, 5);
	get_type(hex[1], type);
	process->carry = 0;
	if (type[0] == REG_CODE
		&& type[1] == REG_CODE
		&& type[2] == REG_CODE)
	{
		num1 = process->reg[hex[2] - 1];
		num2 = process->reg[hex[3] - 1];
		if (!(process->reg[(hex[4] - 1) % REG_NUMBER] = (num1 - num2) % MEM_SIZE))
			process->carry = 1;
	}
	else
		process->carry = 1;
	process->pc = (process->pc + 5) % MEM_SIZE;
}

void	ft_op_add(t_vm *vm, t_process *process)
{
	unsigned char	hex[5];
	int				type[4];
	int				num1;
	int				num2;

	get_hex(vm, process->pc, hex, 5);
	get_type(hex[1], type);
	process->carry = 0;
	if (type[0] == REG_CODE
		&& type[1] == REG_CODE
		&& type[2] == REG_CODE)
	{
		num1 = process->reg[hex[2] - 1];
		num2 = process->reg[hex[3] - 1];
		if (!(process->reg[(hex[4] - 1) % REG_NUMBER] = (num1 + num2) % MEM_SIZE))
			process->carry = 1;
	}
	else
		process->carry = 1;
	process->pc = (process->pc + 5) % MEM_SIZE;
}
