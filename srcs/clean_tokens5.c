/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_tokens5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 11:52:01 by cboutier          #+#    #+#             */
/*   Updated: 2021/10/29 16:11:51 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	ft_clean_tokens_loop9_3(t_token *list, char *tmp1)
{
	char	*tmp2;

	tmp2 = NULL;
	if (list->token_id != END_OF_ARG)
	{
		tmp2 = ft_clean_env_value(tmp1);
		if (tmp1[0] == ' ')
			list->env_in_dq_trad = 2;
		list->str = ft_strtrim(tmp2, ' ');
		free(tmp2);
	}
}

void	ft_clean_tokens_loop9_2(t_token *list)
{
	char	*tmp1;

	tmp1 = NULL;
	if (list && list->str && ft_strlen(list->str) > 0)
	{
		tmp1 = ft_strdup(list->str);
		if (list->token_id != END_OF_ARG)
			free(list->str);
		if (list && list->next && (list->next->str
				&& ft_strlen(list->next->str) > 0
				&& ft_strcmp(list->next->str, " ") != 0))
			list->str = ft_clean_env_value(tmp1);
		else
			ft_clean_tokens_loop9_3(list, tmp1);
		free(tmp1);
	}
}

void	ft_clean_tokens_loop9(t_token *list)
{
	if (ft_strcmp(list->str, "echo") == 0)
	{
		while (list && list->next)
		{
			while (list && list->next && ((list->token_id != ENV
						&& list->env_in_dq_trad == 0) && list->token_id != ARG))
				list = list->next;
			if (list && list->next && list->token_id == END_OF_ARG)
				list = list->next;
			if (list && list->str && !(list->token_id == D_QUOTE
					&& list->env_in_dq_trad == 1) && !is_builtin(list->str))
				ft_clean_tokens_loop9_2(list);
			if (list->next)
				list = list->next;
		}
	}
}
