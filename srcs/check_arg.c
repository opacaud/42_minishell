/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 16:20:10 by cboutier          #+#    #+#             */
/*   Updated: 2021/10/29 16:22:15 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

t_token	*ft_second_check_arg2(t_token *list, char **redir, int j)
{
	while (list && list->token_id != PIPE
		&& ft_strcmp(list->str, redir[j]) != 0)
		list = list->next;
	return (list);
}

char	**ft_second_check_arg(t_token *list, char **arg, char **redir)
{
	int	i;
	int	j;

	i = 0;
	if (!list || !arg || !redir)
		return (0);
	j = 1;
	list = ft_go_to_arg_zero(list, arg);
	while (redir[j] && list && list->token_id != PIPE)
	{
		if (!list)
			return (arg);
		list = ft_second_check_arg2(list, redir, j);
		if (list && list->next && list->token_id != PIPE)
			list = list->next;
		else
			break ;
		list = ft_fill_arg(list, &arg, &i);
		if (j < ft_get_size_tab(redir) - 1)
			j += 2;
	}
	if (i != 0)
		arg[i] = 0;
	return (arg);
}
