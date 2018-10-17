/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouisy- <alouisy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 14:54:40 by alouisy-          #+#    #+#             */
/*   Updated: 2018/10/09 14:54:43 by alouisy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

static int			get_champ_nb(int nb_prog, t_process *begin_list)
{
	t_process	*process;
	int			nb;

	nb = 1;
	if (nb_prog == -1)
		while (1 || nb <= nb_prog)
		{
			process = begin_list;
			while (process)
			{
				if (process->r[0] == nb)
					break ;
				process = process->next;
			}
			if (!process)
				return (nb);
			nb++;
		}
	return (nb_prog);
}

static void		init_process(t_process *process, int nb_prog, int nb_champ, t_pvm *prms)
{
	int		i;

	process->next = NULL;
	process->r[0] = get_champ_nb(nb_prog, prms->processes);
	process->champ_nbr = process->r[0];
	process->pid = nb_champ;
	process->carry = 0;
/*	process->nb_live = 0;
	process->cycles_wo_live = 0;
*/	process->instruction = -1;
	i = 1;
	while (i < REG_NUMBER)
		process->r[i++] = 0;
	i = 0;
/*	while (i < 3)
	{
		process->param[i] = 0;
		process->param_type[i++] = 0;
	}*/
}

t_process	*parse_process(char *path, int nb_prog, t_pvm *prms)
{
	int			fd;
	t_process	*process;
	static int	nb_champ;

	if ((process = (t_process *)malloc(sizeof(t_process))))
	{
		if ((fd = open(path, O_RDONLY)) != -1)
		{
			ft_putendl("Parse 1 init Process");
			init_process(process, nb_prog, nb_champ++, prms);
			ft_putendl("Parse 2 Header");
			parse_process_header(process, fd, path);
			ft_putendl("Parse 3 Prog");
			parse_process_prog(process, fd);
			ft_putendl("Parse 4 Finish");
			close(fd);
		}
		else
			exit_error(ft_strjoin("Can't read source file ", path), 1);
	}
	else
		exit_error("ERROR while trying to malloc", 1);
	return (process);
}
