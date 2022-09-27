/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_%.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthimoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 21:09:16 by nthimoni          #+#    #+#             */
/*   Updated: 2021/12/12 21:18:58 by nthimoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printers.h"
#include "parse_flags.h"
#include "buffer.h"

void	print_percent(t_flags *flags)
{
	if (!flags->minus && !flags->zero)
		print_n_char(' ', flags->size - 1, 0);
	else if (!flags->minus && flags->zero)
		print_n_char('0', flags->size - 1, 0);
	write_buf("%", 1);
	if (flags->minus)
		print_n_char(' ', flags->size - 1, 0);
}
