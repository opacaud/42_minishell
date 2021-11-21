/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 14:52:03 by cboutier          #+#    #+#             */
/*   Updated: 2021/10/28 16:07:52 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	ft_exit_error(char **tab_token)
{
	if (ft_strcmp(tab_token[0], "exit") == 0 && ft_get_size_tab(tab_token) > 1
		&& !ft_isdigit(tab_token[1]))
	{
		ft_putstr_fd("exit: numeric argument required\n", STDERR_FILENO);
		g_exit_status = 2;
		return (g_exit_status);
	}
	if (ft_strcmp(tab_token[0], "exit") == 0 && ft_get_size_tab(tab_token) > 2)
	{
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		g_exit_status = 1;
		ft_free_tab(tab_token);
		return (g_exit_status);
	}
	return (0);
}

void	close_backup(t_cmd *cmd)
{
	close_me(cmd->backup_stdin);
	close_me(cmd->backup_stdout);
}

int	ft_exit(t_token *list, t_cmd *cmd)
{
	char	**tab_token;
	int		ret;

	tab_token = lst_to_array(list);
	ret = ft_exit_error(tab_token);
	if (ret == 1)
		return (g_exit_status);
	else if (ft_strcmp(tab_token[0], "exit") == 0 && !tab_token[1])
	{
		ft_free_tab(tab_token);
		g_exit_status = 0;
	}
	else if (ft_strcmp(tab_token[0], "exit") == 0 && ft_isdigit(tab_token[1]))
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		if (ft_atoi(tab_token[1]) >= 0)
			g_exit_status = ft_atoi(tab_token[1]) % 256;
		else
			g_exit_status = 256 - ((ft_atoi(tab_token[1]) * -1) % 256);
		ft_free_tab(tab_token);
	}
	close_backup(cmd);
	ft_free_token_list(list);
	ft_free_pipefds(cmd);
	exit(g_exit_status);
}
