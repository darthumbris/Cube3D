/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/19 17:37:19 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/06/24 12:12:23 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static void	set_start_draw_variables(t_data *data)
{
	data->floor.ray_dir0.x = data->cam.dir.x - data->cam.plane.x;
	data->floor.ray_dir0.y = data->cam.dir.y - data->cam.plane.y;
	data->floor.ray_dir1.x = data->cam.dir.x + data->cam.plane.x;
	data->floor.ray_dir1.y = data->cam.dir.y + data->cam.plane.y;
}

void	check_door_hit(t_data *data)
{
	t_vector_double			wall;
	const t_vector_double	pos = data->cam.pos;

	if (!is_door_tile(data->level.map_planes[(int)pos.y][(int)pos.x][0]))
		return ;
	if (data->caster.side == 0)
	{
		wall.x = data->caster.map_pos.x + (data->caster.ray_dir.x < 0);
		wall.y = pos.y + data->caster.perp_wall_dist * data->caster.ray_dir.y;
	}
	else
	{
		wall.x = pos.x + data->caster.perp_wall_dist * data->caster.ray_dir.x;
		wall.y = data->caster.map_pos.y + (data->caster.ray_dir.y < 0);
	}
	if (wall.x >= (int)pos.x && wall.x <= (int)pos.x + 1 && \
		wall.y >= (int)pos.y && wall.y <= (int)pos.y + 1)
	{
		data->caster.door = get_door_struct
			(data, (t_vector_int){(int)pos.x, (int)pos.y});
		data->caster.door_hit = 1;
	}
}

void	set_texture_pos(t_data *data, mlx_texture_t *tex, t_raycaster *ray)
{
	if (ray->side == 0)
		ray->wall_x = data->cam.pos.y + ray->perp_wall_dist * ray->ray_dir.y;
	else
		ray->wall_x = data->cam.pos.x + ray->perp_wall_dist * ray->ray_dir.x;
	if (ray->door_hit == 2)
		ray->wall_x += ray->door->s_timer;
	ray->wall_x -= floor(ray->wall_x);
	if ((ray->door_hit == 2 && ray->door->direction == EAST_WEST && \
		ray->ray_dir.x < 0) || (ray->door_hit == 2 && ray->door->direction == \
		NORTH_SOUTH && ray->ray_dir.y > 0))
		ray->wall_x = 1.0 - ray->wall_x;
	ray->tex.x = (int)(ray->wall_x * (double)tex->width);
	if (ray->side == 0 && ray->ray_dir.x < 0)
		ray->tex.x = tex->width - ray->tex.x - 1;
	if (ray->side == 1 && ray->ray_dir.y > 0)
		ray->tex.x = tex->width - ray->tex.x - 1;
	ray->step_y = 0.5 * tex->height * ray->inv_line_height;
	ray->tex_pos = (ray->draw_start - \
		data->floor.halve_height + ray->halve_line_height) * \
		ray->step_y;
}

static void	extra_drawing(t_data *data, int x)
{
	if (data->floor_ceiling)
		draw_floor_ceiling(data, x);
	else
		draw_transparency(data, x);
	data->spr_cast.zbuffer[x] = data->caster.perp_wall_dist;
}

void	raycaster(t_data *data)
{
	int				x;
	mlx_texture_t	*texture;

	x = 0;
	set_start_draw_variables(data);
	while (x < data->mlx.mlx_handle->width)
	{
		set_caster_variables(data, x);
		set_step_direction(data, &data->caster);
		check_wall_collision(data, &data->caster, &data->caster.map_pos);
		calculate_perpendicular_wall_distance(data, &data->caster);
		check_door_hit(data);
		texture = get_texture(data, data->caster.map_pos);
		set_texture_pos(data, texture, &data->caster);
		draw_walls(data, x, texture);
		extra_drawing(data, x);
		x++;
	}
}
