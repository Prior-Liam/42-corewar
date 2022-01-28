/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liamprior <liamprior@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 10:55:01 by lprior            #+#    #+#             */
/*   Updated: 2022/01/27 12:44:16 by liamprior        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		main(int argc, char **argv)
{
	t_vm	vm;

	vm = vm_init_vm();
	if (iter_args(argc, argv, &vm) != 1)
		return (1);
	vm.process_list = create_process_list(&vm);
	vm_run_cycles(&vm);
	return (0);
}
