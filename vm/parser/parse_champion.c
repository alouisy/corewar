/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_champion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouisy- <alouisy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 14:54:40 by alouisy-          #+#    #+#             */
/*   Updated: 2018/10/27 19:37:13 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

inline int	parse_champion(char *path, int nb, t_pvm *vm)
{
	t_champion	champion;
	t_list		*node;
	int			fd;

	nb = get_champ_nb(nb, vm->champions);
	init_champion(&champion, nb, vm->nb_champ + 1);
	if ((fd = open(path, O_RDONLY)) == -1)
		return (ft_strerror(ft_strjoin("Can't read source file ", path), 1));
	if (!parse_champion_header(&champion, fd, path))
		return (0);
	if (!parse_champion_prog(&champion, fd))
		return (0);
	close(fd);
	if (champion.prog[0] == 0)
		return (0);
	if (!(node = ft_lstnew((&champion), sizeof(t_champion))))
		return (ft_strerror("ERROR while trying to malloc", 0));
	ft_lstadd(&vm->champions, node);
	return (1);
}
