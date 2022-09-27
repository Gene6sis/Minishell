/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 02:34:42 by adben-mc          #+#    #+#             */
/*   Updated: 2021/11/18 13:56:38 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*copy_debut(void *dest, const void *src, size_t n)
{
	unsigned int	i;

	i = -1;
	while (++i < n)
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
	return (dest);
}

void	*copy_fin(void *dest, const void *src, size_t n)
{
	unsigned int	i;

	i = -1;
	while (++i < n)
		((unsigned char *)dest)[n - i - 1] = ((unsigned char *)src)[n - i - 1];
	return (dest);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned long long	dest;
	unsigned long long	source;

	dest = (unsigned long long)dst;
	source = (unsigned long long)src;
	if (dest == source)
		return (dst);
	if (source > dest && source <= dest + len - 1)
		return (copy_debut(dst, src, len));
	if (dest > source && dest <= source + len - 1)
		return (copy_fin(dst, src, len));
	return (copy_fin(dst, src, len));
}

/*
#include <stdio.h>

int main()
{
char a[] = "abcde";
ft_memmove(a+0, a+2, 3);
printf("%s\n", a);
return (0);
}*/
