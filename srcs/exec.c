/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 16:30:24 by cboutier          #+#    #+#             */
/*   Updated: 2021/10/29 10:55:23 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	exec_builtin(t_cmd *cmd, t_token *list, t_env **env, int file)
{
	if (!list)
		return ;
	if (ft_strcmp(cmd->arg[0], "cd") == 0)
		g_exit_status = ft_cd(list, *env);
	else if (ft_strcmp(ft_tolower(cmd->arg[0]), "pwd") == 0)
		g_exit_status = get_pwd();
	else if (ft_strcmp(cmd->arg[0], "echo") == 0)
		g_exit_status = ft_echo(list, *env);
	else if (ft_strcmp(cmd->arg[0], "env") == 0
		|| (ft_strcmp(cmd->arg[0], "export") == 0)
		|| (ft_strcmp(cmd->arg[0], "unset") == 0))
		g_exit_status = ft_env(env, list, cmd);
	else if (ft_strcmp(cmd->arg[0], "exit") == 0)
		g_exit_status = ft_exit(list, cmd);
	if (file != -10)
	{
		reset_redir(cmd, file);
		close_me(file);
	}
}

int	cmd_not_found(t_cmd *cmd, int file)
{
	ft_putstr_fd(*cmd->arg, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	g_exit_status = 127;
	reset_redir(cmd, file);
	if (file != -10)
		close_me(file);
	return (127);
}
