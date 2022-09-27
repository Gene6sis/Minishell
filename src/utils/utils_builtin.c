/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 04:09:55 by adben-mc          #+#    #+#             */
/*   Updated: 2022/08/17 03:38:04 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// **
// Builtin 
// **

// status == 1 // out child
// status == 0 // in child
int	builtins(t_token *token, t_data *data, int parent)
{
	if (!ft_strcmp(token->str_split[0], "echo"))
		return (builtin_echo(data, token));
	else if (!ft_strcmp(token->str_split[0], "cd"))
		return (builtin_cd(data, token));
	else if (!ft_strcmp(token->str_split[0], "pwd"))
		return (builtin_pwd(data, token));
	else if (!ft_strcmp(token->str_split[0], "export"))
		return (builtin_export(data, token, parent));
	else if (!ft_strcmp(token->str_split[0], "unset"))
		return (builtin_unset(data, token));
	else if (!ft_strcmp(token->str_split[0], "env"))
		return (builtin_env(data, token));
	else if (!ft_strcmp(token->str_split[0], "exit"))
		return (builtin_exit(data, token, parent));
	return (-42);
}
