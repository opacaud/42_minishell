/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_in_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 10:51:47 by cboutier          #+#    #+#             */
/*   Updated: 2021/10/29 16:13:37 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	ft_parent_waiting(pid_t *pid, int nb_pipes, t_cmd *first)
{
	int	i;
	int	status;

	status = 0;
	if (first->backup_stdin != -1)
		close(first->backup_stdin);
	i = 0;
	while (i <= nb_pipes)
	{
		waitpid(pid[i], &status, 0);
		if (WIFEXITED(status) && g_exit_status != 127)
			g_exit_status = (WEXITSTATUS(status));
		if (g_exit_status == 21)
			g_exit_status = 0;
		i++;
	}
	if (pid)
		free(pid);
}

int	ft_child_handle_redir(int nb_pipes, t_cmd *first, int **pipefds, t_cmd *cmd)
{
	int	j;
	int	file;

	file = -10;
	j = 0;
	(void)first;
	while (j < nb_pipes)
	{
		close_me(pipefds[j][0]);
		close_me(pipefds[j][1]);
		j++;
	}
	if (ft_get_size_tab(cmd->arg) == 0)
	{
		close_me(cmd->backup_stdin);
		close_me(cmd->backup_stdout);
	}
	if (ft_get_size_tab (cmd->redir) > 0)
		file = perform_redirs_pipes(cmd);
	if (file == -1)
	{
		ft_close_free_pipefds(file, cmd);
		exit (1);
	}
	return (file);
}

void	child_exec(t_cmd *cmd, t_cmd *first, int *file, t_token *list)
{
	*file = ft_child_handle_redir(cmd->nb_pipes, first, cmd->pipefds, cmd);
	if (cmd->arg)
	{
		if (is_builtin(cmd->arg[0]))
		{
			exec_builtin(cmd, list, &first->env, *file);
			ft_close_free_pipefds(*file, cmd);
			free(first->pid);
			exit (g_exit_status);
		}
		else
		{
			if (cmd->path && cmd->arg && cmd->our_env_array)
			{
				if (execve(cmd->path, cmd->arg, cmd->our_env_array) == -1)
				{
					perror(cmd->arg[0]);
					execve_failed(*file, cmd, first->pid);
				}
				exit (0);
			}
		}
	}
	else
		exit(0);
}

int	ft_check_path(t_cmd **cmd, t_env *env, t_token *list, int *i)
{
	if ((*cmd) && (*cmd)->arg && !is_builtin((*cmd)->arg[0])
		&& (*cmd)->arg[0][0] != '/' && !ft_isdigit((*cmd)->arg[0])
		&& (*cmd)->arg[0][0] != '.')
	{
		if (check_path(env, (*cmd)->arg[0], &(*cmd)->path) != 1)
		{
			g_exit_status = cmd_not_found((*cmd), 0);
			if (list && cmd)
				list = ft_end_of_loop_pipes(list, (*cmd)->path, (*cmd));
			if ((*cmd)->next)
				(*cmd) = (*cmd)->next;
			(*i)++;
			return (0);
		}
	}
	else if ((*cmd) && (*cmd)->arg && (*cmd)->arg[0]
		&& (*cmd)->arg[0][0] == '/')
		(*cmd)->path = ft_strdup((*cmd)->arg[0]);
	return (1);
}

void	ft_heredoc_in_pipes(t_cmd *cmd)
{
	int	i;

	if (cmd && cmd->redir && ft_has_heredoc(cmd->redir))
	{
		i = 0;
		while (cmd->redir[i])
		{
			if (ft_strcmp(cmd->redir[i], "<<") == 0)
				ft_redir_heredoc(cmd, i);
			i++;
		}
	}
}
