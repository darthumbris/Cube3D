/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils2.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/23 12:58:16 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/23 13:12:30 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	*map_error_msg(char *msg)
{
	printf("Error: %s\n", msg);
	return (NULL);
}

bool	error_msg(char *msg)
{
	printf("Error: %s\n", msg);
	return (false);
}
