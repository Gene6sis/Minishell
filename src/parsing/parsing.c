/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 23:01:12 by adben-mc          #+#    #+#             */
/*   Updated: 2022/08/21 21:03:33 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Delete an element from a t_list
void	ft_lstdeloneelmt(t_list **list, t_list *to_delete)
{
	t_list	*tmp;

	if (!list || !*list || !to_delete)
		return ;
	if (*list == to_delete)
	{
		*list = (*list)->next;
		return ;
	}
	tmp = *list;
	while (tmp->next && tmp->next != to_delete)
		tmp = tmp->next;
	if (tmp->next)
	{
		tmp->next = tmp->next->next;
		return ;
	}
}

int	ft_parsing(t_data *data, char **env)
{
	char	*pwd;

	data->trash = NULL;
	data->env_lst = env_to_lst(env, data);
	if (chdir("."))
		return (1);
	pwd = getcwd(0, 0);
	if (!pwd)
		return (1);
	if (export_add(data, "PWD", pwd))
		return (free(pwd), 1);
	free(pwd);
	if (ft_shlvl(data))
		return (1);
	data->env_str = env;
	return (0);
}

// print a t_list * (content and type)
// void	ft_printtlist(t_list *lst)
// {
// 	t_list	*tmp;
// 	t_token	*token;

// 	tmp = lst;
// 	printf("--------------------------\n");
// 	printf("Parsing of T_List\n");
// 	printf("--------------------------\n");
// 	while (tmp)
// 	{
// 		token = (t_token *)tmp->content;
// 		printf("\ntoken : [%s]\n", token->str);
// 		if (token->type == RD_DIR)
// 			printf("\tRD_DIR\n");
// 		else if (token->type == LD_DIR)
// 		{
// 			printf("\tLD_DIR\n");
// 		}
// 		else if (token->type == L_DIR)
// 			printf("\tL_DIR\n");
// 		else if (token->type == R_DIR)
// 			printf("\tR_DIR\n");
// 		else if (token->type == O_PARENTH)
// 			printf("\tO_PARENTH\n");
// 		else if (token->type == C_PARENTH)
// 			printf("\tC_PARENTH\n");
// 		else if (token->type == AND_OP)
// 			printf("\tAND_OP\n");
// 		else if (token->type == OR_OP)
// 			printf("\tOR_OP\n");
// 		else if (token->type == PIPE)
// 			printf("\tPIPE\n");
// 		else if (token->type == WORD)
// 			printf("\tWORD\n");
// 		else
// 			printf("\tNONE\n");
// 		ft_print_char_star_star(token->str_split);
// 		tmp = tmp->next;
// 	}
// 	printf("size of t_list : %d\n", ft_lstsize(lst));
// 	printf("--------------------------\n");
// }

int	ft_parse_input(t_data *data, char *input)
{
	t_node	*tree;

	data->command = get_tokens(input, data);
	if (!data->command)
		return (1);
	else if (data->command == (t_list *)1)
		return (0);
	if (verif_parenth(data->command))
		return (0);
	tree = build_tree(&data->command, data);
	if (tree)
		g_sig = exec_tree(data, tree);
	return (0);
}

int	fill_env_str(t_data *data)
{
	int		i;
	t_env	*env;

	i = 0;
	env = data->env_lst;
	while (env)
	{
		data->env_str[i] = ft_strjoin3(env->name, "=", env->value);
		if (!data->env_str[i])
			return (1);
		ft_addtotrash(data, data->env_str[i]);
		i++;
		env = env->next;
	}
	data->env_str[i] = NULL;
	return (0);
}

int	update_env_str(t_data *data, t_env *env)
{
	int		size;
	t_env	*acc;

	acc = env;
	size = 0;
	while (acc)
	{
		acc = acc->next;
		size++;
	}
	data->env_str = malloc(sizeof(char *) * (size + 1));
	if (!data->env_str)
		return (1);
	ft_addtotrash(data, data->env_str);
	if (fill_env_str(data))
		return (1);
	return (0);
}
