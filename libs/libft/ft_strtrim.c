/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/08 12:19:34 by pvan-dij      #+#    #+#                 */
/*   Updated: 2021/10/08 12:20:46 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	getstart(const char *s1, const char *set)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(s1);
	i = 0;
	while (i < len)
	{
		if (ft_strchr((char *)set, s1[i]) == 0)
			break ;
		i++;
	}
	return (i);
}

static int	getend(const char *s1, const char *set)
{
	size_t	len;

	len = ft_strlen(s1);
	while (len > 0)
	{
		if (ft_strchr((char *)set, s1[len - 1]) == 0)
			break ;
		len--;
	}
	return (len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*out;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	start = getstart(s1, set);
	end = getend(s1, set);
	if (start >= end)
		return (ft_strdup(""));
	out = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!out)
		return (NULL);
	ft_strlcpy(out, s1 + start, end - start + 1);
	return (out);
}
