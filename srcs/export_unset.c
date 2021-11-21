/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 11:35:37 by cboutier          #+#    #+#             */
/*   Updated: 2021/10/27 10:42:07 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

char	*ft_fill_res(char *res, char *str, int counter)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] == ' ')
		i++;
	while (j <= counter)
	{
		if (!(str[i] == ' ' && str[i + 1] == ' '))
		{
			res[j] = str[i];
			j++;
		}
		i++;
	}
	res[j] = '\0';
	return (res);
}

char	*ft_clean_env_value(char *str)
{
	char	*res;
	int		i;
	int		counter;

	i = 0;
	counter = 0;
	if (!str)
		return (0);
	while (str[i] == ' ')
		i++;
	if (str[i] && str[i + 1])
	{
		while (str[i + 1])
		{
			if (!(str[i] == ' ' && str[i + 1] == ' '))
				counter++;
			i++;
		}
	}
	res = malloc(sizeof(char) * (counter + 2));
	if (!res)
		return (NULL);
	return (ft_fill_res(res, str, counter));
}

void	ft_export_env2(char **tab_token, t_env **env, int *i, char *name)
{
	char	*value;
	char	*tmp;

	value = ft_find_env_value(tab_token[*i]);
	tmp = ft_getenv(name, *env);
	if (tmp)
		ft_change_env_value(name, value, *env);
	else
	{
		if (*env)
			ft_env_add_back(env, name, value);
		else
			*env = new_env_elem(name, value);
	}
	free(tmp);
}

int	ft_export_env(t_env **env, char **tab_token, int i)
{
	char	*name;

	if (!tab_token || ft_get_size_tab(tab_token) < 2)
		return (0);
	if (ft_strlen(tab_token[i]) == 0)
		return (ft_export_error(tab_token[i], NULL));
	name = ft_find_env_name(tab_token[i], *env);
	if (!name)
	{
		if (ft_check_name(tab_token[i]) == 0)
			return (ft_export_error(tab_token[i], NULL));
	}
	else
	{
		if ((ft_check_name(name) == 0 || !ft_strchr(tab_token[i], '=')))
		{
			free(name);
			return (ft_export_error(tab_token[i], NULL));
		}
		else
			ft_export_env2(tab_token, env, &i, name);
	}
	return (g_exit_status);
}

int	ft_unset_env(t_env *env, char **tab_token)
{
	int		i;
	t_env	*first;
	char	*tmp;

	i = 1;
	first = env;
	while (tab_token[i])
	{
		env = first;
		while (env && env->next)
		{
			tmp = ft_strtrim(env->next->name, '=');
			if (ft_strcmp(tab_token[i], tmp) == 0)
				ft_env_delnext(env);
			if (env->next)
				env = env->next;
			free(tmp);
		}
		i++;
	}
	return (0);
}
