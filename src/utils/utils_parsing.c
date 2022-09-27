/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 04:04:54 by adben-mc          #+#    #+#             */
/*   Updated: 2022/08/03 04:05:02 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// **
// Parsing
// **

int	is_only_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '\f' && str[i] != '\t' && str[i] != '\n'
			&& str[i] != '\r' && str[i] != '\v' && str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	have_multiple_str_in_redirection(t_data *data)
{
	t_list	*lst;
	t_token	*token;

	lst = data->command;
	while (lst)
	{
		token = lst->content;
		if (is_partition(lst) && token->type != WORD)
		{
			if (ft_strslen(token->str_split) > 1)
				return (1);
		}
		lst = lst->next;
	}	
	return (0);
}

int	nb_word_in_partition(t_list *lst)
{
	t_token	*token;
	int		i;

	i = 0;
	while (is_partition(lst))
	{
		token = lst->content;
		if (token->type == WORD)
			i += 1;
		lst = lst->next;
	}
	return (i);
}

t_list	*next_word(t_list *lst)
{
	t_token	*token;

	while (is_partition(lst))
	{
		token = lst->content;
		if (token->type == WORD)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

int	nb_words_in_partition(t_list *lst)
{
	t_token	*token;
	int		i;

	i = 0;
	while (is_partition(lst))
	{
		token = lst->content;
		if (token->type == WORD)
			i += ft_strslen(token->str_split);
		lst = lst->next;
	}
	return (i);
}
