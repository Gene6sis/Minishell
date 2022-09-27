/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 00:26:21 by adben-mc          #+#    #+#             */
/*   Updated: 2021/11/30 23:26:50 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	*str;

	str = (char *)s;
	i = ft_strlen(s) + 1;
	while (i--)
		if (str[i] == (char)c)
			return (str + i);
	return (NULL);
}

/*
#include <stdio.h>

int main(int argc, char **argv)
{
	(void)argc;
	printf("True : %s\n", strrchr(argv[1], argv[2][0]));
	printf("Fake : %s\n", ft_strrchr(argv[1], argv[2][0]));
}*/
