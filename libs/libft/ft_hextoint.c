/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_hextoint.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/12 15:23:05 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/05/12 15:23:06 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "math.h"

int	ft_hextoint(char *hex)
{
	int	i;
	int	len;
	int	out;

	len = ft_strlen(hex);
	i = 0;
	out = 0;
	while (hex[i])
	{
		if (ft_isdigit(hex[i]))
			out += ((hex[i] - 48) * ((int)pow(16, (double)(len - i - 1))));
		else
			out += ((hex[i] - 55) * ((int)pow(16, (double)(len - i - 1))));
		i++;
	}
	return (out);
}
