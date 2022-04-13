/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_arrjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/03 16:47:40 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/03/03 17:01:58 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Joins all the strings in a NULL terminated array.
 * Example format: ft_arrjoin((char *[]){str1, str2, "stringliteral", NULL})
 * 
 * @param arr The array
 */
char	*ft_arrjoin(char **arr)
{
	int		i;
	char	*out;

	i = 0;
	out = NULL;
	while (arr[i])
	{
		out = ft_strjoin(out, arr[i]);
		if (!out)
			return (NULL);
		i++;
	}
	return (out);
}
