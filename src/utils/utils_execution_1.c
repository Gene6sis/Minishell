/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execution_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 04:07:04 by adben-mc          #+#    #+#             */
/*   Updated: 2022/08/03 04:07:15 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_partition(t_list *lst)
{
	t_token	*token;

	if (!lst)
		return (0);
	token = lst->content;
	if (token->type == WORD || token->type == LD_DIR
		|| token->type == L_DIR || token->type == R_DIR
		|| token->type == RD_DIR)
		return (1);
	return (0);
}

t_list	*next_partition(t_list *lst)
{
	while (lst)
	{
		if (is_partition(lst))
			lst = lst->next;
		else
			break ;
	}
	while (lst)
	{
		if (!is_partition(lst))
			lst = lst->next;
		else
			break ;
	}
	return (lst);
}

int	getpos_partition(t_data *data, t_list *cmd)
{
	int		compt;
	t_list	*command;

	compt = 0;
	command = data->command;
	while (command)
	{
		if (command == cmd)
			return (compt);
		if (is_partition(command))
			compt++;
		while (is_partition(command))
		{
			command = command->next;
			if (!command)
				return (0);
		}
		command = command->next;
	}
	return (0);
}

char	*concatenate(int size, char *sep, char **strs, char *str)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	len = 0;
	while (i < size)
	{
		j = 0;
		while (strs[i][j])
			str[len++] = strs[i][j++];
		j = 0;
		while (sep[j] && i != (size - 1))
			str[len++] = sep[j++];
		i++;
	}
	str[len] = '\0';
	return (str);
}

char	*ft_strjoinbis(int size, char **strs, char *sep)
{
	int		len;
	int		i;
	char	*str;

	str = NULL;
	i = 0;
	len = 0;
	while (i < size)
	{
		if (strs[i] == NULL)
			return (NULL);
		len += ft_strlen(strs[i]) + ft_strlen(sep);
		i++;
	}
	str = malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	if (size == 0)
		return (str);
	str = concatenate(size, sep, strs, str);
	return (str);
}
