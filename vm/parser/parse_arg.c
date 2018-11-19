/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouisy- <alouisy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 14:51:21 by alouisy-          #+#    #+#             */
/*   Updated: 2018/11/18 17:21:15 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

static int	ft_set_var(char **av, int i, int *var)
{
	if (ft_nbrisinteger(av[i]))
	{
		*var = ft_atoi(av[i]);
		return (1);
	}
	else
		return (ft_strerror("ERROR (not integer)", 0));
}

static int	set_champ_process(char **av, int i, t_pvm *vm, int *champ_nb)
{
	if (!parse_champion(av[i], *champ_nb, vm) || !add_process(vm))
		return (0);
	vm->nb_champ++;
	vm->nb_process++;
	*champ_nb = 0;
	return (1);
}

inline int	parse_arg(t_pvm *vm, int ac, char **av)
{
	int	i;
	int	champ_nb;

	i = 0;
	champ_nb = 0;
	while (++i < ac && vm->nb_champ < MAX_PLAYERS)
	{
		if (ft_strequ("-dump", av[i]))
		{
			if (!ft_set_var(av, ++i, &vm->dump))
				return (0);
		}
		else if (ft_strequ("-nc", av[i]))
			vm->nc_mode = 1;
		else if (ft_strequ("-v", av[i]) && ft_nbrisinteger(av[++i]))
			vm->verbose = ft_atoi(av[i]);
		else if (ft_strequ("-n", av[i]))
		{
			if (!ft_set_var(av, ++i, &champ_nb))
				return (0);
		}
		else if (!set_champ_process(av, i, vm, &champ_nb))
			return (0);
	}
	return (vm->nb_champ ? 1 : (ft_strerror("ERROR (NO CHAMPIONS)", 0)));
}
