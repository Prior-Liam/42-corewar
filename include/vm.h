/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liamprior <liamprior@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 15:18:24 by lprior            #+#    #+#             */
/*   Updated: 2022/01/27 12:37:00 by liamprior        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H
# include "op.h"
# include "libft.h"

# define P1_ID			0xFFFFFFFF

extern t_op						g_op_tab_vm[17];

typedef struct			s_membox
{
	unsigned char		value;
	int					player;
}						t_membox;

typedef struct			s_header
{
	unsigned int		magic;
	char				prog_name[PROG_NAME_LENGTH + 1];
	unsigned int		prog_size;
	char				comment[COMMENT_LENGTH + 1];
}						t_header;

typedef struct			s_player
{
	int					num;
	unsigned int		id;
	t_header			header;
	unsigned char		*program;
}						t_player;

typedef struct			s_process
{
	t_player			player;
	unsigned int		reg[REG_NUMBER];
	unsigned int		pc;
	int					opcode;
	int					dead;
	int					carry;
	int					lives;
	int					cycle_count;
	struct s_process	*next;
}						t_process;

typedef struct			s_vm
{
	t_membox			membox[MEM_SIZE];
	t_player			players[MAX_PLAYERS];
	int					curr_player;
	int					player_count;
	int					winner;
	int					end;
	int					dump_cycle;
	int					current_cycle;
	int					cycle_to_die;
	int					ctd_count;
	int					total_lives;
	int					checks;
	t_process			*process_list;
}						t_vm;

/*
********************** Create and Initialize VM struct *************************
*/

t_vm					vm_init_vm(void);

/*
****************************** Handle Args *************************************
*/

int						iter_args(int ac, char **av, t_vm *vm);
int						parse_args(int *i, int ac, char **av, t_vm *vm);

/*
****************************** Open and Load File ******************************
*/

int						open_file(char *file_name);
int						handle_file(char *file_name, t_vm *vm);
int						read_file_header(int fd, t_header *header);
int						read_file_program(int fd, t_player *champ);

/*
****************************** Create Proces ***********************************
*/

void					add_process(t_process **p, t_player curr_player, int j,
									t_vm *vm);
t_process				*create_process_list(t_vm *vm);

/*
********************************* Run Cycles ***********************************
*/

void					vm_run_cycles(t_vm *vm);
void					vm_print_result(t_vm *vm);

/*
*************************** Free Allocated Memory ******************************
*/

void					vm_free_vm(t_vm *vm);

/*
********************************* Op Functions *********************************
*/

void					get_type(unsigned char byte, int *ret);
int						bigendianconv(unsigned char *hex, size_t size);
void					ft_op_sub(t_vm *vm, t_process *proc);
void					ft_op_add(t_vm *vm, t_process *proc);
void					ft_op_aff(t_vm *vm, t_process *process);
void					ft_op_and(t_vm *vm, t_process *process);
void					ft_op_fork(t_vm *vm, t_process *process);
void					ft_op_ld(t_vm *vm, t_process *process);
void					ft_op_ldi(t_vm *vm, t_process *process);
void					ft_op_lfork(t_vm *vm, t_process *process);
void					ft_op_live(t_vm *vm, t_process *process);
void					ft_op_lld(t_vm *vm, t_process *process);
void					ft_op_lldi(t_vm *vm, t_process *process);
void					ft_op_or(t_vm *vm, t_process *process);
void					ft_op_st(t_vm *vm, t_process *process);
void					ft_op_sti(t_vm *vm, t_process *process);
void					ft_op_xor(t_vm *vm, t_process *process);
void					ft_op_zjmp(t_vm *vm, t_process *process);


void					int_to_hex(int val, unsigned char *dest);
int						cir_mem(int index);
int						check_second_arg(unsigned char *hex, int *type,
										int *num2, int *i);
int						check_first_arg(unsigned char *hex, int *type,
										int *num1, int *i);
void					get_hex(t_vm *vm, int pc, unsigned char *hex,
								size_t size);
int						convert_arg(t_vm *vm, t_process *process,
									int type, int *arg);

#endif
