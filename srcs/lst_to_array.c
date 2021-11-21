/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_to_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 15:50:19 by cboutier          #+#    #+#             */
/*   Updated: 2021/10/29 16:14:19 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

char	**lst_to_array(t_token *list)
{
	char	**tab;
	int		i;
	int		size;

	if (!list)
		return (0);
	size = ft_lstsize(list);
	tab = malloc(sizeof(char *) * (size + 1));
	if (!tab)
		return (0);
	i = 0;
	while (i < size)
	{
		while (list->next && (list->token_id == END_OF_ARG || !list->str))
			list = list->next;
		if (list->token_id == PIPE)
			break ;
		tab[i] = NULL;
		if (list && list->token_id != END_OF_ARG)
			tab[i] = ft_strdup(list->str);
		i++;
		list = list->next;
	}
	tab[i] = 0;
	return (tab);
}

char	**env_to_array(t_env *env)
{
	char	**tab;
	int		i;
	int		size;

	if (!env)
		return (0);
	size = ft_envsize(env);
	tab = malloc(sizeof(char *) * (size + 1));
	if (!tab)
		return (0);
	i = 0;
	while (i < size)
	{
		tab[i] = ft_strjoin(env->name, env->value);
		i++;
		env = env->next;
	}
	tab[i] = 0;
	return (tab);
}
