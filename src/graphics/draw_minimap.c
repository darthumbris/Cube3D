/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_minimap.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/29 13:55:37 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/05/03 16:38:18 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static void draw_walls_x(t_data *data, t_vector_int start, t_vector_int end, t_vector_int square, int i)
{
	int j;

	j = 0;
	while (start.x < end.x)
	{
		if (!(start.x < 0 || start.y < 0 || start.x >= data->level.map_w || start.y >= data->level.map_h) && is_wall_tile(data->level.map[start.y][start.x]))
		{
			draw_square(data, (t_vector_int){.y = square.y * i, .x = square.x *j}, \
							  (t_vector_int){.y = 120/data->mlx.minimap_zoom, .x = 120/data->mlx.minimap_zoom}, WALL_COLOUR); //TODO:120/zoom is near perfect but not quite there, round or something
		}	
		start.x++;
		j++;
	}
}

 //TODO: map is very jumpy when changing zoom and player doesnt collide well on some zoom levels
static void draw_minimap_walls(t_data *data)
{
	t_vector_int start = {.y = (int)(data->cam.pos.y - roundf(data->mlx.minimap_zoom * data->mlx.minimap_scale)), .x = (int)(data->cam.pos.x - data->mlx.minimap_zoom)};
	t_vector_int end = {.y = (int)(data->cam.pos.y + roundf(data->mlx.minimap_zoom * data->mlx.minimap_scale)), .x = (int)(data->cam.pos.x + data->mlx.minimap_zoom)};
	t_vector_int square_loc_calc = {.x = data->mlx.minimap->width / (data->mlx.minimap_zoom * 2), \
									.y = data->mlx.minimap->height / ((data->mlx.minimap_zoom * 2) * data->mlx.minimap_scale)};

	//int dx = end.x - start.x;
	//int dy = end.y - start.y;
	int i, j; //dont like this
	i = 0;
	while (start.y < end.y)
	{
		j = 0;
		draw_walls_x(data, start, end, square_loc_calc, i);
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
