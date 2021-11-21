/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 09:32:53 by cboutier          #+#    #+#             */
/*   Updated: 2021/09/23 10:17:59 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

static void	str_cpy(char *dest, char *src, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
}

static int	len_word(char *word, char sep)
{
	int	i;

	i = 0;
	while (word[i])
	{
		if (word[i] == sep)
			break ;
		i++;
	}
	return (i);
}

int	count_words(char *str, char sep)
{
	int	i;
	int	count;
	int	seen_sep;

	i = 0;
	count = 0;
	seen_sep = 1;
	while (str[i])
	{
		if (str[i] == sep)
			seen_sep = 1;
		else if (seen_sep)
		{
			count++;
			seen_sep = 0;
		}
		i++;
	}
	return (count);
}

char	**free_split(char **words, int i)
{
	int	j;

	j = 0;
	while (j < i)
		free(words[j++]);
	free(words);
	return (NULL);
}

char	**ft_split(char *s, char c)
{
	char	**words;
	size_t	i;

	if (!s)
		return (NULL);
	words = malloc(sizeof(char *) * (count_words((char *)s, c) + 1));
	if (!words)
		return (NULL);
	words[count_words((char *)s, c)] = 0;
	i = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			words[i] = malloc(sizeof(char) * (len_word((char *)s, c) + 1));
			if (!words[i])
				return (free_split(words, i));
			str_cpy(words[i], (char *)s, len_word((char *)s, c));
			i++;
			s = s + len_word((char *)s, c);
		}
	}
	return (words);
}
