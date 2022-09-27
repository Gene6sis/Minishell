/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pre_exec_bis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 01:36:04 by adben-mc          #+#    #+#             */
/*   Updated: 2022/08/12 23:34:53 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//pour pre_exec
int	ft_ft(char ***ft, t_data *data, int size)
{
	*ft = (char **)malloc(sizeof(char *) * (size));
	if (!*ft)
		return (0);
	ft_addtotrash(data, *ft);
	return (1);
}

int	fill_token(t_list **new, t_list **first, t_data *data)
{
	int		i;
	t_token	*tok;
	t_token	*f_tok;

	tok = (*new)->content;
	f_tok = (*first)->content;
	tok->type = WORD;
	tok->str_split = malloc(sizeof(char *) * (ft_strslen(f_tok->str_split)));
	if (!tok->str_split)
		return (ERROR);
	ft_addtotrash(data, tok->str_split);
	i = -1;
	while (f_tok->str_split[++i + 1])
	{
		tok->str_split[i] = ft_strdup(f_tok->str_split[i + 1]);
		if (!tok->str_split[i])
			return (ERROR);
		ft_addtotrash(data, tok->str_split[i]);
	}
	tok->str_split[i] = NULL;
	tok->str = ft_strjoinbis(ft_strslen(tok->str_split), tok->str_split, " ");
	if (!tok->str)
		return (ERROR);
	return (ft_addtotrash(data, tok->str), f_tok->str_split[1] = NULL
		, f_tok->str[ft_strlen(f_tok->str_split[0])] = '\0', 0);
}

int	insert_between(t_list *first, t_list *second, t_data *data)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (ERROR);
	ft_addtotrash(data, new);
	first->next = new;
	new->next = second;
	new->content = (t_token *)malloc(sizeof(t_token));
	if (!new->content)
		return (ERROR);
	ft_addtotrash(data, new->content);
	if (fill_token(&new, &first, data) == ERROR)
		return (ERROR);
	return (0);
}

int	separation_word(t_data *data)
{
	t_token	*token;
	t_list	*lst;

	lst = data->command;
	while (lst)
	{
		token = lst->content;
		if (is_partition(lst) && token->type != WORD)
		{
			if (ft_strslen(token->str_split) > 1)
			{
				if (insert_between(lst, lst->next, data) == ERROR)
					return (ERROR);
			}
		}
		lst = lst->next;
	}
	return (0);
}

int	ft_pre_exec_bis(t_data *data)
{
	if (separation_word(data) == ERROR)
		return (ERROR);
	if (unit_word(data) == ERROR)
		return (ERROR);
	return (0);
}
