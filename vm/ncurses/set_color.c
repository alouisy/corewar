/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 19:47:47 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/10/29 19:27:43 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

inline void	set_color(void)
{
	start_color();
	init_pair(1, 1, COLOR_BLACK);
	init_pair(2, 2, COLOR_BLACK);
	init_pair(3, 3, COLOR_BLACK);
	init_pair(4, 4, COLOR_BLACK);
	init_pair(5, COLOR_BLACK, 1);
	init_pair(6, COLOR_BLACK, 2);
	init_pair(7, COLOR_BLACK, 3);
	init_pair(8, COLOR_BLACK, 4);
}
