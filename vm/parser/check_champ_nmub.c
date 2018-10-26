/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouisy- <alouisy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 14:51:21 by alouisy-          #+#    #+#             */
/*   Updated: 2018/10/25 19:03:41 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

inline int	check_champ_numb(t_list *champions)
{
	t_list	*tmp;
	t_list	*tmp2;

	tmp = champions;
	while (tmp)
	{
		tmp2 = tmp->next;
		while (tmp2)
		{
			if ((CHAMPION(tmp))->nbr == (CHAMPION(tmp2))->nbr)
				return (ft_strerror("ERROR (2 CHAMPIONS WITH THE SAME NUMBER)", 0));
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
	ft_putendl("Checking Completed !");
	return (1);
}
