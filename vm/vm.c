/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouisy- <alouisy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 17:41:07 by alouisy-          #+#    #+#             */
/*   Updated: 2018/10/29 19:34:17 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	aux_usage(char *str)
{
	ft_printf("Usage: %s [-nc] [-dump N] ", str);
	ft_printf("[-n N] <champion1.cor> [-n N] <...>\n");
	ft_printf("	-dump N	: dump memory after N cycles then exit\n");
	ft_printf("	-n N\t: assign number N to champion from the following file\n");
	ft_printf("	-nc	: ncurses graphical mode\n");
	ft_printf("		command: w/z : +/-1  cycle/s\n");
	ft_printf("		         +/- : +/-10 cycles/s\n");
	ft_printf("		         space : pause\n");
	ft_printf("		         any key : continue\n");
}

int			main(int argc, char **argv)
{
	t_pvm	vm;

	if (argc > 1)
	{
		init_vm(&vm);
		if (parse_arg(&vm, argc, argv))
		{
			init_memory(&vm);
			if (vm.verbose != 1)
				print_champ(vm.champions);
			else
				init_ncurses(&vm);
			if (!start_vm(&vm))
			{
				free_vm(&vm);
				return (EXIT_FAILURE);
			}
		}
		free_vm(&vm);
	}
	else
		aux_usage(argv[0]);
	return (EXIT_SUCCESS);
}
