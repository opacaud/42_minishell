/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 09:53:17 by cboutier          #+#    #+#             */
/*   Updated: 2021/10/29 16:13:59 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	ft_close_free_pipefds(int file, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->nb_pipes)
	{
		close(cmd->pipefds[i][0]);
		close(cmd->pipefds[i][1]);
		i++;
	}
	i = 0;
	while (i < cmd->nb_pipes)
	{
		free(cmd->pipefds[i]);
		cmd->pipefds[i] = NULL;
		i++;
	}
	free(cmd->pipefds);
	cmd->pipefds = NULL;
	close_fds(file, cmd);
}

void	ft_free_tab_pipes(t_cmd *cmd, pid_t *pid)
{
	(void)cmd;
	if (pid)
	{
		free(pid);
		pid = NULL;
	}
}

int	ft_free_int_tab(int **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (0);
	while (tab[i])
	{
		if (tab[i])
		{
			free(tab[i]);
			tab[i] = NULL;
			i++;
		}
	}
	free(tab);
	tab = NULL;
	return (0);
}

void	ft_free_pipefds(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->nb_pipes)
	{
		free(cmd->pipefds[i]);
		i++;
	}
	free(cmd->pipefds);
	ft_free_cmd_list(cmd);
}
