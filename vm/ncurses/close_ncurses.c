/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_ncurses.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 19:46:02 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/10/29 19:26:02 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

void	close_ncurses(void)
{
	endwin();
}
