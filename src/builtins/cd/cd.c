/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 17:37:32 by adben-mc          #+#    #+#             */
/*   Updated: 2022/08/18 03:19:36 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_var_pwd(t_data *data, char *path)
{
	if (get_env_val(data->env_lst, "PWD"))
	{
		if (export_add(data, "OLDPWD", get_env_val(data->env_lst, "PWD")))
			return (1);
	}
	else if (get_env_val(data->env_lst, "OLDPWD"))
	{
		if (export_add(data, "OLDPWD", ""))
			return (1);
	}
	if (export_add(data, "PWD", path))
		return (1);
	return (0);
}

int	builtin_cd(t_data *data, t_token *token)
{
	char	*str;

	if (ft_strslen(token->str_split) > 2)
		return (ft_putstr_fd("cd : too many arguments\n", 2), 1);
	str = token->str_split[1];
	if (ft_strslen(token->str_split) == 1)
	{
		str = get_env_val(data->env_lst, "HOME");
		if (!str)
			return (ft_putstr_fd("cd : HOME not set\n", 2), 1);
	}
	if (chdir(str))
		return (ft_putstr_fd("cd : No such file or directory\n", 2), 1);
	str = getcwd(0, 0);
	if (!str)
		return (1);
	ft_addtotrash(data, str);
	if (ft_var_pwd(data, str))
		return (ft_putstr_fd("Malloc error\n", 2), 1);
	return (0);
}
