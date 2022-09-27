/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redirection_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 04:09:11 by adben-mc          #+#    #+#             */
/*   Updated: 2022/08/13 01:44:51 by nthimoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fd_exit(t_list *lst)
{
	int		fd;
	t_token	*token;

	fd = -2;
	while (is_partition(lst))
	{
		token = lst->content;
		if (token->type == RD_DIR || token->type == R_DIR)
		{
			if (fd != -2)
				close(fd);
			fd = opening_fd(token);
			if (fd == -1)
				return (fd);
		}
		lst = lst->next;
	}
	return (fd);
}

int	fd_entry(t_list *lst)
{
	int		fd;
	t_token	*token;

	fd = -2;
	while (is_partition(lst))
	{
		token = lst->content;
		if (token->type == L_DIR || token->type == LD_DIR)
		{
			if (fd != -2)
				close(fd);
			fd = opening_fd(token);
			if (fd == -1)
				return (fd);
		}
		lst = lst->next;
	}
	return (fd);
}

void	print_partition(t_list *lst)
{
	if (!lst)
		return ;
	while (is_partition(lst))
		lst = lst->next;
}

int	check_redirection(t_list *lst)
{
	t_token	*token;
	int		fd;

	while (is_partition(lst))
	{
		token = lst->content;
		if (token->type != WORD && token->type != LD_DIR)
		{
			fd = opening_fd(token);
			if (fd == -1)
			{	
				ft_putstr_fd(token->str, 2);
				ft_putstr_fd(": No such file or directory\n", 2);
				return (exit(1), 0);
			}
			close(fd);
		}
		lst = lst->next;
	}
	return (0);
}
