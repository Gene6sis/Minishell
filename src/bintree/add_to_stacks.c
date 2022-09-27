/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_stacks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthimoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 15:57:30 by nthimoni          #+#    #+#             */
/*   Updated: 2022/08/12 17:08:17 by nthimoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_word_no_stick(t_data *data, t_list **words, t_token *token)
{
	t_list	*new;

	new = ft_lstnew(new_node(CMD, NULL, NULL));
	ft_addtotrash(data, new);
	if (new)
		ft_addtotrash(data, new->content);
	if (!new || !new->content)
		return (1);
	ft_lstadd_back(words, new);
	((t_node *)new->content)->tokens = ft_lstnew(token);
	ft_addtotrash(data, ((t_node *)new->content)->tokens);
	return (0);
}

static int	add_word_stick(t_data *data, t_list **words, t_token *token)
{
	t_list		*new;
	t_list		*last;

	last = ft_lstlast(*words);
	new = ft_lstnew(token);
	if (!new)
		return (1);
	ft_addtotrash(data, new);
	ft_lstadd_back(&((t_node *)last->content)->tokens, new);
	return (0);
}

static int	add_operator(t_data *data, t_list **op, t_token *token)
{
	t_list		*new;	

	new = ft_lstnew(new_node(OPERATOR, NULL, NULL));
	ft_addtotrash(data, new);
	if (new)
		ft_addtotrash(data, new->content);
	if (!new || !new->content)
		return (1);
	ft_lstadd_back(op, new);
	((t_node *)new->content)->tokens = ft_lstnew(token);
	ft_addtotrash(data, ((t_node *)new->content)->tokens);
	return (0);
}

static int	init_token(t_data *data, t_list *tmp, t_token **token)
{
	*token = malloc(sizeof(t_token));
	if (!(*token))
		return (1);
	ft_addtotrash(data, *token);
	**token = *(((t_token *)tmp->content));
	return (0);
}

int	add_to_stacks(t_list **op, t_list **words, t_list *tmp, t_data *data)
{
	t_token		*token;
	static int	should_stick = 0;

	if (init_token(data, tmp, &token))
		return (1);
	if (is_op_or_parenth(token))
	{
		add_operator(data, op, token);
		should_stick = 0;
	}
	else
	{
		if (!should_stick)
		{
			if (add_word_no_stick(data, words, token))
				return (1);
		}
		else
			if (add_word_stick(data, words, token))
				return (1);
		should_stick = 1;
	}
	if (!tmp->next || !verif_syntax(tmp->next, 0))
		should_stick = 0;
	return (0);
}
