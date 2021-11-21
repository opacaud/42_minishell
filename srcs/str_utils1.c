/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 09:46:52 by cboutier          #+#    #+#             */
/*   Updated: 2021/09/27 16:01:12 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(char *str)
{
	char	*dst;
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	dst = malloc(ft_strlen(str) * sizeof(char) + 1);
	if (dst == 0)
		return (NULL);
	while (str[i])
	{
		dst[i] = str[i];
		i++;
	}
	dst[i] = 0;
	return (dst);
}

char	*ft_strndup(char *str, int start, int counter)
{
	char	*res;
	int		i;

	res = malloc(sizeof(char) * (counter + 2));
	if (res == 0)
		return (0);
	i = 0;
	while (i <= counter)
	{
		res[i] = str[start + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_strcpy(char *src, char *dest)
{
	unsigned int	i;

	if (!src)
		return (0);
	i = 0;
	while (src[i] != 0)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strncpy(char *src, char *dest, unsigned int n)
{
	unsigned int	i;

	if (!src || !n)
		return (0);
	i = 0;
	while (src[i] != 0 && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
