/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthimoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 14:05:37 by nthimoni          #+#    #+#             */
/*   Updated: 2021/12/06 19:20:22 by nthimoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_FLAGS_H
# define PARSE_FLAGS_H

typedef struct s_flags
{
	int		minus;
	int		zero;
	int		diez;
	int		space;
	int		plus;
	int		dot;
	int		size;
	char	type;
}	t_flags;

const char	*parse_flags(const char *str, t_flags *flags);

#endif
