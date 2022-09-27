/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 15:28:59 by nthimoni          #+#    #+#             */
/*   Updated: 2022/08/11 12:39:17 by nthimoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_len(char *word, t_data *data)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (word[i])
	{
		if (word[i] == '\"' || word[i] == '\'')
			expand_len_quote(word, data, &i, &len);
		if (word[i] == '$')
			len += process_dollar(word, &i, data);
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

void	add_exit_code(char *ret)
{
	char	*code;

	code = ft_itoa(g_sig);
	ft_strlcat(ret, code, ft_strlen(ret) + 4);
	free(code);
}

void	cpy_var(char *word, int *s, char *ret, t_data *data)
{
	char	*str;
	t_env	*tmp;

	(*s)++;
	str = word + *s;
	if (*str == '?')
	{
		add_exit_code(ret);
		(*s)++;
		return ;
	}
	tmp = data->env_lst;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, str, ft_strlen(tmp->name))
			&& !ft_isalnum(*(str + ft_strlen(tmp->name)))
			&& *(str + ft_strlen(tmp->name)) != '_')
			ft_strlcat(ret, tmp->value,
				ft_strlen(ret) + ft_strlen(tmp->value) + 1);
		tmp = tmp->next;
	}
	process_dollar(word, s, data);
}

void	expand_quote(char *word, char *ret, int *s, t_data *data)
{
	char	sep;

	sep = word[*s];
	(*s)++;
	while (word[*s] && word[*s] != sep)
	{
		if (word[*s] == '$' && (word[(*s) + 1] == '_' || word[(*s) + 1] == '?'
				|| ft_isalnum(word[(*s) + 1])) && sep == '\"')
			cpy_var(word, s, ret, data);
		else
		{
			ret[ft_strlen(ret)] = word[*s];
			(*s)++;
		}
	}
	(*s)++;
}

void	rp_wild(char *str)
{
	char	sep;

	while (*str)
	{
		if (*str == '*')
			*str = WILDCARD;
		else if (*str == '\'' || *str == '\"')
		{
			sep = *str;
			str++;
			while (*str != sep)
				str++;
		}
		str++;
	}
}
