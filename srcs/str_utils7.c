/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils7.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 10:02:32 by cboutier          #+#    #+#             */
/*   Updated: 2021/10/21 16:19:08 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
	write(fd, "\n", 1);
}

void	*ft_calloc(size_t count, size_t size)
{
	size_t	total;
	char	*dst;
	size_t	i;

	total = count * size;
	dst = malloc(total);
	if (dst == 0)
		return (NULL);
	i = 0;
	while (i < total)
	{
		dst[i] = 0;
		i++;
	}
	return (dst);
}

void	ft_sort_tab(char **env, int size)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < size)
	{
		j = i + 1;
		while (j < size)
		{
			if (env[i][0] > env[j][0])
			{
				tmp = ft_strdup(env[i]);
				free(env[i]);
				env[i] = ft_strdup(env[j]);
				free(env[j]);
				env[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

int	ft_in_squote(char *line, int *ptr_i)
{
	int	counter;
	int	i;

	if (!line)
		return (0);
	counter = 0;
	i = *ptr_i;
	while (line[i] && line[i] != '$')
	{
		if (line[i] == '\'')
			counter++;
		i++;
	}
	if (counter % 2 == 1)
		return (1);
	return (0);
}
