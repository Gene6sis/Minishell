/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:16:31 by adben-mc          #+#    #+#             */
/*   Updated: 2021/11/30 23:35:50 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(char const *str, char charset)
{
	unsigned int	i;
	unsigned int	compt;

	i = 0;
	compt = 0;
	while (str[i])
	{
		while (str[i] == charset && str[i])
			i++;
		while (str[i] != charset && str[i])
		{
			i++;
			compt++;
		}
	}
	return (compt);
}

static int	ft_elements(char const *str, char charset)
{
	unsigned int	i;
	unsigned int	compt;

	i = 0;
	compt = 0;
	while (str[i])
	{
		while (str[i] == charset && str[i])
			i++;
		if (str[i] != charset && str[i])
			compt++;
		while (str[i] != charset && str[i])
			i++;
	}
	return (compt);
}

char	**ft_split(char const *s, char c)
{
	char			**result;
	int				i;
	unsigned int	j;
	unsigned int	x;

	result = malloc(sizeof(char *) * (ft_elements(s, c) + 1));
	if (!s || !result)
		return (0);
	i = 0;
	x = 0;
	while (i < ft_elements(s, c))
	{
		j = 0;
		result[i] = malloc(sizeof(char) * (ft_len(&s[x], c) + 1));
		if (!result[i])
			return (0);
		while (s[x] == c && s[x])
			x++;
		while (s[x] != c && s[x])
			result[i][j++] = s[x++];
		result[i++][j] = '\0';
	}
	result[i] = 0;
	return (result);
}

/*
#include <string.h>

int main(int argc, char **argv)
{
	char **result = ft_split((char const *)argv[1], argv[2][0]);
	int i;
	i=0;
	(void)argc;
	while (result[i])
	{
		printf("%d : '%s' || Sa taille : %ld\n", i, result[i], strlen(result[i]));
		i++;
	}
	printf("%d : '%s'\n", i, result[i]);
}
*/