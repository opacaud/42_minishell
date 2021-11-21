/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 14:27:01 by cboutier          #+#    #+#             */
/*   Updated: 2021/10/28 13:59:06 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

char	*ft_scan_env(char *str, char *line, int *ptr_i, t_env *env)
{
	int		in_squote;
	char	*res;
	char	*tmp;

	if (!line || !str)
		return (0);
	res = 0;
	in_squote = ft_in_squote(line, ptr_i);
	if (in_squote == 0)
	{
		tmp = ft_strtrim(str, '$');
		free(str);
		res = ft_getenv(tmp, env);
		free(tmp);
	}
	return (res);
}

int	ft_count_till_sep_env(char *line, int *ptr_i)
{
	int	counter;

	counter = 0;
	if (line[*ptr_i] == '$')
	{
		counter++;
		(*ptr_i)++;
		while (line[*ptr_i] && !is_sep(line, *ptr_i)
			&& (ft_isalnum(line[*ptr_i]) || line[*ptr_i] == '_'))
		{
			counter++;
			(*ptr_i)++;
		}
		return (counter);
	}
	while (line[*ptr_i] && !is_sep(line, *ptr_i))
	{
		counter++;
		(*ptr_i)++;
	}
	return (counter);
}

t_token	*ft_split_export_egal(t_token *list)
{
	char	*tmp;
	int		pos;
	int		i;
	t_token	*tmp2;

	i = 0;
	pos = 0;
	while (list->str[i])
	{
		if (list->str[i] == '=')
			pos = i;
		i++;
	}
	tmp = ft_strdup(list->str + pos);
	tmp2 = list->next;
	list->next = ft_insert_elem(tmp, ARG, tmp2);
	tmp = ft_strdup(list->str);
	ft_strncpy(tmp, list->str, pos);
	free(tmp);
	return (list);
}

void	ft_env_in_dq_trad(t_token *list)
{
	if (list->next->token_id == D_QUOTE)
		list->token_id = D_QUOTE;
	if (list->next->token_id == ENV)
		list->token_id = ENV;
	if (list->next->env_in_dq_trad == 1)
		list->env_in_dq_trad = 1;
}
