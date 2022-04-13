/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/08 12:17:27 by pvan-dij      #+#    #+#                 */
/*   Updated: 2021/10/08 12:22:34 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t n, size_t size)
{
	void	*out;

	out = (void *)malloc(n * size);
	if (!out)
		return (NULL);
	ft_memset(out, 0, n * size);
	return (out);
}
