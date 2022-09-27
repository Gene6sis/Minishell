/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 17:29:11 by nthimoni          #+#    #+#             */
/*   Updated: 2022/08/03 03:45:46 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_newtoken(t_token_type type)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->type = type;
	new->str = NULL;
	return (new);
}

int	add_token(t_list **head, char *line, t_token_type type, t_data *data)
{
	t_list	*new;
	int		len;
	t_token	*token;

	token = ft_newtoken(type);
	if (!token)
		return (1);
	ft_addtotrash(data, token);
	len = get_token_len(type, line);
	if (len == -1)
		return (2);
	token->str = ft_substr(line, 0, len);
	if (!token->str)
		return (1);
	ft_addtotrash(data, token->str);
	token->str_split = NULL;
	new = ft_lstnew(token);
	if (!new)
		return (1);
	ft_addtotrash(data, new);
	ft_lstadd_back(head, new);
	return (0);
}
