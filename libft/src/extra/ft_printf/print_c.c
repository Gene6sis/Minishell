/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_c.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthimoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 17:10:13 by nthimoni          #+#    #+#             */
/*   Updated: 2021/12/12 21:13:26 by nthimoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printers.h"
#include "parse_flags.h"
#include "buffer.h"

void	print_c(unsigned char c, t_flags *flags)
{
	int	i;

	i = 0;
	while (!flags->minus && i < flags->size - 1)
	{
		write_buf(" ", 1);
		i++;
	}
	write_buf((const char *)&c, 1);
	while (flags->minus && i < flags->size - 1)
	{
		write_buf(" ", 1);
		i++;
	}
}
