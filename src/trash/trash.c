/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trash.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 17:09:24 by adben-mc          #+#    #+#             */
/*   Updated: 2022/07/12 18:59:00 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_create_trash(t_data *data, void *addr)
{
	t_trash	*cur;

	cur = malloc(sizeof(*cur));
	if (!cur)
		return (1);
	cur->to_free = addr;
	cur->next = NULL;
	data->trash = cur;
	return (0);
}

void	printtrash(t_trash *trash)
{
	int	i;

	i = 0;
	while (trash)
	{
		printf("%d: %p\n", i, trash->to_free);
		trash = trash->next;
		i++;
	}
}

int	ft_addtotrash(t_data *data, void *addr)
{
	t_trash	*cur;
	t_trash	*next;

	if (!data->trash)
	{
		if (ft_create_trash(data, addr))
			return (1);
		return (0);
	}
	cur = data->trash;
	while (cur->next)
		cur = cur->next;
	next = malloc(sizeof(t_trash));
	if (!next)
		return (1);
	next->next = NULL;
	next->to_free = addr;
	cur->next = next;
	return (0);
}

void	free_trash(t_data *data)
{
	t_trash	*cur;
	t_trash	*next;

	cur = data->trash;
	while (cur)
	{
		next = cur->next;
		free(cur->to_free);
		free(cur);
		cur = next;
	}
	data->trash = NULL;
	rl_clear_history();
}
