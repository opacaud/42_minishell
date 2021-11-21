/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 14:20:09 by cboutier          #+#    #+#             */
/*   Updated: 2021/10/29 16:13:00 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

t_env	*ft_update_shlvl(t_env **env)
{
	int		shlvl_value;
	t_env	*tmp;

	tmp = *env;
	while (*env)
	{
		if (ft_strcmp((*env)->name, "SHLVL=") == 0)
		{
			shlvl_value = ft_atoi((*env)->value);
			shlvl_value++;
			free((*env)->value);
			(*env)->value = ft_itoa(shlvl_value);
		}
		*env = (*env)->next;
	}
	return (tmp);
}

int	ft_counter_till_sep(char *str, int i)
{
	int	counter;

	counter = 0;
	while (str[i] && is_sep(str, i) == 0)
	{
		counter++;
		i++;
	}
	return (counter);
}

t_token	*ft_change_env3(t_token *list, t_token *first, char *str, int *i)
{
	t_token	*tmp;
	int		start;
	int		cnt;

	if (str[(*i)] && str[(*i)] == ' ')
	{
		while (list && list->next && list->next->token_id != END_OF_ARG)
			list = list->next;
		tmp = list->next;
		list->next = ft_insert_elem(ft_strdup(" "), ARG, tmp);
	}
	else
	{
		start = (*i);
		(*i)++;
		cnt = ft_counter_till_sep(str, (*i));
		while (list && list->next && list->next->token_id != END_OF_ARG)
			list = list->next;
		tmp = list->next;
		list->next = ft_insert_elem(ft_strndup(str, start, cnt), D_QUOTE, tmp);
		(*i) = start + cnt;
	}
	list = first;
	(*i)++;
	return (list);
}

t_token	*ft_change_env2(t_token *list, char *str)
{
	int		i;
	t_token	*first;

	i = 0;
	first = list;
	while (str[i])
	{
		if (i == 0 && str[i] != '$')
			while (str[i] && str[i] != '$')
				i++;
		else
			list = ft_change_env3(list, first, str, &i);
	}
	return (list);
}

int	ft_change_env(t_token *list, char *str)
{
	t_token	*tmp;

	tmp = list->next;
	list->next = ft_insert_elem(" ", END_OF_ARG, tmp);
	list = ft_change_env2(list, str);
	while (list && list->next && list->next->token_id != END_OF_ARG)
		list = list->next;
	ft_lstdelnext(list);
	while (list->next)
		list = list->next;
	if (list->token_id != END_OF_ARG)
		list->next = ft_insert_elem(" ", END_OF_ARG, NULL);
	return (0);
}
