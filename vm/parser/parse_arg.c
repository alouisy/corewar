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

static int	ft_set_var(int ac, char **av, int i, int *var)
{
	if (i >= ac)
		return (ft_strerror("ERROR (missing arguments)", 0));
	if (ft_nbrisinteger(av[i]))
	{
		*var = ft_atoi(av[i]);
		return (1);
	}
	else
		return (ft_strerror("ERROR (not integer)", 0));
}

static int	ft_set_champion(t_pvm *vm, int ac, char **av, int *i)
{
	int	champ_nb;
	char	*search;

	champ_nb = 0;
	if (ft_strequ("-n",  av[*i]))
	{
		if (!ft_set_var(ac, av, ++(*i), &champ_nb))
			return (0);
		if (++(*i) >= ac)
			return (ft_strerror("ERROR (missing champions)", 0));
	}
	if (!(search = ft_strstr(av[*i], ".cor")) || search[4] != '\0')
	{
		ft_printf("ERROR (%s is not a .cor file)\n", av[*i]);
		return (0);
	}
	if (!parse_champion(av[*i], champ_nb, vm) || !add_process(vm))
		return (0);
	vm->nb_champ++;
	vm->nb_process++;
	return (1);
}

static int	ft_set_option(t_pvm *vm, int ac, char **av, int *i)
{
	if (ft_strequ("-dump", av[*i]))
	{
		if (!ft_set_var(ac, av, ++(*i), &vm->dump))
			return (0);
	}
	else if (ft_strequ("-nc", av[*i]))
		vm->nc_mode = 1;
	else if (ft_strequ("-v", av[*i]))
	{
		if (!ft_set_var(ac, av, ++(*i), &vm->verbose))
			return (0);
	}
	else if (ft_strequ("-n", av[*i]) || (ft_strstr(av[*i], ".cor")))
	{
		if (!(ft_set_champion(vm, ac, av, i)))
			return (0);
	}
	else
		return (ft_strerror("ERROR (unknown options)", 0));
	return (1);
}

inline int	parse_arg(t_pvm *vm, int ac, char **av)
{
	int	i;

	i = 0;
	while (++i < ac && vm->nb_champ < MAX_PLAYERS)
	{
		if (av[i][0] == '-')
		{
			if (!ft_set_option(vm, ac, av, &i))
				return (0);
		}
		else
		{
			if (!ft_set_champion(vm, ac, av, &i))
				return (0);
		}
	}
	return (vm->nb_champ ? 1 : (ft_strerror("ERROR (NO CHAMPIONS)", 0)));
}
