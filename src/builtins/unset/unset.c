/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 17:43:14 by adben-mc          #+#    #+#             */
/*   Updated: 2022/07/11 20:45:33 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static char	*get_name_val_status(int *status, char **name)
// {
// 	char	*val;

// 	*status = 1;
// 	val = ft_strnstr(*name, "+=", ft_strlen(*name));
// 	if (!val)
// 		*status = 0;
// 	if (!val)
// 		val = ft_strnstr(*name, "=", ft_strlen(*name));
// 	if (val)
// 	{
// 		val[0] = '\0';
// 		val = val + 1;
// 		val += *status;
// 	}
// 	return (val);
// }

int	check_unset(char *name)
{
	int	i;

	i = 0;
	if (!name)
		return (1);
	if (ft_strlen(name) == 0)
		return (1);
	if (!(ft_isalpha(name[0]) || name[0] == '_'))
		return (1);
	while (name[++i])
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (1);
	return (0);
}

int	builtin_unset(t_data *data, t_token *token)
{
	int		i;
	t_env	*lst;
	int		ret;

	i = 0;
	ret = 0;
	while (++i < ft_strslen(token->str_split))
	{
		if (check_unset(token->str_split[i]))
		{
			ret = 1;
			ft_putstr_fd("unset: not a valid identifier\n", 2);
			continue ;
		}
		lst = get_env(data->env_lst, token->str_split[i]);
		if (!lst)
			continue ;
		ft_envdeloneelmt(&data->env_lst, lst);
	}
	return (ret);
}
