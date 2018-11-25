/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouisy- <alouisy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 17:41:07 by alouisy-          #+#    #+#             */
/*   Updated: 2018/11/24 14:26:47 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	aux_usage(char *str)
{
	ft_printf("Usage: %s [-nc] [-dump N] [-v N] ", str);
	ft_printf("[-n N] <champion1.cor> [-n N] <...>\n");
	ft_printf("	-dump N\t: dump memory after N cycles then exit\n");
	ft_printf("	-dumpC N\t: dump colorized memory after N cycles then exit\n");
	ft_printf("	-n N\t: assign number N (can NOT be 0!) to champion ");
	ft_printf("from the following file\n");
	ft_printf("	-v N\t: equivalent of zaz verbose mode, can be added\n");
	ft_printf("\t\t\t- 0 : show only essentials\n");
	ft_printf("\t\t\t- 1 : show lives\n");
	ft_printf("\t\t\t- 2 : show cycles\n");
	ft_printf("\t\t\t- 4 : show operations\n");
	ft_printf("\t\t\t- 8 : show deaths\n");
	ft_printf("\t\t\t- 16 : show PC movements\n");
	ft_printf("\t\t\t- 32 : show Aff\n");
	ft_printf("	-nc\t: ncurses graphical mode\n");
	ft_printf("		command: w/z : +/-1  cycle/s\n");
	ft_printf("		         +/- : +/-10 cycles/s\n");
	ft_printf("		         space : pause\n");
	ft_printf("		         any key : continue\n");
}

int			aux_out(t_pvm *vm)
{
	free_vm(vm);
	return (EXIT_FAILURE);
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
			if (vm.nc_mode && vm.verbose)
				vm.verbose = 0;
			if (vm.nc_mode != 1)
				print_champ(vm.champions);
			else
				init_ncurses(&vm);
			if (!start_vm(&vm))
				return (aux_out(&vm));
		}
		else
			return (aux_out(&vm));
		free_vm(&vm);
	}
	else
		aux_usage(argv[0]);
	return (EXIT_SUCCESS);
}
