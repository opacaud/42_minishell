/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lst_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 15:28:50 by cboutier          #+#    #+#             */
/*   Updated: 2021/10/29 16:20:00 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

t_cmd	*new_cmd_elem(char **arg, char **redir)
{
	t_cmd	*elem;

	if (!arg && !redir)
		return (NULL);
	elem = malloc(sizeof(t_cmd));
	if (!elem)
		return (NULL);
	elem->next = 0;
	if (arg)
		elem->arg = arg;
	else
		elem->arg = NULL;
	if (redir)
		elem->redir = redir;
	else
		elem->redir = NULL;
	elem->backup_stdin = -1;
	elem->backup_stdout = -1;
	elem->nb_pipes = 0;
	elem->our_env_array = NULL;
	elem->pipefds = NULL;
	elem->pid = NULL;
	elem->env = NULL;
	elem->path = NULL;
	return (elem);
}

t_cmd	*ft_cmd_last(t_cmd *cmd)
{
	t_cmd	*elem;

	if (cmd == NULL)
		return (NULL);
	elem = cmd;
	while (elem->next != NULL)
		elem = elem->next;
	return (elem);
}

void	ft_cmd_add_back(t_cmd **cmd, char **arg, char **redir)
{
	t_cmd	*elem;

	if (cmd)
	{
		if (*cmd)
		{
			elem = ft_cmd_last(*cmd);
			elem->next = new_cmd_elem(arg, redir);
		}
		else
			*cmd = new_cmd_elem(arg, redir);
	}
}

int	ft_cmd_delnext(t_cmd *list)
{
	t_cmd	*tmp;
	int		i;

	if (!list)
		return (0);
	if (list)
	{
		tmp = list->next;
		if (list->next->next)
			list->next = list->next->next;
		else
			list->next = NULL;
		i = 0;
		while (tmp->arg[i])
		{
			free(tmp->arg[i]);
			i++;
		}
		free(tmp->arg);
		free(tmp);
	}
	tmp = NULL;
	return (0);
}

int	cmd_lst_size(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return (0);
	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}

// void	ft_print_cmd_lst(t_cmd *cmd)
// {
// 	int	i;
// 	int	j;

// 	j = 0;
// 	if (!cmd)
// 		return ;
// 	while (cmd != 0)
// 	{
// 		i = 0;
// 		printf("-------------------------------------\n");
// 		if (cmd->arg)
// 		{
// 			while (cmd->arg[i])
// 			{
// 				printf("node %d ==>\tcmd->arg[%d] : [%s]\n", j, i, cmd->arg[i]);
// 				i++;
// 			}
// 		}
// 		if (cmd->redir)
// 		{
// 			i = 0;
// 			while (cmd->redir[i])
// 			{
// 				printf("node %d ==>\tcmd->redir[%d] :
//				[%s]\n", j, i, cmd->redir[i]);
// 				i++;
// 			}
// 		}
// 		printf("\t\tcmd->nb_pipes : %d\n", cmd->nb_pipes);
// 		cmd = cmd->next;
// 		j++;
// 	}
// }
