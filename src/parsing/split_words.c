/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 23:29:01 by adben-mc          #+#    #+#             */
/*   Updated: 2022/08/13 01:09:08 by nthimoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	in_quote(char const *str, int pos)
{
	int	quoted;
	int	i;

	i = 0;
	quoted = 0;
	while (i <= pos && str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (quoted == 0)
				quoted = (int)str[i];
			else if (quoted == str[i])
				quoted = 0;
		}
		i++;
	}
	return (quoted);
}

static int	ft_len(char const *str)
{
	unsigned int	i;
	unsigned int	compt;

	i = 0;
	compt = 0;
	while (str[i])
	{
		while (str[i] == ' ' && !in_quote(str, i) && str[i])
			i++;
		while (!(str[i] == ' ' && !in_quote(str, i)) && str[i])
		{
			i++;
			compt++;
		}
	}
	return (compt);
}

static int	ft_elements(char const *str)
{
	unsigned int	i;
	unsigned int	compt;

	i = 0;
	compt = 0;
	while (str[i])
	{
		while (str[i] == ' ' && !in_quote(str, i) && str[i])
			i++;
		if (!(str[i] == ' ' && !in_quote(str, i)) && str[i])
			compt++;
		while (!(str[i] == ' ' && !in_quote(str, i)) && str[i])
			i++;
	}
	return (compt);
}

int	ft_null(char ***result, t_data *data)
{
	if (ft_strslen(*result))
		return (1);
	*result = malloc(sizeof(char *) * 2);
	if (!*result)
		return (0);
	ft_addtotrash(data, *result);
	(*result)[0] = "";
	(*result)[1] = NULL;
	return (1);
}

char	**ft_split_words(char const *s, t_data *data)
{
	char			**result;
	int				i;
	unsigned int	j;
	unsigned int	x;

	result = malloc(sizeof(char *) * (ft_elements(s) + 1));
	if (!s || !result)
		return (0);
	ft_addtotrash(data, result);
	i = 0;
	x = 0;
	while (i < ft_elements(s))
	{
		j = 0;
		result[i] = malloc(sizeof(char) * (ft_len(&s[x]) + 1));
		if (!result[i])
			return (0);
		ft_addtotrash(data, result[i]);
		while (s[x] == ' ' && !in_quote(s, x) && s[x])
			x++;
		while (!(s[x] == ' ' && !in_quote(s, x)) && s[x])
			result[i][j++] = s[x++];
		result[i++][j] = '\0';
	}
	return (result[i] = 0, ft_null(&result, data), result);
}
