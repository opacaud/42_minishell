/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 10:46:15 by cboutier          #+#    #+#             */
/*   Updated: 2021/10/29 16:15:40 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	ft_redir_in(t_cmd *cmd, int i)
{
	int	fd_in;

	if (!cmd->redir)
		return (0);
	fd_in = open(cmd->redir[i + 1], O_RDONLY);
	if (fd_in == -1)
	{
		perror(cmd->redir[i + 1]);
		return (-1);
	}
	if (dup2(fd_in, STDIN_FILENO) == -1)
		return (dup2_failed());
	close_me(fd_in);
	return (cmd->backup_stdin);
}

int	ft_redir_out(t_cmd *cmd, int i)
{
	int	fd_out;

	fd_out = -1;
	if (ft_strcmp(cmd->redir[i], ">") == 0
		&& ft_is_redir(cmd->redir[i + 1]) == 0)
		fd_out = open(cmd->redir[i + 1], O_RDWR | O_CREAT | O_TRUNC, 0666);
	else if (ft_strcmp(cmd->redir[i], ">>") == 0
		&& ft_is_redir(cmd->redir[i + 1]) == 0)
		fd_out = open(cmd->redir[1 + i], O_RDWR | O_CREAT | O_APPEND, 0666);
	else
		return (ambiguous_redir(cmd));
	if (fd_out == -1)
	{
		perror(cmd->redir[i + 1]);
		reset_redir(cmd, cmd->backup_stdout);
		return (-1);
	}
	if (dup2(fd_out, STDOUT_FILENO) == -1)
	{
		ft_putstr_fd("dup2 failed\n", 2);
		return (1);
	}
	close_me(fd_out);
	return (cmd->backup_stdout);
}

void	ft_redir_in_or_heredoc_pipes(t_cmd *cmd, int *i, int *file, int *ret)
{
	if (ft_strcmp(cmd->redir[*i], "<") == 0)
	{
		if (*file == -10)
			*file = ft_redir_in(cmd, *i);
		else
			*ret = ft_redir_in(cmd, *i);
	}
}

int	perform_redirs_pipes2(int *file, t_cmd *cmd, int *i, int ret)
{
	if (ft_strcmp(cmd->redir[*i], "<") == 0)
		ft_redir_in_or_heredoc_pipes(cmd, i, file, &ret);
	else if (ft_strcmp(cmd->redir[*i], "<<") == 0)
	{
		*file = heredoc_open(cmd, *file);
		if (*file == -1)
			perror("heredoc");
		if (dup2(*file, STDIN_FILENO) == -1)
			return (dup2_failed());
		if (ft_has_heredoc(cmd->redir) && !cmd->arg)
			close(*file);
	}
	else if (ft_strcmp(cmd->redir[*i], ">") == 0
		|| ft_strcmp(cmd->redir[*i], ">>") == 0)
	{
		if (*file == -10)
			*file = ft_redir_out(cmd, *i);
		else
			ret = ft_redir_out(cmd, *i);
	}
	if (*file == -1 || ret == -1)
		return (-1);
	return (0);
}

int	perform_redirs_pipes(t_cmd *cmd)
{
	int	i;
	int	file;
	int	ret;

	i = 0;
	file = -10;
	ret = 0;
	while (cmd->redir[i])
	{
		if (perform_redirs_pipes2(&file, cmd, &i, ret) == -1)
			return (-1);
		i++;
	}
	if (ft_has_heredoc(cmd->redir))
		unlink("heredoc");
	return (file);
}
