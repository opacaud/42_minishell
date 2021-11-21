/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 10:37:27 by cboutier          #+#    #+#             */
/*   Updated: 2021/09/29 14:45:40 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

char	*ft_getstr_quote(char *line, int *ptr_i, char quote)
{
	int		counter;
	char	*str;
	int		start;
	int		j;

	(*ptr_i)++;
	start = *ptr_i;
	counter = 0;
	while (line[*ptr_i] && line[*ptr_i] != quote)
	{
		counter++;
		(*ptr_i)++;
	}
	str = (char *)malloc(sizeof(char) * (counter + 1));
	if (str == 0)
		return (0);
	j = 0;
	while (j < counter)
	{
		str[j] = line[start + j];
		j++;
	}
	str[j] = '\0';
	return (str);
}

int	ft_has_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

int	ft_go_through_quotes(char *str, int *i)
{
	char	quote;
	int		counter;
	int		ret;

	ret = 0;
	quote = 0;
	counter = 0;
	while (str[*i] && str[*i] != '\'' && str[*i] != '"')
		(*i)++;
	quote = str[*i];
	if (quote != 0)
	{
		counter++;
		(*i)++;
	}
	while (str[*i] && str[*i] != quote)
		(*i)++;
	if (str[*i] == quote)
		counter--;
	else if (!str[*i] && counter != 0)
		ret = -1;
	if (str[*i])
		(*i)++;
	return (ret);
}

int	is_quote_closed(char *str)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	if (!str)
		return (0);
	if (ft_has_quotes(str))
	{
		while (str[i])
			ret = ft_go_through_quotes(str, &i);
		if (ret < 0)
			return (0);
	}
	return (1);
}

char	*ft_delete_quotes(char *str, int token_id)
{
	int		i;
	char	quote;
	int		counter;

	i = 0;
	if (!str)
		return (0);
	if (token_id == D_QUOTE)
		quote = '"';
	else
		quote = '\'';
	counter = 0;
	while (str[i])
	{
		if (str[i] != quote)
			counter++;
		i++;
	}
	return (ft_res_without_quotes(counter, str, quote));
}
