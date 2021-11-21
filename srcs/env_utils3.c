/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 14:55:35 by cboutier          #+#    #+#             */
/*   Updated: 2021/10/29 16:30:03 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

char	*ft_getenv(char *str, t_env *env)
{
	char	*tmp;
	int		joined;

	tmp = NULL;
	joined = 0;
	if (!str)
		return (0);
	if (ft_strlen(str) > 0 && str[ft_strlen(str) - 1] != '=')
	{
		tmp = ft_charjoin(str, '=');
		joined = 1;
	}
	while (env)
	{
		if ((ft_strcmp(env->name, tmp) == 0 && joined == 1)
			|| (ft_strcmp(env->name, str) == 0 && joined == 0))
		{
			free (tmp);
			return (ft_strdup(env->value));
		}
		env = env->next;
	}
	free (tmp);
	return (0);
}

char	*ft_find_env_value(char *str)
{
	int		i;
	char	*res;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '=')
		i++;
	i++;
	res = ft_strdup(str + i);
	return (res);
}

char	*ft_find_env_name2(char *str, char *res, int repere)
{
	free(res);
	ft_putstr_fd("export: `", STDERR_FILENO);
	ft_putstr_fd(str + repere, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	g_exit_status = 1;
	return (0);
}

int	ft_count_till_egal(char *str)
{
	int	counter;

	if (!str)
		return (0);
	counter = 0;
	while (str[counter] && str[counter] != '=')
		counter++;
	if (counter == ft_strlen(str))
		return (0);
	return (counter);
}

char	*ft_find_env_name(char *str, t_env *env)
{
	int		counter;
	char	*res;
	char	*tmp;

	counter = ft_count_till_egal(str);
	if (counter == 0 || !str)
		return (0);
	res = malloc(sizeof(char) * (counter + 2));
	if (!res)
		return (NULL);
	res = ft_strncpy(str, res, counter + 1);
	if (res[0] == '$')
	{
		tmp = ft_strtrim(res, '$');
		res = ft_getenv(tmp, env);
		if (!(res))
			return (ft_find_env_name2(str, res, counter));
		free(tmp);
		tmp = ft_strdup(res);
		free(res);
		res = ft_charjoin(tmp, '=');
		free(tmp);
	}
	return (res);
}
