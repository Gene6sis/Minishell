/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 17:43:14 by adben-mc          #+#    #+#             */
/*   Updated: 2022/08/17 03:31:40 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_exit_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == '+' || str[i] == '-'))
		i++;
	while (str[i] && ft_isdigit(str[i]))
		i++;
	if (str[i])
		return (1);
	return (0);
}

int	builtin_exit(t_data *data, t_token *token, int parent)
{
	int				i;
	unsigned char	code;

	i = 0;
	if (parent)
		ft_putstr_fd("exit\n", 2);
	if (ft_strslen(token->str_split) == 1)
		return (free_trash(data), exit(g_sig), g_sig);
	while (token->str_split[++i])
	{
		if (i > 1)
			return (ft_putstr_fd("exit: too many arguments\n", 2), 1);
		if (check_exit_numeric(token->str_split[i]))
			return (ft_putstr_fd("exit: numeric argument required\n", 2),
				free_trash(data), exit(2), 0);
	}
	code = ft_atoi(token->str_split[1]);
	return (free_trash(data), exit((int)code), 0);
}
