/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liamprior <liamprior@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 01:55:28 by lprior            #+#    #+#             */
/*   Updated: 2022/01/27 12:42:51 by liamprior        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_op_fork(t_vm *vm, t_process *process)
{
	t_process		new_process;
	unsigned char	hex[3];

	ft_memcpy(&new_process, process, sizeof(t_process));
	get_hex(vm, process->pc, hex, 3);
	new_process.pc += cir_mem(bigendianconv(&(hex[1]), 2)) % IDX_MOD;
	new_process.pc %= MEM_SIZE;
	new_process.cycle_count = 0;
	new_process.opcode = 0;
	while (vm->process_list->next)
		vm->process_list = vm->process_list->next;
	vm->process_list->next = &new_process;
	process->pc = (process->pc + 4) % MEM_SIZE;
}
