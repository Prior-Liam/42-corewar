/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liamprior <liamprior@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by lprio             #+#    #+#             */
/*   Updated: 2022/01/27 12:39:55 by liamprior        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "asm.h"

t_op    g_op_tab_asm[17] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0, NULL, check_live_args},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0, NULL, check_ld_args},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0, NULL, check_st_args},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0, NULL, check_add_args},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0, NULL, check_sub_args},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0, NULL, check_and_args},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0, NULL, check_or_args},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0, NULL, check_xor_args},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1, NULL, check_zjmp_args},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1, NULL, check_ldi_args},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1, NULL, check_sti_args},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1, NULL, check_fork_args},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0, NULL, check_lld_args},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1, NULL, check_lldi_args},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1, NULL, check_lfork_args},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0, NULL, check_aff_args},
	{0, 0, {0}, 0, 0, 0, 0, 0, NULL, NULL}
};
