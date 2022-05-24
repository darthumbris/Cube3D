/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsetextures.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/13 14:47:17 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/05/24 09:36:03 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

//stores textures for all directions 

void	store_path(char *line, t_data *data, int kind)
{
	//printf("line: %s\n", line);
	line += 2;
	while (*line == ' ')
		line++;
	data->level.paths.path[kind] = line;
}
