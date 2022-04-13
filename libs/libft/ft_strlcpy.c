/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/08 12:19:12 by pvan-dij      #+#    #+#                 */
/*   Updated: 2021/10/13 15:45:27 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	srclen;
	size_t	i;

	i = 0;
	srclen = ft_strlen(src);
	if (size == 0)
		return (srclen);
	while (*src != 0 && i < (size - 1))
	{
		*dst = *src;
		dst++;
		src++;
		i++;
	}
	*dst = 0;
	return (srclen);
}
