/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 01:40:13 by adben-mc          #+#    #+#             */
/*   Updated: 2022/08/21 21:01:16 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_command(t_data *data, t_list *lst, int status)
{
	t_token	*command;
	char	*str;
	int		len;
	int		ret;

	command = lst->content;
	ret = builtins(command, data, status);
	if (ret != -42 && !status)
		return (free_trash(data), exit(ret), 0);
	if (ret != -42)
		return (ret);
	len = ft_strlen(command->str_split[0]);
	str = get_absolute_path(command->str_split,
			data->env_lst, data);
	if (!str)
		return (free_trash(data), perror("malloc"), exit(-1), 0);
	if (update_env_str(data, data->env_lst))
		return (free_trash(data), perror("malloc"), exit(-1), 0);
	if (execve(str, command->str_split, data->env_str) == ERROR)
		return (not_found(command->str_split[0], len),
			free_trash(data), exit(127), 0);
	return (free_trash(data), exit(0), 0);
}

int	_exec(t_data *data, t_list **lst, int *prevfd)
{
	int	code;
	int	fd[2];

	*lst = data->command;
	if (!exec_heredocs(data))
		return (*prevfd = g_sig, *prevfd);
	code = bultin_simple_command(data, find_cmd(*lst));
	if (code == -1)
		return (*prevfd = 0, 0);
	if (code)
	{
		fd[0] = dup(STDIN_FILENO);
		fd[1] = dup(STDOUT_FILENO);
		*prevfd = simple_exec(data, *lst);
		dup2(fd[0], STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		close(fd[0]);
		return (*prevfd);
	}
	*prevfd = 0;
	signal_set("child");
	return (-1);
}

int	exec(t_data *data)
{
	int		pipefd[2];
	int		prevfd;
	int		pid;
	t_list	*lst;

	if (_exec(data, &lst, &prevfd) != -1)
		return (prevfd);
	while (lst)
	{
		if (is_partition(lst))
		{
			if (pipe(pipefd) == ERROR)
				return (ft_error_pipe(prevfd));
			pid = fork();
			if (pid == ERROR)
				return (ft_error_fork(prevfd, pipefd));
			else if (pid == 0)
				pid_child(data, prevfd, pipefd, lst);
			else if (pid_father(data, &prevfd, pipefd, lst) == ERROR)
				return (ERROR);
		}
		lst = next_partition(lst);
	}
	return (ft_wait(pid));
}
