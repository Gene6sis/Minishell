/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 04:01:20 by adben-mc          #+#    #+#             */
/*   Updated: 2022/08/03 04:01:22 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// **
// ENVIRONNEMENT UTILS
// **

char	*get_env_name_from_string(char *str)
{
	char			*env_name;
	unsigned int	i;

	i = 0;
	env_name = NULL;
	while (str[i])
	{
		if (str[i] == '=')
		{
			env_name = malloc(i + 1);
			if (env_name)
			{
				ft_memcpy(env_name, str, i);
				env_name[i] = 0;
			}
			break ;
		}
		i++;
	}
	return (env_name);
}

t_env	*envlst_last(t_env *lst)
{
	t_env	*last;

	last = NULL;
	if (lst)
	{
		last = lst;
		while (last->next)
			last = last->next;
	}
	return (last);
}

t_env	*envlst_new(char *var_name, char *var_value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->name = var_name;
	new->value = var_value;
	new->next = NULL;
	return (new);
}

void	envlst_add_back(t_env **env, t_env *new)
{
	t_env	*last;

	if (*env)
	{
		last = envlst_last(*env);
		last->next = new;
	}
	else
		*env = new;
}
