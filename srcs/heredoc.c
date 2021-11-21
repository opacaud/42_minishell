/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 16:06:33 by cboutier          #+#    #+#             */
/*   Updated: 2021/10/29 16:14:10 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	heredoc_open(t_cmd *cmd, int fd)
{
	if (fd == -1)
		fd = open("heredoc", O_RDWR | O_CREAT | O_TRUNC, 0666);
	else
		fd = open("heredoc", O_RDWR | O_CREAT | O_APPEND, 0666);
	if (fd == -1)
	{
		perror("heredoc");
		reset_redir(cmd, cmd->backup_stdout);
		return (-1);
	}
	return (fd);
}

int	ft_redir_heredoc2(t_cmd *cmd, char *line, int i)
{
	int		fd;

	fd = -1;
	while (1)
	{
		g_exit_status = 147258369;
		line = readline("\033[0;95mheredoc > \033[0m");
		if (!line)
			return (heredoc_error(cmd));
		fd = heredoc_open(cmd, fd);
		if (fd == -1)
			return (ft_error_redir(cmd, i));
		if (ft_strcmp(line, cmd->redir[i + 1]) != 0)
			ft_env_in_heredoc(line, fd, cmd);
		if (ft_strcmp(line, cmd->redir[i + 1]) == 0)
			break ;
		free(line);
	}
	free(line);
	return (fd);
}

int	ft_last_heredoc(char **redir, int i)
{
	while (redir[i])
	{
		if (ft_strcmp(redir[i], "<<") == 0)
			return (0);
		i++;
	}
	return (1);
}

int	ft_redir_heredoc(t_cmd *cmd, int i)
{
	int		fd;
	char	*line;

	fd = -1;
	line = NULL;
	fd = ft_redir_heredoc2(cmd, line, i);
	if ((cmd->nb_pipes > 0 && cmd_lst_size(cmd) == 1 && fd != -1)
		|| (cmd->nb_pipes == 0 && ft_last_heredoc(cmd->redir, i + 1)
			&& fd != -1))
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			return (dup2_failed());
	}
	if (fd != -1)
		close_me(fd);
	if (cmd->nb_pipes == 0)
		unlink("heredoc");
	return (cmd->backup_stdin);
}

int	ft_has_heredoc(char **redir)
{
	int	i;

	i = 0;
	if (!redir)
		return (0);
	while (redir[i])
	{
		if (ft_strcmp(redir[i], "<<") == 0)
			return (1);
		i++;
	}
	return (0);
}
