/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bintree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthimoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 17:08:38 by nthimoni          #+#    #+#             */
/*   Updated: 2022/08/12 17:09:25 by nthimoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_parenthesis(t_list **operators)
{
	t_list	*tmp;
	t_list	**prev_next_ptr;

	if (ft_lstsize(*operators) == 2)
	{
		*operators = NULL;
		return ;
	}
	tmp = *operators;
	prev_next_ptr = operators;
	while (tmp->next->next)
	{
		if (((t_token *)((t_node *)tmp->next->content)->tokens->content)->type
				== O_PARENTH)
			prev_next_ptr = &tmp->next;
		tmp = tmp->next;
	}
	tmp->next = NULL;
	*prev_next_ptr = (*prev_next_ptr)->next;
}

t_node	*new_node(t_node_type type, t_node *left, t_node *right)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	if (!new)
		return (NULL);
	new->left = left;
	new->right = right;
	new->type = type;
	new->tokens = NULL;
	return (new);
}

int	is_op_or_parenth(t_token *token)
{
	if (token->type == OR_OP || token->type == AND_OP
		|| token->type == O_PARENTH || token->type == C_PARENTH)
		return (1);
	return (0);
}

void	link_node(t_list *penult, t_list **words)
{
	t_list	*last_word;
	t_list	*penult_word;
	t_list	*tmp;

	if (ft_lstsize(*words) == 2)
	{
		penult_word = *words;
		*words = penult;
	}
	else
	{
		tmp = *words;
		while (tmp->next->next->next)
			tmp = tmp->next;
		penult_word = tmp->next;
		tmp->next = penult;
	}
	last_word = penult_word->next;
	penult->next = NULL;
	((t_node *)(penult->content))->left = penult_word->content;
	((t_node *)(penult->content))->right = last_word->content;
}

void	process_double_op(t_list **operators, t_list **words)
{
	t_list	*penult_op;
	t_list	*prev;
	t_list	*tmp;

	if (ft_lstsize(*operators) == 2)
	{
		penult_op = *operators;
		*operators = penult_op->next;
	}
	else
	{
		tmp = *operators;
		while (tmp->next->next)
		{
			prev = tmp;
			penult_op = tmp->next;
			tmp = tmp->next;
		}
		prev->next = penult_op->next;
	}
	link_node(penult_op, words);
}
