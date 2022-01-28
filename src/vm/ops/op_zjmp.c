/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liamprior <liamprior@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 16:18:18 by lprior            #+#    #+#             */
/*   Updated: 2022/01/27 12:43:42 by liamprior        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_op_zjmp(t_vm *vm, t_process *process)
{
	unsigned char	hex[3];
	unsigned int	address;

	get_hex(vm, process->pc, hex, 3);
	address = (process->pc + (bigendianconv(&(hex[1]), 2) % IDX_MOD));

	process->pc = address % MEM_SIZE;
}
