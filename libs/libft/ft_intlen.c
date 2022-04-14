/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_intlen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/08 12:17:39 by pvan-dij      #+#    #+#                 */
/*   Updated: 2021/10/08 12:22:31 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_intlen(int val)
{
	int	i;

	i = 0;
	if (val < 0)
		val = -val;
	while (val > 9)
	{
		i++;
		val /= 10;
	}
	return (i);
}
