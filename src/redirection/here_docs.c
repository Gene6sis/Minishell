/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_docs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 21:12:28 by adben-mc          #+#    #+#             */
/*   Updated: 2022/08/19 01:21:36 by nthimoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_content(t_data *data, t_token *token)
{
	char		*str;
	char		*gnl;
	const int	x_dup = dup(0);

	str = "";
	gnl = readline("");
	if (!gnl)
		return (dup2(x_dup, 0), close(x_dup), 0);
	delete_quotes(token->str);
	while (!(!ft_strncmp(gnl, token->str, ft_strlen(gnl))
			&& (ft_strlen(gnl) == ft_strlen(token->str))) && g_sig >= 0)
	{
		if (!*gnl)
			ft_printf("\n");
		token->content = ft_strjoin3(str, gnl, "\n");
		if (!token->content)
			return (dup2(x_dup, 0), close(x_dup), 0);
		ft_addtotrash(data, token->content);
		str = ft_strdup(token->content);
		ft_addtotrash(data, str);
		gnl = readline("");
		if (!str || !gnl)
			return (dup2(x_dup, 0), close(x_dup), 0);
	}
	return (dup2(x_dup, 0), close(x_dup), free(gnl), 1);
}

int	find_name_put(t_token *token)
{
	long	i;
	char	*str;
	int		fd;

	i = 0;
	token->name = NULL;
	while (++i)
	{
		str = ft_itoa(i);
		if (!str)
			return (0);
		if (token->name)
			free(token->name);
		token->name = ft_strjoin3("/tmp/.", str, "docs");
		free(str);
		if (!token->name)
			return (0);
		fd = open(token->name, O_RDWR | O_CREAT | O_EXCL, 0600);
		if (fd != -1)
			return (write(fd, token->content,
					ft_strlen(token->content)), close(fd), 1);
	}
	return (1);
}

int	exec_heredocs(t_data *data)
{
	t_list	*lst;
	t_token	*token;

	lst = data->command;
	while (lst)
	{
		token = lst->content;
		if (token->type == LD_DIR)
		{
			signal_set("heredoc");
			token->content = "";
			if (!get_content(data, token))
			{
				if (g_sig == -42)
					g_sig = 130;
				return (signal_set("normal"), 0);
			}
			signal_set("normal");
			if (!find_name_put(token))
				return (0);
			ft_addtotrash(data, token->name);
		}
		lst = lst->next;
	}
	return (1);
}
