/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_g_exit_status.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 11:30:38 by cboutier          #+#    #+#             */
/*   Updated: 2021/10/29 16:16:12 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	set_g_exit_status(int n, char *str)
{
	g_exit_status = n;
	if (str)
		perror(str);
	return (g_exit_status);
}

int	dup2_failed(void)
{
	ft_putstr_fd("dup2 failed\n", STDERR_FILENO);
	g_exit_status = 1;
	return (-1);
}

t_token	*cmd_failed(char *str)
{
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	free(str);
	g_exit_status = 127;
	return (0);
}

int	fork_failed(void)
{
	ft_putstr_fd("fork failed\n", STDERR_FILENO);
	return (1);
}
