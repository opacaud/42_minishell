/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_tokens1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 10:34:00 by cboutier          #+#    #+#             */
/*   Updated: 2021/10/29 16:11:17 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	ft_clean_tokens_loop1(t_token *list)
{
	char	*tmp;

	if (!list)
		return ;
	while (list)
	{
		if (list->token_id == D_QUOTE || list->token_id == S_QUOTE)
		{
			tmp = ft_strdup(list->str);
			free(list->str);
			list->str = ft_delete_quotes(tmp, list->token_id);
			free(tmp);
		}
		else if (list->token_id == D_LESS)
			list = ft_clean_tokens_loop1_2(list);
		list = list->next;
	}
}

void	ft_change_env_levels(char **levels, t_env *env)
{
	int		i;
	char	*tmp;

	i = 0;
	while (levels[i])
	{
		if (levels[i][0] == '$')
		{
			tmp = ft_strtrim(levels[i], '$');
			free (levels[i]);
			levels[i] = ft_getenv(tmp, env);
			free (tmp);
		}
		i++;
	}
}

void	ft_expand_path_with_env(t_token *list, t_env *env)
{
	int		i;
	char	**levels;
	char	*tmp;

	levels = ft_split(list->str, '/');
	ft_change_env_levels(levels, env);
	i = -1;
	while (levels[++i])
	{
		tmp = ft_strdup(levels[i]);
		free (levels[i]);
		levels[i] = ft_charjoin(tmp, '/');
		free (tmp);
	}
	free(list->str);
	list->str = ft_strdup(levels[0]);
	i = 0;
	while (levels[++i])
	{
		tmp = ft_strdup(list->str);
		free (list->str);
		list->str = ft_strjoin(tmp, levels[i]);
		free(tmp);
	}
	ft_free_tab(levels);
}

int	ft_clean_tokens(t_token *list, t_env *env)
{
	t_token	*first;

	if (!list)
		return (0);
	first = list;
	ft_clean_tokens_loop1(list);
	ft_clean_tokens_loop2(list, first);
	ft_clean_tokens_loop3(list);
	ft_clean_tokens_loop4(list, env);
	ft_clean_tokens_loop5(list, first, env);
	ft_clean_tokens_loop6(list, first);
	if (ft_clean_tokens_loop6_2(list, first) == -1)
		return (-1);
	ft_clean_tokens_loop7(list);
	ft_clean_tokens_loop8(list);
	ft_clean_tokens_loop9(list);
	return (0);
}
