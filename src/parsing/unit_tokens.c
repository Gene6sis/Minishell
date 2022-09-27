/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 01:32:02 by adben-mc          #+#    #+#             */
/*   Updated: 2022/08/05 00:42:29 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_unit_tokens(t_data *data, t_token *t_b, t_token *t_f)
{
	t_f->str_split = unified_token(t_b->str,
			t_f->str, t_b->str_split, data);
	if (!t_f->str_split)
		return (1);
	t_f->str = ft_strjoin3(t_b->str, " ", t_f->str);
	if (!t_f->str)
		return (1);
	ft_addtotrash(data, t_f->str);
	return (0);
}

int	unit_tokens(t_list **lst, t_data *data)
{
	t_list		*cur;
	t_token		*t_b;
	t_token		*t_f;

	cur = *lst;
	if (cur && !cur->next)
		return (0);
	while (cur)
	{
		t_b = cur->content;
		if (cur->next)
		{
			t_f = cur->next->content;
			if (t_f->type == WORD && t_b->type == WORD)
			{
				if (_unit_tokens(data, t_b, t_f))
					return (1);
				ft_lstdeloneelmt(lst, cur);
				cur = *lst;
				continue ;
			}
		}
		cur = cur->next;
	}
	return (0);
}

// t_f->str_split = unified_token(t_b->str,
// 						t_f->str, t_b->str_split, data);
// 				if (!t_f->str_split)
// 					return (1);
// 				t_f->str = ft_strjoin3(t_b->str, " ", t_f->str);
// 				if (!t_f->str)
// 					return (1);
// 				ft_addtotrash(data, t_f->str);

char	**ft_unified_token_bis(char *s2, char **strs, t_data *data)
{
	int	i;

	i = 0;
	while (strs[i])
		i++;
	strs = ft_append_to_tab(strs, s2, data);
	if (!strs)
		return (NULL);
	return (strs);
}

// Create a char ** from a char * in each t_token in t_list
char	**unified_token(char *s1, char *s2, char **strs, t_data *data)
{
	if (!strs)
	{
		strs = malloc(sizeof(char *) * 3);
		if (!strs)
			return (NULL);
		ft_addtotrash(data, strs);
		strs[0] = ft_strdup(s1);
		if (!strs[0])
			return (NULL);
		ft_addtotrash(data, strs[0]);
		strs[1] = ft_strdup(s2);
		if (!strs[1])
			return (NULL);
		ft_addtotrash(data, strs[1]);
		return (strs[2] = NULL, strs);
	}
	return (ft_unified_token_bis(s2, strs, data));
}

// 	else
// 	{
// 		i = 0;
// 		while (strs[i])
// 			i++;
// 		strs = ft_append_to_tab(strs, s2, data);
// 		if (!strs)
// 			return (NULL);
// 	}
// 	return (strs);
// }
