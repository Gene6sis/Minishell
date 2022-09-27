/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 04:44:20 by adben-mc          #+#    #+#             */
/*   Updated: 2022/08/18 00:52:13 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_absolute(char *cmd, t_data *data)
{
	struct stat	statpath;

	if (stat(cmd, &statpath) != 0)
	{
		ft_putstr_fd(cmd, 2);
		return (ft_putstr_fd(": No such file or directory\n", 2),
			free_trash(data), exit(127), NULL);
	}
	if (!S_ISREG(statpath.st_mode))
		return (ft_putstr_fd(cmd, 2), ft_putstr_fd(": Is a directory\n", 2),
			free_trash(data), exit(126), NULL);
	if (access(cmd, X_OK))
		return (ft_putstr_fd(cmd, 2), ft_putstr_fd(": Permission denied\n", 2),
			free_trash(data), exit(126), NULL);
	return (cmd);
}

// Get the absolute path of a command (if it exists)
// with the environnement and return it. 

int	replace_absolute_path(char **cmd, char **path_split,
	char **bin, t_data *data)
{
	int		i;
	char	*temp;
	char	*temp2;

	i = -1;
	while (path_split[++i])
	{
		temp = (char *)ft_calloc(sizeof(char),
				(ft_strlen(path_split[i]) + 1 + ft_strlen(cmd[0]) + 1));
		if (temp == NULL)
			return (0);
		temp2 = ft_strjoin("/", cmd[0]);
		if (!temp2)
			return (free(temp), 0);
		*bin = ft_strjoin3(temp, path_split[i], temp2);
		if (!*bin)
			return (free(temp), free(temp2), 0);
		if (!access(*bin, F_OK))
			return (free(temp), free(temp2), ft_addtotrash(data, *bin), 1);
		free(temp);
		free(temp2);
		free(*bin);
	}
	return (1);
}

char	*get_path(t_env *envp, char **bin)
{
	*bin = NULL;
	if (get_env_val(envp, "PATH"))
		return (ft_strdup(get_env_val(envp, "PATH")));
	return (NULL);
}

char	*get_absolute_path(char **cmd, t_env *envp, t_data *data)
{
	char	*path;
	char	*bin;
	char	**path_split;

	if (ft_strchr(cmd[0], '/'))
		return (check_absolute(cmd[0], data));
	path = get_path(envp, &bin);
	if (!path)
		return (check_absolute(cmd[0], data));
	if (cmd[0][0] != '/' && ft_strncmp(cmd[0], "./", 2) != 0)
	{
		path_split = ft_split(path, ':');
		if (!path_split)
			return (free(path), cmd[0]);
		if (replace_absolute_path(cmd, path_split, &bin, data))
			return (free_array(path_split), bin);
		free_array(path_split);
	}
	return (free(path), check_absolute(cmd[0], data));
}

// char	*get_absolute_path(char **cmd, t_env *envp, t_data *data)
// {
// 	if (ft_strchr(cmd[0], '/'))
// 		return (check_absolute(cmd[0], data));
// 	(void)cmd;
// 	(void)envp;
// 	(void)data;
// 	return (NULL);
// }

int	simple_exec(t_data *data, t_list *lst)
{
	int	fd;

	if (have_redirection_in(lst))
	{
		fd = fd_entry(lst);
		if (fd == -1)
			return (ft_error("open"), 1);
		if (dup2(fd, STDIN_FILENO) == -1)
			return (close(fd), ft_error("dup2"), 127);
		close(fd);
	}
	if (have_redirection_out(lst))
	{
		fd = fd_exit(lst);
		if (fd == -1)
			return (ft_error("open"), 1);
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (close(fd), ft_error("dup2"), 127);
		close(fd);
	}
	if (have_command(lst))
		return (exec_command(data, find_cmd(lst), 1));
	return (0);
}
