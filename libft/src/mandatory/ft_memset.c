/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 00:32:41 by adben-mc          #+#    #+#             */
/*   Updated: 2021/09/11 04:24:23 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*str;

	str = (unsigned char *)s;
	while (n)
	{
		n--;
		str[n] = c;
	}
	return (str);
}
/*
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


int	ft_atoi(char *str)
{
	int res;
	int	i;
	int sign;

	sign = 1;
	res = 0;
	i = 0;

	if (str[i] == '-')
	{
		sign = -sign;
		i++;
	}
	while (str[i])
	{
		res = res * 10 + str[i] - 48;
		i++;
	}
	return (res * sign);
}

int	ft_strncmp(char s1, char s2)
{
	return ((unsigned char)s1 - (unsigned char)s2);
}

void	ch_memset(int a, int b)
{
	char	test1[b];
	char	test2[b];

	int	i;

	for (i = 0; i < b; i++)
		printf("Before ft_memset  : %d <---> memset : %d\n", test1[i], test2[i]);
	ft_memset(test1, a, b);
	test1[18] = 12; //false pour true enlever
	memset(test2, a, b);
	printf("\n\n");
	for (i = 0; i < b; i++)
		printf("	Ft_memset : %d <---> memset : %d\n", test1[i], test2[i]);
    for(i = 0; i < b; i++)
        if (ft_strncmp(test1[i], test2[i]) != 0)
        {
          printf("KO Check_memset --> ligne %d\n", i);
          exit(1);
        }
  	printf("\n		----- MEMSET valide -----\n");
}

int main(int ac, char **av)
{
	if (ac == 3)
		ch_memset(ft_atoi(av[1]), ft_atoi(av[2]));
	else if (ac > 3)
		ch_memset(av[3][0], ft_atoi(av[2]));
	else
		return (0);
	return (0);
}

*/
