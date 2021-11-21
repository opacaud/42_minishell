/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 17:21:46 by cboutier          #+#    #+#             */
/*   Updated: 2021/09/27 14:05:19 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	get_pwd(void)
{
	int		i;
	char	*pwd;

	pwd = malloc(1);
	if (pwd == 0)
		return (0);
	i = 1;
	while (getcwd(pwd, i) == 0)
	{
		free(pwd);
		pwd = malloc(sizeof(char) * (i + 1));
		if (pwd == 0)
			return (0);
		i++;
	}
	free(pwd);
	pwd = malloc(sizeof(char) * (i + 1));
	if (pwd == 0)
		return (0);
	if (!getcwd(pwd, i))
		return (set_g_exit_status(1, NULL));
	printf("%s\n", pwd);
	free (pwd);
	return (0);
}
