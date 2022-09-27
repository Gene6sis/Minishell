/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 04:04:19 by adben-mc          #+#    #+#             */
/*   Updated: 2022/08/03 04:04:30 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_env(t_data *data, char *name, char *value)
{
	if (update_env_lst(data, name, value))
		return (1);
	if (update_env_strs(data, name, value))
		return (1);
	return (0);
}
