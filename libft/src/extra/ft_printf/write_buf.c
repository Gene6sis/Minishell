/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_buf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthimoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 16:37:48 by nthimoni          #+#    #+#             */
/*   Updated: 2021/12/09 19:12:41 by nthimoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "buffer.h"

static int	flush(char *buffer, size_t *len)
{
	int	wrote;

	wrote = write(1, buffer, *len);
	buffer[0] = '\0';
	*len = 0;
	return (wrote);
}

static int	ft_subcat(char *dst, const char *src, size_t len, size_t content)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		dst[content + i] = src[i];
		++i;
	}
	dst[content + i] = '\0';
	return (len);
}

int	write_buf(const char *str, size_t len)
{
	static char		buffer[PRINTF_BUFFER + 1];
	static int		wrote = 0;
	static size_t	content_size = 0;
	int				tmp;

	if (!len && !str)
	{
		wrote += flush(buffer, &content_size);
		tmp = wrote;
		wrote = 0;
		return (tmp);
	}
	if (len >= PRINTF_BUFFER - content_size)
	{
		wrote += flush(buffer, &content_size);
		wrote += write(1, str, len);
	}
	else
		content_size += ft_subcat(buffer, str, len, content_size);
	return (0);
}
