/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/08 12:18:37 by pvan-dij      #+#    #+#                 */
/*   Updated: 2021/10/08 12:22:07 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t len)
{
	unsigned char		*dest;
	const unsigned char	*sorc;
	int					i;

	if (!dst && !src)
		return (dst);
	i = 0;
	dest = dst;
	sorc = src;
	while (len > 0)
	{
		dest[i] = sorc[i];
		i++;
		len--;
	}
	return (dest);
}
