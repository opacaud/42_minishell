/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 16:31:25 by cboutier          #+#    #+#             */
/*   Updated: 2021/10/29 16:16:23 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	ft_redir_in_simple(t_cmd *cmd, int i)
{
	int	fd_in;

	if (cmd->redir[i + 1])
		fd_in = open(cmd->redir[i + 1], O_RDONLY);
	else
		return (cmd->backup_stdin);
	if (fd_in == -1)
		return (ft_error_redir(cmd, i));
	if (dup2(fd_in, STDIN_FILENO) == -1)
		return (dup2_failed());
	close_me(fd_in);
	return (cmd->backup_stdin);
}

int	ft_redir_out_simple(t_cmd *cmd, int i)
{
	int	fd_out;

	fd_out = -1;
	if (ft_strcmp(cmd->redir[i], ">") == 0
		&& ft_is_redir(cmd->redir[i + 1]) == 0)
		fd_out = open(cmd->redir[1 + i], O_RDWR | O_CREAT | O_TRUNC, 0666);
	else if (ft_strcmp(cmd->redir[i], ">>") == 0
		&& ft_is_redir(cmd->redir[i + 1]) == 0)
		fd_out = open(cmd->redir[1 + i], O_RDWR | O_CREAT | O_APPEND, 0666);
	else
		return (ambiguous_redir(cmd));
	if (fd_out == -1)
	{
		print_errno(cmd);
		reset_redir(cmd, cmd->backup_stdout);
		return (-1);
	}
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		return (dup2_failed());
	close_me(fd_out);
	return (cmd->backup_stdout);
}

void	ft_in_or_heredoc(t_cmd *cmd, int *i, int *file, int *ret)
{
	if (ft_strcmp(cmd->redir[*i], "<") == 0)
	{
		if (*file == -10)
			*file = ft_redir_in_simple(cmd, *i);
		else
			*ret = ft_redir_in_simple(cmd, *i);
	}
	else if (ft_strcmp(cmd->redir[*i], "<<") == 0)
	{
		if (*file == -10)
			*file = ft_redir_heredoc(cmd, *i);
		else
			*ret = ft_redir_heredoc(cmd, *i);
	}
}

int	perform_redirs2(int *file, t_cmd *cmd, int *i)
{
	int		ret;

	ret = 0;
	if (ft_strcmp(cmd->redir[*i], "<") == 0
		|| ft_strcmp(cmd->redir[*i], "<<") == 0)
		ft_in_or_heredoc(cmd, i, file, &ret);
	else if (ft_strcmp(cmd->redir[*i], ">") == 0
		|| ft_strcmp(cmd->redir[*i], ">>") == 0)
	{
		if (*file == -10)
			*file = ft_redir_out_simple(cmd, *i);
		else
			ret = ft_redir_out_simple(cmd, *i);
	}
	if (*file == -1 || ret == -1)
		return (-1);
	return (0);
}

int	perform_redirs(t_cmd *cmd)
{
	int	i;
	int	file;

	i = 0;
	file = -10;
	if (cmd->redir)
	{
		while (cmd->redir[i])
		{
			if (perform_redirs2(&file, cmd, &i) == -1)
				return (-1);
			i++;
		}
	}
	return (file);
}
