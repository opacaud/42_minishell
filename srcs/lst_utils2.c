/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 10:41:32 by cboutier          #+#    #+#             */
/*   Updated: 2021/10/29 16:22:51 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	ft_lstsize(t_token *lst)
{
	int		i;
	t_token	*elem;

	i = 0;
	if (!lst)
		return (i);
	elem = lst;
	while (elem != NULL)
	{
		if (elem && elem->token_id != END_OF_ARG && elem->str)
			i++;
		elem = elem->next;
	}
	return (i);
}

void	ft_print_tokens(t_token *token)
{
	while (token != 0)
	{
		printf("str : [%s] | token_id : [%d] | env trad: [%d]\n",
			token->str, token->token_id, token->env_in_dq_trad);
		token = token->next;
	}
}

void	ft_print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("tab[%d] : [%s]\n", i, tab[i]);
		i++;
	}
}
