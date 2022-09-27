/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthimoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 17:19:24 by nthimoni          #+#    #+#             */
/*   Updated: 2022/08/20 15:47:38 by nthimoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	syntax_error(t_list *token, int should_print)
{
	if (should_print)
		ft_printf("Syntax error near : %s\n", ((t_token *)token->content)->str);
	return (0);
}

int	verif_parenth(t_list *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		if (((t_token *)lst->content)->type == O_PARENTH)
			count++;
		else if (((t_token *)lst->content)->type == C_PARENTH)
			count--;
		if (count < 0)
			return (ft_printf("Unmatching parenthesis : )\n"), 1);
		lst = lst->next;
	}
	if (count > 0)
		return (ft_printf("Unmatching parenthesis : (\n"), 1);
	return (0);
}

int	last_token(t_list *token, t_token_type *type, int should_print)
{
	*type = ((t_token *)token->content)->type;
	if (!token->next)
	{
		if (*type == WORD || *type == C_PARENTH)
			return (1);
		else
			return (syntax_error(token, should_print));
	}
	return (-1);
}

int	test_op(t_token_type type, t_list *token)
{
	if ((type == AND_OP || type == OR_OP)
		&& (((t_token *)token->next->content)->type != O_PARENTH
			&& ((t_token *)token->next->content)->type != LD_DIR
			&& ((t_token *)token->next->content)->type != RD_DIR
			&& ((t_token *)token->next->content)->type != L_DIR
			&& ((t_token *)token->next->content)->type != R_DIR
			&& ((t_token *)token->next->content)->type != WORD))
		return (1);
	return (0);
}

int	verif_syntax(t_list *token, int should_print)
{
	t_token_type	type;
	t_token_type	next;

	if (last_token(token, &type, should_print) != -1)
		return (last_token(token, &type, 0));
	next = ((t_token *)token->next->content)->type;
	if ((type == WORD)
		&& next == O_PARENTH)
		return (syntax_error(token, should_print));
	else if ((type == R_DIR || type == L_DIR || type == RD_DIR
			|| type == LD_DIR) && (next != WORD))
		return (syntax_error(token, should_print));
	else if (type == O_PARENTH
		&& (next != WORD && next != LD_DIR && next != L_DIR && next != RD_DIR
			&& next != R_DIR && next != O_PARENTH))
		return (syntax_error(token, should_print));
	else if (type == C_PARENTH
		&& (next != C_PARENTH && next != OR_OP && next != AND_OP))
		return (syntax_error(token, should_print));
	else if (type == PIPE && (next == C_PARENTH || next == AND_OP
			|| next == OR_OP || next == PIPE))
		return (syntax_error(token, should_print));
	else if (test_op(type, token))
		return (syntax_error(token, should_print));
	return (1);
}
