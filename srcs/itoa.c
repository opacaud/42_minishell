/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 09:57:52 by cboutier          #+#    #+#             */
/*   Updated: 2021/09/14 09:59:07 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

static int	ft_size(int n)
{
	int		size;
	long	nb;

	nb = n;
	size = 1;
	if (nb < 0)
	{
		size++;
		nb = -nb;
	}
	while (nb >= 10)
	{
		size++;
		nb = nb / 10;
	}
	return (size);
}

char	*ft_itoa(int nb)
{
	char	*str;
	long	nbr;
	int		i;

	i = 1;
	str = malloc(sizeof(char) * ft_size(nb) + 1);
	if (!str)
		return (NULL);
	if (nb < 0)
		str[0] = '-';
	nbr = nb;
	if (nbr < 0)
		nbr = -nbr;
	str[ft_size(nb)] = '\0';
	while (nbr >= 10)
	{
		str[ft_size(nb) - i] = (nbr % 10) + 48;
		nbr = nbr / 10;
		i++;
	}
	str[ft_size(nb) - i] = (nbr % 10) + 48;
	return (str);
}
