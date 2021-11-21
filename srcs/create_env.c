/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 10:58:35 by cboutier          #+#    #+#             */
/*   Updated: 2021/10/29 16:22:26 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	ft_env2(t_env *env, char **tab_token, int *i)
{
	if (ft_strcmp(tab_token[0], "export") == 0 && tab_token[*i]
		&& (ft_strcmp(tab_token[*i], "") == 0
			|| ft_env_name_has_space(tab_token[*i]) == 1))
		ft_export_error(tab_token[*i], NULL);
	else if (ft_strcmp(tab_token[0], "unset") == 0 && (tab_token[*i]
			&& (ft_has_space(tab_token[*i]) == 1
				|| ft_strcmp(tab_token[*i], "") == 0
				|| ft_check_name(tab_token[*i]) == 0)))
		ft_unset_error(tab_token[*i], NULL);
	else if (ft_strcmp(tab_token[0], "unset") == 0 && tab_token[*i]
		&& ft_strcmp(tab_token[*i], " ") != 0)
		ft_unset_env(env, tab_token);
}

void	ft_env_invalid_option(char **tab_token)
{
	int	i;

	i = 0;
	g_exit_status = 2;
	ft_putstr_fd(tab_token[0], STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	while (tab_token[1][i] && tab_token[1][i] != '=')
	{
		ft_putchar_fd(tab_token[1][i], STDERR_FILENO);
		i++;
	}
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd("invalid option\n", STDERR_FILENO);
}

void	ft_env3(t_token *list)
{
	while (list)
	{
		if (ft_strlen(list->str) == 0 && list->token_id == D_QUOTE)
			g_exit_status = 1;
		list = list->next;
	}
}

void	ft_env4(t_token *list, t_env **env, char **tab_token)
{
	int	i;

	i = 1;
	while (tab_token[i])
	{
		if (ft_strcmp(tab_token[0], "export") == 0 && tab_token[i]
			&& ft_strlen(tab_token[i]) > 0
			&& ft_env_name_has_space(tab_token[i]) == 0)
		{
			if (ft_start_with_slash(tab_token[i]) != 0)
				break ;
			g_exit_status = ft_export_env(env, tab_token, i);
			ft_env3(list);
		}
		else
			ft_env2(*env, tab_token, &i);
		i++;
	}
}

int	ft_env(t_env **env, t_token *list, t_cmd *cmd)
{
	char	**tab_token;

	if (!list)
		return (0);
	tab_token = lst_to_array(list);
	if ((ft_strcmp(ft_tolower(cmd->arg[0]), "env") == 0 && !cmd->arg[1]))
		g_exit_status = ft_print_env_lst(*env, 0);
	else if (ft_strcmp(tab_token[0], "export") == 0
		&& !ft_strchr(tab_token[1], '=') && !tab_token[1])
		ft_print_env_lst(*env, 1);
	else if (ft_strcmp(tab_token[0], "export") == 0 && tab_token[1]
		&& tab_token[1][0] == '-')
	{
		ft_env_invalid_option(tab_token);
		ft_free_tab(tab_token);
		return (g_exit_status);
	}
	ft_env4(list, env, tab_token);
	ft_free_tab(tab_token);
	return (g_exit_status);
}
