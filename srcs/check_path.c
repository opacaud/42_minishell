/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 10:50:40 by cboutier          #+#    #+#             */
/*   Updated: 2021/10/29 16:10:43 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	is_builtin(char *str)
{
	if (!str)
		return (0);
	if (ft_strcmp(str, "echo") == 0 || ft_strcmp(str, "export") == 0
		|| ft_strcmp(str, "unset") == 0 || ft_strcmp(str, "cd") == 0
		|| ft_strcmp(str, "env") == 0 || ft_strcmp(str, "pwd") == 0
		|| ft_strcmp(str, "exit") == 0)
		return (1);
	else
		return (0);
}

char	**ft_get_path(t_env *env)
{
	char	**paths;

	paths = NULL;
	if (!env)
		return (0);
	while (env)
	{
		if (ft_strncmp(env->name, "PATH=", 5) == 0)
		{
			paths = ft_split(env->value, ':');
			if (paths == NULL)
				return (0);
			break ;
		}
		env = env->next;
	}
	return (paths);
}

int	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (0);
	while (tab[i])
	{
		if (tab[i])
		{
			free(tab[i]);
			tab[i] = NULL;
			i++;
		}
	}
	free(tab);
	tab = NULL;
	return (0);
}

int	check_path(t_env *env, char *str, char **res)
{
	char	**paths;
	char	*tmp;
	int		i;

	i = 0;
	if (str == NULL || ft_strlen(str) == 0 || ft_strcmp(str, "..") == 0)
		return (127);
	paths = ft_get_path(env);
	if (!paths)
		return (print_file_error(NULL));
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		free(paths[i]);
		paths[i] = ft_strjoin(tmp, str);
		free(tmp);
		if (access(paths[i], F_OK) == 0)
		{
			*res = ft_strdup(paths[i]);
			ft_free_tab(paths);
			return (1);
		}
		i++;
	}
	return (ft_free_tab(paths));
}
