/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipexfather.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 06:27:53 by adben-mc          #+#    #+#             */
/*   Updated: 2022/08/11 04:28:40 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_parent(t_data *data, t_list *lst)
{
	t_token	*token;
	int		i;

	i = -1;
	if (!lst)
		return ;
	token = lst->content;
	if (!ft_strcmp(token->str_split[0], "cd"))
	{
		if (ft_strslen(token->str_split) == 1)
			if (!get_env_val(data->env_lst, "HOME"))
				ft_putstr_fd("cd : HOME not set\n", 2);
		if (ft_strslen(token->str_split) > 2)
			ft_putstr_fd("cd : too many arguments\n", 2);
	}
	if (!ft_strcmp(token->str_split[0], "export"))
	{
		while (++i < check_export_return(token))
			ft_putstr_fd("export: not a valid identifier\n", 2);
	}
}

int	pid_father(t_data *data, int *prevfd, int pipefd[2], t_list *lst)
{
	builtin_parent(data, find_cmd(lst));
	if (ft_nb_partition(data) == 1)
		return (close(pipefd[0]), close(pipefd[1]), 0);
	else if (getpos_partition(data, lst) == 0)
	{
		*prevfd = dup(pipefd[0]);
		close(pipefd[0]);
		close(pipefd[1]);
		if (*prevfd == ERROR)
			return (ft_error("dup"));
	}
	else if (getpos_partition(data, lst) == ft_nb_partition(data) - 1)
		return (close(pipefd[0]), close(pipefd[1]), close(*prevfd), 0);
	else
	{
		close(*prevfd);
		*prevfd = dup(pipefd[0]);
		close(pipefd[0]);
		close(pipefd[1]);
		if (*prevfd == ERROR)
			return (ft_error("dup"));
	}
	return (0);
}
