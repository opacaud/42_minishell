/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 17:10:31 by cboutier          #+#    #+#             */
/*   Updated: 2021/10/28 17:10:50 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	ft_where_is_env(char *line, int i)
{
	if (!line)
		return (-1);
	while (line[i] && line[i] != '$')
		i++;
	if (!line)
		return (-1);
	return (i);
}

void	ft_get_env_in_heredoc(int *j, char *line, t_cmd *cmd, int fd)
{
	int		pos;
	char	*tmp1;
	char	*tmp2;

	pos = -1;
	tmp1 = NULL;
	tmp2 = NULL;
	pos = ft_where_is_env(line, *j);
	if (pos >= 0)
	{
		while (*j < pos)
		{
			write(fd, &line[*j], 1);
			(*j)++;
		}
		tmp1 = ft_getstr_env_arg(line, j);
		tmp2 = ft_strtrim(tmp1, '$');
		free(tmp1);
		tmp1 = ft_getenv(tmp2, cmd->env);
		free(tmp2);
		ft_putstr_fd(tmp1, fd);
		free(tmp1);
	}
}

void	ft_env_in_heredoc(char *line, int fd, t_cmd *cmd)
{
	int		j;

	if (ft_has_env(line))
	{
		j = 0;
		while (line[j])
		{
			ft_get_env_in_heredoc(&j, line, cmd, fd);
			j++;
		}
		write(fd, "\n", 1);
	}
	else
		ft_putendl_fd(line, fd);
	close_me(fd);
}
