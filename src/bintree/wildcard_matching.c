/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_matching.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthimoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 19:31:24 by nthimoni          #+#    #+#             */
/*   Updated: 2022/08/07 22:18:13 by nthimoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main_comparaison_loop(char **w, char **s, char *s_save, char *w_save)
{
	while (**s)
	{
		if (**w == WILDCARD)
		{
			if (!*++(*w))
				return (1);
			w_save = *w;
			s_save = (*s) + 1;
		}
		else if (**w == **s || **w == '?')
		{
			(*w)++;
			(*s)++;
		}
		else
		{
			*w = w_save;
			*s = s_save++;
		}
	}
	return (0);
}

int	wildcard_matching(char *wild, char *string)
{
	char	*string_save;
	char	*wild_save;

	string_save = string;
	wild_save = wild;
	while (*wild && (*wild == *string || *wild == '?'))
	{
		wild++;
		string++;
	}
	if (*wild != WILDCARD && *wild != '?' && *wild)
		return (0);
	if (main_comparaison_loop(&wild, &string, string_save, wild_save))
		return (1);
	while (*wild == WILDCARD)
		wild++;
	return (!*wild);
}
