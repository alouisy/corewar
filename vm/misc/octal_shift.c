/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouisy- <alouisy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 17:41:07 by alouisy-          #+#    #+#             */
/*   Updated: 2018/11/15 12:36:33 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

int		octal_shift(unsigned char ocp, unsigned char label_size,
			unsigned char nb_param)
{
	int shift;

	shift = 2;
	while (++nb_param <= 4)
		ocp >>= 2;
	while (ocp)
	{
		shift += ((ocp & 0b11) == 0b01) ? 1 : 0;
		shift += ((ocp & 0b11) == 0b11) ? 2 : 0;
		shift += ((ocp & 0b11) == 0b10) ? label_size : 0;
		ocp >>= 2;
	}
	return (shift);
}
