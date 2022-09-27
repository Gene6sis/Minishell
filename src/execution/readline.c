/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 23:22:10 by adben-mc          #+#    #+#             */
/*   Updated: 2022/08/04 01:48:36 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Function that checks if a string is not only made of space
static int	ft_is_not_only_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n'
			&& str[i] != '\r' && str[i] != '\v' && str[i] != '\f')
			return (1);
		i++;
	}
	return (0);
}

void	ft_readlinehistory(t_data *data, char *input)
{
	char	*tmp;

	if (input && ft_is_not_only_spaces(input))
	{
		tmp = ft_strdup(input);
		add_history(tmp);
		ft_addtotrash(data, tmp);
	}
}
