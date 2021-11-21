/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prgm_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 15:43:48 by cboutier          #+#    #+#             */
/*   Updated: 2021/10/29 16:15:29 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	close_fds(int file, t_cmd *first)
{
	if (!first)
		return ;
	if (file != -10)
		close_me(file);
	if (first->backup_stdin != -1)
		close_me(first->backup_stdin);
	if (first->backup_stdout != -1)
		close_me(first->backup_stdout);
}

void	close_backup_exit(t_cmd *cmd)
{
	close_me(cmd->backup_stdin);
	close_me(cmd->backup_stdout);
	exit(0);
}

int	ambiguous_redir(t_cmd *cmd)
{
	ft_putstr_fd("Ambiguous redirect\n", STDERR_FILENO);
	reset_redir(cmd, cmd->backup_stdout);
	return (-1);
}
