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
	champ_nb = 0;
	while (++i < ac && vm->nb_champ < MAX_PLAYERS)
	{
		if (ft_strequ("-dump", av[i]))
		{
			if (ft_nbrisinteger(av[++i]))
				vm->dump = ft_atoi(av[i]);
			else
				return (ft_strerror("ERROR (not integer)", 0));
		}
		else if (ft_strequ("-nc", av[i]))
			vm->verbose = 1;
		else if (ft_strequ("-v", av[i]))
			vm->verbose = 2;
		else if (ft_strequ("-vp", av[i]))
			vm->verbose = 3;
		else if (ft_strequ("-n", av[i]))
		{
			if (ft_nbrisinteger(av[++i]))
				champ_nb = ft_atoi(av[i]) * (-1);
			else
				return (ft_strerror("ERROR (not integer)", 0));
		}
		else
		{
			if (!parse_champion(av[i], champ_nb, vm) || !add_process(vm))
				return (0);
			champ_nb = 0;
			vm->nb_champ++;
			vm->nb_process++;
		}
	}
	if (vm->nb_champ == 0)
		return (ft_strerror("ERROR (NO CHAMPIONS)", 0));
	return (1);
}
