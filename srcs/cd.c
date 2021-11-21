/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 17:32:33 by cboutier          #+#    #+#             */
/*   Updated: 2021/10/29 16:10:40 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	cd_home(t_env *env)
{
	char	*tmp;

	tmp = ft_getenv("HOME", env);
	if (!tmp)
	{
		g_exit_status = 1;
		ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
	}
	else if (chdir(tmp) == -1 && ft_is_in_env(env) == 0)
	{
		g_exit_status = 1;
		ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
	}
	else if (g_exit_status == -1 && ft_is_in_env(env) == 1)
		g_exit_status = 0;
	free(tmp);
}

void	cd_home3(char **tab)
{
	int	i;

	i = 2;
	while (tab[i])
	{
		if (chdir(tab[i]) == -1)
			chdir_err(tab);
		i++;
	}
}

int	cd_home2(t_env *env, char **tab)
{
	char	*tmp1;
	char	*tmp2;

	tmp2 = ft_getenv("HOME", env);
	if (chdir(tmp2) == -1)
	{
		free (tmp2);
		return (set_g_exit_status(1, tab[1]));
	}
	free(tmp2);
	tmp2 = ft_strtrim(tab[1], '~');
	tmp1 = ft_strtrim(tmp2, '/');
	if (chdir(tmp1) == -1)
	{
		free(tmp1);
		free(tmp2);
		return (set_g_exit_status(1, tab[1]));
	}
	cd_home3(tab);
	free(tmp1);
	free(tmp2);
	return (0);
}

void	cd_old_pwd(t_env *env)
{
	char	*tmp;

	tmp = ft_getenv("OLDPWD", env);
	if (chdir(tmp) == -1)
	{
		g_exit_status = 1;
		ft_putstr_fd("cd: OLDPWD not set\n", STDERR_FILENO);
	}
	else
		get_pwd();
	free(tmp);
}

int	ft_cd(t_token *list, t_env *env)
{
	char	**tab;
	char	*old;

	tab = lst_to_array(list);
	if (ft_get_size_tab(tab) > 2)
	{
		ft_putstr_fd("cd : too many arguments\n", STDERR_FILENO);
		ft_free_tab(tab);
		return (1);
	}
	old = ft_getenv("PWD", env);
	if (!tab[1] || ft_strcmp("~", tab[1]) == 0)
		cd_home(env);
	else if (ft_strcmp("-", tab[1]) == 0)
		cd_old_pwd(env);
	else if (tab[1][0] == '~' && ft_strlen(tab[1]) > 1)
		cd_home2(env, tab);
	else
		if (chdir(tab[1]) == -1)
			chdir_err(tab);
	if (g_exit_status == 0)
		ft_update_pwd(old, env);
	ft_free_tab(tab);
	free(old);
	return (g_exit_status);
}
