/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 18:20:03 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/10/18 19:26:55 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** aff comme … comme … affooo… non affaaaa… non affuuuuu? non plus. affouuuuuuu!
*/

void	ft_aff(t_pvm *pvm, t_process *process)
{
	char	c;

	(void)pvm;
	c = process->r[process->param[0]] % 256;
	ft_printf("%s: %c\n", process->header.prog_name, c);
	if (c == 0)
		process->carry = 1;
	else
		process->carry = 0;
}
