/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execution_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 04:07:51 by adben-mc          #+#    #+#             */
/*   Updated: 2022/08/13 01:20:04 by nthimoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bultin_simple_command(t_data *data, t_list *lst)
{
	t_token	*token;

	if (ft_nb_partition(data) != 1 || !lst)
		return (0);
	token = lst->content;
	if (!token->str_split[0])
		return (-1);
	if (!ft_strcmp(token->str_split[0], "echo"))
		return (1);
	else if (!ft_strcmp(token->str_split[0], "cd"))
		return (1);
	else if (!ft_strcmp(token->str_split[0], "pwd"))
		return (1);
	else if (!ft_strcmp(token->str_split[0], "export"))
		return (1);
	else if (!ft_strcmp(token->str_split[0], "unset"))
		return (1);
	else if (!ft_strcmp(token->str_split[0], "env"))
		return (1);
	else if (!ft_strcmp(token->str_split[0], "exit"))
		return (1);
	return (0);
}
