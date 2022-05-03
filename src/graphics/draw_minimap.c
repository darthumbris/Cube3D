/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_minimap.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/29 13:55:37 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/05/03 16:13:07 by pvan-dij      ########   odam.nl         */
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
			if (c != WALL_COLOUR && *(uint32_t *)(map + ((i * data->mlx.minimap->width + j) * 4)) == WALL_COLOUR)
				return(false);
			*(uint32_t *)(map + ((i * data->mlx.minimap->width + j) * 4)) = c;
			j++;
		}
		i++;
	}
	return (true);
}

 //TODO: map is very jumpy when changing zoom and player doestn collide well on some zoom levels
static void draw_minimap_walls(t_data *data)
{
	t_vector_int start = {.y = (int)(data->cam.pos.y - roundf(data->mlx.minimap_zoom * data->mlx.minimap_scale)), .x = (int)(data->cam.pos.x - data->mlx.minimap_zoom)};
	t_vector_int end = {.y = (int)(data->cam.pos.y + roundf(data->mlx.minimap_zoom * data->mlx.minimap_scale)), .x = (int)(data->cam.pos.x + data->mlx.minimap_zoom)};
	const int square_x = data->mlx.minimap->width / (data->mlx.minimap_zoom * 2);
	const int square_y = data->mlx.minimap->height / ((data->mlx.minimap_zoom * 2) * data->mlx.minimap_scale);

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
				draw_square(data, (t_vector_int){.y = square_y * i, .x = square_x *j}, \
								  (t_vector_int){.y = 120/data->mlx.minimap_zoom, .x = 120/data->mlx.minimap_zoom}, WALL_COLOUR); //TODO:120/zoom is near perfect but not quite there, round or something
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
	draw_minimap_walls(data); //TODO: change colours outside of wall

	const t_vector_int			wh = {.y = data->mlx.minimap->height / 2, .x = data->mlx.minimap->width / 2};
	int i;
	//const t_vector_double		playerpos = data->cam.pos;
	i = -1;
	bool temp = true; 
	while (++i < 5 * data->mlx.hud_scale && temp) //TODO: view cone instead of line
		temp = draw_square(data, (t_vector_int){.y = wh.y + (i * data->cam.dir.y), .x = wh.x + (i * data->cam.dir.x)}, (t_vector_int){.y = data->mlx.hud_scale, .x = data->mlx.hud_scale}, 0xD7FFFFFF);

	draw_square(data, wh, (t_vector_int) {.y = data->mlx.hud_scale, .x = data->mlx.hud_scale}, 0x000000FF);
}
