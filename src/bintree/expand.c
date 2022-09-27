/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 21:01:00 by nthimoni          #+#    #+#             */
/*   Updated: 2022/08/13 01:55:31 by nthimoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_all(t_list *lst, t_data *data)
{
	char	*str;

	while (lst)
	{
		str = expand2(lst->content, data);
		if (!str)
			return (1);
		lst->content = str;
		lst = lst->next;
	}
	return (0);
}

static void	cpy_quote_content(char *word, int *s, char *ret)
{
	char	sep;

	sep = word[*s];
	ret[ft_strlen(ret)] = word[(*s)++];
	while (word[*s] && word[*s] != sep)
		ret[ft_strlen(ret)] = word[(*s)++];
	ret[ft_strlen(ret)] = word[(*s)++];
}

char	*expand1(char *word, t_data *data)
{
	char	*ret;
	int		s;

	ret = ft_calloc(expand_len(word, data) + ft_strlen(word) + 1, sizeof(char));
	if (!ret)
		return (NULL);
	ft_addtotrash(data, ret);
	s = 0;
	while (word[s])
	{
		if (word[s] == '\"' || word[s] == '\'')
			cpy_quote_content(word, &s, ret);
		else
		{
			if (word[s] == '$' && (word[s + 1] == '_'
					|| ft_isalnum(word[s + 1])
					|| word[s + 1] == '?'))
				cpy_var(word, &s, ret, data);
			else
				ret[ft_strlen(ret)] = word[s++];
		}
	}
	return (ret);
}

int	empty_str(char ***args, char u)
{
	if (!u)
	{
		(*args)++;
		return (1);
	}
	return (0);
}

char	**expand(char **args, t_data *data)
{
	t_list	*tmp;
	char	*str;
	char	**sp;

	if (!args)
		return (NULL);
	tmp = NULL;
	while (*args)
	{
		rp_wild(*args);
		str = expand1(*args, data);
		if (!str)
			return (NULL);
		if (empty_str(&args, *str))
			continue ;
		sp = ft_split_words(str, data);
		if (!sp)
			return (NULL);
		if (add_all(&tmp, sp, data))
			return (NULL);
		args++;
	}
	if (expand_all(tmp, data))
		return (NULL);
	return (convert_lst_to_2d_char(tmp, data));
}
