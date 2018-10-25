/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_champion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouisy- <alouisy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 14:54:40 by alouisy-          #+#    #+#             */
/*   Updated: 2018/10/25 17:05:52 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*int		get_champ_nb(int nb_prog, t_list *begin_list)
{
	t_list	*champion;
	int		nb;

	nb = 1;
	if (nb_prog == -1)
	{
		while (1 || nb <= nb_prog)
		{
			champion = begin_list;
			while (champion)
			{
				if ((PROCESS(champion))->r[0] == nb)
					break ;
				champion = champion->next;
			}
			if (!champion)
				return (nb);
			nb++;
		}
	}
	return (nb_prog);
}*/

void		init_champion(t_champion *champion, int nb_prog)
{
	champion->nbr = nb_prog;
	champion->vm_pos = 0;
	champion->l_live = 0;
	champion->nb_live = 0;
}

t_list	*parse_champion(char *path, int nb_prog, UNUSED t_pvm *vm)
{
	int			fd;
	t_champion	champion;
	t_list		*node;

	node = NULL;
	if ((fd = open(path, O_RDONLY)) != -1)
	{
		ft_putendl("Parse 1 init Champion");
		init_champion(&champion, nb_prog);
		ft_putendl("Parse 2 Header");
		parse_champion_header(&champion, fd, path);
		ft_putendl("Parse 3 Prog");
		parse_champion_prog(&champion, fd);
		ft_putendl("Parse 4 Finish");
		close(fd);
		node = ft_lstnew((void*)(&champion), sizeof(t_champion));
		if (!node)
			exit_error("ERROR while trying to malloc", 1);
	}
	else
		exit_error(ft_strjoin("Can't read source file ", path), 1);
	return (node);
}
