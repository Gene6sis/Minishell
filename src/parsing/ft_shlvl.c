/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shlvl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 19:06:54 by adben-mc          #+#    #+#             */
/*   Updated: 2022/08/21 21:00:57 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_atoi_shlvl(char *str)
{
	int	i;
	int	res;

	i = 0;
	while ((str[i] <= '\r' && str[i] >= '\t') || str[i] == ' ')
		i++;
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			return (0);
		i++;
	}
	if (!ft_isdigit(str[i]))
		return (1);
	res = i;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if ((i - res) > 3)
		return (ft_putstr_fd("shell level too high, resetting to 1\n", 2), 1);
	return (ft_atoi(&str[res]) + 1);
}

int	check_shlvl(t_data *data, char *nb)
{
	char	*value;

	value = ft_itoa(ft_atoi_shlvl(nb));
	if (!value)
		return (1);
	if (export_add(data, "SHLVL", value))
		return (free(value), 1);
	free(value);
	return (0);
}

int	ft_shlvl(t_data *data)
{
	char	*lvl;

	if (!get_env_val(data->env_lst, "SHLVL"))
	{
		if (export_add(data, "SHLVL", "1"))
			return (1);
		return (0);
	}
	lvl = get_env_val(data->env_lst, "SHLVL");
	if (check_shlvl(data, lvl))
		return (1);
	return (0);
}
