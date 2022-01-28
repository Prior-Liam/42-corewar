/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_print_result.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liamprior <liamprior@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 15:00:39 by lprior            #+#    #+#             */
/*   Updated: 2022/01/27 12:44:49 by liamprior        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	vm_print_arena(t_vm *vm)
{
	int		i;
	int		check;

	i = 0;
	check = 1;
	ft_putchar('\n');
	ft_printf("At Cycle %d:\n", vm->dump_cycle);



	int 	j = 0;
	ft_printf("         ");
	while (j < 64)
	{
		ft_printf("%02d ", j);
		j++;
	}
	ft_printf("\n");
	while (j > 0)
	{
		ft_printf("---");
		j--;
	}
	ft_printf("\n");



	while (i < MEM_SIZE)
	{
		if ((i + 1) % 64 == 0)
		{
			ft_printf("%02x ", vm->membox[i].value);
			ft_printf("\n");
			check = 1;
		}
		else if (i % 64 == 0 && check == 1)
		{
			ft_printf("0x%04x : ", i);
			check = 0;
			i--;
		}
		else
			ft_printf("%02x ", vm->membox[i].value);
		i++;
	}
	ft_putchar('\n');
}

void	vm_print_result(t_vm *vm)
{
	int		i;

	ft_printf("Introducing contestants...\n");
	i = 0;
	ft_printf("player count = %d\n", vm->player_count);
	while (i < vm->player_count)
	{
		ft_printf("%c Player %d, weighing %u bytes, \"%s\" (\"%s\") !\n",
			'*', vm->players[i].num, vm->players[i].header.prog_size, \
			vm->players[i].header.prog_name, vm->players[i].header.comment);
		i++;
	}
	if (vm->dump_cycle != -1)
	{
		vm_print_arena(vm);
		return ;
	}
	if (vm->player_count == 1)
			vm->winner = 1;
	if (vm->winner > -1)
	{
		ft_printf("Contestant %d, '%s', has won !\n",
					vm->players[vm->winner - 1].num,
					vm->players[vm->winner - 1].header.prog_name);
	}
}
