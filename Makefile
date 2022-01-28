# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: liamprior <liamprior@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/25 11:03:14 by lprior            #+#    #+#              #
#    Updated: 2022/01/27 16:15:53 by liamprior        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# targets
ASM := asm
VM := corewar

# compiler and flags
CC = gcc
CFLAG = -c
WFLAG = -Wall -Wextra -Werror

# libft
LIBFT = libft/
ASM_LIBS = -L $(LIBFT) -lft
VM_LIBS = -L $(LIBFT) -lft

# headers
ASM_HEADER = -I include -I $(LIBFT)include
VM_HEADER = -I include -I $(LIBFT)include

# files and directories
SRC_VM	=	vm_free_vm.c \
			vm_init_vm.c \
			vm_load_process_to_arena.c \
			vm_main.c \
			vm_op.c \
			vm_parse_args.c \
			vm_print_result.c \
			vm_read_cor.c \
			vm_run_cycles.c \
			ops/bit_operators.c \
			ops/op_add_sub.c \
			ops/op_aff.c \
			ops/op_and.c \
			ops/op_fork.c \
			ops/op_helpers.c \
			ops/op_ld.c \
			ops/op_ldi.c \
			ops/op_lfork.c \
			ops/op_live.c \
			ops/op_lld.c \
			ops/op_lldi.c \
			ops/op_or.c \
			ops/op_st.c \
			ops/op_sti.c \
			ops/op_xor.c \
			ops/op_zjmp.c

SRC_ASM =	asm_parse.c \
			asm_op.c \
			asm_parse_instruction.c \
			asm_read_file.c \
			asm_check_param_type.c \
			asm_check_skip.c \
			asm_main.c \
			asm_strsplit.c \
			asm_helper.c \
			asm_check_op_args.c

OBJ_ASM = $(SRC_ASM:.c=.o)
SRCDIR_ASM = src/asm/
OBJDIR_ASM = objs/asm/
SRCS_ASM = $(addprefix $(SRCDIR_ASM), $(SRC_ASM))
OBJS_ASM = $(addprefix $(OBJDIR_ASM), $(OBJ_ASM))

OBJ_VM = $(SRC_VM:.c=.o)
SRCDIR_VM = src/vm/
OBJDIR_VM = objs/vm/
OBJDIR_OP = objs/vm/ops/
SRCS_VM = $(addprefix $(SRCDIR_VM), $(SRC_VM))
OBJS_VM = $(addprefix $(OBJDIR_VM), $(OBJ_VM))

.PHONY: all clean fclean re
.SUFFIXES: .c .o

all:  $(VM) $(ASM)

# #COMPILING ASSEMBLER
$(OBJDIR_ASM)%.o: $(SRCDIR_ASM)%.c
	@/bin/mkdir -p $(OBJDIR_ASM)
	@$(CC) $(CFLAG) $(WFLAG) $(ASM_HEADER) $< -o $@

$(ASM): $(OBJS_ASM)
	@make -s -C $(LIBFT)
	@$(CC) $(OBJS_ASM) $(ASM_LIBS) -o $@
	@echo "\033[32massembler compiled.\033[0m"

# COMPILING VIRTUAL MACHINE
$(OBJDIR_VM)%.o: $(SRCDIR_VM)%.c
	@/bin/mkdir -p $(OBJDIR_VM)
	@/bin/mkdir -p $(OBJDIR_OP)
	@$(CC) $(CFLAG) $(WFLAG) $(VM_HEADER) $< -o $@

$(VM): $(OBJS_VM)
	@make -s -C $(LIBFT)
	@$(CC) $(OBJS_VM) $(VM_LIBS) -o $@
	@echo "\033[32mvirtural machine compiled.\033[0m"

clean:
	@/bin/rm -rf objs
	@make -s -C $(LIBFT) clean
	@echo "\033[32mobject files removed.\033[0m"

fclean: clean
	@/bin/rm -rf $(VM) $(ASM) $(LIBFT)libft.a
	@echo "\033[32mexecutables removed.\033[0m"

re: fclean all
