/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_in_dquotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 11:33:55 by cboutier          #+#    #+#             */
/*   Updated: 2021/10/29 16:16:00 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

char	*ft_isolate_non_quotes(t_token *list, int *i)
{
	int		start;
	int		counter;
	char	*res;

	start = *i;
	counter = 0;
	if (list->str[*i] == ' ')
		return (ft_strdup(" "));
	if (list->str[*i] == '$')
	{
		counter++;
		(*i)++;
	}
	while (list->str[*i] && list->str[*i] != '$'
		&& list->str[*i] != ' ' && list->str[*i] != '\'')
	{
		counter++;
		(*i)++;
	}
	res = malloc(sizeof(char) * (counter + 1));
	if (res == 0)
		return (0);
	res = ft_strncpy(list->str + start, res, counter);
	(*i)--;
	return (res);
}

t_token	*ft_s_in_dquotes2(t_token *list, int *i)
{
	char	*res;
	t_token	*first;
	t_token	*tmp;

	if (list->str[*i] == '\'')
		res = ft_strdup("'");
	else
		res = ft_isolate_non_quotes(list, i);
	first = list;
	while (list && list->next && list->next->token_id != END_OF_ARG)
		list = list->next;
	tmp = list->next;
	if (res[0] == '$')
		list->next = ft_insert_elem(res, ENV, tmp);
	else
		list->next = ft_insert_elem(res, D_QUOTE, tmp);
	list = first;
	(*i)++;
	return (list);
}

void	ft_free_and_null(t_token *list)
{
	free(list->str);
	list->str = NULL;
	list->token_id = END_OF_ARG;
}

t_token	*ft_s_in_dquotes(t_token *list, t_token *real_first)
{
	int		i;
	t_token	*first;
	t_token	*tmp;

	first = list;
	tmp = list->next;
	list->next = ft_insert_elem(" ", END_OF_ARG, tmp);
	i = 0;
	list = first;
	while (list->str[i])
		list = ft_s_in_dquotes2(list, &i);
	ft_free_and_null(list);
	while (list && list->next && list->next->token_id != END_OF_ARG)
		list = list->next;
	ft_lstdelnext(list);
	while (real_first && real_first->next)
	{
		if (!real_first->next->str && real_first->next->token_id == END_OF_ARG)
		{
			ft_lstdelnext(real_first);
			return (real_first);
		}
		real_first = real_first->next;
	}
	return (0);
}
