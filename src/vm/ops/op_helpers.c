/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liamprior <liamprior@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 21:31:35 by lprior            #+#    #+#             */
/*   Updated: 2022/01/27 12:42:54 by liamprior        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**Keeps negatives in bound!
*/

int		cir_mem(int index)
{
	while (index >= MEM_SIZE)
		index = index - MEM_SIZE;
	return (index);
}

/*
**Simply checks any arg with three types, except the first.
*/

int		check_second_arg(unsigned char *hex, int *type, int *num2, int *i)
{
	if (type[1] == DIR_CODE && type[5] != 69 && (*i += 4))
		*num2 = bigendianconv(hex, 4);
	else if ((type[1] == IND_CODE || (type[5] == 69 && type[1] != REG_CODE))
				&& (*i += 2))
	{
		*num2 = (short)bigendianconv(hex, 2);
		*num2 %= (type[6] == 420) ? IDX_MOD : *num2 + 1;
	}
	else if (type[1] == REG_CODE && (*i += 1))
		*num2 = bigendianconv(hex, 1);
	else
		return (0);
	return (1);
}

/*
**Made this one specificly if the first arg has three types, it skips the
**opcode, and the coding byte.
**69 is a flag to truncate the hex
*/

int		check_first_arg(unsigned char *hex, int *type, int *num1, int *i)
{
	if (type[0] == DIR_CODE && type[5] != 69 && (*i += 6))
		*num1 = bigendianconv(hex, 4);
	else if ((type[0] == IND_CODE || (type[5] == 69 && type[0] != REG_CODE))
				&& (*i += 4))
	{
		*num1 = (short)bigendianconv(hex, 2);
		*num1 %= (type[6] == 420) ? IDX_MOD : *num1 + 1;
	}
	else if (type[0] == REG_CODE && (*i += 3))
		*num1 = bigendianconv(hex, 1);
	else
		return (0);
	return (1);
}

/*
**Grabs bytes from membox starting at pc and goes until size;
*/

void	get_hex(t_vm *vm, int pc, unsigned char *hex, size_t size)
{
	unsigned int	i;
	unsigned int	x;

	i = 1;
	x = pc + 1;
	hex[0] = vm->membox[pc].value;

	while (i < size)
	{
		hex[i++] = vm->membox[x++].value;
		if (x >= MEM_SIZE)
			x = 0;
	}
}

/*
**Convert index into a valid memory value.
*/

int		convert_arg(t_vm *vm, t_process *process, int type, int *arg)
{
	unsigned char hex[10];

	if (type == REG_CODE)
		*arg = process->reg[(*arg - 1) % REG_NUMBER];
	else if (type == IND_CODE)
	{
		get_hex(vm, cir_mem(process->pc + cir_mem(*arg)) % MEM_SIZE, hex, 4);
		*arg = bigendianconv(hex, 4);
	}
	else if (type != DIR_CODE)
		return (0);
	return (1);
}
