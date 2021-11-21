/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 09:45:00 by cboutier          #+#    #+#             */
/*   Updated: 2021/10/29 16:12:34 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

t_token	*ft_make_first_token(char *line, int *ptr_i, t_env *env)
{
	if (!line)
		return (NULL);
	while (line[*ptr_i] == ' ')
		(*ptr_i)++;
	if (line[*ptr_i] == '<' || line[*ptr_i] == '>')
		return (make_first_chevron(line, ptr_i));
	else if (line[*ptr_i] == '\'' || line[*ptr_i] == '"')
		return (make_first_quote(line, ptr_i));
	else if (line[*ptr_i] == '|')
		return (make_first_pipe(line, ptr_i));
	else
		return (make_first_env(line, ptr_i, env));
}

void	ft_add_unknown_tokens2(t_token *list, char *line, int *ptr_i, char *str)
{
	char	quote;

	quote = 0;
	if (line[*ptr_i] == '\'' || line[*ptr_i] == '"')
	{
		quote = line[*ptr_i];
		str = ft_getstr_quote(line, ptr_i, line[*ptr_i]);
		if (quote == '\'')
			ft_lstadd_back(&list, str, S_QUOTE);
		else if (quote == '"')
			ft_lstadd_back(&list, str, D_QUOTE);
	}
	else if (is_sep(line, *ptr_i) == 0)
	{
		str = ft_getstr_env_arg(line, ptr_i);
		ft_lstadd_back(&list, str, ARG);
	}
}

void	ft_add_unknown_tokens(t_token *list, char *line, int *ptr_i)
{
	char	*str;

	str = NULL;
	if (line[*ptr_i] == '$' && line[(*ptr_i) + 1] && line[(*ptr_i) + 1] == '?')
	{
		ft_lstadd_back(&list, ft_itoa(g_exit_status), ARG);
		(*ptr_i)++;
	}	
	else if (line[*ptr_i] == '$' && line[(*ptr_i) + 1]
		&& line[(*ptr_i) + 1] != ' ')
	{
		str = ft_getstr_env_arg(line, ptr_i);
		ft_lstadd_back(&list, str, ENV);
	}
	else if (line[*ptr_i] == '$' && (!line[(*ptr_i) + 1]
			|| line[(*ptr_i) + 1] == ' '))
	{
		str = ft_strdup("$");
		ft_lstadd_back(&list, str, ARG);
	}
	else
		ft_add_unknown_tokens2(list, line, ptr_i, str);
}

void	ft_add_tokens2(t_token *list, char *line, int *ptr_i)
{
	if (line[*ptr_i] == '>' && line[*ptr_i + 1] == '>')
	{
		ft_lstadd_back(&list, ">>", D_GREATER);
		(*ptr_i)++;
	}
	else if (line[*ptr_i] == '>')
		ft_lstadd_back(&list, ">", S_GREATER);
	else
		ft_add_unknown_tokens(list, line, ptr_i);
}

void	ft_add_tokens(t_token *list, char *line, int *ptr_i)
{
	while (line[*ptr_i])
	{
		if (line[*ptr_i] == ' ' && line[(*ptr_i) + 1] != ' ')
			ft_lstadd_back(&list, " ", END_OF_ARG);
		if (line[*ptr_i] == '<' && line[*ptr_i + 1] == '<')
		{
			ft_lstadd_back(&list, "<<", D_LESS);
			(*ptr_i)++;
		}
		else if (line[*ptr_i] == '<')
			ft_lstadd_back(&list, "<", S_LESS);
		else if (line[*ptr_i] == '|')
			ft_lstadd_back(&list, "|", PIPE);
		else
			ft_add_tokens2(list, line, ptr_i);
		if (line[*ptr_i])
			(*ptr_i)++;
	}
	ft_lstadd_back(&list, " ", END_OF_ARG);
}
