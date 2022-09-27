/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 17:35:11 by adben-mc          #+#    #+#             */
/*   Updated: 2021/11/29 23:24:40 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*cur;

	cur = *alst;
	while (cur)
	{
		if (cur->next == NULL)
		{
			cur->next = new;
			return ;
		}
		cur = cur->next;
	}
	*alst = new;
}
