/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_check_op_name.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liamprior <liamprior@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 15:43:01 by lprior            #+#    #+#             */
/*   Updated: 2022/01/27 12:38:12 by liamprior        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		asm_check_op_name(char *str)
{
	int		i;

	i = 0;
	while (i < 16)
	{
		if (!ft_strcmp(g_op_tab[i].name, str))
			return (i + 1);
		i++;
	}
	return (0);
}
