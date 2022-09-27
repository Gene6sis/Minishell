/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthimoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 16:08:39 by nthimoni          #+#    #+#             */
/*   Updated: 2022/08/18 16:25:40 by nthimoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*delete_quotes(char *str)
{
	int		i;
	char	del;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			del = str[i];
			ft_memmove(str + i, str + i + 1, ft_strlen(str + i + 1) + 1);
			while (str[i] && str[i] != del)
				i++;
			if (str[i] == del)
				ft_memmove(str + i, str + i + 1, ft_strlen(str + i + 1) + 1);
		}
		else
			i++;
	}
	return (str);
}
