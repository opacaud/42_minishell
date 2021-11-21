/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_tokens4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 15:10:57 by cboutier          #+#    #+#             */
/*   Updated: 2021/10/29 16:11:47 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	ft_clean_tokens_loop6_3(t_token *first)
{
	if (ft_count_pipes(first) > 0)
	{
		if (first->token_id == PIPE)
			return (-1);
		while (first)
		{
			while (first && first->next && first->token_id != PIPE)
				first = first->next;
			first = first->next;
			while (first && first->next && first->token_id == END_OF_ARG)
				first = first->next;
			if (first && (!first->next || first->token_id == PIPE))
				return (-1);
			else if (first && first->next)
				first = first->next;
		}
	}
	return (0);
}

void	ft_clean_tokens_loop7(t_token *list)
{
	while (list && list->next && list->next->next)
	{
		if (list->token_id == END_OF_ARG && !list->next->str
			&& list->next->token_id == ENV
			&& list->next->next->token_id == END_OF_ARG)
		{
			ft_lstdelnext(list);
			ft_lstdelnext(list);
		}
		list = list->next;
	}
}

void	ft_clean_tokens_loop8(t_token *list)
{
	while (list && list->next)
	{
		if ((list->token_id == S_LESS || list->token_id == D_LESS
				|| list->token_id == S_GREATER
				|| list->token_id == D_GREATER || list->token_id == PIPE)
			&& list->next->token_id != END_OF_ARG)
		{
			list->next = ft_insert_elem(" ", END_OF_ARG, list->next);
		}
		list = list->next;
	}
}
