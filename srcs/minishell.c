/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 14:05:21 by opacaud           #+#    #+#             */
/*   Updated: 2021/11/01 09:57:30 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

char	*ft_getstr_env_arg(char *line, int *ptr_i)
{
	int		counter;
	char	*str;
	int		start;
	int		j;

	start = *ptr_i;
	counter = ft_count_till_sep_env(line, ptr_i);
	(*ptr_i)--;
	str = (char *)malloc(sizeof(char) * (counter + 1));
	if (str == 0)
		return (0);
	j = -1;
	while (++j < counter)
		str[j] = line[start + j];
	str[j] = '\0';
	return (str);
}

void	ft_env_in_cmd(t_env *env, t_cmd *cmd)
{
	if (!cmd)
		return ;
	while (cmd)
	{
		cmd->env = env;
		cmd = cmd->next;
	}
}

void	ft_launch(t_token *list, t_env *env, char *line, char **our_env_array)
{
	int		nb_pipes;
	t_cmd	*cmd;

	nb_pipes = 0;
	cmd = NULL;
	cmd = create_cmds(list);
	ft_env_in_cmd(env, cmd);
	nb_pipes = ft_count_pipes(list);
	ft_create_nb_pipes(cmd, nb_pipes, our_env_array);
	if (ft_count_pipes(list) == 0)
	{
		g_exit_status = ft_simple_cmd(cmd, list, &env);
		if (g_exit_status == -3)
			g_exit_status = 1;
	}
	else
		g_exit_status = ft_pipes(list, env, cmd);
	ft_free_everything(list, cmd, line);
}

void	ft_prelaunch(char *line, t_env *env, char **our_env_array)
{
	int		i;
	t_token	*list;

	i = 0;
	list = ft_make_first_token(line, &i, env);
	if (list)
	{
		ft_add_tokens(list, line, &i);
		if (ft_clean_tokens(list, env) == -1)
		{
			ft_putstr_fd("syntax error\n", STDERR_FILENO);
			ft_free_token_list(list);
			g_exit_status = 2;
			return ;
		}
		if (ft_strlen(list->str) == 0 && list->token_id == ARG)
		{
			ft_free_token_list(list);
			return ;
		}
		ft_launch(list, env, line, our_env_array);
	}
	else
		free(line);
}
