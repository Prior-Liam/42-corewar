/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_load_process_to_arena.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liamprior <liamprior@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 18:26:12 by lprior            #+#    #+#             */
/*   Updated: 2022/01/27 12:44:05 by liamprior        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Load player program to the arena.
*/

void		load_program_to_arena(t_vm *vm, t_process *p)
{
	unsigned int i;

	i = 0;
	while (i < p->player.header.prog_size)
	{
		vm->membox[p->pc + i % MEM_SIZE].value = p->player.program[i];
		vm->membox[p->pc + i % MEM_SIZE].player = p->player.num;
		i++;
	}
}

/*
** Initialize and add a new process to the process list.
*/

void		add_process(t_process **p, t_player player, int j,
						t_vm *vm)
{
	int			i;
	t_process	*new_p;

	i = 0;
	if (!(new_p = ft_memalloc(sizeof(t_process))))
		return ;
	new_p->player = player;
	new_p->dead = 0;
	new_p->carry = 0;
	new_p->lives = 0;
	new_p->opcode = new_p->player.program[0];
	new_p->cycle_count = 0;
	new_p->pc = (MEM_SIZE / (unsigned int)vm->player_count) * j;
	i = -1;
	while (++i < REG_NUMBER)
		new_p->reg[i] = 0;
	new_p->reg[0] = player.id;
	load_program_to_arena(vm, new_p);
	new_p->next = *p;
	*p = new_p;
}

/*
** Create the process list from each player program
*/

t_process	*create_process_list(t_vm *vm)
{
	int			i;
	t_process	*p;

	i = vm->player_count;
	p = NULL;
	while (--i >= 0)
		add_process(&p, vm->players[i], i, vm);
	return (p);
}
