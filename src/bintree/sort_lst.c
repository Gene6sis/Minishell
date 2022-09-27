/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthimoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 10:54:13 by nthimoni          #+#    #+#             */
/*   Updated: 2022/08/20 15:37:17 by nthimoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	strcmp_no_case_sensitive(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s2[i] && ft_tolower(s1[i]) == ft_tolower(s2[i])
		&& i < n - 1)
		i++;
	return (ft_tolower(s1[i]) - ft_tolower(s2[i]));
}

static void	swap(t_list *lst)
{
	void	*tmp;

	tmp = lst->content;
	lst->content = lst->next->content;
	lst->next->content = tmp;
}

void	sort_lst(t_list *to_sort, t_list **lst)
{
	t_list	*tmp;

	tmp = to_sort;
	while (tmp && tmp->next)
	{
		if (strcmp_no_case_sensitive(tmp->content, tmp->next->content,
				ft_strlen(tmp->content) + 1) > 0)
		{
			swap(tmp);
			tmp = to_sort;
		}
		else
			tmp = tmp->next;
	}
	ft_lstadd_back(lst, to_sort);
}
