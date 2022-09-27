/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 23:26:56 by adben-mc          #+#    #+#             */
/*   Updated: 2022/08/03 03:45:23 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reprint_c(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", 2);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_sig = 130;
}

void	ctrl_c(int sig)
{
	(void)sig;
	signal(SIGINT, SIG_IGN);
	ft_putstr_fd("\n", 2);
	close(0);
	g_sig = -42;
}

void	ignore_slash(void)
{
	signal(SIGQUIT, SIG_IGN);
}

void	child_c(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", 2);
	g_sig = 130;
}

void	signal_set(char *stage)
{
	if (!ft_strcmp("normal", stage))
	{
		ignore_slash();
		signal(SIGINT, reprint_c);
	}
	if (!ft_strcmp("heredoc", stage))
	{
		ignore_slash();
		signal(SIGINT, SIG_IGN);
		signal(SIGINT, ctrl_c);
	}
	if (!ft_strcmp("child", stage))
	{
		signal(SIGINT, SIG_IGN);
	}
}
