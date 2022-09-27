/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_first_tokens.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 01:34:02 by adben-mc          #+#    #+#             */
/*   Updated: 2022/08/04 01:34:10 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//function that return a char ** from a char *,
// if this char ** is empty, return NULL

char	**ft_addstrs(char *cmd, t_data *data)
{
	char	**strs;

	strs = malloc(sizeof(char *) * 2);
	if (!strs)
		return (NULL);
	ft_addtotrash(data, strs);
	strs[0] = ft_strdup(cmd);
	if (!strs[0])
		return (NULL);
	ft_addtotrash(data, strs[0]);
	strs[1] = NULL;
	return (strs);
}

int	unit_first_tokens(t_list **lst, t_data *data)
{
	t_list		*cur;
	t_token		*token;

	cur = *lst;
	while (cur)
	{
		token = cur->content;
		if (token->type == WORD && token->str_split == NULL)
		{
			token->str_split = ft_addstrs(token->str, data);
			if (!token->str_split)
				return (1);
		}
		cur = cur->next;
	}
	return (0);
}
