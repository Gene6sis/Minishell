/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 04:06:08 by adben-mc          #+#    #+#             */
/*   Updated: 2022/08/03 04:06:28 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// **
// Execution
// **

void	not_found(char *str, int len)
{
	ft_putstr_fd(&str[ft_strlen(str) - len], 2);
	ft_putstr_fd(": command not found\n", 2);
}

t_list	*find_cmd(t_list *lst)
{
	t_token	*token;

	while (is_partition(lst))
	{
		token = lst->content;
		if (token->type == WORD)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

//Function that append a char * to a char **
char	**ft_append_to_tab(char **tab, char *str, t_data *data)
{
	char	**new_tab;
	int		i;

	i = 0;
	while (tab[i])
		i++;
	new_tab = malloc(sizeof(char *) * (i + 2));
	if (!new_tab)
		return (NULL);
	ft_addtotrash(data, new_tab);
	i = 0;
	while (tab[i])
	{
		new_tab[i] = ft_strdup(tab[i]);
		if (!new_tab[i])
			return (NULL);
		ft_addtotrash(data, new_tab[i]);
		i++;
	}
	new_tab[i] = ft_strdup(str);
	if (!new_tab[i])
		return (NULL);
	ft_addtotrash(data, new_tab[i]);
	new_tab[i + 1] = NULL;
	return (new_tab);
}

int	ft_nb_partition(t_data *data)
{
	int		compt;
	t_list	*command;

	compt = 0;
	command = data->command;
	while (command)
	{
		if (is_partition(command))
			compt++;
		while (is_partition(command))
		{
			command = command->next;
			if (!command)
				return (compt);
		}
		command = command->next;
	}
	return (compt);
}

t_token	*get_n_command(t_data *data, int n)
{
	int		i;
	t_list	*command;

	i = 0;
	command = data->command;
	while (command)
	{
		if (is_partition(command))
		{
			if (i == n)
				return (command->content);
			i++;
		}
		command = next_partition(command);
	}
	return (NULL);
}
