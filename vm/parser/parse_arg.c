/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouisy- <alouisy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 14:51:21 by alouisy-          #+#    #+#             */
/*   Updated: 2018/10/09 14:51:27 by alouisy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

static inline int		ft_check_champ_numb(t_pvm *prms)
{
	t_list	*process;
	char	check[prms->nb_champ + 1];
	int		i;
	int		j;

	i = -1;
	while (++i < prms->nb_champ)
		check[i] = 0;
	process = prms->processes;
	i = 0;
	while (process)
	{
		check[i] = (get_content(process))->r[0];
		process = process->next;
		i++;
	}
	i = -1;
	while (++i < prms->nb_champ)
	{
		j = -1;
		while (++j < prms->nb_champ)
			if (j != i && check[i] == check[j])
				return (1);
	}
	return (0);
}

static inline void		ft_last_check_champ(t_pvm *prms)
{
	if (prms->nb_champ > 4)
		exit_error("ERROR (MORE THAN 4 CHAMPIONS)", 1);
	if (ft_check_champ_numb(prms))
		exit_error("ERROR (2 CHAMPIONS WITH THE SAME NUMBER)", 1);
}

static inline void		save_champ(char *path, int nb_prog, t_pvm *prms)
{
	t_list	*process;

	if ((process = parse_process(path, nb_prog, prms)))
	{
		ft_putendl("One Champ Save...");
		ft_lstadd(&prms->processes, process);
		ft_putendl("Save Completed !");
	}
}

int				parse_arg(t_pvm *prms, int ac, char **av)
{
	int	i;
	int	nb_prog;

	i = 0;
	nb_prog = -1;
	while (++i < ac && prms->nb_champ < MAX_PLAYERS)
	{
		if (!ft_strcmp("-dump", av[i]) && ft_nbrisinteger(av[++i]))
			prms->dump = ft_atoi(av[i]);
		else if (!ft_strcmp("-n", av[i]) && ft_nbrisinteger(av[++i]))
			nb_prog = ft_atoi(av[i]);
		else
		{
			save_champ(av[i], nb_prog, prms);
			nb_prog = -1;
			prms->nb_champ++;
		}
	}
	ft_putendl("Checking Champ Pos&Stuff...");
	ft_last_check_champ(prms);
	ft_putendl("Checking Completed !");
	return (1);
}
