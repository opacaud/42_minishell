/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 11:24:16 by cboutier          #+#    #+#             */
/*   Updated: 2021/09/27 15:50:11 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

t_env	*new_env_elem(char *name, char *value)
{
	t_env	*elem;

	if (!name || !value)
		return (NULL);
	elem = malloc(sizeof(t_env));
	if (!elem)
		return (NULL);
	elem->next = 0;
	elem->name = name;
	elem->value = value;
	return (elem);
}

t_env	*ft_env_last(t_env *env)
{
	t_env	*elem;

	if (env == NULL)
		return (NULL);
	elem = env;
	while (elem->next != NULL)
		elem = elem->next;
	return (elem);
}

void	ft_env_add_back(t_env **env, char *name, char *value)
{
	t_env	*elem;

	if (env)
	{
		if (*env)
		{
			elem = ft_env_last(*env);
			elem->next = new_env_elem(name, value);
		}
		else
			*env = new_env_elem(name, value);
	}
}

int	ft_env_delnext(t_env *list)
{
	t_env	*tmp;

	if (!list)
		return (0);
	if (list)
	{
		tmp = list->next;
		if (list->next->next)
			list->next = list->next->next;
		else
			list->next = NULL;
		if (tmp->name)
		{
			free(tmp->name);
			tmp->name = NULL;
		}
		if (tmp->value)
		{
			free(tmp->value);
			tmp->value = NULL;
		}
		free(tmp);
	}
	tmp = NULL;
	return (0);
}

int	ft_envsize(t_env *env)
{
	int		i;
	t_env	*elem;

	i = 0;
	if (!env)
		return (i);
	elem = env;
	while (elem != NULL)
	{
		i++;
		elem = elem->next;
	}
	return (i);
}
