/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_first_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 16:29:39 by cboutier          #+#    #+#             */
/*   Updated: 2021/10/21 16:18:57 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

t_token	*make_first_pipe(char *line, int *ptr_i)
{
	char	*str;

	if (!line)
		return (0);
	str = ft_strdup("|");
	(*ptr_i)++;
	return (new_elem(str, PIPE));
}

t_token	*make_first_chevron(char *line, int *ptr_i)
{
	int		j;
	char	*str;
	int		chevron_type;

	if (!line)
		return (0);
	chevron_type = 1;
	if (line[*ptr_i + 1] == line[*ptr_i])
		chevron_type = 2;
	str = malloc(sizeof(char) * (chevron_type + 1));
	if (str == 0)
		return (0);
	j = 0;
	while (j < chevron_type)
	{
		str[j] = line[*ptr_i + j];
		j++;
	}
	str[j] = '\0';
	if (chevron_type == 2)
		(*ptr_i)++;
	(*ptr_i)++;
	return (new_elem(str, ft_which_token(str)));
}

t_token	*make_first_quote(char *line, int *ptr_i)
{
	char	*str;
	int		counter;
	int		start;
	int		j;
	char	quote;

	if (!line)
		return (0);
	counter = 0;
	start = *ptr_i + 1;
	quote = line[*ptr_i];
	while (line[++(*ptr_i)] && line[*ptr_i] != quote)
		counter++;
	str = malloc(sizeof(char) * (counter + 1));
	if (str == 0)
		return (0);
	j = -1;
	while (++j < counter)
		str[j] = line[start + j];
	str[j] = '\0';
	(*ptr_i)++;
	if (quote == '\'')
		return (new_elem(str, S_QUOTE));
	return (new_elem(str, D_QUOTE));
}

char	*make_first_env_str(char *line, int start, int counter)
{
	char	*str;
	int		i;

	str = malloc(sizeof(char) * (counter + 1));
	if (str == 0)
		return (0);
	i = 0;
	while (i < counter)
	{
		str[i] = line[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

t_token	*make_first_env(char *line, int *ptr_i, t_env *env)
{
	char	*str;
	int		counter;
	int		start;

	if (!line)
		return (0);
	if (ft_strcmp(line, "$?") == 0)
	{
		(*ptr_i) += 2;
		return (new_elem(ft_itoa(g_exit_status), ARG));
	}
	start = *ptr_i;
	counter = ft_count_till_sep_env(line, ptr_i);
	str = make_first_env_str(line, start, counter);
	if (ft_strcmp(str, "$") == 0)
		return (cmd_failed(str));
	if (line[start] == '$')
		return (new_elem(ft_scan_env(str, line, ptr_i, env), ENV));
	return (new_elem(str, ARG));
}
