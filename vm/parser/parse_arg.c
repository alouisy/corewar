/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouisy- <alouisy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 14:51:21 by alouisy-          #+#    #+#             */
/*   Updated: 2018/10/25 19:03:41 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

static inline int	ft_check_champ_numb(t_list *champions, int nb)
{
	t_list	*tmp;
	t_list	*tmp2;

	ft_putendl("Checking Champ Pos&Stuff...");
	if (nb > 4)
		return (ft_strerror("ERROR (MORE THAN 4 CHAMPIONS)", 0));
	tmp = champions;
	while (tmp)
	{
		tmp2 = tmp->next;
		while (tmp2)
		{
			if ((CHAMPION(tmp))->nbr == (CHAMPION(tmp2))->nbr)
				return (ft_strerror("ERROR (2 CHAMPIONS WITH THE SAME NUMBER)", 0));
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
	ft_putendl("Checking Completed !");
	return (1);
}

inline int			save_champ(char *path, int nb_prog, t_pvm *vm)
{
	t_list		*champion;
	t_list		*node;
	t_process	process;

	if ((champion = parse_champion(path, nb_prog, vm)))
	{
		init_process(&process, -1, vm);	
		if (!(node = ft_lstnew(&process, sizeof(process))))
			return (ft_strerror("Malloc fail", 0));
		ft_putendl("One Champ Save...");
		ft_lstadd(&vm->champions, champion);
		ft_lstadd(&vm->processes, node);
		ft_putendl("Save Completed !");
	}
	else
		return (0);
	return (1);
}

inline int			parse_arg(t_pvm *vm, int ac, char **av)
{
	int	i;

	i = 0;
	while (++i < ac)
	{
		if (!ft_strcmp("-dump", av[i]) && ft_nbrisinteger(av[++i]))
			vm->dump = ft_atoi(av[i]);
		else
		{
			if (!save_champ(av[i], vm->nb_champ, vm))
				return(0);
			vm->nb_champ++;
		}
	}
	return (ft_check_champ_numb(vm->champions, vm->nb_champ));
}
//else if (!ft_strcmp("-n", av[i]) && ft_nbrisinteger(av[++i]))
//	nb_prog = ft_atoi(av[i]);
