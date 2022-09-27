/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthimoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 19:09:18 by nthimoni          #+#    #+#             */
/*   Updated: 2022/08/11 15:21:10 by nthimoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	var_len(char *str, t_data *data)
{
	t_env	*tmp;

	tmp = data->env_lst;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, str, ft_strlen(tmp->name))
			&& !ft_isalnum(*(str + ft_strlen(tmp->name)))
			&& *(str + ft_strlen(tmp->name)) != '_')
			return (ft_strlen(tmp->value));
		tmp = tmp->next;
	}
	return (0);
}

int	process_dollar(char *str, int *i, t_data *data)
{
	int	len;

	len = var_len(str + (*i) + 1, data);
	(*i)++;
	if (str[*i] == '?')
	{
		(*i)++;
		return (3);
	}
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	return (len);
}

void	expand_len_quote(char *word, t_data *data, int *i, int *len)
{
	char	sep;

	sep = word[*i];
	(*i)++;
	(*len)++;
	while (word[*i] && word[*i] != sep)
	{
		if (word[*i] == '$' && sep == '\"')
			*len += process_dollar(word, i, data);
		else
		{
			(*len)++;
			(*i)++;
		}
	}
	(*len) -= 2;
}

char	*expand2(char *word, t_data *data)
{
	char	*ret;
	int		s;

	if (!word)
		return (NULL);
	ret = ft_calloc(expand_len(word, data) + ft_strlen(word) + 1, sizeof(char));
	if (!ret)
		return (NULL);
	ft_addtotrash(data, ret);
	s = 0;
	while (word[s])
	{
		if (word[s] == '\"' || word[s] == '\'')
			expand_quote(word, ret, &s, data);
		else
			ret[ft_strlen(ret)] = word[s++];
	}
	return (ret);
}
