/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 17:43:14 by adben-mc          #+#    #+#             */
/*   Updated: 2022/08/10 03:00:44 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(t_data *data, t_token *token)
{
	char	*cwd;

	if (!access(".", F_OK))
	{
		cwd = getcwd(0, 0);
		if (cwd)
			return (ft_addtotrash(data, cwd), !printf("%s\n", cwd));
		return (ft_putstr_fd("pwd : is nowhere and somewhere\n", 2), 0);
	}
	else
		ft_putstr_fd("pwd : is nowhere and somewhere\n", 2);
	return ((void)token, (void)data, 0);
}
