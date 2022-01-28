/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_free_vm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liamprior <liamprior@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 10:19:18 by lprior            #+#    #+#             */
/*   Updated: 2022/01/27 12:43:54 by liamprior        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	vm_free_process(t_process *process)
{
	t_process	*tmp;

	while (process)
	{
		tmp = process;
		process = process->next;
		ft_memdel((void**)&tmp);
	}
}

void	vm_free_vm(t_vm *vm)
{
	if (vm->process_list)
		vm_free_process(vm->process_list);
	ft_memdel((void**)&vm);
}
