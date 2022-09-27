/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthimoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 14:11:58 by nthimoni          #+#    #+#             */
/*   Updated: 2021/12/13 17:11:54 by nthimoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_flags.h"
#include "libft.h"
#include "printers.h"

static int	type_specifier(char c, char *u)
{
	if (c == 'd' || c == 'i' || c == 'u' || c == 'x' || c == 'X'
		|| c == 'c' || c == 's' || c == 'p' || c == '%')
	{
		*u = c;
		return (1);
	}
	return (0);
}

static int	read_nb(t_flags *flags, const char *str)
{
	if (flags->dot > -1)
	{
		flags->dot = ft_atoi(str);
		return (ui_len(flags->dot, 10) - 1);
	}
	else
	{
		flags->size = ft_atoi(str);
		return (ui_len(flags->size, 10) - 1);
	}
}

static void	process_dot(t_flags *flags)
{
	flags->zero = 0;
	flags->dot = 0;
}

const char	*parse_flags(const char *str, t_flags *flags)
{
	int	i;

	i = 0;
	str++;
	while (str[i])
	{
		if (str[i] == '-')
			flags->minus = 1;
		else if (str[i] == '0' && flags->dot == -1)
			flags->zero = 1;
		else if (str[i] == '#')
			flags->diez = 1;
		else if (str[i] == ' ')
			flags->space = 1;
		else if (str[i] == '+')
			flags->plus = 1;
		else if (str[i] == '.')
			process_dot(flags);
		else if (type_specifier(str[i], &flags->type))
			return (str + i + 1);
		else if (ft_isdigit(str[i]))
			i += read_nb(flags, str + i);
		i++;
	}
	return (str + i);
}
