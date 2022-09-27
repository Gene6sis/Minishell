/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 03:48:50 by adben-mc          #+#    #+#             */
/*   Updated: 2021/11/29 19:54:00 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (dstsize != 0 && i < dstsize - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	if (i < dstsize)
		dst[i] = 0;
	while (src[i])
		i++;
	return (i);
}

/*
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	(void)argc;
	char dest[100];
	char *src = argv[2];
	int nb = atoi(argv[3]);
	printf("Original : %zu\t%s\n\n", strlcpy(dest, src, nb), dest);


	char dest1[100];
	printf("Fake : %zu\t%s\n\n", ft_strlcpy(dest1, src, nb), dest1);


	char dest2[100];
	printf("Fuck : %zu\t%s\n\n", ft_strlcpy1(dest2, src, nb), dest2);
}
*/
