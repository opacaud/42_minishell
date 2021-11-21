/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 12:02:45 by cboutier          #+#    #+#             */
/*   Updated: 2021/10/06 09:54:14 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	ft_count_pipes(t_token *list)
{
	int	counter;

	counter = 0;
	if (!list)
		return (0);
	while (list)
	{
		if (list->token_id == PIPE)
			counter++;
		list = list->next;
	}
	return (counter);
}

char	*ft_get_cmd(char *arg)
{
	int		counter;
	int		i;
	char	*cmd;

	counter = 0;
	while (arg[counter] && arg[counter] != ' ')
		counter++;
	cmd = malloc(sizeof(char) * (counter + 1));
	if (!cmd)
		return (0);
	i = 0;
	while (i < counter)
	{
		cmd[i] = arg[i];
		i++;
	}
	cmd[i] = '\0';
	return (cmd);
}

int	ft_is_a_cmd(char *str, t_env **env)
{
	char	*path;

	path = NULL;
	if (is_builtin(str) || check_path(*env, str, &path))
	{
		free (path);
		return (1);
	}
	free (path);
	return (0);
}

int	ft_count_chevrons(t_token *list)
{
	int	counter;

	counter = 0;
	while (list)
	{
		if (list->token_id == S_LESS || list->token_id == D_LESS
			|| list->token_id == S_GREATER || list->token_id == D_GREATER)
			counter++;
		list = list->next;
	}
	return (counter);
}
