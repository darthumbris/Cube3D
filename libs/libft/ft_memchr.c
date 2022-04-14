/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/08 12:18:23 by pvan-dij      #+#    #+#                 */
/*   Updated: 2021/10/08 12:22:12 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(void *buf, int c, size_t len)
{
	unsigned char	*mem;
	size_t			i;

	i = 0;
	mem = buf;
	while (i < len)
	{
		if (*mem == (unsigned char)c)
			return (mem);
		i++;
		mem++;
	}
	return (NULL);
}
