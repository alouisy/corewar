/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 14:11:00 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/02/14 16:25:00 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libprintf.h"

void	init_t_printf(t_printf *p)
{
	int i;

	i= 0;
	while (i < 5)
		p->option[i++] = 0;
	p->width = 0;
	p->precision = -1;
	p->size = 0;
	p->index = 16;
	p->str = NULL;
	p->base = "0123456789";
}

void	init_ft_conv(t_conv *conv)
{
	conv[0].fct = &ft_conv_s;
	conv[1].fct = &ft_conv_ls;
	conv[2].fct = &ft_conv_p;
	conv[3].fct = &ft_conv_d;
	conv[4].fct = &ft_conv_d;
	conv[5].fct = &ft_conv_d;
	conv[6].fct = &ft_conv_oux;
	conv[7].fct = &ft_conv_oux;
	conv[8].fct = &ft_conv_oux;
	conv[9].fct = &ft_conv_oux;
	conv[10].fct = &ft_conv_oux;
	conv[11].fct = &ft_conv_oux;
	conv[12].fct = &ft_conv_c;
	conv[13].fct = &ft_conv_lc;
	conv[14].fct = &ft_conv_bin;
	conv[15].fct = &ft_conv_lbin;
	conv[16].fct = &ft_conv_percent;
	conv[17].fct = &ft_conv_else;
}

void	init_ft_d_size(t_conv *conv)
{
	conv[0].fct = &ft_d_size_h;
	conv[1].fct = &ft_d_size_hh;
	conv[2].fct = &ft_d_size_l;
	conv[3].fct = &ft_d_size_ll;
	conv[4].fct = &ft_d_size_j;
	conv[5].fct = &ft_d_size_z;
	conv[6].fct = &ft_d_size_;
}

void	init_ft_oux_size(t_conv *conv)
{
	conv[0].fct = &ft_oux_size_h;
	conv[1].fct = &ft_oux_size_hh;
	conv[2].fct = &ft_oux_size_l;
	conv[3].fct = &ft_oux_size_ll;
	conv[4].fct = &ft_oux_size_j;
	conv[5].fct = &ft_oux_size_z;
	conv[6].fct = &ft_oux_size_;
}
