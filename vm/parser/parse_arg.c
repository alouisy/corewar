/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouisy- <alouisy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 14:51:21 by alouisy-          #+#    #+#             */
/*   Updated: 2018/10/19 13:47:55 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

static inline void		ft_check_champ_numb(t_list *champions, int nb)
{
	t_list	*tmp;
	t_list	*tmp2;

	ft_putendl("Checking Champ Pos&Stuff...");
	if (nb > 4)
		exit_error("ERROR (MORE THAN 4 CHAMPIONS)", 1);
	tmp = champions;
	while (tmp)
	{
		tmp2 = tmp->next;
		while (tmp2)
		{
			if ((CHAMPION(tmp))->nbr == (CHAMPION(tmp2))->nbr)
				exit_error("ERROR (2 CHAMPIONS WITH THE SAME NUMBER)", 1);
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
	ft_putendl("Checking Completed !");
}

inline int				parse_arg(t_pvm *vm, int ac, char **av)
{
	int	i;

	i = 0;
	while (++i < ac)
	{
		if (!ft_strcmp("-dump", av[i]) && ft_nbrisinteger(av[++i]))
			vm->dump = ft_atoi(av[i]);
		else
		{
			save_champ(av[i], vm->nb_champ, vm);
			vm->nb_champ++;
		}
	}
	ft_check_champ_numb(vm->champions, vm->nb_champ);
	return (1);
}
//else if (!ft_strcmp("-n", av[i]) && ft_nbrisinteger(av[++i]))
//	nb_prog = ft_atoi(av[i]);
