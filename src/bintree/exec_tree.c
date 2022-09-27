/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthimoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 16:03:19 by nthimoni          #+#    #+#             */
/*   Updated: 2022/08/12 17:07:30 by nthimoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	unit_pre_exec(t_data *data)
{
	if (unit_tokens(&data->command, data))
		return (1);
	if (unit_first_tokens(&data->command, data))
		return (1);
	if (ft_pre_exec(data))
		return (1);
	if (ft_pre_exec_bis(data))
		return (1);
	return (0);
}

int	exec_tree(t_data *data, t_node *tree)
{
	t_list	*tmp;

	if (tree->type == CMD)
	{
		data->command = tree->tokens;
		if (unit_pre_exec(data))
			return (1);
		tmp = data->command;
		while (tmp)
		{
			((t_token *)tmp->content)->str_split
				= expand_wild_args(((t_token *)tmp->content)->str_split, data);
			if (((t_token *)tmp->content)->str_split == (char **)1)
				return (g_sig = 0);
			tmp = tmp->next;
		}
		return (data->last_exit_code = exec(data));
	}
	g_sig = exec_tree(data, tree->left);
	if (!g_sig && ((t_token *)tree->tokens->content)->type == AND_OP)
		return (exec_tree(data, tree->right));
	else if (g_sig && ((t_token *)tree->tokens->content)->type == OR_OP)
		return (exec_tree(data, tree->right));
	return (g_sig);
}
