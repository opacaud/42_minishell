/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 13:49:39 by cboutier          #+#    #+#             */
/*   Updated: 2021/11/01 09:29:01 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	signal_handler2(int signal)
{
	if (signal == SIGINT && g_exit_status == 147258369)
	{
		write(STDOUT_FILENO, "\b\b  \b\b", 6);
		close(STDIN_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		g_exit_status = 130;
	}
	else if (signal == SIGQUIT && g_exit_status == 123456789)
	{
		write(STDERR_FILENO, "Quit: 3\n", 8);
		g_exit_status = 131;
	}
	else if (signal == SIGQUIT)
		write(STDOUT_FILENO, "\b\b  \b\b", 6);
}

void	signal_handler(int signal)
{
	if (signal == SIGINT && g_exit_status != 123456789
		&& g_exit_status != 147258369 && g_exit_status != 741852963)
	{
		write(STDOUT_FILENO, "\b\b  \b\b", 6);
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_status = 130;
	}
	else if (signal == SIGINT && g_exit_status == 123456789)
	{
		write(STDOUT_FILENO, "\b\b  \b\b", 6);
		rl_on_new_line();
		rl_replace_line("", 0);
		g_exit_status = 130;
	}
	else
		signal_handler2(signal);
}

void	ft_exit_empty_line(void)
{
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	exit (0);
}
