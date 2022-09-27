/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 17:43:14 by adben-mc          #+#    #+#             */
/*   Updated: 2022/08/09 00:47:01 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_append(t_data *data, char *name_tmp, char *value_tmp)
{
	char	*value;
	t_env	*new;

	new = get_env(data->env_lst, name_tmp);
	value = malloc(sizeof(char) * (ft_strlen(new->value)
				+ ft_strlen(value_tmp) + 1));
	if (!value)
		return (ERROR);
	ft_addtotrash(data, value);
	ft_memcpy(value, new->value, ft_strlen(new->value));
	ft_memcpy(value + ft_strlen(new->value), value_tmp, ft_strlen(value_tmp));
	value[ft_strlen(new->value) + ft_strlen(value_tmp)] = '\0';
	new->value = value;
	return (0);
}

int	export_update(t_data *data, char *name, char *value_tmp)
{
	t_env	*new;
	char	*value;

	value = ft_strdup(value_tmp);
	if (!value)
		return (ERROR);
	ft_addtotrash(data, value);
	new = get_env(data->env_lst, name);
	new->value = value;
	return (0);
}

int	export_add(t_data *data, char *name_tmp, char *value_tmp)
{
	char	*name;
	char	*value;
	t_env	*new;

	if (get_env_val(data->env_lst, name_tmp))
		return (export_update(data, name_tmp, value_tmp));
	value = ft_strdup(value_tmp);
	if (!value)
		return (ERROR);
	ft_addtotrash(data, value);
	name = ft_strdup(name_tmp);
	if (!name)
		return (ERROR);
	ft_addtotrash(data, name);
	new = envlst_new(name, value);
	if (!new)
		return (ERROR);
	ft_addtotrash(data, new);
	envlst_add_back(&data->env_lst, new);
	return (0);
}

static char	*get_name_val_status(char **name, int *ret)
{
	char	*val;

	if (ft_strnstr(*name, "=", ft_strlen(*name)) == NULL)
	{
		if (check_export(*name, NULL) == 1)
		{
			ft_putstr_fd("export : not a valid identifier\n", 2);
			*ret = 1;
		}
		return (NULL);
	}
	val = ft_strnstr(*name, "=", ft_strlen(*name));
	if (val)
	{
		val[0] = '\0';
		val = val + 1;
	}
	return (val);
}

int	builtin_export(t_data *dt, t_token *t, int dad)
{
	int		i;
	char	*val;
	int		ret;

	i = 0;
	ret = 0;
	while (++i < ft_strslen(t->str_split))
	{
		val = get_name_val_status(&t->str_split[i], &ret);
		if (!val)
			continue ;
		if (check_export(t->str_split[i], val) == 1)
		{
			ret = 1;
			ft_putstr_fd("export: not a valid identifier\n", 2);
			continue ;
		}
		if (dad && export_add(dt, t->str_split[i], val) == ERROR)
			return (ERROR);
	}
	return (ret);
}
