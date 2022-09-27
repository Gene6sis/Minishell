/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wild_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 15:38:59 by nthimoni          #+#    #+#             */
/*   Updated: 2022/08/19 11:11:43 by nthimoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>

int	check_valid_filename(char *name, char *str)
{
	if (ft_strncmp(name, "..", 3)
		&& ft_strncmp(name, ".", 2)
		&& wildcard_matching(str, name)
		&& ((*str == '.' && *name == '.')
			|| (*str != '.' && *name != '.')))
		return (1);
	return (0);
}

int	add_file_name(char *name, int *flag, t_data *data, t_list **lst)
{
	t_list	*tmp;

	name = ft_strdup(name);
	if (!name)
		return (1);
	ft_addtotrash(data, name);
	tmp = new_lst_str(name, data);
	if (!tmp)
		return (1);
	ft_lstadd_back(lst, tmp);
	*flag = 1;
	return (0);
}

static int	process_wild(t_list **lst, char *str, t_data *data)
{
	DIR				*dir;
	struct dirent	*file;
	int				flag;
	t_list			*to_sort;

	to_sort = NULL;
	dir = opendir(".");
	if (!dir)
		return (2);
	file = readdir(dir);
	flag = 0;
	while (file)
	{
		if (check_valid_filename(file->d_name, str))
			if (add_file_name(file->d_name, &flag, data, &to_sort))
				return (closedir(dir), 1);
		file = readdir(dir);
	}
	if (check_flag(flag, str, data, lst))
		return (closedir(dir), 1);
	sort_lst(to_sort, lst);
	return (closedir(dir), 0);
}

int	process_add(char *str, t_list **lst, t_data *data)
{
	t_list	*tmp;

	if (!is_in(str, WILDCARD) && !is_in(str, '?'))
	{
		rp_back_wild(str);
		tmp = new_lst_str(str, data);
		if (!tmp)
			return (1);
		ft_lstadd_back(lst, tmp);
	}
	else
		if (process_wild(lst, str, data))
			return (1);
	return (0);
}

char	**expand_wild_args(char **args, t_data *data)
{
	t_list	*lst;
	char	**ret;

	args = expand(args, data);
	lst = NULL;
	if (!args)
		return (NULL);
	while (*args)
	{
		process_add(*args, &lst, data);
		args++;
	}
	ret = convert_lst_to_2d_char(lst, data);
	if (ft_strslen(ret) == 1 && ret[0][0] == 0)
		return ((char **)1);
	return (ret);
}
