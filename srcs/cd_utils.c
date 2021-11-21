/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 09:08:43 by cboutier          #+#    #+#             */
/*   Updated: 2021/10/14 10:04:13 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	ft_is_in_env(t_env *env)
{
	while (env)
	{
		if (ft_strcmp("HOME=", env->name) == 0)
			return (1);
		env = env->next;
	}
	return (0);
}

void	update_pwd_env(char *old, t_env *env, char *pwd, int i)
{
	while (env)
	{
		if (ft_strcmp("OLDPWD=", env->name) == 0)
		{
			free(env->value);
			env->value = ft_strdup(old);
		}
		if (ft_strcmp("PWD=", env->name) == 0)
		{
			free(env->value);
			env->value = ft_strdup(getcwd(pwd, i));
		}
		env = env->next;
	}
}

int	ft_update_pwd(char *old, t_env *env)
{
	char	*pwd;
	int		i;

	pwd = malloc(1);
	if (pwd == 0)
		return (0);
	i = 1;
	while (getcwd(pwd, i) == 0)
	{
		free(pwd);
		pwd = malloc(sizeof(char) * (i + 1));
		if (pwd == 0)
			return (0);
		i++;
	}
	free(pwd);
	pwd = malloc(sizeof(char) * (i + 1));
	if (pwd == 0)
		return (0);
	update_pwd_env(old, env, pwd, i);
	free (pwd);
	return (0);
}

void	chdir_err(char **tab)
{
	g_exit_status = 1;
	ft_putstr_fd(tab[0], STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	perror(tab[1]);
}
