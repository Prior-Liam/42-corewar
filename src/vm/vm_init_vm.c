/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_init_vm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liamprior <liamprior@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 10:32:20 by lprior            #+#    #+#             */
/*   Updated: 2022/01/27 12:44:00 by liamprior        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	init_membox(t_vm *vm)
{
	int		i;

	i = 0;
	while (i < MEM_SIZE)
	{
		vm->membox[i].player = 0;
		vm->membox[i].value = 0;
		i++;
	}
}

void	init_players(t_vm *vm)
{
	int		i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		vm->players[i].header.magic = 0;
		vm->players[i].header.prog_size = 0;
		vm->players[i].id = P1_ID - i;
		i++;
	}
}

t_vm	vm_init_vm(void)
{
	t_vm	vm;

	vm.curr_player = -1;
	vm.player_count = 0;
	vm.winner = -1;
	vm.end = 0;
	vm.dump_cycle = -1;
	vm.current_cycle = 0;
	vm.cycle_to_die = CYCLE_TO_DIE;
	vm.ctd_count = 0;
	vm.total_lives = 0;
	vm.checks = 0;
	vm.process_list = NULL;
	init_membox(&vm);
	init_players(&vm);
	return (vm);
}
