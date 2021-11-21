/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 12:06:34 by cboutier          #+#    #+#             */
/*   Updated: 2021/10/29 16:15:50 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	ft_error_redir(t_cmd *cmd, int i)
{
	perror(cmd->redir[i + 1]);
	g_exit_status = 1;
	reset_redir(cmd, cmd->backup_stdin);
	return (-1);
}

int	reset_redir(t_cmd *cmd, int file)
{
	int	i;

	i = 0;
	if (cmd->redir)
	{
		while (cmd->redir[i])
		{
			if (ft_strcmp(cmd->redir[i], "<") == 0
				|| ft_strcmp(cmd->redir[i], "<<") == 0)
			{
				if (dup2(file, STDIN_FILENO) == -1)
					return (dup2_failed());
			}
			else if (ft_strcmp(cmd->redir[i], ">") == 0
				|| ft_strcmp(cmd->redir[i], ">>") == 0)
			{
				if (dup2(file, STDOUT_FILENO) == -1)
					return (dup2_failed());
			}
			i++;
		}
	}
	return (0);
}

void	reset_if_no_arg(t_cmd *cmd)
{
	if (cmd->redir[0] && (ft_strcmp(cmd->redir[0], ">") == 0
			|| ft_strcmp(cmd->redir[0], ">>") == 0))
		reset_redir(cmd, cmd->backup_stdout);
	else if (cmd->redir[0] && (ft_strcmp(cmd->redir[0], "<") == 0
			|| ft_strcmp(cmd->redir[0], "<<") == 0))
		reset_redir(cmd, cmd->backup_stdin);
}

void	close_me(int fd)
{
	if (fd > 2)
		close(fd);
}

int	ft_set_backupstd(t_cmd *cmd)
{
	int	in;
	int	out;

	if (!cmd)
		return (0);
	in = -1;
	out = -1;
	cmd->backup_stdin = dup(STDIN_FILENO);
	if (cmd->backup_stdin == -1)
		return (dup2_failed());
	cmd->backup_stdout = dup(STDOUT_FILENO);
	if (cmd->backup_stdout == -1)
		return (dup2_failed());
	in = cmd->backup_stdin;
	out = cmd->backup_stdout;
	while (cmd)
	{
		cmd->backup_stdin = in;
		cmd->backup_stdout = out;
		cmd = cmd->next;
	}
	return (0);
}
