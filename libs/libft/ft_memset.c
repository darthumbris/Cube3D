/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/08 12:18:41 by pvan-dij      #+#    #+#                 */
/*   Updated: 2021/10/13 15:44:43 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dst, int c, size_t len)
{
	unsigned char	*dest;
	int				i;

	i = 0;
	dest = dst;
	while (len > 0)
	{
		dest[i] = c;
		i++;
		len--;
	}
	return (dest);
}
