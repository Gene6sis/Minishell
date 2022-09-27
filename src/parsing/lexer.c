/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 18:33:35 by nthimoni          #+#    #+#             */
/*   Updated: 2022/08/03 03:45:37 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_ws(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r')
		return (1);
	return (0);
}

static t_token_type	get_token_type(char *inp, int i)
{
	if (!ft_strncmp(inp + i, ">>", 2))
		return (RD_DIR);
	else if (!ft_strncmp(inp + i, "<<", 2))
		return (LD_DIR);
	else if (!ft_strncmp(inp + i, "<", 1))
		return (L_DIR);
	else if (!ft_strncmp(inp + i, ">", 1))
		return (R_DIR);
	else if (!ft_strncmp(inp + i, "(", 1))
		return (O_PARENTH);
	else if (!ft_strncmp(inp + i, ")", 1))
		return (C_PARENTH);
	else if (!ft_strncmp(inp + i, "&&", 2))
		return (AND_OP);
	else if (!ft_strncmp(inp + i, "||", 2))
		return (OR_OP);
	else if (!ft_strncmp(inp + i, "|", 1))
		return (PIPE);
	else if (!ft_is_ws(inp[i]))
		return (WORD);
	return (NONE_TOKEN);
}

static int	word_len(char *str)
{
	int				i;
	t_token_type	type;
	char			sep;

	i = 0;
	type = get_token_type(str, i);
	while (str[i] && (type == NONE_TOKEN || type == WORD) && !ft_is_ws(str[i]))
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			sep = str[i];
			i++;
			while (str[i] && str[i] != sep)
				i++;
			if (!str[i])
			{
				ft_printf("Unmatching Quote : %c\n", sep);
				return (-1);
			}
		}
		i++;
		type = get_token_type(str, i);
	}
	return (i);
}

int	get_token_len(t_token_type type, char *str)
{
	if (type == RD_DIR)
		return (2);
	if (type == LD_DIR)
		return (2);
	if (type == L_DIR)
		return (1);
	if (type == R_DIR)
		return (1);
	if (type == O_PARENTH)
		return (1);
	if (type == C_PARENTH)
		return (1);
	if (type == AND_OP)
		return (2);
	if (type == OR_OP)
		return (2);
	if (type == PIPE)
		return (1);
	if (type == WORD)
		return (word_len(str));
	return (0);
}

t_list	*get_tokens(char *line, t_data *data)
{
	t_list			*head;
	int				i;
	t_token_type	type;
	int				tmp;

	i = 0;
	head = NULL;
	while (line[i])
	{
		type = get_token_type(line, i);
		if (type != NONE_TOKEN)
		{
			tmp = add_token(&head, &line[i], type, data);
			if (tmp == 2)
				return ((t_list *)1);
			else if (tmp)
				return (NULL);
			i += get_token_len(type, line + i);
		}
		else
			i++;
	}
	return (head);
}
