/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:31:05 by cboutier          #+#    #+#             */
/*   Updated: 2021/10/29 16:20:05 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	ft_create_arg3(t_token *list, char **arg, int i)
{
	while (list && list->token_id != PIPE && list->token_id != S_LESS
		&& list->token_id != D_LESS && list->token_id != S_GREATER
		&& list->token_id != D_GREATER)
	{
		if (list->str && list->token_id != END_OF_ARG && list->str[0] != '-')
		{
			arg[i] = ft_strdup(list->str);
			i++;
		}
		list = list->next;
	}
	arg[i] = 0;
}

void	ft_create_arg2(t_token *list, t_token *tmp, char **arg)
{
	int	i;

	i = 1;
	while (list && list->token_id != PIPE)
	{
		if ((list->token_id == ARG || list->token_id == ENV)
			&& list->str && list->str[0] == '-')
		{
			arg[i] = ft_strdup(list->str);
			i++;
		}
		list = list->next;
	}
	list = tmp->next;
	ft_create_arg3(list, arg, i);
}

char	**ft_create_arg(t_token *list)
{
	int		counter;
	char	**arg;
	t_token	*tmp;

	arg = NULL;
	counter = 1;
	list = ft_go_forward(list);
	if (!list || !list->next || list->token_id == PIPE
		|| ft_is_redir(list->str))
		return (0);
	tmp = list;
	counter = ft_count_arg(list, tmp, counter);
	arg = ft_calloc(sizeof(char *), (counter + 1));
	if (arg == 0)
		return (0);
	list = tmp;
	if (list->token_id == END_OF_ARG && list->next)
		list = list->next;
	tmp = list;
	arg[0] = ft_strdup(list->str);
	if (list && list->next)
		list = list->next;
	ft_create_arg2(list, tmp, arg);
	return (arg);
}

t_token	*ft_fill_arg(t_token *list, char ***arg, int *i)
{
	while (list && list->token_id != PIPE && list->token_id != S_LESS
		&& list->token_id != D_LESS && list->token_id != S_GREATER
		&& list->token_id != D_GREATER)
	{
		while ((*arg)[(*i)])
			(*i)++;
		if (list->token_id == ARG || list->token_id == ENV
			|| list->token_id == S_QUOTE || list->token_id == D_QUOTE)
		{
			(*arg)[(*i)] = ft_strdup(list->str);
			(*i)++;
		}
		list = list->next;
	}
	return (list);
}
