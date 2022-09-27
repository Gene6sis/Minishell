/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bintree.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 16:42:23 by nthimoni          #+#    #+#             */
/*   Updated: 2022/08/15 17:50:04 by nthimoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "libft.h"
#include <stdlib.h>

int	fill_stacks(t_list **operators, t_list **words, t_list **tmp, t_data *d)
{
	while (*tmp)
	{
		if (!verif_syntax(*tmp, 1))
			return (1);
		if (add_to_stacks(operators, words, *tmp, d))
			return (1);
		process_tree(operators, words);
		*tmp = (*tmp)->next;
	}
	return (0);
}

int	check_first_token_syntax(t_list *tmp)
{
	if (((t_token *)tmp->content)->type != WORD
		&& ((t_token *)tmp->content)->type != LD_DIR
		&& ((t_token *)tmp->content)->type != L_DIR
		&& ((t_token *)tmp->content)->type != RD_DIR
		&& ((t_token *)tmp->content)->type != R_DIR
		&& ((t_token *)tmp->content)->type != O_PARENTH)
		return (syntax_error(tmp, 1));
	return (1);
}

void	init_local_var(t_list **wrds, t_list **op, t_list **tmp, t_list **head)
{	
	*wrds = NULL;
	*op = NULL;
	*tmp = *head;
}

t_node	*build_tree(t_list **head, t_data *data)
{
	t_list	*operators;
	t_list	*words;
	t_list	*tmp;

	init_local_var(&words, &operators, &tmp, head);
	if (!check_first_token_syntax(tmp))
		return (NULL);
	if (fill_stacks(&operators, &words, &tmp, data))
		return (NULL);
	if (!operators)
		return (words->content);
	tmp = operators;
	while (tmp)
	{
		if (((t_token *)((t_node *)tmp->content)->tokens->content)->type
			== OR_OP
				||
			((t_token *)((t_node *)tmp->content)->tokens->content)->type
			== AND_OP)
			break ;
		tmp = tmp->next;
	}
	((t_node *)tmp->content)->left = words->content;
	((t_node *)tmp->content)->right = words->next->content;
	return (tmp->content);
}
