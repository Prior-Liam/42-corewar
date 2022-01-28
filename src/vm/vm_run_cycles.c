/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_run_cycles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liamprior <liamprior@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 11:07:40 by lprior            #+#    #+#             */
/*   Updated: 2022/01/27 12:45:03 by liamprior        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** run a process
*/

void	vm_run_process(t_process *process, t_vm *vm)
{
	process->opcode = vm->membox[process->pc].value;
	if (process->cycle_count == g_op_tab_vm[process->opcode - 1].cycles)
	{
		// printf("cycle_count = %d | pc = %d | opcode = %d\n", process->cycle_count, process->pc, process->opcode);
		g_op_tab_vm[process->opcode - 1].func(vm, process);
		process->cycle_count = 0;
	}
}

/*
** update cycle_to_die
*/

void	vm_update_ctd(t_vm *vm)
{
	vm->cycle_to_die -= CYCLE_DELTA;
	vm->total_lives = 0;
	vm->ctd_count = 0;
	vm->checks = 0;
}

/*
** run one cycle, check each condition
*/

void	vm_run_cycle(t_vm *vm)
{
	t_process	*current_process;

	if (vm->current_cycle == vm->dump_cycle)
		vm->end = 1;
	current_process = vm->process_list;
	while (vm->end != 1 && current_process != NULL)
	{
		if (vm->current_cycle >= CYCLE_TO_DIE && current_process->dead == 1)
		{
			current_process = current_process->next;
			continue ;
		}
		else if (vm->cycle_to_die <= 0)
			vm->end = 1;
		else if (vm->cycle_to_die <= vm->ctd_count || vm->checks >= MAX_CHECKS
					|| vm->total_lives >= NBR_LIVE)
		{
			if (current_process->lives == 0)
				current_process->dead = 1;
			if (vm->total_lives == 0)
				vm->end = 1;
			vm_update_ctd(vm);
		}
		else
			vm_run_process(current_process, vm);
		current_process = current_process->next;
	}
}

/*
** run cycles until all processes die
*/

void	vm_run_cycles(t_vm *vm)
{
	t_process	*process;

	while (vm->end != 1)
	{
		vm_run_cycle(vm);
		// printf("**** current_cycle = %d | cycle_to_die = %d | ctd_count = %d | checks = %d | total_lives = %d | end = %d\n", vm->current_cycle, vm->cycle_to_die, vm->ctd_count, vm->checks, vm->total_lives, vm->end);
		vm->current_cycle++;
		vm->ctd_count++;
		if (vm->total_lives >= NBR_LIVE)
			vm->checks++;
		process = vm->process_list;
		while (process)
		{
			process->cycle_count++;
			process = process->next;
		}
	}
	vm_print_result(vm);
}
