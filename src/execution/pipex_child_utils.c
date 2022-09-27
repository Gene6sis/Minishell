/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_child_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 03:05:23 by adben-mc          #+#    #+#             */
/*   Updated: 2022/08/04 03:10:41 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_fd(t_list *lst, int *fd)
{
	if (have_redirection_in(lst))
	{
		*fd = fd_entry(lst);
		if (*fd == -1)
			return (ft_error("open"), exit(1), 0);
		if (dup2(*fd, STDIN_FILENO) == -1)
			return (close(*fd), ft_error("dup2"), exit(127), 0);
		close(*fd);
	}
	if (have_redirection_out(lst))
	{
		*fd = fd_exit(lst);
		if (*fd == -1)
			return (ft_error("open"), exit(1), 0);
		if (dup2(*fd, STDOUT_FILENO) == -1)
			return (close(*fd), ft_error("dup2"), exit(127), 0);
		close(*fd);
	}
	return (0);
}
