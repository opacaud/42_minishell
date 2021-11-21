/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 11:55:47 by cboutier          #+#    #+#             */
/*   Updated: 2021/09/21 11:56:34 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	is_env_sep(char *line, int i)
{
	if (line[i] == '\'')
		return (S_QUOTE);
	else if (line[i] == '"')
		return (D_QUOTE);
	else if (line[i] == '<' && line[i + 1] != '<')
		return (S_LESS);
	else if (line[i] == '<' && line[i + 1] == '<')
		return (D_LESS);
	else if (line[i] == '>' && line[i + 1] != '>')
		return (S_GREATER);
	else if (line[i] == '>' && line[i + 1] == '>')
		return (D_GREATER);
	else if (line[i] == '|')
		return (PIPE);
	else if (line[i] == '$')
		return (ENV);
	else if (line[i] == ' ')
		return (END_OF_ARG);
	else if (line[i] == '/')
		return (11);
	else
		return (0);
}

int	is_sep(char *line, int i)
{
	if (line[i] == '\'')
		return (S_QUOTE);
	else if (line[i] == '"')
		return (D_QUOTE);
	else if (line[i] == '<' && line[i + 1] != '<')
		return (S_LESS);
	else if (line[i] == '<' && line[i + 1] == '<')
		return (D_LESS);
	else if (line[i] == '>' && line[i + 1] != '>')
		return (S_GREATER);
	else if (line[i] == '>' && line[i + 1] == '>')
		return (D_GREATER);
	else if (line[i] == '|')
		return (PIPE);
	else if (line[i] == '$')
		return (ENV);
	else if (line[i] == ' ')
		return (END_OF_ARG);
	else
		return (0);
}

int	ft_which_token(char *str)
{
	if (ft_strcmp(str, "'") == 0)
		return (S_QUOTE);
	else if (ft_strcmp(str, "\"") == 0)
		return (D_QUOTE);
	else if (ft_strcmp(str, "<") == 0)
		return (S_LESS);
	else if (ft_strcmp(str, "<<") == 0)
		return (D_LESS);
	else if (ft_strcmp(str, ">") == 0)
		return (S_GREATER);
	else if (ft_strcmp(str, ">>") == 0)
		return (D_GREATER);
	else if (ft_strcmp(str, "|") == 0)
		return (PIPE);
	else if (str[0] == '$')
		return (ENV);
	else if (ft_strcmp(str, " ") == 0)
		return (END_OF_ARG);
	return (ARG);
}
