/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 15:49:03 by cboutier          #+#    #+#             */
/*   Updated: 2021/10/26 11:12:05 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	ft_print_export(char **env_tab)
{
	int	i;

	i = 0;
	while (env_tab[i])
	{
		ft_putstr_fd("export ", STDOUT_FILENO);
		ft_putstr_fd(env_tab[i], STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		i++;
	}
}

int	ft_print_env_lst(t_env *env, int n)
{
	char	**env_tab;

	if (!env)
		return (0);
	if (n == 1)
	{
		env_tab = env_to_array(env);
		ft_sort_tab(env_tab, ft_envsize(env));
		ft_print_export(env_tab);
		ft_free_tab(env_tab);
	}
	else
	{
		while (env)
		{
			printf("%s%s\n", env->name, env->value);
			env = env->next;
		}
	}
	return (0);
}

t_env	*ft_shlvl(t_env *env)
{
	char	*name;
	char	*value;

	name = ft_strdup("SHLVL=");
	value = ft_strdup("1");
	env = new_env_elem(name, value);
	return (env);
}

t_env	*create_env_lst(char **envp)
{
	int		i;
	char	*name;
	char	*value;
	t_env	*env;

	env = NULL;
	if (envp[0])
	{
		name = ft_find_env_name(envp[0], 0);
		value = ft_find_env_value(envp[0]);
		env = new_env_elem(name, value);
		i = 1;
		while (envp[i])
		{
			name = ft_find_env_name(envp[i], env);
			value = ft_find_env_value(envp[i]);
			ft_env_add_back(&env, name, value);
			i++;
		}
		return (env);
	}
	else
		return (ft_shlvl(env));
	return (0);
}
