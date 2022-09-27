/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wild_args2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthimoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 18:48:27 by nthimoni          #+#    #+#             */
/*   Updated: 2022/08/07 23:16:20 by nthimoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**convert_lst_to_2d_char(t_list *lst, t_data *data)
{
	char	**ptr;
	int		i;

	ptr = ft_calloc(ft_lstsize(lst) + 1, sizeof(char *));
	if (!ptr)
		return (NULL);
	ft_addtotrash(data, ptr);
	i = 0;
	while (lst)
	{
		ptr[i] = lst->content;
		lst = lst->next;
		i++;
	}
	ptr[i] = NULL;
	return (ptr);
}

t_list	*new_lst_str(char *str, t_data *data)
{
	t_list	*ptr;

	ptr = ft_lstnew(str);
	if (!ptr)
		return (NULL);
	ft_addtotrash(data, ptr);
	return (ptr);
}

int	is_in(char *str, char a)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == a)
			return (1);
		i++;
	}
	return (0);
}

int	check_flag(int flag, char *str, t_data *data, t_list **lst)
{
	t_list	*tmp;

	rp_back_wild(str);
	if (!flag)
	{
		tmp = new_lst_str(str, data);
		if (!tmp)
			return (1);
		ft_lstadd_back(lst, tmp);
	}
	return (0);
}
