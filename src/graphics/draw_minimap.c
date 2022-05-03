/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_minimap.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/29 13:55:37 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/05/03 15:38:29 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

#define WALL_COLOUR 0xFF0000FF

bool draw_square(t_data *data, t_vector_int rec, \
t_vector_int wh, unsigned int c)
{
	uint8_t	*map;
	int		i;
	int		j;

	i = rec.y;
	map = data->mlx.minimap->pixels;
	if (i < 0)
		i = 0;
	while (i < rec.y + wh.y && i < (int)data->mlx.minimap->height)
	{
		j = rec.x;
		while (j < rec.x + wh.x)
		{
			if (*(uint32_t *)(map + ((i * data->mlx.minimap->width + j) * 4)) == WALL_COLOUR)
				return(false);
			*(uint32_t *)(map + ((i * data->mlx.minimap->width + j) * 4)) = c;
			j++;
		}
		i++;
	}
	return (true);
}

static void draw_minimap_walls(t_data *data)
{
	t_vector_int start = {.y = (int)(data->cam.pos.y - 10), .x = (int)(data->cam.pos.x - 20)}; //TODO: change 10/20 in appropriate w-h ratio to change map zoom. put these inside data and we can change map zoom
	t_vector_int end = {.y = (int)(data->cam.pos.y + 10), .x = (int)(data->cam.pos.x + 20)};

	int temp = start.x;
	int i, j;
	i = 0;
	while (start.y < end.y)
	{
		start.x = temp;
		j = 0;
		while (start.x < end.x)
		{
			if (!(start.x < 0 || start.y < 0 || start.x >= data->level.map_w || start.y >= data->level.map_h) && is_wall_tile(data->level.map[start.y][start.x]))
			{
				draw_square(data, (t_vector_int){.y = (data->mlx.minimap->height/20) * i, .x = (data->mlx.minimap->width/40) *j}, \
								  (t_vector_int){.y = 6, .x = 6}, WALL_COLOUR);
			}	
			start.x++;
			j++;
		}
		i++;
		start.y++;
	}
}

//TODO: doors, hidden rooms
void	draw_minimap(t_data *data)
{
	ft_memset(data->mlx.minimap->pixels, 255, data->mlx.minimap->width * data->mlx.minimap->height * sizeof(int));
	draw_minimap_walls(data);


	const t_vector_int			wh = {.y = data->mlx.minimap->height / 2, .x = data->mlx.minimap->width / 2};
	int i;
	//const t_vector_double		playerpos = data->cam.pos;
	i = -1;
	bool temp = true; 
	while (++i < 5 * data->mlx.hud_scale && temp) //TODO: view cone instead of line
		temp = draw_square(data, (t_vector_int){.y = wh.y + (i * data->cam.dir.y), .x = wh.x + (i * data->cam.dir.x)}, (t_vector_int){.y = data->mlx.hud_scale, .x = data->mlx.hud_scale}, 0xD7FFFFFF);

	draw_square(data, wh, (t_vector_int) {.y = data->mlx.hud_scale, .x = data->mlx.hud_scale}, 0x000000FF);
}

//TODO: norm is cringe