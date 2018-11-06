/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouisy- <alouisy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 14:51:21 by alouisy-          #+#    #+#             */
/*   Updated: 2018/10/29 19:24:34 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

inline int			parse_arg(t_pvm *vm, int ac, char **av)
{
	int	i;
	int	champ_nb;

	i = 0;
	champ_nb = -1;
	while (++i < ac)
	{
		//if (ft_strequ("-dump", av[i]) && ft_nbrisinteger(av[++i]))
		if (ft_strequ("-dump", av[i]))
			vm->dump = ft_atoi(av[i]);
		else if (ft_strequ("-nc", av[i]))
			vm->nc.ncurses = 1;
		else if (ft_strequ("-v", av[i]))
			vm->verbose = 1;
		//else if (ft_strequ("-n", av[i]) && ft_nbrisinteger(av[++i]))
		else if (ft_strequ("-n", av[i]))
			champ_nb = ft_atoi(av[i]);
		else
		{
			if (!parse_champion(av[i], champ_nb, vm) || !add_process(vm))
				return (0);
			champ_nb = -1;
			vm->nb_champ++;
		}
	}
	if (vm->nb_champ > 4 || vm->nb_champ == 0)
		return (ft_strerror("ERROR (MORE THAN 4 OR NO CHAMPIONS)", 0));
	return (1);
}
