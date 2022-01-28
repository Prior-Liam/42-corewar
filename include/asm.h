/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liamprior <liamprior@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 18:46:03 by lprior            #+#    #+#             */
/*   Updated: 2022/01/27 12:35:18 by liamprior        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "vm.h"
# include "libft.h"

extern t_op						g_op_tab_asm[17];

/* haven't stored anything yet */
/*
typedef struct				s_command // this will be the op instruction command, each line
{
	//char					*label; // if there is a label store label
	char					op_name[5];
	char 					**op_arg; r10
	int 					arg_values[3]; 10
	int 					arg_sizes[3]; 1
	int 					op_code; 11;
	char 					byte_code; 100
	int 					size; // size of the whole arg
	int 					index;
	int						byte_counter;

	int 					byte_code; // store
	//int						first_byte;
	//int						last_byte;
	//int						byte_size;

	t_label					*label;
	struct s_command	*next;
}							t_command;
*/

typedef struct 		s_instruction
{
	int				opcode;
	int				jump_nb; //how many btye in arg without bytecode and opcode
	char			**op_arg; // op_arg include op name
	int				label_ref; // if there is %:live label_ref = 1
	int 			label_ref_1; //
}					t_instruction;

typedef struct		s_label // live will be the label (i.e. l2: or live:)
{
	char			*label_name;
	int				index; // we have to get the index to reference and jump
	struct s_label 	*next;
}					t_label;

typedef struct		s_asm
{
	char			*file;
	int				part[2]; //part[0] = 1 means .name part is parsed, part[1] =1 means .comment
	size_t			i; //index_counter for the whole reading file
	size_t			j; //storage index counter
	size_t			k; //just the line index counter
	char			*line; // store each line of instruction, waiting for validation and store in t_instruction
	int				error; // check if any step is wrong, mark error = 1
	int				index;
	int				instruction_index;
	int				nb_op; // counting how many instruction
	t_header		header; //header struct is in op.h
	t_instruction	**op_array; // the array that store
	t_list			*byte_lst;
}					t_asm;


/*
** **************  asm_parse.c  **************************
*/

void				asm_parse_file(t_asm *tasm);
void				asm_parse_name(t_asm *tasm);
void				asm_parse_comment(t_asm *tasm);

/*
** **************  asm_parse_instruction.c  **************
*/

// void	asm_conv_int_to_reg(int val, unsigned char *dest);
// void	asm_conv_int_to_indir(int val, unsigned char *dest);
// void	asm_conv_int_to_dir(int val, unsigned char *dest);
int					asm_parse_instruction(t_asm *tasm);
void				asm_get_line(t_asm *tasm);
int					ft_check_char(char *str, char c);

/*
** **************  asm_helper.c  **************
*/
int					ft_strlen_til(char *str, char c);
int					asm_get_nb_array(char **instruction);
int					get_line_len(char **line);
int					ft_check_char(char *str, char c);

/*
**  **************  asm_read_file.c  *********************
*/
int					asm_read_file(char *file, t_asm *tasm);
int					asm_check_space_wnl(char space);
int					asm_check_space_wonl(char space);
void				asm_skip_space(t_asm *tasm);
void				asm_skip_routine(t_asm *tasm);

/*
** **********  asm_check_param_type.c  *********************
*/
int					asm_check_REG(char *str);
int					asm_check_DIR(char *str);
int					asm_check_label(char *str, int colon);
int					asm_check_IND(char *str);

/*
**  **************  asm_check_skip.c  *********************
*/
int					asm_check_comment(char comment);
int					asm_check_space_wnl(char space);
int					asm_check_space_wonl(char space);
void				asm_skip_space(t_asm *tasm);
void				asm_skip_routine(t_asm *tasm);

/*
**  **************  asm_strsplit.c  *********************
*/
int					is_delim(char c, char *delims);
int					asm_count_words(char const *str, char *delims);
char				*asm_malloc_word(char const *str, char *delims);
char				**asm_strsplit(char const *s, char *delims);

/*
** **************  asm_main.c  ****************************
*/
void				asm_perror(t_asm *tasm, char *error_string);
void				asm_usage(void);

/*
** **************  asm_check_op_args.c  ****************************
*/
int		asm_identify_arg_type(char *str);
int					check_live_args(char **op);
int 				check_ld_args(char **op);
int     check_st_args(char **op);
int     check_add_args(char **op);
int     check_sub_args(char **op);
int     check_and_args(char **op);
int     check_or_args(char **op);
int     check_xor_args(char **op);
int    check_zjmp_args(char **op);
int     check_ldi_args(char **op);
int     check_lldi_args(char **op);
int     check_sti_args(char **op);
int    check_fork_args(char **op);
int     check_lld_args(char **op);
int    check_lfork_args(char **op);
int    check_aff_args(char **op);



# define BLACK		"\033[0;30m"
# define BLUE		"\033[0;34m"
# define CYAN		"\033[1;36m"
# define DARKYELLOW	"\033[0;33m"
# define GREEN		"\033[0;32m"
# define GREY		"\033[1;30m"
# define LAVENDER	"\033[1;35m"
# define LIGHTBLUE	"\033[0;36m"
# define LIGHTGREY	"\033[0;37m"
# define LIME		"\033[1;32m"
# define MAGENTA	"\033[0;35m"
# define PINK		"\033[1;31m"
# define PURPLE		"\033[1;34m"
# define RED		"\033[0;31m"
# define UNDERLINE	"\033[4m"
# define WHITE		"\033[1;37m"
# define YELLOW		"\033[1;33m"
# define RESET		"\033[0m"

#endif
