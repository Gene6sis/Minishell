/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 01:38:20 by adben-mc          #+#    #+#             */
/*   Updated: 2022/08/04 01:39:26 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**fill_content(t_data *data, t_list *lst, int i)
{
	int		j;
	char	**strs;

	strs = malloc(sizeof(char *) * (nb_words_in_partition(lst) + 1));
	if (!strs)
		return (NULL);
	ft_addtotrash(data, strs);
	while (is_partition(lst))
	{
		if (((t_token *)lst->content)->type == WORD)
		{
			j = -1;
			while (((t_token *)lst->content)->str_split[++j])
			{
				strs[i] = ft_strdup(((t_token *)lst->content)->str_split[j]);
				if (!strs[i])
					return (NULL);
				ft_addtotrash(data, strs[i]);
				strs[++i] = NULL;
			}
		}
		lst = lst->next;
	}
	return (strs);
}

int	unit_word(t_data *data)
{
	t_list	*lst;
	char	**strs;

	lst = data->command;
	while (lst)
	{
		if (nb_word_in_partition(lst) > 1)
		{
			strs = fill_content(data, lst, 0);
			if (!strs)
				return (ERROR);
			lst = next_word(lst);
			((t_token *)lst->content)->str_split = strs;
			((t_token *)lst->content)->str = ft_strjoinbis(ft_strslen(strs),
					strs, " ");
			if (!((t_token *)lst->content)->str)
				return (ERROR);
			ft_addtotrash(data, ((t_token *)lst->content)->str);
			remove_other_words(lst, data);
		}
		lst = next_partition(lst);
	}
	return (0);
}
