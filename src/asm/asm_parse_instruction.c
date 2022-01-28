/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parse_instruction.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liamprior <liamprior@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 21:58:52 by lprior            #+#    #+#             */
/*   Updated: 2022/01/27 12:40:06 by liamprior        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** 1. first two line of printf just to debug
** 2. use while the file is not reading to the end
** 3. 	do: * asm_get_line, bascially modify version of gnl, and update the tasm->i (the file index)
**			* asm_trim_line, bascially trim the line in the front and back, and do following:
**				--> asm_parse_instruction() 1, check if there is label and store in t_label linked list
**											2. char **instruction = strsplit(line + i)
**											3. parse the (char **), to t_instruction w/ opcode, nb_index_jump, char **params
*/

int		is_valid_operation(char **operation)
{
	int i;

	i = 0;
	if (!operation[0])
		return (1);
	while (i < 16)
	{
		if (ft_strequ(operation[0], g_op_tab_asm[i].name))
			return (g_op_tab_asm[i].is_valid_args(operation));
		i++;
	}
	return (0);
}

t_op	asm_get_op_from_name(char *name)
{
	int i;

	i = -1;
	while (++i < 16)
	{
		if (ft_strequ(name, g_op_tab_asm[i].name))
			return (g_op_tab_asm[i]);
	}
	return (g_op_tab_asm[16]);
}

/*
**Yacine ur a bitch if u see this bruh
*/

unsigned char 	asm_build_code_byte(char **gang)
{
	int				i;
	int				bit_shift;
	unsigned char	code_byte;

	i = 0;
	code_byte = 0;
	bit_shift = 6;
	while (gang[++i])
	{
		if (asm_check_REG(gang[i]))
			code_byte |= 1 << bit_shift;
		else if (asm_check_DIR(gang[i]))
			code_byte |= 2 << bit_shift;
		else if (asm_check_IND(gang[i]))
			code_byte |= 3 << bit_shift;
		bit_shift -= 2;
	}
	return (code_byte);
}

void	asm_conv_int_to_reg(int val, unsigned char *dest, int *x)
{
	dest[0] = (val & 0x000000ff);
	x += 1;
}

void	asm_conv_int_to_indir(int val, unsigned char *dest, int *x)
{
    dest[0] = (val & 0x0000ff00) >>  8;
    dest[1] = (val & 0x000000ff);
	x += 2;
}

void	asm_conv_int_to_dir(int val, unsigned char *dest, int *x)
{
    dest[0] = (val & 0xff000000) >> 24;
    dest[1] = (val & 0x00ff0000) >> 16;
    dest[2] = (val & 0x0000ff00) >>  8;
    dest[3] = (val & 0x000000ff);
	x += 4;
	printf("0[%d]1[%d]2[%d]3[%d]\n", dest[0], dest[1], dest[2], dest[3]);
}

void	asm_load_arg_to_byte_code(unsigned char **byte_code, char **gang, int trunk)
{
	int				i;
	int				x;
	unsigned char	hex[11];

	i = 1;
	x = 1;
	hex[0] = *byte_code[0];
	printf("byte_code = %d\n", *byte_code[0]);
	while (gang[i])
	{
		printf("gang in byte_code_conv = %s\n", gang[i]);
		if (asm_check_REG(gang[i]))
			asm_conv_int_to_reg(ft_atoi(gang[i] + 1), &(hex[x]), &x);
		else if (asm_check_IND(gang[i]) || (trunk == 1 && asm_check_DIR(gang[i])))
			asm_conv_int_to_indir(ft_atoi(gang[i]), &(hex[x]), &x);
		else if (asm_check_DIR(gang[i]) && trunk != 1)
			asm_conv_int_to_dir(ft_atoi(gang[i] + 1), &(hex[x]), &x);
		printf("hex = 0[%d] 1[%d] 2[%d] 3[%d] 4[%d] 5[%d] 6[%d] 7[%d] 8[%d] 9[%d] 10[%d]\n", hex[0], hex[1], hex[2], hex[3], hex[4], hex[5], hex[6], hex[7], hex[8], hex[9], hex[10]);
		i++;
	}
	*byte_code = hex;
	printf("hex = 0[%d] 1[%d] 2[%d] 3[%d] 4[%d] 5[%d] 6[%d] 7[%d] 8[%d] 9[%d] 10[%d]\n", hex[0], hex[1], hex[2], hex[3], hex[4], hex[5], hex[6], hex[7], hex[8], hex[9], hex[10]);
}

void	add_to_op_list(t_asm *tasm, char **gang)
{
	unsigned char	*byte_code;
	t_op			op;

	tasm->i = tasm->i;
	op = asm_get_op_from_name(gang[0]);
	byte_code = (unsigned char	*)ft_strnew(op.nb_params * 4);
	byte_code[0] = op.opcode;
	if (op.coding_byte)
		byte_code[1] = asm_build_code_byte(gang);
	asm_load_arg_to_byte_code(&byte_code, gang, op.label_size);
}

int	asm_parse_instruction(t_asm *tasm)
{
	char **gang;

	tasm->byte_lst = (t_list *)ft_memalloc(sizeof(t_list));
	tasm->byte_lst->content = NULL;
	tasm->byte_lst->next = NULL;
	while (tasm->file[tasm->i])
	{
		printf("gang[%s]\n", gang[0]);
		asm_get_line(tasm);
		// printf("[%s]\n", tasm->line);
		// tasm->line = ft_strtrim(tasm->line);
		tasm->line = ft_strtrim(tasm->line);
		if (!tasm->line && (tasm->i += 1))
			continue ;
		if (tasm->line)
			gang = asm_strsplit(tasm->line, " \t");
		printf("gang after string split = %s %s %s\n", gang[0], gang[1], gang[2]);
		if (gang && !is_valid_operation(gang))
			return (-1);
		add_to_op_list(tasm, gang);
		printf("print each line: %s\n", gang[0]); // this is for debug
	}
	// ft_printf(DARKYELLOW"print the whole file: \n %s"RESET, tasm->file);
	return (1);
}

/*
** k is the gap between tasm->i to '\n'
** asm_get_line is like get_next_line, store line into tasm->line and return one line by one line
*/

void	asm_get_line(t_asm *tasm)
{
	while (tasm->file[tasm->i] == '\n' && tasm->file[tasm->i + 1] == '\n')
		tasm->i += 1;
	tasm->k = ft_strlen_til(tasm->file + tasm->i, '\n'); // this function is in the asm_helper.c // don't delete
	tasm->line = ft_strndup(tasm->file + tasm->i, tasm->k); //assign tasm->line for everyline after comment , like gnl
	if (tasm->file[tasm->i + tasm->k] == '\0')
		tasm->i += tasm->k;
	else
		tasm->i += tasm->k + 1;
}

/*
** trim the line, remove the ' ' and '\t' in the front and end of the line
*/

void	asm_trim_line(t_asm *tasm)
{
	char *line;

	line = ft_strtrim(tasm->line);
	if (line)
		asm_parse_instruction(tasm);
	free(line);
	free(tasm->line);
}

/*
** 1. check if there is a LABEL_CHAR ':', if yes, store the label in the struct
** 			and keep the offset,
** 2. if not set the i = 0, if yes, set do strsplit with the line without label by line + i
** 3. get the char **, and store in the struct, we can use array
*/
// void	asm_parse_instruction(t_asm *tasm, char *line, char **instruction)
// {
// 	int		i;

// 	i = 0;
// 	while (line[i] && !is_delim(line[i], " \t") && line[i] != LABEL_CHAR)
// 		i++;
// 	if (line[i++] == LABEL_CHAR)//might be able to delete
// 		asm_check_save_label(tasm, line); // next function
// 	else
// 		i = 0;
// 	while (is_delim(line[i], " \t"))
// 		i++;
// 	if (line[i] == '\0')
// 		return ;
// 	else
// 	{
// 		instruction = asm_strsplit(line + i, " ,\t");
// 		asm_convert_instruction(instruction, tasm, 0)
// 	}
// 	i = 0;
// 	while (instruction && instruction[i])
// 		free(instruction[i]);
// 	(instruction) ? ft_strdel(instruction): 0;
// 	tasm->final_index = tasm->index;
// }

// /*
// ** to check if the label has the right LABEL_CHARS
// ** if not exit and free and perror, if yes store in the t_label, with offset (index)
// */
// void	asm_check_save_label(tasm *tasm, char *line)
// {
// 	int	i;

// 	i = 0;
// 	while (line[i] != LABEL_CHAR)
// 	{
// 		if (!ft_strchr(LABEL_CHARS, line[i++]))
// 		{

// 			ft_printf("ERROR: Invalid label name\n");
// 			free(); //tasm->file, tasm->line, struct
// 			exit();
// 		}
// 	}
// 	asm_store_label_lst(&tasm->label, ft_strsub(line, 0, i), tasm->index); // the next function
// }


// void	asm_store_label_lst(t_label **label, char *label_name, int index)
// {
// 	t_label	*head;

// 	head = *label;
// 	if (head)
// 	{
// 		while (head->next)
// 			head = head->next;
// 		head->next = (t_label *)ft_memalloc(sizeof(t_label));
// 		head->next->label_name = label_name;
// 		head->next->index = index;
// 		head->next->next = NULL;
// 	}
// 	else
// 	{
// 		head = (t_label *)ft_memalloc(sizeof(t_label));
// 		head->label_name = label_name;
// 		head->index = index;
// 		head->next = NULL;
// 	}
// }

// /*
// ** get the byte[0] byte[1] byte[2] to get the REG_SIZE, DIR_SIZE, and IND_SIZE,
// ** 		also check the if (!g_op_tab_asm[i].label_size)
// **							change the T_DIR = 4 , originally 2 for T_DIR
// ** 		also if the type == T_IND -> the size will be 2
// */
// void	asm_calc_jumping_bytes(char **instruction, t_asm *tasm, int i, int byte[3])
// {
// 	int type;
// 	int jump_nb;
// 	int j

// 	type = 0;
// 	jump_nb = 0;
// 	while (instruction[j])
// 	{
// 		if (!type = asm_valid_arg_type(instruction[j]))
// 		{
// 			ft_printf("wrong arg type");
// 			free();
// 			exit();
// 		}

// 	}
// }

// haven't finished it yet
// !!! before malloc check ','////// don't need any more (optional handling if we have time)
// 		--> if there is two (char *) // don't check //i.g.live %1
//		--> if there is three (char *)// check 2nd arg, last char is ',' // i.g. ld %1, r1
//		--> if there is four (char *) // check 2nd and 3 rd, last char is ',' // i.g. add r1, r2, r3
//		--> more there four --> perror
// void	asm_convert_instruction(char **instruction, t_asm *tasm, int i)
// {
// 	int i; // i == opcode nb
// 	int byte[3];

// 	i = 0;
// 	ft_bzero(&byte, 0, 3); // have to check if this is correct way to initial
// 	if ((i = asm_check_op_name(instruction[0])) == 0)
// 	{
// 		ft_printf("ERROR: Instruction is not valid\n"); //handle_error
// 		free();
// 		close();
// 		exit();
// 	}
// 	if (!asm_valid_op_arg(instruction, tasm, i, byte))
// 	{
// 		ft_printf("ERROR: wrong arg number at %s", g_op_tab_asm[i].name);
// 		free();
// 		exit();
// 	}
// 	tasm->op_array[tasm->op_nb] = ft_memalloc(sizeof(t_instruction));
// 	tasm->op_array[tasm->op_nb]->op_org = ft_memalloc(sizeof(char *) * MAX_ARGS_NUMBER);
// 	tasm->op_array[tasm->op_nb]->opcode = g_op_tab_asm[i].opcode;
// 	tasm->instruction_index = tasm->index;
// 	tasm->index++;
// 	if (g_op_tab_asm[i].bytecode)
// 	{
// 		asm_calc_jumping_bytes(instruction, tasm, i, byte); // haven't write calc acb function
// 		tasm->op_array[tasm->nb_op]->jump_nb += 2;
// 	}
// 	else
// 	{
// 		if (!type = asm_valid_arg_type(instruction[j]))
// 		{
// 			ft_printf("wrong arg type");
// 			free();
// 			exit();
// 		}
// 		if (type = T_DIR && t_op_tab[i].label_size == 0)
// 			type = 4;
// 		jump_nb = type;
// 		tasm->op_array[tasm->nb_op]->jump_nb += jump_nb;
// 		j++;
// 		//depend on the byte arg , get the nb_byte in and add into offset (index).
// 	}
// }

// /*
// ** to check if op param nb is correct and check if the arg belongs to any of 3 types (i.e. T_REG, T_DIR, T_IND)
// ** int byte[3] bascially store which type T_REG, T_DIR, T_IND is
// */
// int	asm_valid_op_arg(char **instruction, t_asm *tasm, int i, int byte[3])
// {
// 	int	nb;
// 	int j;
// 	int	type;

// 	j = 1
// 	nb = asm_get_nb_array(instruction);
// 	if (nb != g_op_tab_asm[i].nb_params + 1)
// 	{
// 		// ft_printf("ERROR: wrong arg number at %s", g_op_tab_asm[i].name);
// 		free();
// 		exit();
// 		return (0);
// 	}
// 	while (instruction[j])
// 	{
// 		if ((type = asm_identify_arg_type(instruction[j])) == 0)
// 		{
// 			// ft_printf("ERROR: wrong arg format at %s", g_op_tab_asm[i].name);
// 			return (0);
// 		}
// 		else
// 		{
// 			if (g_op_tab_asm[i].params_type[j] == 3)
// 			{
// 				if (type = T_REG)
// 					byte[j - 1] = type;
// 				if (type = T_DIR)
// 					byte[j - 1] = type;
// 			}
// 			else if (type & g_op_tab_asm[i].params_type[j])
// 			{

// 				byte[j - 1] = type
// 			}
// 			else
// 				return (0);
// 		}
// 		j++;
// 	}
// 	return (1);
// }

// /* this is not in the correcting
// int		asm_check_sep_char(char **instruction, int nb)
// {
// 	if (nb == 2)
// 	{
// 		if (ft_strchr(instruction[1], SEPARATOR_CHAR))
// 		{
// 			ft_printf("ERROR: wrong arg format, include ',' in the only one arg");
// 			free();
// 			exit();
// 		}
// 	}
// 	else if (nb == 3)
// 	{
// 		if (instruction[1][ft_strlen(instruction[1]) - 1] != SEPARATOR_CHAR &&
// 			ft_check_char_til())

// 		if (ft_strchr(instruction[2], SEPARATOR_CHAR))
// 		{
// 			ft_printf("ERROR: wrong arg format, include ',' in the only one arg");
// 			free();
// 			exit();
// 		}
// 	}
// 	else if (nb == 4)
// 	{
// 		if (ft_strchr(instruction[3], SEPARATOR_CHAR))
// 		{
// 			ft_printf("ERROR: wrong arg format, include ',' in the only one arg");
// 			free();
// 			exit();
// 		}
// 	}
// }
// identify which arg type and return type number in order to do bitwise comparison
int		asm_identify_arg_type(char *str)
{
	if (asm_check_REG(str))
		return (T_REG);
	else if (asm_check_DIR(str))
		return (T_DIR);
	else if (asm_check_IND(str))
		return (T_IND);
	else
		return (0);
}
