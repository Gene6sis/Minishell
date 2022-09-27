/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_p.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthimoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 17:18:13 by nthimoni          #+#    #+#             */
/*   Updated: 2021/12/09 18:22:54 by nthimoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_flags.h"
#include "buffer.h"
#include "bases.h"
#include "printers.h"

void	print_p(void *p, t_flags *flags)
{
	unsigned long int	uli;
	size_t				len;

	uli = (unsigned long int)p;
	len = ui_len(uli, 16);
	len += 2;
	if (!flags->minus)
		print_n_char(' ', flags->size - len, 0);
	write_buf("0x", 2);
	print_ui_base(uli, BASE_16_LOW);
	if (flags->minus)
		print_n_char(' ', flags->size - len, 0);
}
