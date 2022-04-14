/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/08 12:19:06 by pvan-dij      #+#    #+#                 */
/*   Updated: 2021/10/27 22:45:38 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*out;
	size_t	i1;
	size_t	i2;

	if (!s1)
		return (ft_strdup(s2));
	i1 = ft_strlen(s1);
	i2 = ft_strlen(s2);
	out = malloc(sizeof(char) * (i1 + i2 + 1));
	if (!out)
		return (NULL);
	ft_memmove(out, s1, i1);
	free(s1);
	s1 = NULL;
	ft_memmove(out + i1, s2, i2);
	out[i1 + i2] = 0;
	return (out);
}
