/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 04:22:30 by adben-mc          #+#    #+#             */
/*   Updated: 2021/10/13 13:31:12 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
	}
	if ((char)c == s[i])
		return ((char *)(s + i));
	return (NULL);
}
/*
#include <stdio.h>

int main(int argc, char **argv)
{
(void)argc;
printf("True : %s\n", strchr(argv[1], argv[2][0]));
printf("Fake : %s\n", ft_strchr(argv[1], argv[2][0]));
}*/
