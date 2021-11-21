/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 16:12:38 by cboutier          #+#    #+#             */
/*   Updated: 2021/10/29 16:12:45 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

t_token	*ft_echo_n(t_token *list, int *n)
{
	while (ft_strcmp(list->str, "-n") == 0
		|| (ft_strncmp(list->str, "-n", 2) == 0
			&& ft_has_only_n(list->str)))
	{
		*n = 1;
		if (list->next->next)
			list = list->next->next;
		else
		{
			while (list)
				list = list->next;
			return (list);
		}
	}
	return (list);
}

t_token	*ft_second_echo_loop(t_token *list)
{
	if (!list)
		return (0);
	while (list->next->next)
	{
		if (list->token_id == PIPE)
			return (list);
		if ((list->next->next->token_id == ARG
				|| list->next->next->token_id == ENV)
			&& (list->token_id != D_GREATER && list->token_id != S_GREATER
				&& list->token_id != S_LESS && list->token_id != D_LESS))
		{
			ft_putstr_fd(" ", STDOUT_FILENO);
			ft_putstr_fd(list->next->next->str, STDOUT_FILENO);
		}
		list = list->next;
	}
	return (list);
}
