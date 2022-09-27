/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bintree2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthimoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 17:15:18 by nthimoni          #+#    #+#             */
/*   Updated: 2022/08/12 17:15:38 by nthimoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	nb_op_in_parenth(t_list **operators)
{
	t_list	*tmp;
	int		ret;

	tmp = *operators;
	ret = 0;
	while (tmp)
	{
		if (((t_token *)((t_node *)tmp->content)->tokens->content)->type
				== AND_OP
				||
				((t_token *)((t_node *)tmp->content)->tokens->content)->type
				== OR_OP)
			ret++;
		else if (((t_token *)((t_node *)tmp->content)->tokens->content)->type
				== O_PARENTH)
			ret = 0;
	}
	return (ret);
}

void	init_var(t_list **tmp, t_list ***prev_next, t_list **last, t_list **op)
{
	*tmp = *op;
	*prev_next = NULL;
	*last = NULL;
	if (((t_token *)((t_node *)(*tmp)->content)->tokens->content)->type
			== AND_OP ||
		((t_token *)((t_node *)(*tmp)->content)->tokens->content)->type
			== OR_OP)
	{
		*prev_next = op;
		*last = *tmp;
	}
}

void	process_c_parenth(t_list **operators, t_list **words)
{
	t_list	**prev_next;
	t_list	*last;
	t_list	*tmp;

	init_var(&tmp, &prev_next, &last, operators);
	while (tmp->next)
	{
		if (
			((t_token *)((t_node *)tmp->next->content)->tokens->content)->type
			== OR_OP
			||
			((t_token *)((t_node *)tmp->next->content)->tokens->content)->type
			== AND_OP
		)
		{
			prev_next = &tmp->next;
			last = tmp->next;
		}
		tmp = tmp->next;
	}
	if (!prev_next || !last)
		return (delete_parenthesis(operators));
	*prev_next = last->next;
	delete_parenthesis(operators);
	link_node(last, words);
}

int	check_op_stacks(t_list *last, t_list *penult)
{
	if (
		(
			((t_token *)((t_node *)penult->content)->tokens->content)->type
		== OR_OP
		|| ((t_token *)((t_node *)penult->content)->tokens->content)->type
			== AND_OP
			)
			&&
			(
			((t_token *)((t_node *)last->content)->tokens->content)->type
			== OR_OP ||
			((t_token *)((t_node *)last->content)->tokens->content)->type
			== AND_OP
			)
		)
		return (1);
	return (0);
}

void	process_tree(t_list **operators, t_list **words)
{
	t_list	*last;
	t_list	*penult;
	t_list	*tmp;

	if (!*operators || !(*operators)->next)
		return ;
	tmp = *operators;
	while (tmp->next)
	{
		penult = tmp;
		last = tmp->next;
		tmp = tmp->next;
	}
	if (check_op_stacks(last, penult))
		process_double_op(operators, words);
	else if (((t_token *)((t_node *)last->content)->tokens->content)->type
			== C_PARENTH)
		process_c_parenth(operators, words);
}
