/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 19:37:07 by nthimoni          #+#    #+#             */
/*   Updated: 2022/07/26 18:49:21 by nthimoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef enum e_token_type
{
	NONE_TOKEN = 0,
	WORD,
	R_DIR,
	L_DIR,
	RD_DIR,
	LD_DIR,
	O_PARENTH,
	C_PARENTH,
	AND_OP,
	OR_OP,
	PIPE,
}	t_token_type;

#endif
