/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/08 12:19:39 by pvan-dij      #+#    #+#                 */
/*   Updated: 2021/10/13 15:46:29 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*out;
	size_t	i;
	size_t	strlen;

	strlen = (ft_strlen(s));
	if (!s)
		return (NULL);
	if (start > strlen)
		return (ft_strdup(""));
	if (len > strlen - start)
		return (ft_strdup(s + start));
	out = (char *)malloc((len + 1) * sizeof(char));
	if (!out)
		return (NULL);
	i = 0;
	while (i < len && s[start] != 0)
	{
		out[i] = s[start];
		i++;
		start++;
	}
	out[i] = 0;
	return (out);
}
