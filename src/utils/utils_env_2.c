/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 04:03:21 by adben-mc          #+#    #+#             */
/*   Updated: 2022/08/03 04:03:31 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env_to_lst(char **env, t_data *data)
{
	t_env	*lst;
	char	*var_name;
	char	*var_value;
	t_env	*new;

	lst = NULL;
	if (env)
	{
		while (*env)
		{
			var_name = get_env_name_from_string(*env);
			ft_addtotrash(data, var_name);
			var_value = ft_strdup(&(*env)[ft_strlen(var_name) + 1]);
			ft_addtotrash(data, var_value);
			new = envlst_new(var_name, var_value);
			envlst_add_back(&lst, new);
			ft_addtotrash(data, new);
			env++;
		}
	}
	return (lst);
}

void	print_env(t_env *env)
{
	if (env)
	{
		if (env->name && env->value)
		{
			printf("%s=%s\n", env->name, env->value);
			print_env(env->next);
		}
	}
}

//	Modif : 0
//  Not found : -1
//	ERROR : 1
int	update_in_strs(t_data *data, char *name, char *value)
{
	int	i;

	i = 0;
	while (data->env_str[i])
	{
		if (!ft_strncmp(data->env_str[i], name, ft_strlen(name)))
		{
			data->env_str[i] = ft_strjoin3(name, "=", value);
			if (!data->env_str[i])
				return (1);
			ft_addtotrash(data, data->env_str[i]);
			return (0);
		}
		i++;
	}
	return (-1);
}

int	update_env_strs(t_data *data, char *name, char *value)
{
	char	**new_env;
	int		i;

	if (!data->env_str)
		return (1);
	new_env = malloc(sizeof(char *) * (ft_strslen(data->env_str) + 2));
	if (!new_env)
		return (1);
	ft_addtotrash(data, new_env);
	i = 0;
	while (data->env_str[i])
	{
		new_env[i] = data->env_str[i];
		i++;
	}
	new_env[i] = ft_strjoin3(name, "=", value);
	if (!new_env[i])
		return (1);
	ft_addtotrash(data, new_env[i]);
	new_env[i + 1] = 0;
	data->env_str = new_env;
	return (0);
}

int	update_env_lst(t_data *data, char *name, char *value)
{
	t_env	*cur;

	cur = data->env_lst;
	while (cur)
	{
		if (!ft_strcmp(cur->name, name))
		{
			cur->value = ft_strdup(value);
			if (!cur->value)
				return (0);
			ft_addtotrash(data, cur->value);
			return (1);
		}
		cur = cur->next;
	}
	return (0);
}
