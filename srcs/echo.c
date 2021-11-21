/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 09:45:19 by cboutier          #+#    #+#             */
/*   Updated: 2021/10/29 16:12:42 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	ft_echo_home(t_env *env)
{
	char	*home;

	home = NULL;
	home = ft_getenv("HOME", env);
	ft_putstr_fd(home, STDOUT_FILENO);
	free(home);
}

void	ft_print_spaces_before_after(t_token *list)
{
	if (list->token_id == D_QUOTE && ft_strlen(list->str) == 0
		&& list->next->token_id == ENV && list->next->env_in_dq_trad == 2)
		ft_putstr_fd(" ", STDOUT_FILENO);
	if (list->str)
		ft_putstr_fd(list->str, STDOUT_FILENO);
	if (list->next->token_id == D_QUOTE && ft_strlen(list->next->str) == 0
		&& list->token_id == ENV && list->env_in_dq_trad == 2)
		ft_putstr_fd(" ", STDOUT_FILENO);
}

t_token	*ft_echo2(t_token *list, t_token **tmp, t_env *env)
{
	if (ft_strcmp(list->str, "$?") == 0)
	{
		ft_putnbr_fd(g_exit_status, STDOUT_FILENO);
		*tmp = list;
	}
	else if (ft_strcmp(list->str, "~") == 0)
		ft_echo_home(env);
	else if (!((ft_strcmp(list->str, " ") == 0
				&& ft_strcmp(list->next->str, " ") == 0)
			|| (list->str == 0 && ft_strcmp(list->next->str, " ") == 0)
			|| (list->str == 0 && list->next->str == 0)
			|| (ft_strcmp(list->str, " ") == 0
				&& list->next->token_id == S_GREATER)
			|| (ft_strcmp(list->str, " ") == 0
				&& list->next->token_id == D_GREATER)
			|| (ft_strcmp(list->str, " ") == 0
				&& list->next->token_id == D_LESS)
			|| (ft_strcmp(list->str, " ") == 0
				&& list->next->token_id == PIPE)))
	{
		ft_print_spaces_before_after(list);
		*tmp = list;
	}
	return (list);
}

t_token	*echo(t_token *list, t_env *env)
{
	t_token	*tmp;

	tmp = NULL;
	while (list && list->next && list->token_id != S_LESS
		&& list->token_id != D_LESS && list->token_id != S_GREATER
		&& list->token_id != D_GREATER && list->token_id != PIPE)
	{
		list = ft_echo2(list, &tmp, env);
		list = list->next;
		if (list->token_id == PIPE)
			return (list);
	}
	if (tmp)
		if (tmp->next)
			if (tmp->next->next)
				return (ft_second_echo_loop(tmp->next));
	return (list);
}

int	ft_echo(t_token *list, t_env *env)
{
	int	n;

	n = 0;
	if (!list)
		return (0);
	while (list && list->token_id != PIPE)
	{
		while (list && ft_strcmp(list->str, "echo") != 0)
			list = list->next;
		if (list && ft_strcmp(list->str, "echo") == 0 && !list->next->next)
			return (ft_putstr_fd("\n", STDOUT_FILENO));
		else if (list && ft_strcmp(list->str, "echo") == 0)
			list = list->next->next;
		if (list && list->str && ft_is_redir(list->str) && list->next)
			list = ft_go_forward(list);
		if (list && list->str)
			list = ft_echo_n(list, &n);
		if (list)
			list = echo(list, env);
		if (list && list->token_id != PIPE && list->next)
			list = list->next;
	}
	if (n == 0)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
