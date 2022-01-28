/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liamprior <liamprior@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 16:12:05 by lprior            #+#    #+#             */
/*   Updated: 2022/01/27 12:43:16 by liamprior        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_op_live(t_vm *vm, t_process *process)
{
	int	pnum;

	pnum = process->player.num;
	process->lives++;
	vm->total_lives++;
	vm->winner = pnum;
	process->pc = (process->pc + 5) % MEM_SIZE;
}
