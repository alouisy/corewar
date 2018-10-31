/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 19:47:47 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/10/31 16:50:38 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** insert each champion's programme in left panel
*/

static char aux_hexa(int i)
{
	char *str;

	str = "0123456789abcdef";
	return (str[i]);
}

static void			aux_strncpy(char dest[CHAMP_MAX3], unsigned char *src, unsigned int len)
{
	unsigned int	i;

	i = 0;
	while (i < len)
	{
		dest[i * 3] = aux_hexa(src[i] / 16);
		dest[i * 3 + 1] = aux_hexa(src[i] % 16);
		dest[i * 3 + 2] = ' ';
		i++;
	}
}

static inline void	insert_champion(t_pvm *vm)
{
	unsigned int	i;
	int				pos;
	t_list			*node;
	char			str[CHAMP_MAX3];

	node = vm->champions;
	while (node)
	{
		pos = (CHAMPION(node))->vm_pos / 64;
		wattron(vm->nc.wleft, COLOR_PAIR((CHAMPION(node))->color));
		aux_strncpy(str, (CHAMPION(node))->prog, (CHAMPION(node))->header.prog_size);
		i = 0;
		while (i < (CHAMPION(node))->header.prog_size)
		{
			mvwprintw(vm->nc.wleft, 1 + pos++, 1, "%.192s", str + i * 3);	
			i += 64;
		}
		wattroff(vm->nc.wleft, COLOR_PAIR((CHAMPION(node))->color));
		node = node->next;
	}
}

/*
** first print of map with "00" only
*/

static inline void	init_map(t_pvm *vm)
{
	unsigned int	i;
	char			str[192];

	i = 0;
	while (i < 192)
	{
		if (i % 3 == 2)
			str[i] = ' ';
		else
			str[i] = '0';
		i++;
	}
	i = 0;
	while (i < 64)
	{
		mvwprintw(vm->nc.wleft, i + 1, 1, "%s", str);
		i++;
	}
}

void	init_left_panel(t_pvm *vm)
{
	init_map(vm);
	insert_champion(vm);
}
