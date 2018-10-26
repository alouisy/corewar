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

inline int	parse_champion(char *path, int nb, t_pvm *vm)
{
	t_champion	champion;
	t_list		*node;
	int			fd;

	init_champion(&champion, nb);
	if ((fd = open(path, O_RDONLY)) == -1)
		return (ft_strerror(ft_strjoin("Can't read source file ", path), 1));
	if (!parse_champion_header(&champion, fd, path))
		return (0);
	if (!parse_champion_prog(&champion, fd))
		return (0);
	close(fd);
	if (champion.nbr == -1)
		return(0);
	if (!(node = ft_lstnew((&champion), sizeof(t_champion))))
		return (ft_strerror("ERROR while trying to malloc", 0));
	ft_lstadd(&vm->champions, node);
	return (1);
}
