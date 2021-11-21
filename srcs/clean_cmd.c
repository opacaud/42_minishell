/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 12:03:26 by cboutier          #+#    #+#             */
/*   Updated: 2021/10/29 11:41:15 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	ft_has_dash(char *str)
{
	int	i;

	if (!str || ft_strlen(str) < 2)
		return (0);
	i = 1;
	while (str[i])
	{
		if (str[i] == '-')
			return (1);
		i++;
	}
	return (0);
}

int	ft_count_spaces(char **str)
{
	int	i;
	int	j;
	int	counter;

	if (!str)
		return (0);
	counter = 0;
	i = 0;
	while (str[i])
	{
		j = 1;
		if (ft_strlen(str[i]) > 1)
		{
			while (str[i][j])
			{
				if (str[i][j] == ' ')
					counter++;
				j++;
			}
		}
		i++;
	}
	return (counter);
}

void	dup_and_incr(char *arg, char **res, int *k)
{
	*res = ft_strdup(arg);
	(*k)++;
}

void	ft_clean_cmd2(char **arg, char **res)
{
	int		i;
	int		j;
	int		k;
	char	**tmp;

	i = -1;
	k = 0;
	while (arg[++i])
	{
		if (ft_has_dash(arg[i]) == 0)
			dup_and_incr(arg[i], &res[k], &k);
		else
		{
			tmp = ft_split(arg[i], ' ');
			j = -1;
			while (tmp[++j])
			{
				res[k] = ft_strdup(tmp[j]);
				k++;
			}
			ft_free_tab(tmp);
		}
	}
	res[k] = 0;
}

void	ft_clean_cmd(t_cmd *cmd)
{
	int		size;
	int		options;
	char	**tmp;

	tmp = NULL;
	size = 0;
	options = 0;
	while (cmd)
	{
		if (cmd->arg)
		{
			size = ft_get_size_tab(cmd->arg);
			options = ft_count_spaces(cmd->arg);
			tmp = malloc(sizeof(char *) * (size + options + 1));
			if (tmp == 0)
				return ;
			ft_clean_cmd2(cmd->arg, tmp);
			ft_free_tab(cmd->arg);
			cmd->arg = tmp;
		}
		cmd = cmd->next;
	}
}
