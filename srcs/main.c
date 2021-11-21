/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 16:17:45 by cboutier          #+#    #+#             */
/*   Updated: 2021/10/29 16:17:54 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	main_loop(t_env *env)
{
	char	*line;
	char	**our_env_array;

	our_env_array = NULL;
	our_env_array = env_to_array(env);
	while (1)
	{
		line = readline("\033[34;1mminishell > \033[0m");
		if (!line)
			ft_exit_empty_line();
		else if (ft_strlen(line) == 0)
		{
			free(line);
			continue ;
		}
		add_history(line);
		if (is_quote_closed(line) == 0)
		{
			free(line);
			ft_putstr_fd("syntax error: quotes not closed\n", STDERR_FILENO);
			g_exit_status = 1;
			continue ;
		}
		ft_prelaunch(line, env, our_env_array);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_env	*env;

	(void)av;
	if (ac != 1)
		return (0);
	g_exit_status = 0;
	env = create_env_lst(envp);
	if (!env)
		return (0);
	if (signal(SIGINT, signal_handler) == SIG_ERR)
		exit(1);
	if (signal(SIGQUIT, signal_handler) == SIG_ERR)
		exit(1);
	main_loop(env);
	ft_free_env_list(env);
	return (g_exit_status);
}
