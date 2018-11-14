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
	int	fd;
	int	i;

	i = vm->nb_champ;
	nb = get_champ_nb(nb, vm->champions);
	init_champion(vm, nb);
	if ((fd = open(path, O_RDONLY)) == -1)
		return (ft_strerror(ft_strjoin("Can't read source file ", path), 1));
	if (!parse_champion_header(&(vm->champions[i]), fd, path))
		return (0);
	if (!parse_champion_prog(&(vm->champions[i]), fd))
		return (0);
	close(fd);
	if (vm->champions[i].prog[0] == 0)
		return (0);
	return (1);
}
