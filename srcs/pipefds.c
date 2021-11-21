/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipefds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 10:48:53 by cboutier          #+#    #+#             */
/*   Updated: 2021/10/29 16:15:13 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	ft_dup_pipefds(int i, int nb_pipes, int **pipefds)
{
	if (!(i == nb_pipes))
	{
		if (dup2(pipefds[i][1], STDOUT_FILENO) == -1)
			return (dup2_failed());
		close(pipefds[i][0]);
		close(pipefds[i][1]);
	}
	if (!(i == 0))
	{
		if (dup2(pipefds[i - 1][0], STDIN_FILENO) == -1)
			return (dup2_failed());
		close(pipefds[i - 1][1]);
		close(pipefds[i - 1][0]);
	}
	return (0);
}

int	ft_create_pipe(int i, int nb_pipes, int **pipefds)
{
	if (i < nb_pipes)
	{
		if (pipe(pipefds[i]) < 0)
		{
			ft_putstr_fd("Pipe failed\n", STDERR_FILENO);
			g_exit_status = 1;
			return (-1);
		}
	}
	return (0);
}

int	**ft_calloc_pipefds(int nb_pipes)
{
	int		**pipefds;
	int		i;

	pipefds = ft_calloc(sizeof(int *), nb_pipes);
	if (!pipefds)
		return (0);
	i = 0;
	while (i < nb_pipes)
	{
		pipefds[i] = ft_calloc(sizeof(int), 2);
		if (!pipefds[i])
			return (0);
		i++;
	}
	return (pipefds);
}

int	ft_pipefds_in_cmd(t_cmd *cmd)
{
	int	**tmp;

	if (!cmd || !cmd->next)
		return (-1);
	cmd->pipefds = ft_calloc_pipefds(cmd->nb_pipes);
	if (cmd->pipefds == 0)
		return (-1);
	tmp = cmd->pipefds;
	if (cmd->next)
		cmd = cmd->next;
	while (cmd)
	{
		cmd->pipefds = tmp;
		cmd = cmd->next;
	}
	return (0);
}
