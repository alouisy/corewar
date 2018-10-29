/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouisy- <alouisy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 17:41:07 by alouisy-          #+#    #+#             */
/*   Updated: 2018/10/29 18:00:38 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	aux_usage(char *str)
{
	ft_printf("Usage: %s [-nc] [-dump N] [-n N] file [-n N] <champion1.cor> [-n N] <...>\n", str);
	ft_printf("	-dump N	: dump memory after N cycles then exit\n", str);
	ft_printf("	-n N	: assign number N to champion from the following file\n", str);
	ft_printf("	-nc	: ncurses graphical mode\n", str);
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

	printf("%d\n", COLOR_GREEN);
	printf("%d\n", COLOR_RED);
	printf("%d\n", COLOR_BLUE);
	printf("%d\n", COLOR_YELLOW);
	if (argc > 1)
	{
		init_vm(&vm);
		if (parse_arg(&vm, argc, argv))
		{
			init_memory(&vm);
			if (!(vm.nc.ncurses))
				ft_lstiter(vm.champions, &aux_print_champ);
			print_memory(&vm);
			start_vm(&vm);
		}
		free_vm(&vm);
	}
	else
		aux_usage(argv[0]);
	return (0);
}
