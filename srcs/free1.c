/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 16:53:54 by cboutier          #+#    #+#             */
/*   Updated: 2021/10/29 16:13:51 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	ft_free_token_list(t_token *list)
{
	t_token	*tmp;

	if (!list)
		return ;
	if (list->str && (list->token_id == S_LESS
			|| list->token_id == D_LESS || list->token_id == S_GREATER
			|| list->token_id == D_GREATER || list->token_id == PIPE))
	{
		tmp = list;
		free(list->str);
		list = list->next;
		free(tmp);
		tmp = NULL;
	}
	while (list)
	{
		tmp = list;
		if (list && list->str && (list->token_id != END_OF_ARG
				&& list->token_id != S_LESS && list->token_id != D_LESS
				&& list->token_id != S_GREATER && list->token_id != D_GREATER
				&& list->token_id != PIPE))
			list->str = free_str(list->str);
		list = list->next;
		free(tmp);
	}
}

void	ft_free_cmd_list(t_cmd *cmd)
{
	t_cmd	*tmp;

	if (!cmd)
		return ;
	while (cmd)
	{
		tmp = cmd;
		if (cmd->arg && cmd->arg[0])
			ft_free_tab(cmd->arg);
		if (cmd->redir)
			ft_free_tab(cmd->redir);
		cmd = cmd->next;
		free(tmp);
	}
}

void	ft_free_env_list(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		free(env->value);
		free(env->name);
		env = env->next;
		free(tmp);
	}
}

void	ft_free_everything(t_token *list, t_cmd *cmd, char *line)
{
	if (cmd->backup_stdin != -1)
		close_me(cmd->backup_stdin);
	if (cmd->backup_stdout != -1)
		close_me(cmd->backup_stdout);
	if (list)
		ft_free_token_list(list);
	if (cmd)
		ft_free_cmd_list(cmd);
	if (line)
		free(line);
}

void	*free_str(char *str)
{
	free(str);
	str = NULL;
	return (str);
}
