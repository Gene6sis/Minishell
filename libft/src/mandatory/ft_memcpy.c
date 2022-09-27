/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 03:43:41 by adben-mc          #+#    #+#             */
/*   Updated: 2021/11/25 18:02:12 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dest;
	unsigned char	*source;

	if (!dst && !src)
		return (dst);
	dest = (unsigned char *)dst;
	source = (unsigned char *)src;
	while (n)
	{
		n--;
		dest[n] = source[n];
	}
	return (dst);
}
