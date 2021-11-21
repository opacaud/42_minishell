/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 12:00:22 by cboutier          #+#    #+#             */
/*   Updated: 2021/10/29 11:41:43 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

t_token	*ft_fill_arg_redir(t_token *list, char **arg, char **redir, t_cmd *cmd)
{
	while (list)
	{
		while (list && list->token_id != PIPE)
			list = list->next;
		if (list && list->next)
		{
			while (list->token_id == PIPE || list->token_id == END_OF_ARG)
				list = list->next;
			arg = ft_create_arg(list);
			redir = ft_create_redir(list);
			if (redir && ft_get_size_tab(redir) > 2)
				arg = ft_second_check_arg(list, arg, redir);
			ft_cmd_add_back(&cmd, arg, redir);
		}
	}
	return (list);
}

t_cmd	*create_cmds(t_token *list)
{
	char	**arg;
	t_cmd	*cmd;
	char	**redir;

	redir = NULL;
	arg = NULL;
	cmd = NULL;
	arg = ft_create_arg(list);
	redir = ft_create_redir(list);
	if (redir && ft_get_size_tab(redir) > 2)
		arg = ft_second_check_arg(list, arg, redir);
	cmd = new_cmd_elem(arg, redir);
	list = ft_fill_arg_redir(list, arg, redir, cmd);
	ft_clean_cmd(cmd);
	return (cmd);
}

void	ft_create_nb_pipes(t_cmd *cmd, int nb_pipes, char **our_env_array)
{
	if (!cmd)
		return ;
	ft_env_array_in_cmd(cmd, our_env_array);
	while (cmd)
	{
		cmd->nb_pipes = nb_pipes;
		cmd = cmd->next;
	}
}
