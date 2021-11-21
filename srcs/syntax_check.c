/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 15:07:47 by cboutier          #+#    #+#             */
/*   Updated: 2021/10/21 16:27:33 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	ft_check_name(char *name)
{
	int	i;

	i = 0;
	if (!name)
		return (0);
	if (ft_isalpha(name[i]) == 0 && name[i] != '_')
		return (0);
	i++;
	while (name[i])
	{
		if ((ft_isalnum(name[i]) == 0 && name[i] != '_')
			&& (name[i] == '=' && i != (ft_strlen(name) - 1)))
			return (0);
		i++;
	}
	return (1);
}
