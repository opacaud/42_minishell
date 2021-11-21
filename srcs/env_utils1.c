/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 14:03:33 by cboutier          #+#    #+#             */
/*   Updated: 2021/10/29 16:12:55 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	ft_change_env_value(char *name, char *value, t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->name, name) == 0)
		{
			free(env->value);
			env->value = value;
		}
		env = env->next;
	}
	free (name);
}

int	ft_calculate_pos(char *tab_token)
{
	int	i;

	i = 0;
	while (tab_token[i])
	{
		if (tab_token[i] != '=')
			i++;
		else
			return (i);
	}
	return (-1);
}

int	ft_check_export_name2(char *tab_token)
{
	char	*trimmed_tab;
	int		pos;

	trimmed_tab = NULL;
	pos = -1;
	pos = ft_calculate_pos(tab_token);
	if (pos >= 0)
	{
		trimmed_tab = malloc(sizeof(char) * (pos + 2));
		if (!trimmed_tab)
			return (0);
		trimmed_tab = ft_strncpy(tab_token, trimmed_tab, pos);
		if (ft_check_name(trimmed_tab) == 0)
			return (ft_export_error(tab_token, trimmed_tab));
		free(trimmed_tab);
	}
	return (0);
}

int	ft_check_export_name(char *tab_token)
{
	int		ret;

	ret = 0;
	if (!tab_token)
		return (0);
	ret = ft_check_export_name2(tab_token);
	return (ret);
}

void	ft_env_join(t_token *list, int *joined)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = list->str;
	tmp2 = ft_strjoin(tmp1, list->next->str);
	list->str = ft_strdup(tmp2);
	if (list->str)
		ft_lstdelnext(list);
	if (tmp1 && ft_strcmp(tmp1, tmp2) != 0)
		free(tmp1);
	if (tmp2)
		free(tmp2);
	*joined = 1;
}
