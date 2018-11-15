/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libprintf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 17:02:42 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/11/15 12:09:01 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBPRINTF_H
# define LIBPRINTF_H

# include "../../libft.h"
# include <stdio.h>

# define SIZE "hHlLjz"

/*
**	stuct used to store options
*/

typedef struct	s_printf
{
	char	option[5];
	int		width;
	int		precision;
	char	size;
	int		result;
	size_t	index;
	char	*str;
	char	*base;
}				t_printf;

/*
**	stucture
*/

typedef struct	s_option
{
	char	*s;
	void	(*fct)(const char **, t_printf*);
}				t_option;

typedef struct	s_conv
{
	char	*(*fct)(va_list *, t_printf *);
}				t_conv;

/*
**	fonctions in order of appearance
*/

int				ft_printf(const char *restrict format, ...);
void			init_t_printf(t_printf *all);
void			init_ft_conv(t_conv *p);
int				ft_option(const char **format, t_printf *all);

/*
** option evaluation functions
*/

void			ft_inc_width(const char **f, t_printf *p);
void			ft_inc_acc(const char **f, t_printf *p);
void			ft_inc_size(const char **f, t_printf *p);
void			ft_conv_index(const char **f, t_printf *p);

/*
**	conversion's functions
*/

char			*ft_conv_s(va_list *ap, t_printf *all);
char			*ft_conv_ls(va_list *arg_var, t_printf *all);
char			*ft_conv_d(va_list *ap, t_printf *all);
char			*ft_conv_oux(va_list *ap, t_printf *all);
char			*ft_conv_p(va_list *ap, t_printf *all);
char			*ft_conv_c(va_list *ap, t_printf *all);
char			*ft_conv_lc(va_list *arg_var, t_printf *all);
char			*ft_conv_percent(va_list *arg_var, t_printf *all);
char			*ft_conv_bin(va_list *arg_var, t_printf *all);
char			*ft_conv_lbin(va_list *arg_var, t_printf *all);
char			*ft_conv_else(va_list *ap, t_printf *all);

/*
**	option's functions
*/

char			*ft_width(t_printf *all);
char			*ft_precision_str(t_printf *all);
char			*ft_precision_digit(t_printf *all);
void			ft_zero(t_printf *all);
char			*ft_plus(t_printf *all);
char			*ft_hash(t_printf *all);

/*
**	size's functions for 'd' conversion
*/

void			init_ft_d_size(t_conv *conv);
char			*ft_d_size_h(va_list *ap, t_printf *all);
char			*ft_d_size_hh(va_list *ap, t_printf *all);
char			*ft_d_size_l(va_list *ap, t_printf *all);
char			*ft_d_size_ll(va_list *ap, t_printf *all);
char			*ft_d_size_j(va_list *ap, t_printf *all);
char			*ft_d_size_z(va_list *ap, t_printf *all);
char			*ft_d_size_(va_list *ap, t_printf *all);

/*
**	size's functions for 'd' conversion
*/

void			init_ft_oux_size(t_conv *conv);
char			*ft_oux_size(uintmax_t nbr, t_printf *all);
char			*ft_oux_size_h(va_list *ap, t_printf *all);
char			*ft_oux_size_hh(va_list *ap, t_printf *all);
char			*ft_oux_size_l(va_list *ap, t_printf *all);
char			*ft_oux_size_ll(va_list *ap, t_printf *all);
char			*ft_oux_size_j(va_list *ap, t_printf *all);
char			*ft_oux_size_z(va_list *ap, t_printf *all);
char			*ft_oux_size_(va_list *ap, t_printf *all);

#endif
