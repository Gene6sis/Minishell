/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 04:02:24 by adben-mc          #+#    #+#             */
/*   Updated: 2022/08/03 04:02:51 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// **
// ENVIRONNEMENT
// **

char	*get_env_val(t_env *env, const char *var_name)
{
	while (env)
	{
		if (!ft_strcmp(env->name, var_name))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

t_env	*get_env(t_env *env, const char *name)
{
	while (env)
	{
		if (!ft_strcmp(env->name, name))
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	ft_envdeloneelmt(t_env **list, t_env *to_delete)
{
	t_env	*tmp;

	if (!list || !*list || !to_delete)
		return ;
	if (*list == to_delete)
	{
		*list = (*list)->next;
		return ;
	}
	tmp = *list;
	while (tmp->next && tmp->next != to_delete)
		tmp = tmp->next;
	if (tmp->next)
	{
		tmp->next = tmp->next->next;
		return ;
	}
}

int	env_size(t_env *env)
{
	int		size;
	t_env	*cur;

	size = 0;
	cur = env;
	while (cur)
	{
		size++;
		cur = cur->next;
	}
	return (size);
}

//t_env * to a char **
char	**envlst_to_tab(t_env *env)
{
	char	**tab;
	int		i;
	t_env	*cur;

	i = 0;
	cur = env;
	tab = malloc(sizeof(char *) * (env_size(env) + 1));
	if (!tab)
		return (NULL);
	while (cur)
	{
		tab[i] = ft_strjoin3(cur->name, "=", cur->value);
		cur = cur->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
