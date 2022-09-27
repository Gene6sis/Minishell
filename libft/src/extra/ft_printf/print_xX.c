/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_xX.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthimoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 17:34:50 by nthimoni          #+#    #+#             */
/*   Updated: 2022/02/09 19:14:57 by nthimoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_flags.h"
#include "buffer.h"
#include "bases.h"
#include "printers.h"

static void	print_before(t_flags *flags, unsigned int len, int i, int pref)
{
	if (!flags->minus && !flags->zero && flags->size != -1)
		print_n_char(' ', flags->size - flags->dot - pref, 0);
	if (flags->diez && flags->type == 'x' && (unsigned int)i != 0)
		write_buf("0x", 2);
	if (flags->diez && flags->type == 'X' && (unsigned int)i != 0)
		write_buf("0X", 2);
	if (!flags->minus && flags->zero && flags->size != -1)
		print_n_char('0', flags->size - flags->dot - pref, 0);
	print_n_char('0', flags->dot - len, 0);
}

void	print_x(int i, t_flags *flags)
{	
	size_t	len;
	int		prefix;

	if (!i && flags->dot == 0)
	{
		print_n_char(' ', flags->size, 0);
		return ;
	}
	prefix = 0;
	if (flags->diez && i != 0)
		prefix = 2;
	len = ui_len((unsigned int)i, 16);
	reg_dot(flags, len);
	print_before(flags, len, i, prefix);
	if (flags->type == 'x')
		print_ui_base((unsigned int)i, BASE_16_LOW);
	if (flags->type == 'X')
		print_ui_base((unsigned int)i, BASE_16_UP);
	if (flags->minus)
		print_n_char(' ', flags->size - flags->dot - prefix, 0);
}
