/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouisy- <alouisy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 17:41:07 by alouisy-          #+#    #+#             */
/*   Updated: 2018/10/27 19:48:15 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	aux_usage(char *str)
{
	ft_printf("Usaqe: %s [-nc] [-dump N] [-n N] file [-n N] <champion1.cor> [-n N] <...>\n", str);
	ft_printf("	-dump N	: dump memory after N cycles then exit\n", str);
	ft_printf("	-n N	: assign number N to champion from the following file\n", str);
	ft_printf("	-nc		: ncurses graphical mode\n", str);
}

static void	aux_print_champ(t_list *node)
{
	t_champion	*champion;

	champion = CHAMPION(node);
	ft_printf(
		"Pos: %d\nMagic: %d\nProg_name: %s\nProg_size: %d\nComment: %s\n\n",
		champion->nbr,
		champion->header.magic,
		champion->header.prog_name,
		champion->header.prog_size,
		champion->header.comment);
}

int			main(int argc, char **argv)
{
	t_pvm	vm;

	if (argc > 1)
	{
		init_vm(&vm);
		if (parse_arg(&vm, argc, argv))
		{
			if (vm.ncurses)
				init_ncurses(&vm);
			else
				ft_lstiter(vm.champions, &aux_print_champ);
			init_memory(&vm);
			print_memory(&vm);
			start_vm(&vm);
			if (vm.ncurses)
				close_ncurses(&vm);
		}
		free_vm(&vm);
	}
	else
		aux_usage(argv[0]);
	return (0);
}
