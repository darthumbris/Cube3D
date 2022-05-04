/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_minimap.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/29 13:55:37 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/05/04 15:19:39 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static bool	x_conditions(t_data *data, t_vector_int start)
{
	return (!(start.x < 0 || \
		start.y < 0 || \
		start.x >= data->level.map_w || \
		start.y >= data->level.map_h) && \
		is_wall_tile(data->level.map[start.y][start.x]));
}

static void	draw_walls_x(t_data *data, \
t_vector_int *se, t_vector_double square, int i)
{
	int	j;

	j = 0;
	while (se[0].x < se[1].x)
	{
		if (x_conditions(data, se[0]))
		{
			draw_square(data, (t_vector_int) \
			{.y = (int)(square.y * i), .x = (int)(square.x * j)}, \
			(t_vector_int){.y = 120 / data->mlx.minimap_zoom + 1, \
				.x = 120 / data->mlx.minimap_zoom + 1}, WALL_COLOUR);
		}	
		se[0].x++;
		j++;
	}
}

static void	set_start_end(t_data *data, t_vector_int *start, t_vector_int *end)
{
	start->y = (int)(data->cam.pos.y - \
				roundf(data->mlx.minimap_zoom * data->mlx.minimap_scale));
	start->x = (int)(data->cam.pos.x - data->mlx.minimap_zoom);
	end->y = (int)(data->cam.pos.y + \
		roundf(data->mlx.minimap_zoom * data->mlx.minimap_scale));
	end->x = (int)(data->cam.pos.x + data->mlx.minimap_zoom);
}

//TODO: map is very jumpy when changing zoom and player doesnt collide well on some zoom levels
static void	draw_minimap_walls(t_data *data)
{	
	int						i;
	int						j;
	t_vector_int			start_end[2];
	const t_vector_double	square_loc_calc = \
	{.x = data->mlx.minimap->width / (data->mlx.minimap_zoom * 2), \
	.y = data->mlx.minimap->height / ((data->mlx.minimap_zoom * 2) * \
	data->mlx.minimap_scale)};

	set_start_end(data, &(start_end[0]), &(start_end[1]));
	i = 0;
	while (start_end[0].y < start_end[1].y)
	{
		j = 0;
		draw_walls_x(data, start_end, square_loc_calc, i);
		i++;
		start_end[0].x = (int)(data->cam.pos.x - data->mlx.minimap_zoom);
		start_end[0].y++;
	}
}

//TODO: doors, hidden rooms
void	draw_minimap(t_data *data)
{
	int					i;
	bool				temp;
	const t_vector_int	wh = {.y = data->mlx.minimap->height \
		/ 2, .x = data->mlx.minimap->width / 2};

	i = -1;
	ft_memset(data->mlx.minimap->pixels, 0, data->mlx.minimap->width \
		* data->mlx.minimap->height * sizeof(int));
	draw_minimap_walls(data);
	temp = true;
	while (++i < 5 * data->mlx.hud_scale && temp)
		temp = draw_square(data, (t_vector_int) \
		{.y = wh.y + (i * data->cam.dir.y), .x = wh.x + (i * data->cam.dir.x)}, \
		(t_vector_int){.y = data->mlx.hud_scale, .x = data->mlx.hud_scale}, \
		VIEW_LINE_COLOUR);

	draw_square(data, wh, (t_vector_int) \
		{.y = data->mlx.hud_scale, .x = data->mlx.hud_scale}, 0xFF000000);
}
