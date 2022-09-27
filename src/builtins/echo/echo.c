/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 17:43:14 by adben-mc          #+#    #+#             */
/*   Updated: 2022/08/26 22:59:59 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	echo_n(char *str)
{
	int	i;

	i = 0;
	if (ft_strncmp(str, "-n", 2))
		return (0);
	while (str[++i])
		if (str[i] != 'n')
			return (0);
	return (1);
}

int	builtin_echo(t_data *data, t_token *token)
{
	int	i;
	int	s;

	i = 1;
	s = 0;
	while (token->str_split[i] && echo_n(token->str_split[i]))
	{
		i++;
		s = 1;
	}
	while (token->str_split[i])
	{
		if (i < ft_strslen(token->str_split) - 1)
			ft_printf("%s ", token->str_split[i++]);
		else
			ft_printf("%s", token->str_split[i++]);
	}
	if (!s)
		ft_printf("\n");
	return ((void)data, 0);
}
