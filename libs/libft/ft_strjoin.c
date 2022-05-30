/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/08 12:19:06 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/05/30 15:11:54 by shoogenb      ########   odam.nl         */
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

char	*ft_strjoin_r(char const *s1, char const *s2)
{
	char	*joined;
	int		i;

	i = 0;
	if (s1 == 0 || s2 == 0)
		return (NULL);
	joined = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (joined == 0)
		return (NULL);
	while (s1[i])
	{
		joined[i] = s1[i];
		i++;
	}
	while (*s2)
	{
		joined[i] = *s2;
		i++;
		s2++;
	}
	joined[i] = '\0';
	return (joined);
}