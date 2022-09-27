/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 04:05:24 by adben-mc          #+#    #+#             */
/*   Updated: 2022/08/03 04:05:47 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_other_words(t_list *lst, t_data *data)
{
	t_token	*token;
	t_list	*backup;

	backup = lst;
	lst = lst->next;
	while (is_partition(lst))
	{
		token = lst->content;
		if (token->type == WORD)
		{
			ft_lstdeloneelmt(&data->command, lst);
			lst = backup->next;
		}
		else
			lst = lst->next;
	}
}
