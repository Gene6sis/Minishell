/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 01:49:08 by adben-mc          #+#    #+#             */
/*   Updated: 2022/08/04 01:50:36 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_error(char *str)
{
	if (!ft_strcmp(str, "execve"))
		ft_putstr_fd(": command not found\n", 2);
	else
		perror(str);
	return (ERROR);
}

int	ft_error_pipe(int prevfd)
{
	if (prevfd)
		close(prevfd);
	return (ft_error("pipe"));
}

int	ft_error_fork(int prevfd, int pipefd[2])
{
	if (prevfd)
		close(prevfd);
	if (pipefd)
	{
		close(pipefd[0]);
		close(pipefd[1]);
	}
	return (ft_error("fork"));
}

void	print_signal(int signal)
{
	if (signal == SIGINT)
	{
		write(2, "\n", 2);
		rl_replace_line("", 0);
		rl_on_new_line();
	}
	if (signal - 128 == SIGQUIT)
	{
		write(2, "Quit (core dumped)\n", 20);
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

int	ft_wait(int pid)
{
	int	status;
	int	tmp;
	int	ret;

	tmp = wait(&status);
	while (tmp != -1)
	{
		if (tmp == pid)
			ret = status;
		tmp = wait(&status);
	}
	signal_set("normal");
	if (WIFEXITED(ret))
		return (WEXITSTATUS(ret));
	else if (WIFSIGNALED(ret))
	{
		print_signal(ret);
		return (128 + WTERMSIG(ret));
	}
	return (WEXITSTATUS(ret));
}
