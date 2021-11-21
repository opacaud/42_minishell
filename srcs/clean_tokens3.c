/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_tokens3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 09:49:24 by cboutier          #+#    #+#             */
/*   Updated: 2021/10/29 16:11:39 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	ft_clean_tokens_loop4(t_token *list, t_env *env)
{
	while (list)
	{
		if (list->str == NULL)
			list = list->next;
		if (list->next)
			if (list->next->next)
				if (ft_strcmp(list->str, "export") == 0
					&& list->next->next->str
					&& ft_strchr(list->next->next->str, '=')
					&& list->next->next->str[0] != '=')
					list = ft_split_export_egal(list->next->next);
		if ((list->token_id == ENV || list->token_id == D_QUOTE)
			&& list->str[0] == '$' && list->str[1])
			ft_clean_tokens_loop4_2(list, env);
		if (list->token_id == ENV && list->next->token_id == ARG)
		{
			if (!list->str)
				list->str = ft_strdup(list->next->str);
			else
				list = ft_dup_and_join(list);
			ft_lstdelnext(list);
		}
		list = list->next;
	}
}

void	ft_clean_tokens_loop5_2(t_token *list, t_env *env, int *joined)
{
	char	*tmp;
	char	*res;

	if (list->next->str && ((list->next->token_id == ARG
				|| list->next->token_id == S_QUOTE
				|| list->next->token_id == D_QUOTE)
			|| (list->next->token_id == ENV
				&& list->next->str[0] != '$')))
	{
		tmp = ft_strdup(list->str);
		free(list->str);
		list->str = ft_strjoin(tmp, list->next->str);
		ft_env_in_dq_trad(list);
		if (list->str)
			ft_lstdelnext(list);
		free(tmp);
		res = NULL;
		if (check_path(env, list->str, &res))
			list->token_id = ARG;
		free(res);
		*joined = 1;
	}
}

void	ft_clean_tokens_loop5(t_token *list, t_token *first, t_env *env)
{
	int		joined;

	while (list)
	{
		while (list->str == NULL)
			list = list->next;
		while (list && list->next && ft_join_remaining(first))
		{
			joined = 0;
			if (ft_strlen(list->str) > 0 && (list->token_id == ARG
					|| list->token_id == S_QUOTE
					|| list->token_id == D_QUOTE) && list->str[0] != '$')
				ft_clean_tokens_loop5_2(list, env, &joined);
			if (joined == 1)
				list = first;
			else
				list = list->next;
		}
		list = list->next;
	}
}

void	ft_clean_tokens_loop6(t_token *list, t_token *first)
{
	int		joined;

	while (list)
	{
		while (list && list->next && ft_join_remaining_env(first))
		{
			joined = 0;
			while (list->str == NULL)
				list = list->next;
			if (list->token_id == ENV)
				if (list->next->token_id == ENV)
					ft_env_join(list, &joined);
			if (joined == 1)
				list = first;
			else
				list = list->next;
		}
		if (list)
			list = list->next;
	}
}

int	ft_clean_tokens_loop6_2(t_token *list, t_token *first)
{
	while (list && list->next)
	{
		if (list && (list->token_id == S_LESS || list->token_id == D_LESS
				|| list->token_id == S_GREATER || list->token_id == D_GREATER))
		{
			if (list->next)
				list = list->next;
			else
				return (-1);
			while (list && list->next && list->token_id == END_OF_ARG)
				list = list->next;
			if (!list->next || (list->token_id == S_LESS
					|| list->token_id == D_LESS
					|| list->token_id == S_GREATER
					|| list->token_id == D_GREATER
					|| list->token_id == PIPE))
				return (-1);
		}
		list = list->next;
	}
	return (ft_clean_tokens_loop6_3(first));
}
