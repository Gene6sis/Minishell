/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 03:58:59 by nthimoni          #+#    #+#             */
/*   Updated: 2022/08/18 03:07:41 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig = 0;

int	main(int argc, char **argv, char **env)
{
	t_data		data;
	const char	*prompt = "Minichevre : ";
	char		*input;

	signal_set("normal");
	if (!ft_parsing(&data, env))
	{
		while (1)
		{
			input = readline(prompt);
			if (!input)
				return (free_trash(&data), printf("exit\n"), 0);
			if (is_only_space(input))
				continue ;
			if (ft_parse_input(&data, input))
				break ;
			ft_readlinehistory(&data, input);
		}
	}
	free_trash(&data);
	return ((void)argc, (void)argv, 0);
}

void	print_tree(t_node *tree, int lvl)
{
	if (tree->left)
		print_tree(tree->left, lvl + 1);
	if (tree->right)
		print_tree(tree->right, lvl + 1);
}
