/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 15:01:31 by cboutier          #+#    #+#             */
/*   Updated: 2021/10/05 13:57:18 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

char	*ft_charjoin(char *s1, char c)
{
	size_t	i;
	char	*dst;
	int		size;

	if (!s1 || !c)
		return (NULL);
	i = 0;
	size = ft_strlen(s1);
	dst = malloc(sizeof(char) * (size + 2));
	if (dst == 0)
		return (NULL);
	while (s1[i])
	{
		dst[i] = s1[i];
		i++;
	}
	dst[i] = c;
	i++;
	dst[i] = '\0';
	return (dst);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*dst;

	if (!s1)
		return (NULL);
	if (!s2)
		return (s1);
	i = 0;
	j = 0;
	dst = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (dst == 0)
		return (NULL);
	while (s1[i])
	{
		dst[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		dst[i + j] = s2[j];
		j++;
	}
	dst[i + j] = '\0';
	return (dst);
}

int	ft_join_remaining(t_token *list)
{
	while (list)
	{
		if ((list->token_id == ARG || list->token_id == S_QUOTE
				|| list->token_id == D_QUOTE)
			&& list->next && list->next->str
			&& ((list->next->token_id == ARG
					|| list->next->token_id == S_QUOTE
					|| list->next->token_id == D_QUOTE)
				|| (list->next->token_id == ENV && list->next->str[0] != '$')))
			return (1);
		list = list->next;
	}
	return (0);
}

int	ft_join_remaining_env(t_token *list)
{
	while (list)
	{
		if (list->token_id == ENV && list->next->token_id == ENV)
			return (1);
		list = list->next;
	}
	return (0);
}
