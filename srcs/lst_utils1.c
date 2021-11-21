/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 08:49:32 by cboutier          #+#    #+#             */
/*   Updated: 2021/10/29 16:14:28 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

t_token	*new_elem(char *str, int token_id)
{
	t_token	*elem;

	if (!str)
		return (NULL);
	elem = malloc(sizeof(t_token));
	if (!elem)
		return (NULL);
	elem->next = 0;
	elem->str = str;
	elem->token_id = token_id;
	elem->env_in_dq_trad = 0;
	return (elem);
}

t_token	*ft_insert_elem(char *str, int token_id, t_token *tmp)
{
	t_token	*elem;

	elem = malloc(sizeof(t_token));
	if (!elem)
		return (NULL);
	elem->str = str;
	elem->token_id = token_id;
	elem->env_in_dq_trad = 0;
	elem->next = tmp;
	return (elem);
}

t_token	*ft_lstlast(t_token *lst)
{
	t_token	*elem;

	if (lst == NULL)
		return (NULL);
	elem = lst;
	while (elem->next != NULL)
		elem = elem->next;
	return (elem);
}

void	ft_lstadd_back(t_token **lst, char *str, int token_id)
{
	t_token	*elem;

	if (lst)
	{
		if (*lst)
		{
			elem = ft_lstlast(*lst);
			elem->next = new_elem(str, token_id);
		}
		else
			*lst = new_elem(str, token_id);
	}
}

int	ft_lstdelnext(t_token *list)
{
	t_token	*tmp;

	if (!list)
		return (0);
	if (list)
	{
		tmp = list->next;
		list->next = list->next->next;
		if (tmp->str && (tmp->token_id == S_QUOTE || tmp->token_id == D_QUOTE
				|| tmp->token_id == ARG || tmp->token_id == ENV))
		{
			free(tmp->str);
			tmp->str = NULL;
		}
		free(tmp);
	}
	tmp = NULL;
	return (0);
}
