/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 19:47:47 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/10/29 19:26:36 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** print one case
*/

void	print_case(WINDOW *win, int i, int pos, unsigned char *str)
{
	if (str[i] == 0)
	{
		wattron(win, COLOR_PAIR(0));
		mvwprintw(win, (pos) / 64 + 1, ((pos) % 64) * 3 + 1, "00");
		wattroff(win, COLOR_PAIR(0));
	}
	else
		mvwprintw(win, (pos) / 64 + 1, ((pos) % 64) * 3 + 1, "%.2hhx", str[i]);
}
