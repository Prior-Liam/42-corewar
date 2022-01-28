/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_check_op_args.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liamprior <liamprior@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 00:39:38 by lprior            #+#    #+#             */
/*   Updated: 2022/01/27 12:39:02 by liamprior        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int    check_live_args(char **op)
{
    if (asm_get_nb_array(op) != 2)
        return (0);
    if (asm_identify_arg_type(op[1]) != T_DIR)
        return (0);
    return (1);
}

int     check_ld_args(char **op)
{
    if (asm_get_nb_array(op) != 3)
        return (0);
    if (asm_identify_arg_type(op[1]) != T_DIR &&
        asm_identify_arg_type(op[1]) != T_IND)
        return (0);
    if (asm_identify_arg_type(op[2]) != T_REG)
        return (0);
    return (1);
}

int     check_st_args(char **op)
{
    if (asm_get_nb_array(op) != 3)
        return (0);
    if (asm_identify_arg_type(op[1]) != T_REG)
        return (0);
    if (asm_identify_arg_type(op[2]) != T_REG &&
        asm_identify_arg_type(op[2]) != T_IND)
        return (0);
    return (1);
}

int     check_add_args(char **op)
{
    if (asm_get_nb_array(op) != 4)
        return (0);
    if (asm_identify_arg_type(op[1]) != T_REG)
        return (0);
    if (asm_identify_arg_type(op[2]) != T_REG)
        return (0);
    if (asm_identify_arg_type(op[3]) != T_REG)
        return (0);
    return (1);
}

int     check_sub_args(char **op)
{
    if (asm_get_nb_array(op) != 4)
        return (0);
    if (asm_identify_arg_type(op[1]) != T_REG)
        return (0);
    if (asm_identify_arg_type(op[2]) != T_REG)
        return (0);
    if (asm_identify_arg_type(op[3]) != T_REG)
        return (0);
    return (1);
}

int     check_and_args(char **op)
{
    if (asm_get_nb_array(op) != 4)
        return (0);
    if (asm_identify_arg_type(op[1]) != T_REG &&
        asm_identify_arg_type(op[1]) != T_IND &&
        asm_identify_arg_type(op[1]) != T_DIR)
        return (0);
    if (asm_identify_arg_type(op[2]) != T_REG &&
        asm_identify_arg_type(op[2]) != T_IND &&
        asm_identify_arg_type(op[2]) != T_DIR)
        return (0);
    if (asm_identify_arg_type(op[3]) != T_REG)
        return (0);
    return (1);
}

int     check_or_args(char **op)
{
    if (asm_get_nb_array(op) != 4)
        return (0);
    if (asm_identify_arg_type(op[1]) != T_REG &&
        asm_identify_arg_type(op[1]) != T_IND &&
        asm_identify_arg_type(op[1]) != T_DIR)
        return (0);
    if (asm_identify_arg_type(op[2]) != T_REG &&
        asm_identify_arg_type(op[2]) != T_IND &&
        asm_identify_arg_type(op[2]) != T_DIR)
        return (0);
    if (asm_identify_arg_type(op[3]) != T_REG)
        return (0);
    return (1);
}

int     check_xor_args(char **op)
{
    if (asm_get_nb_array(op) != 4)
        return (0);
    if (asm_identify_arg_type(op[1]) != T_REG &&
        asm_identify_arg_type(op[1]) != T_IND &&
        asm_identify_arg_type(op[1]) != T_DIR)
        return (0);
    if (asm_identify_arg_type(op[2]) != T_REG &&
        asm_identify_arg_type(op[2]) != T_IND &&
        asm_identify_arg_type(op[2]) != T_DIR)
        return (0);
    if (asm_identify_arg_type(op[3]) != T_REG)
        return (0);
    return (1);
}

int    check_zjmp_args(char **op)
{
    if (asm_get_nb_array(op) != 2)
        return (0);
    if (asm_identify_arg_type(op[1]) != T_DIR)
        return (0);
    return (1);
}

int     check_ldi_args(char **op)
{
    if (asm_get_nb_array(op) != 4)
        return (0);
    if (asm_identify_arg_type(op[1]) != T_REG &&
        asm_identify_arg_type(op[1]) != T_IND &&
        asm_identify_arg_type(op[1]) != T_DIR)
        return (0);
    if (asm_identify_arg_type(op[2]) != T_REG &&
        asm_identify_arg_type(op[2]) != T_DIR)
        return (0);
    if (asm_identify_arg_type(op[3]) != T_REG)
        return (0);
    return (1);
}

int     check_lldi_args(char **op)
{
    if (asm_get_nb_array(op) != 4)
        return (0);
    if (asm_identify_arg_type(op[1]) != T_REG &&
        asm_identify_arg_type(op[1]) != T_IND &&
        asm_identify_arg_type(op[1]) != T_DIR)
        return (0);
    if (asm_identify_arg_type(op[2]) != T_REG &&
        asm_identify_arg_type(op[2]) != T_DIR)
        return (0);
    if (asm_identify_arg_type(op[3]) != T_REG)
        return (0);
    return (1);
}

int     check_sti_args(char **op)
{
    if (asm_get_nb_array(op) != 4)
        return (0);
    if (asm_identify_arg_type(op[1]) != T_REG)
        return (0);
    if (asm_identify_arg_type(op[2]) != T_REG &&
        asm_identify_arg_type(op[2]) != T_DIR &&
        asm_identify_arg_type(op[2]) != T_IND)
        return (0);
    if (asm_identify_arg_type(op[3]) != T_REG &&
        asm_identify_arg_type(op[3]) != T_DIR)
        return (0);
    return (1);
}

int    check_fork_args(char **op)
{
    if (asm_get_nb_array(op) != 2)
        return (0);
    if (asm_identify_arg_type(op[1]) != T_DIR)
        return (0);
    return (1);
}

int     check_lld_args(char **op)
{
    if (asm_get_nb_array(op) != 3)
        return (0);
    if (asm_identify_arg_type(op[1]) != T_DIR &&
        asm_identify_arg_type(op[1]) != T_IND)
        return (0);
    if (asm_identify_arg_type(op[2]) != T_REG)
        return (0);
    return (1);
}

int    check_lfork_args(char **op)
{
    if (asm_get_nb_array(op) != 2)
        return (0);
    if (asm_identify_arg_type(op[1]) != T_DIR)
        return (0);
    return (1);
}

int    check_aff_args(char **op)
{
    if (asm_get_nb_array(op) != 2)
        return (0);
    if (asm_identify_arg_type(op[1]) != T_REG)
        return (0);
    return (1);
}

