/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liamprior <liamprior@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 18:15:06 by lprior            #+#    #+#             */
/*   Updated: 2022/01/27 12:42:34 by liamprior        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_op_aff(t_vm *vm, t_process *process)
{
	unsigned char	hex[3];
	int				type[6];

	get_hex(vm, process->pc, hex, 3);
	get_type(hex[1], type);
	process->carry = 0;
	if (type[0] == DIR_CODE || type[0] == IND_CODE)
		process->carry = 1;
	else if (type[0] == REG_CODE)
	{
		check_first_arg(&(hex[2]), &(type[3]), &(type[4]), &(type[5]));
		ft_printf("%C", type[3] % 256);
	}
}
