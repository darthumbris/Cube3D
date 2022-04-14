/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsetextures.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/13 14:47:17 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/04/13 20:41:14 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

//stores textures for all directions 

void	no_store(char *line, t_data *data)
{
	line += 2;
	while (*line == ' ')
		line++;
	data->level.no_texture_path = line;
}

void	so_store(char *line, t_data *data)
{
	line += 2;
	while (*line == ' ')
		line++;
	data->level.so_texture_path = line;
}

void	we_store(char *line, t_data *data)
{
	line += 2;
	while (*line == ' ')
		line++;
	data->level.we_texture_path = line;
}

void	ea_store(char *line, t_data *data)
{
	line += 2;
	while (*line == ' ')
		line++;
	data->level.ea_texture_path = line;
}
