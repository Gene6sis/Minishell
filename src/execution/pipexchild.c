/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipexchild.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 06:18:10 by adben-mc          #+#    #+#             */
/*   Updated: 2022/08/17 03:22:26 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// #define pipefd[0] pipefd[0]
// #define pipefd[1] pipefd[1]

int	exec_first(t_data *data, int pipefd[2], t_list *lst)
{
	int		fd;

	close(pipefd[0]);
	if (dup2(pipefd[1], STDOUT_FILENO) == ERROR)
		return (close(pipefd[1]), ft_error("dup2"), exit(127), 0);
	close(pipefd[1]);
	open_fd(lst, &fd);
	if (have_command(lst))
		return (exec_command(data, find_cmd(lst), 0));
	return (free_trash(data), exit(0), 0);
}

int	exec_between(t_data *data, int prevfd, int pipefd[2], t_list *lst)
{
	int		fd;

	close(pipefd[0]);
	if (dup2(prevfd, STDIN_FILENO) == ERROR)
		return (close(prevfd), close(pipefd[1]), ft_error("dup2"));
	close(prevfd);
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		return (close(pipefd[1]), ft_error("dup2"));
	close(pipefd[1]);
	open_fd(lst, &fd);
	if (have_command(lst))
		return (exec_command(data, find_cmd(lst), 0));
	return (free_trash(data), exit(0), 0);
}

int	exec_last(t_data *data, int prevfd, t_list *lst)
{
	int		fd;

	if (dup2(prevfd, STDIN_FILENO) == -1)
		return (close(prevfd), ft_error("dup2"));
	close(prevfd);
	open_fd(lst, &fd);
	if (have_command(lst))
		return (exec_command(data, find_cmd(lst), 0));
	return (free_trash(data), exit(0), 0);
}

int	exec_unique(t_data *data, t_list *lst)
{
	int	fd;

	open_fd(lst, &fd);
	if (have_command(lst))
		return (exec_command(data, find_cmd(lst), 0));
	return (free_trash(data), exit(0), 0);
}

int	pid_child(t_data *data, int prevfd, int pipefd[2], t_list *lst)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	check_redirection(lst);
	if (ft_nb_partition(data) == 1)
		return (close(pipefd[0]), close(pipefd[1]), exec_unique(data, lst));
	else if (getpos_partition(data, lst) == 0)
		exec_first(data, pipefd, lst);
	else if (getpos_partition(data, lst) == ft_nb_partition(data) - 1)
		return (close(pipefd[0]), close(pipefd[1]),
			exec_last(data, prevfd, lst));
	else
		exec_between(data, prevfd, pipefd, lst);
	return (0);
}
