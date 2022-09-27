/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 04:08:14 by adben-mc          #+#    #+#             */
/*   Updated: 2022/08/03 04:08:44 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// **
// Redirection 
// **

int	have_command(t_list *lst)
{
	t_token	*token;

	while (is_partition(lst))
	{
		token = lst->content;
		if (token->type == WORD)
			return (1);
		lst = lst->next;
	}
	return (0);
}

int	have_redirection_in(t_list *lst)
{
	t_token	*token;

	while (is_partition(lst))
	{
		token = lst->content;
		if (token->type == LD_DIR || token->type == L_DIR)
			return (1);
		lst = lst->next;
	}
	return (0);
}

int	have_redirection_out(t_list *lst)
{
	t_token	*token;

	while (is_partition(lst))
	{
		token = lst->content;
		if (token->type == R_DIR || token->type == RD_DIR)
			return (1);
		lst = lst->next;
	}
	return (0);
}

int	have_heredocs(t_list *lst)
{
	t_token	*token;

	while (lst)
	{
		token = lst->content;
		if (token->type == LD_DIR)
			return (1);
		lst = lst->next;
	}
	return (0);
}

int	opening_fd(t_token *token)
{
	if (token->type == R_DIR)
		return (open(token->str, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	else if (token->type == RD_DIR)
		return (open(token->str, O_WRONLY | O_CREAT | O_APPEND, 0644));
	else if (token->type == L_DIR)
		return (open(token->str, O_RDONLY));
	else if (token->type == LD_DIR)
		return (open(token->name, O_RDONLY));
	return (-1);
}
