/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_di.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthimoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 17:03:31 by nthimoni          #+#    #+#             */
/*   Updated: 2021/12/13 17:07:39 by nthimoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printers.h"
#include "buffer.h"
#include "parse_flags.h"
#include "bases.h"

#include <stdio.h>

void	reg_dot(t_flags *flags, size_t len)
{
	if (flags->dot < (int)len)
		flags->dot = len;
}

static void	print_before(t_flags *flags, int a, unsigned int len, int sign)
{
	if (!flags->minus && (!flags->zero)
		&& flags->size != -1)
		print_n_char(' ', flags->size - flags->dot - sign, 0);
	if (a < 0)
		write_buf("-", 1);
	else if (flags->plus)
		write_buf("+", 1);
	else if (flags->space)
		write_buf(" ", 1);
	if (!flags->minus && (flags->zero) && flags->size != -1)
		print_n_char('0', flags->size - flags->dot - sign, 0);
	print_n_char('0', flags->dot - len, 0);
}

void	print_di(int a, t_flags *flags)
{
	unsigned int	u;
	unsigned int	len;
	int				sign;

	if (a < 0)
		u = -a;
	else
		u = a;
	len = ui_len(u, 10);
	if (!a && flags->dot == 0)
		len--;
	sign = 0;
	if (a < 0 || flags->plus || flags->space)
		sign = 1;
	reg_dot(flags, len);
	print_before(flags, a, len, sign);
	if (u || flags->dot != 0)
		print_ui_base(u, BASE_10);
	if (flags->minus)
		print_n_char(' ', flags->size - flags->dot - sign, 0);
}
