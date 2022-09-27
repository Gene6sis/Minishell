/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_s.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthimoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 17:07:28 by nthimoni          #+#    #+#             */
/*   Updated: 2021/12/12 20:55:46 by nthimoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_flags.h" 
#include "buffer.h"
#include "libft.h"
#include "printers.h"

static int	bound_str_size(const char *str, int max)
{	
	int	len;

	len = ft_strlen(str);
	if (len <= max || max == -1)
		return (len);
	return (max);
}

static int	null_str(const char *str, t_flags *flags)
{
	if (str)
		return (0);
	if (flags->dot > 6 || flags->dot == -1)
		flags->dot = 6;
	if (!flags->minus)
		print_n_char(' ', flags->size - flags->dot, 0);
	write_buf("(null)", flags->dot);
	if (flags->minus)
		print_n_char(' ', flags->size - flags->dot, 0);
	return (1);
}

void	print_s(const char *s, t_flags *flags)
{
	int		i;
	int		len;

	if (null_str(s, flags))
		return ;
	len = bound_str_size(s, flags->dot);
	i = 0;
	while (!flags->minus && i < flags->size - len)
	{
		write_buf(" ", 1);
		i++;
	}
	write_buf(s, len);
	while (flags->minus && i < flags->size - len)
	{
		write_buf(" ", 1);
		i++;
	}
}
