/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 11:39:59 by cboutier          #+#    #+#             */
/*   Updated: 2021/10/29 16:10:33 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

t_token	*ft_go_forward(t_token *list)
{
	if (!list)
		return (0);
	while (list && (list->token_id == S_LESS || list->token_id == D_LESS
			|| list->token_id == S_GREATER || list->token_id == D_GREATER))
	{
		if (list->token_id == S_LESS || list->token_id == D_LESS
			|| list->token_id == S_GREATER || list->token_id == D_GREATER)
		{
			if (list->next)
				list = list->next;
			if (list->token_id == END_OF_ARG)
				list = list->next;
			if (list && list->next)
				list = list->next;
			if (list && list->next && list->token_id == END_OF_ARG)
				list = list->next;
		}
	}
	return (list);
}

int	ft_count_arg(t_token *list, t_token *tmp, int counter)
{
	while (list && list->token_id != PIPE)
	{
		while (list && list->token_id != PIPE && list->token_id != S_LESS
			&& list->token_id != D_LESS && list->token_id != S_GREATER
			&& list->token_id != D_GREATER)
		{
			if (list->token_id != END_OF_ARG)
				counter++;
			list = list->next;
		}
		if (list && list->next)
			list = ft_go_forward(list);
	}
	list = tmp;
	while (list && list->token_id != PIPE)
	{
		if ((list->token_id == ARG || list->token_id == ENV)
			&& list->str && list->str[0] == '-')
			counter++;
		list = list->next;
	}
	return (counter);
}

t_token	*ft_go_to_arg_zero(t_token *list, char **arg)
{
	while (ft_strcmp(list->str, arg[0]) != 0)
		list = list->next;
	return (list);
}
