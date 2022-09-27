/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthimoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 16:53:59 by nthimoni          #+#    #+#             */
/*   Updated: 2021/12/07 17:05:11 by nthimoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFFER_H
# define BUFFER_H

# ifndef PRINTF_BUFFER
#  define PRINTF_BUFFER 400
# endif

# include <stdlib.h>

int	write_buf(const char *str, size_t len);

#endif
