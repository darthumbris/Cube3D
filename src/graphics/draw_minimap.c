/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_minimap.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/29 13:55:37 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/05/11 20:55:27 by pvan-dij      ########   odam.nl         */
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

//TODO: weird line
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
		(t_vector_int){.y = (SCREEN_WIDTH / 10) / data->mlx.minimap_zoom, \
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
	int						j;
	t_vector_int			start_end[2];
	const t_vector_double	square_loc_calc = \
	{.x = data->mlx.minimap->width / (data->mlx.minimap_zoom * 2), \
	.y = data->mlx.minimap->height / ((data->mlx.minimap_zoom * 2) * \
	data->mlx.minimap_scale)};

	i = 0;
	set_start_end(data, &(start_end[0]), &(start_end[1]));
	while (start_end[0].y < start_end[1].y)
	{
		j = 0;
		draw_walls_x(data, start_end, square_loc_calc, i);
		start_end[0].x = (int)(data->cam.pos.x - data->mlx.minimap_zoom);
		start_end[0].y++;
		i++;
	}
}

void	draw_minimap(t_data *data)
{
	int					i;
	bool				temp;
	const int			s_dim = data->mlx.minimap_zoom * data->mlx.hud_scale;
	const t_vector_int	wh = {.y = data->mlx.minimap->height \
		/ 2, .x = data->mlx.minimap->width / 2};

	i = -1;
	clean_wall_map(data); //TODO: this really should not be run every frame
	check_for_walls(data, (t_vector_int){.x = (int)data->cam.pos.x, .y = (int)data->cam.pos.y});
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

bool	is_door_opening(t_data *data, int y, int x)
{
	int				i;

	i = 0;
	while (i < data->level.door_count)
	{
		if ((data->doors[i].state == OPENING || data->doors[i].state == OPEN) && data->doors[i].y == y && \
			data->doors[i].x == x)
			return (true);
		i++;
	}
	i = 0;
	while (i < data->level.secret_count)
	{
		if ((data->secrets[i].state == OPENING || data->doors[i].state == OPEN) && data->secrets[i].y == y && \
			data->secrets[i].x == x)
			return (true);
		i++;
	}
	return (false);
}
void check_for_walls(t_data *data, t_vector_int c)
{
	if (is_wall_tile(data->level.map[c.y][c.x]) || (is_door_tile(data->level.map[c.y][c.x]) && !is_door_opening(data, c.y, c.x)))
		data->level.wall_map[c.y][c.x] = true;
	else if (data->level.wall_map[c.y][c.x] == 0)
	{
		data->level.wall_map[c.y][c.x] = 2;
		if (c.y - 1 > -1)
			check_for_walls(data, (t_vector_int){.x = c.x, .y = c.y - 1});
		if (c.y + 1 < data->level.map_h)
			check_for_walls(data, (t_vector_int){.x = c.x, .y = c.y + 1});
		if (c.x - 1 > -1)
			check_for_walls(data, (t_vector_int){.x = c.x - 1, .y = c.y});
		if (c.x + 1 < data->level.map_w)
			check_for_walls(data, (t_vector_int){.x = c.x + 1, .y = c.y});
	}
	if (is_door_tile(data->level.map[c.y][c.x]) && is_door_opening(data, c.y, c.x))
		data->level.wall_map[c.y][c.x] = 2;

}

void clean_wall_map(t_data *data)
{
	int **map = data->level.wall_map;
	int i = 0;

	while (map[i])
	{
		ft_bzero(map[i], data->level.map_w + 1);
		i++;
	}

}

//if door is opened trigger a floodfill that sets which walls should be drawn, draw only those walls. creates a procedural map