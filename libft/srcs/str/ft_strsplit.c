/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 18:10:05 by zcugni            #+#    #+#             */
/*   Updated: 2017/11/09 18:10:06 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int first_word;
	int nb_words;
	int i;

	i = 0;
	first_word = 1;
	nb_words = 0;
	while (s[i])
	{
		if (s[i] != c)
			if (first_word == 1 || s[i - 1] == c)
			{
				first_word = 0;
				nb_words++;
			}
		i++;
	}
	return (nb_words);
}

static int	add_words(char const *s, char c, char **tmp_arr)
{
	int		first_word;
	size_t	size;
	int		nb_words;
	size_t	i;

	nb_words = 0;
	first_word = 1;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
			if (first_word == 1 || s[i - 1] == c)
			{
				first_word = 0;
				size = 0;
				while (s[i + size] != c && s[i + size])
					size++;
				tmp_arr[nb_words] = ft_strndup(&s[i], size);
				if (!tmp_arr[nb_words])
					return (0);
				nb_words++;
			}
		i++;
	}
	return (1);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**tmp_arr;
	int		nb_words;
	int		i;

	if (!s)
		return (NULL);
	nb_words = count_words(s, c);
	tmp_arr = malloc(sizeof(char*) * (nb_words + 1));
	if (!tmp_arr)
		return (NULL);
	if (!add_words(s, c, tmp_arr))
	{
		i = 0;
		while (i < nb_words)
		{
			ft_memdel((void **)&tmp_arr[i]);
			i++;
		}
		ft_memdel((void **)tmp_arr);
		return (NULL);
	}
	tmp_arr[nb_words] = 0;
	return (tmp_arr);
}
