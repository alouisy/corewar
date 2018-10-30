/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 12:13:48 by zcugni            #+#    #+#             */
/*   Updated: 2018/06/29 18:37:08 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	if_return(char **rest, char **line, int index)
{
	*line = ft_strndup(*rest, index);
	if (index == (int)ft_strlen(*rest) - 1)
		ft_memdel((void **)rest);
	else
		ft_memmove(*rest, &((*rest)[index + 1]),
				ft_strlen(&((*rest)[index + 1])) + 1);
	return (1);
}

char		*ft_strncpyat(char *dst, const char *src, int shift)
{
	int i;

	i = 0;
	while (src[i])
	{
		dst[i + shift] = src[i];
		i++;
	}
	dst[i + shift] = 'a';
	return (dst);
}

static char	*ft_strjoin_overlap(char **s1, char **s2)
{
	size_t	i;
	size_t	j;
	char	*str;
	int		len_1;
	int		len_2;

	if (!*s2)
		return (NULL);
	if (!*s1)
		str = ft_strdup(*s2);
	else
	{
		i = 0;
		len_1 = ft_strlen(*s1);
		len_2 = ft_strlen(*s2);
		str = malloc(len_1 + len_2 + 1);
		ft_lstadd(&g_to_free, ft_lstnew_p(str, 0, 0));
		if (!str)
			exit_error("malloc error\n", MALLOC_ERR);
		ft_strncpyat(str, *s1, 0);
		ft_strncpyat(str, *s2, len_1);
		ft_memdel((void **)s1);
		str[len_1 + len_2] = '\0';
	}
	ft_memdel((void **)s2);
	return (str);
}

static int	stopped_reading(char **buff, int state, char **line, char **rest)
{
	free(*buff);
	if (state == 0)
	{
		if (!*rest)
			return (0);
		*line = ft_strdup(*rest);
		ft_strdel(rest);
		return (1);
	}
	else
		return (state);
}

int			get_next_line(const int fd, char **line, char separator)
{
	static char *rest = NULL;
	char		*buff;
	int			state;
	int			index;

	while (1)
	{
		if ((index = ft_strchri(rest, separator)) == -1)
		{
			buff = ft_strnew(BUFF_SIZE + 1);
			state = read(fd, buff, BUFF_SIZE);
			if (state <= 0)
				return (stopped_reading(&buff, state, line, &rest));
			rest = ft_strjoin_overlap(&rest, &buff);
		}
		else
			return (if_return(&rest, line, index));
	}
}
