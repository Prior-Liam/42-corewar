/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liamprior <liamprior@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 16:29:06 by lprior            #+#    #+#             */
/*   Updated: 2022/01/27 12:43:31 by liamprior        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	store_register(t_process *process, unsigned char *hex)//should store a reg into a reg
{
	hex += 2;
	process->reg[(hex[1] - 1) % REG_NUMBER]
	= process->reg[(hex[0] - 1) % REG_NUMBER];
	process->pc = (process->pc + 4) % MEM_SIZE;
}

void	store_indirect(t_vm *vm, t_process *process, unsigned char *hex)
{
	int i;
	int offset;
	int size;

	size = 0;
	i = hex[2];
	offset = bigendianconv(&(hex[3]), 2);
	offset = (offset % IDX_MOD) + process->pc;
	offset = cir_mem(offset);
	int_to_hex(process->reg[(i - 1) % REG_NUMBER], hex);
	while (size < 4)
		vm->membox[offset++ % MEM_SIZE].value = hex[size++];
	process->pc = (process->pc + 5) % MEM_SIZE;
}

void	ft_op_st(t_vm *vm, t_process *process)
{
	unsigned char	hex[5];
	int				type[4];

	get_hex(vm, process->pc, hex, 5);
	get_type(hex[1], type);
	if (type[1] == REG_CODE)
		store_register(process, hex);
	else if (type[1] == IND_CODE)
		store_indirect(vm, process, hex);
}
