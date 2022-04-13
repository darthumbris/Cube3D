/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/08 12:18:39 by pvan-dij      #+#    #+#                 */
/*   Updated: 2021/10/13 15:59:31 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*dest;
	int					i;

	i = 0;
	if (dst == src)
		return (dst);
	dest = dst;
	if (src < dst)
	{
		while (len)
		{
			--len;
			dest[len] = ((unsigned char *)src)[len];
		}
	}	
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
