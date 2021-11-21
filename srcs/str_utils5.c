/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 14:53:53 by cboutier          #+#    #+#             */
/*   Updated: 2021/09/29 09:50:17 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	ft_has_null(t_token *list)
{
	while (list)
	{
		if (ft_strlen(list->str) == 0)
			return (1);
		list = list->next;
	}
	return (0);
}

int	ft_has_several_env(char *str)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (str[i])
	{
		if (str[i] == '$')
			counter++;
		i++;
	}
	if (counter > 1)
		return (1);
	return (0);
}

int	ft_has_slash(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_trim_first_arg(char *str)
{
	int		i;
	int		counter;
	char	*res;

	i = 0;
	counter = 0;
	while (str[i] && str[i] != '$')
	{
		i++;
		counter++;
	}
	res = malloc(sizeof(char) * (counter + 1));
	if (res == 0)
		return (0);
	i = 0;
	while (str[i] && str[i] != '$')
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

t_token	*ft_dup_and_join(t_token *list)
{
	char	*tmp;

	tmp = ft_strdup(list->str);
	free(list->str);
	list->str = ft_strjoin(tmp, list->next->str);
	free(tmp);
	return (list);
}
