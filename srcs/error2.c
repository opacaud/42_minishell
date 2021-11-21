/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 13:46:56 by cboutier          #+#    #+#             */
/*   Updated: 2021/10/29 11:43:03 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	fork_failed_err(int **pipefds, int file, t_cmd *cmd, pid_t *pid)
{
	perror("Fork failed\n");
	if (pipefds && cmd)
		ft_close_free_pipefds(file, cmd);
	if (cmd && pid)
		ft_free_tab_pipes(cmd, pid);
	return (1);
}

void	execve_failed(int file, t_cmd *cmd, pid_t *pid)
{
	ft_close_free_pipefds(file, cmd);
	free(pid);
	exit (1);
}

int	heredoc_error(t_cmd *cmd)
{
	ft_putstr_fd("\n", STDOUT_FILENO);
	reset_redir(cmd, cmd->backup_stdin);
	unlink("heredoc");
	return (-1);
}
