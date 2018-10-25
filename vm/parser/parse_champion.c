/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_champion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouisy- <alouisy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 14:54:40 by alouisy-          #+#    #+#             */
/*   Updated: 2018/10/25 19:06:40 by jgroc-de         ###   ########.fr       */
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

t_list	*parse_champion(char *path, int nb_prog, UNUSED t_pvm *vm)
{
	int			fd;
	t_champion	champion;
	t_list		*node;
	int			out;

	node = NULL;
	out = 0;
	if ((fd = open(path, O_RDONLY)) != -1)
	{
		init_champion(&champion, nb_prog);
		if (parse_champion_header(&champion, fd, path)
			&& parse_champion_prog(&champion, fd))
			out = 1;
		close(fd);
		if (out && !(node = ft_lstnew((&champion), sizeof(t_champion))))
			out = ft_strerror("ERROR while trying to malloc", 0);
	}
	else
		ft_strerror(ft_strjoin("Can't read source file ", path), 1);
	return (out? node : NULL);
}
