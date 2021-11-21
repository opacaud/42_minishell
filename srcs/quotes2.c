/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 14:45:14 by cboutier          #+#    #+#             */
/*   Updated: 2021/09/29 14:45:44 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

char	*ft_res_without_quotes(int counter, char *str, char quote)
{
	char	*res;
	int		i;
	int		j;

	res = malloc(sizeof(char) * (counter + 1));
	if (res == 0)
		return (0);
	i = 0;
	j = 0;
	while (str[i + j])
	{
		if (str[i + j] != quote)
		{
			res[j] = str[i + j];
			j++;
		}
		else
			i++;
	}
	res[j] = '\0';
	return (res);
}
