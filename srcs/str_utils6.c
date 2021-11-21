/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils6.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 12:12:21 by cboutier          #+#    #+#             */
/*   Updated: 2021/10/05 16:07:23 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	ft_get_size_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab || !tab[0])
		return (0);
	while (tab[i])
		i++;
	return (i);
}

int	ft_is_redir(char *str)
{
	if (!str || ft_strcmp(str, ">") == 0 || ft_strcmp(str, ">>") == 0
		|| ft_strcmp(str, "<") == 0 || ft_strcmp(str, "<<") == 0)
		return (1);
	return (0);
}

int	ft_env_name_has_space(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (str[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}

int	ft_has_space(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}

int	ft_start_with_slash(char *str)
{
	if (str[0] == '/')
	{
		ft_export_error(str, NULL);
		g_exit_status = 1;
		return (g_exit_status);
	}
	return (0);
}
