/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pre_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 01:34:56 by adben-mc          #+#    #+#             */
/*   Updated: 2022/08/17 03:38:20 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_st(char ***st, t_token *t_s, t_data *data)
{
	(*st) = (char **)malloc(sizeof(char *) * 2);
	if (!(*st))
		return (0);
	ft_addtotrash(data, (*st));
	(*st)[0] = ft_strdup(t_s->str_split[0]);
	if (!(*st)[0])
		return (0);
	ft_addtotrash(data, (*st)[0]);
	(*st)[1] = NULL;
	return (1);
}

int	ft_fill_first_ft(char ***ft, t_token *t_f, t_data *data)
{
	int	i;

	i = -1;
	while (++i < ft_strslen(t_f->str_split))
	{
		(*ft)[i] = ft_strdup(t_f->str_split[i]);
		if (!(*ft)[i])
			return (0);
		ft_addtotrash(data, (*ft)[i]);
	}
	return (1);
}

int	ft_fill_second_ft(char ***ft, t_token *t_s, t_data *data, int size)
{
	int	i;

	i = -1;
	while (++i < ft_strslen(t_s->str_split) - 1)
	{
		(*ft)[i + size] = ft_strdup(t_s->str_split[i + 1]);
		if (!(*ft)[i + size])
			return (0);
		ft_addtotrash(data, (*ft)[i + size]);
	}
	(*ft)[i + size] = NULL;
	return (1);
}

int	swap_after(t_data *data, t_token *t_f, t_token *t_s)
{
	char	**ft;
	char	**st;

	if (!ft_ft(&ft, data, ft_strslen(t_s->str_split)
			+ ft_strslen(t_f->str_split)))
		return (ERROR);
	if (!ft_st(&st, t_s, data))
		return (ERROR);
	if (!ft_fill_first_ft(&ft, t_f, data))
		return (ERROR);
	if (!ft_fill_second_ft(&ft, t_s, data, ft_strslen(t_f->str_split)))
		return (ERROR);
	t_f->str = ft_strjoinbis(ft_strslen(ft), ft, " ");
	if (!t_f->str)
		return (ERROR);
	ft_addtotrash(data, t_f->str);
	t_s->str = ft_strjoinbis(ft_strslen(st), st, " ");
	if (!t_s->str)
		return (ERROR);
	return (ft_addtotrash(data, t_s->str), t_f->str_split = ft,
		t_s->str_split = st, 0);
}

// Reste a gerer si redirection comme premier token
int	ft_pre_exec(t_data *data)
{
	t_list		*lst;
	t_token		*token;
	t_list		*prev;
	t_list		*temp;

	lst = data->command;
	prev = NULL;
	while (lst)
	{
		token = lst->content;
		if (is_partition(lst) && token->type != WORD)
		{
			((t_token *)lst->next->content)->type = token->type;
			if (prev && lst->next && ((t_token *)prev->content)->type == WORD
				&& swap_after(data, prev->content, lst->next->content) == ERROR)
				return (ERROR);
			temp = lst;
			lst = lst->next->next;
			ft_lstdeloneelmt(&data->command, temp);
			continue ;
		}
		prev = lst;
		lst = lst->next;
	}
	return (0);
}
