/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 14:43:37 by cboutier          #+#    #+#             */
/*   Updated: 2021/10/29 16:15:18 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	ft_env_array_in_cmd(t_cmd *cmd, char **our_env_array)
{
	if (!our_env_array)
		return ;
	if (!cmd)
		return ;
	while (cmd)
	{
		cmd->our_env_array = our_env_array;
		cmd = cmd->next;
	}
}

t_token	*ft_end_of_loop_pipes(t_token *list, char *path, t_cmd *cmd)
{
	if (!list || !cmd)
		return (0);
	while (list && list->token_id != PIPE)
		list = list->next;
	if (list && list->next)
		list = list->next;
	if (cmd && cmd->arg && cmd->arg[0] && !is_builtin(cmd->arg[0]) && path)
	{
		free(path);
		path = NULL;
	}
	return (list);
}

t_token	*ft_go_ahead_end_loop(t_token *list, t_cmd **cmd, int *i)
{
	if (list && (*cmd))
		list = ft_end_of_loop_pipes(list, (*cmd)->path, (*cmd));
	if ((*cmd) && (*cmd)->next)
		(*cmd) = (*cmd)->next;
	(*i)++;
	return (list);
}

int	ft_pipe_loop(t_cmd *first, t_env *env, t_token *list, t_cmd *cmd)
{
	int		i;
	int		file;

	i = 0;
	while (i <= first->nb_pipes)
	{
		ft_heredoc_in_pipes(cmd);
		if (cmd && ft_create_pipe(i, cmd->nb_pipes, cmd->pipefds) == -1)
			return (0);
		file = -10;
		if (ft_check_path(&cmd, env, list, &i) == 0)
			continue ;
		first->pid[i] = fork();
		g_exit_status = 123456789;
		if (first->pid[i] < 0)
			return (fork_failed_err(first->pipefds, file, cmd, first->pid));
		else if (first->pid[i] == 0)
		{
			if (ft_dup_pipefds(i, cmd->nb_pipes, first->pipefds) == -1)
				return (-1);
			child_exec(cmd, first, &file, list);
		}
		list = ft_go_ahead_end_loop(list, &cmd, &i);
	}
	return (file);
}

int	ft_pipes(t_token *list, t_env *env, t_cmd *cmd)
{
	t_cmd	*first;
	int		file;

	if (!cmd)
		return (0);
	first = cmd;
	if (ft_pipefds_in_cmd(cmd) == -1)
		return (0);
	first->pid = ft_calloc(sizeof(pid_t), (cmd->nb_pipes + 1));
	if (first->pid == 0)
		return (0);
	ft_set_backupstd(first);
	file = ft_pipe_loop(first, env, list, first);
	if (dup2(first->backup_stdin, STDIN_FILENO) == -1)
		return (dup2_failed());
	if (dup2(first->backup_stdout, STDOUT_FILENO) == -1)
		return (dup2_failed());
	ft_close_free_pipefds(file, first);
	ft_parent_waiting(first->pid, first->nb_pipes, first);
	return (g_exit_status);
}
