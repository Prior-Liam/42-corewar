/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_parse_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liamprior <liamprior@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 16:54:57 by lprior            #+#    #+#             */
/*   Updated: 2022/01/27 12:44:38 by liamprior        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Verify whether the argument of the argument is valid, load to appropriate
** variable if so, return an error code otherwise.
*/

int		parse_args(int *i, int ac, char **av, t_vm *vm)
{
	if (ft_strequ(av[*i], "-dump") == 1)
		return (((*i)++ < ac && (vm->dump_cycle = ft_atoi(av[*i])) >= 0)
					&& (*i)++ < ac ? 1 : -1);
	else if (ft_strequ(av[*i], "-n") == 1)
		return (((*i)++ < ac && (vm->curr_player = ft_atoi(av[*i])) >= 0)
					&& (*i)++ < ac ? 1 : -1);
	else if (handle_file(av[*i], vm))
	{
		(*i)++;
		return (1);
	}
	(*i)++;
	return (-1);
}

/*
** Iterate throught the list of arguments, call parse args.
*/

int		iter_args(int ac, char **av, t_vm *vm)
{
	int i;

	i = 1;
	if (ac <= 1)
		return (ft_puterror(-1, "Usage: ./corewar [player]"));
	while (i < ac)
	{
		if (parse_args(&i, ac, av, vm) == -1)
			return (ft_puterror(-1, "Parsing Error"));
	}
	return (1);
}
