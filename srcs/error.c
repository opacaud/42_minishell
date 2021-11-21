/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:22:53 by cboutier          #+#    #+#             */
/*   Updated: 2021/10/29 16:13:12 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	print_file_error(char *str)
{
	if (str)
	{
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	}
	return (-1);
}

int	ft_export_error(char *tab_token, char *trimmed_tab)
{
	ft_putstr_fd("export: `", STDERR_FILENO);
	ft_putstr_fd(tab_token, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	g_exit_status = 1;
	if (trimmed_tab)
		free(trimmed_tab);
	return (g_exit_status);
}

int	ft_unset_error(char *tab_token, char *trimmed_tab)
{
	g_exit_status = 1;
	ft_putstr_fd("unset: `", STDERR_FILENO);
	ft_putstr_fd(tab_token, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	if (trimmed_tab)
		free(trimmed_tab);
	return (g_exit_status);
}

void	ft_execve_error(t_cmd *cmd, int file)
{
	perror(*cmd->arg);
	g_exit_status = 127;
	if (cmd->arg[0][0] == '.' && cmd->arg[0][1] == '/')
		g_exit_status = 126;
	reset_redir(cmd, file);
	if (file != -10)
		close_me(file);
	if (cmd->backup_stdin != -1)
		close_me(cmd->backup_stdin);
	if (cmd->backup_stdout != -1)
		close_me(cmd->backup_stdout);
	exit(g_exit_status);
}

int	print_errno(t_cmd *cmd)
{
	perror(cmd->redir[1]);
	g_exit_status = 1;
	return (g_exit_status);
}
