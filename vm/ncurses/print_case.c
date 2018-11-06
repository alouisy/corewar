/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 19:47:47 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/10/31 16:17:52 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** print one case
*/

void	print_case(WINDOW *win, int pos, unsigned char c)
{
	if (c == 0)
	{
		mvwprintw(win, (pos) / 64 + 1, ((pos) % 64) * 3 + 1, "00");
	}
	else
		mvwprintw(win, (pos) / 64 + 1, ((pos) % 64) * 3 + 1, "%.2hhx", c);
}

void	print_4case(WINDOW *win, int pos, unsigned char *str)
{
	int i;

	i = 0;
	while (i < 4)
	{
		if (str[i] == 0)
			mvwprintw(win, (pos) / 64 + 1, ((pos) % 64) * 3 + 1, "00");
		else
			mvwprintw(win, (pos) / 64 + 1, ((pos) % 64) * 3 + 1, "%.2hhx ", str[i]);
		i++;
	}
}
