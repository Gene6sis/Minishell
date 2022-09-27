/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthimoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 15:35:20 by nthimoni          #+#    #+#             */
/*   Updated: 2022/08/09 15:35:32 by nthimoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	rp_back_wild(char *str)
{
	while (*str)
	{
		if (*str == WILDCARD)
			*str = '*';
		str++;
	}
}

int	add_all(t_list **head, char **sp, t_data *data)
{
	t_list	*tmp;

	while (*sp)
	{
		tmp = new_lst_str(*sp, data);
		if (!tmp)
			return (1);
		ft_lstadd_back(head, tmp);
		sp++;
	}	
	return (0);
}
