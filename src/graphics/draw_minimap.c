/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_minimap.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/29 13:55:37 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/05/12 16:52:48 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static bool	x_conditions(t_data *data, t_vector_int start)
{
	return (!(start.x < 0 || \
		start.y < 0 || \
		start.x >= data->level.map_w || \
		start.y >= data->level.map_h) && \
		data->level.wall_map[start.y][start.x] == 1);
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
		(t_vector_int){.y = (SCREEN_WIDTH / 10 + 2) / data->mlx.minimap_zoom, \
		.x = (SCREEN_WIDTH / 10) / data->mlx.minimap_zoom}, WALL_COLOUR);
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

//TODO: map is very jumpy when changing zoom and player doesnt collide 
//well on some zoom levels
static void	draw_minimap_walls(t_data *data)
{	
	int						i;
	t_vector_int			start_end[2];
	const t_vector_double	square_loc_calc = \
	{.x = data->mlx.minimap->width / (data->mlx.minimap_zoom * 2), \
	.y = data->mlx.minimap->height / ((data->mlx.minimap_zoom * 2) * \
	data->mlx.minimap_scale)};

	i = 0;
	set_start_end(data, &(start_end[0]), &(start_end[1]));
	while (start_end[0].y < start_end[1].y)
	{
		draw_walls_x(data, start_end, square_loc_calc, i);
		start_end[0].x = (int)(data->cam.pos.x - data->mlx.minimap_zoom);
		start_end[0].y++;
		i++;
	}
}

//draws the minimap
void	draw_minimap(t_data *data)
{
	int					i;
	bool				temp;
	const int			s_dim = data->mlx.minimap_zoom * data->mlx.hud_scale;
	const t_vector_int	wh = {.y = data->mlx.minimap->height \
		/ 2, .x = data->mlx.minimap->width / 2};

	i = -1;

	//TODO: this really should not be run every frame
	wall_detection(data);

	ft_memset(data->mlx.minimap->pixels, 0, data->mlx.minimap->width \
		* data->mlx.minimap->height * sizeof(int));
	draw_minimap_walls(data);
	temp = true;
	while (++i < 10 && temp)
		temp = draw_square(data, (t_vector_int) \
		{.y = wh.y + (i * data->cam.dir.y) + s_dim / 2, \
		.x = wh.x + (i * data->cam.dir.x) + s_dim / 2}, \
		(t_vector_int){.y = s_dim / 2 + 1, .x = s_dim / 2 + 1}, \
		VIEW_LINE_COLOUR);
	draw_square(data, wh, (t_vector_int){.y = s_dim + 1, .x = s_dim + 1}, \
	0xFF000000);
}
