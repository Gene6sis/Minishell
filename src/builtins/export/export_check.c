/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 17:50:51 by adben-mc          #+#    #+#             */
/*   Updated: 2022/07/11 20:12:33 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_export_append(char *name, char *value)
{
	(void)value;
	if (ft_strlen(name) == 0)
		return (0);
	if (name[ft_strlen(name) - 1] == '+')
		return (1);
	return (0);
}

int	check_export_return(t_token *t)
{
	char	*val;
	int		i;
	int		status;
	int		compt;

	i = 0;
	compt = 0;
	while (++i < ft_strslen(t->str_split))
	{
		status = 1;
		val = ft_strnstr(t->str_split[i], "+=", ft_strlen(t->str_split[i]));
		if (!val)
			status = 0;
		if (!val)
			val = ft_strnstr(t->str_split[i], "=", ft_strlen(t->str_split[i]));
		if (!val)
			continue ;
		val[0] = '\0';
		val = val + 1 + status;
		if (check_export(t->str_split[i], val) == 1)
			compt++;
	}
	return (compt);
}

int	check_export(char *name, char *value)
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
		if (!ft_isalnum(name[i]) && name[i] != '=' && name[i] != '_')
			return (1);
	(void)value;
	return (0);
}
