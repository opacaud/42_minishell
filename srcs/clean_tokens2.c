/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_tokens2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 11:36:56 by cboutier          #+#    #+#             */
/*   Updated: 2021/10/29 16:11:24 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	ft_clean_tokens_loop1_3(t_token *list)
{
	while (list->token_id == ENV)
	{
		list->token_id = ARG;
		list = list->next;
	}
}

t_token	*ft_clean_tokens_loop1_2(t_token *list)
{
	char	*tmp;

	if (list->next)
		list = list->next;
	if (!list->next || list->token_id == D_LESS || list->token_id == S_LESS)
		return (list);
	while (list && list->next && list->token_id == END_OF_ARG)
		list = list->next;
	ft_clean_tokens_loop1_3(list);
	while (list->next && list->next->token_id != END_OF_ARG
		&& !ft_is_redir(list->next->str) && list->next->token_id != PIPE)
	{
		tmp = ft_strjoin(list->str, list->next->str);
		free(list->str);
		list->str = ft_strdup(tmp);
		ft_lstdelnext(list);
		free(tmp);
	}
	return (list);
}

void	ft_clean_tokens_loop2(t_token *list, t_token *first)
{
	if (!list)
		return ;
	while (list)
	{
		if (list && list->token_id == D_QUOTE && ft_has_squote(list->str)
			&& ft_strlen(list->str) > 1)
			list = ft_s_in_dquotes(list, first);
		list = list->next;
	}
}

void	ft_clean_tokens_loop3(t_token *list)
{
	char	*tmp;

	if (!list)
		return ;
	while (list)
	{
		if (list->token_id == D_QUOTE && ft_has_env(list->str))
		{
			ft_change_env(list, list->str);
			if (list->str[0] != '$')
			{
				tmp = ft_strdup(list->str);
				free(list->str);
				list->str = ft_trim_first_arg(tmp);
				free(tmp);
			}
			else if (ft_strcmp(list->str, list->next->str) == 0)
				ft_lstdelnext(list);
			else
				list->str = free_str(list->str);
			while (list && list->next && list->next->token_id != END_OF_ARG)
				list = list->next;
		}
		list = list->next;
	}
}

void	ft_clean_tokens_loop4_2(t_token *list, t_env *env)
{
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;

	tmp1 = ft_strtrim(list->str, '$');
	tmp3 = ft_strtrim(tmp1, ' ');
	tmp2 = ft_getenv(tmp3, env);
	if (list->token_id == ENV && ft_has_slash(list->str))
		ft_expand_path_with_env(list, env);
	else if (tmp2 == 0
		&& list->token_id == D_QUOTE && list->next->token_id == END_OF_ARG)
		list->str = free_str(list->str);
	else if (list->token_id == ENV && list->str[1] == '?')
	{
		free(list->str);
		list->str = ft_itoa(g_exit_status);
	}
	else
	{
		free(list->str);
		list->str = tmp2;
		list->env_in_dq_trad = 1;
	}
	free(tmp1);
	free(tmp3);
}
