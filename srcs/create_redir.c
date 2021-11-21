/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:25:16 by cboutier          #+#    #+#             */
/*   Updated: 2021/10/28 14:25:19 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

t_token	*ft_advance_in_list(t_token *list)
{
	while (list && ((list->token_id != S_LESS && list->token_id != D_LESS
				&& list->token_id != S_GREATER
				&& list->token_id != D_GREATER && list->token_id != PIPE)
			|| list->token_id == END_OF_ARG))
		list = list->next;
	return (list);
}

void	ft_fill_redir(t_token *list, int size, char **redir_tab)
{
	int	i;

	i = 0;
	while (list && i < size)
	{
		if (list->token_id == PIPE)
			break ;
		redir_tab[i] = ft_strdup(list->str);
		list = list->next;
		while (list && list->token_id == END_OF_ARG)
			list = list->next;
		if (list && (list->token_id == ARG || list->token_id == S_QUOTE
				|| list->token_id == D_QUOTE || list->token_id == ENV))
			redir_tab[i + 1] = ft_strdup(list->str);
		else
		{
			i++;
			break ;
		}
		i += 2;
		list = ft_advance_in_list(list);
	}
	redir_tab[i] = 0;
}

char	**ft_create_redir(t_token *list)
{
	char	**redir_tab;
	int		size;

	redir_tab = NULL;
	while (list && list->token_id != PIPE && list->token_id != S_LESS
		&& list->token_id != D_LESS && list->token_id != S_GREATER
		&& list->token_id != D_GREATER)
		list = list->next;
	if (!list || list->token_id == PIPE)
		return (0);
	if (list->token_id == S_LESS || list->token_id == D_LESS
		|| list->token_id == S_GREATER || list->token_id == D_GREATER)
	{
		size = ft_count_chevrons(list) * 2;
		redir_tab = malloc(sizeof(char *) * (size + 1));
		if (redir_tab == 0)
			return (0);
		ft_fill_redir(list, size, redir_tab);
	}
	return (redir_tab);
}

int	ft_has_redir(char **redir)
{
	int	i;

	i = 0;
	if (!redir)
		return (0);
	while (redir[i])
	{
		if (ft_strcmp(redir[i], "<") == 0 || ft_strcmp(redir[i], ">") == 0
			|| ft_strcmp(redir[i], ">>") == 0)
			return (1);
		i++;
	}
	return (0);
}
