/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/19 17:37:16 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/05/09 11:48:12 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static void	set_direction(t_raycaster *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir.x < 0)
			ray->dir = WEST;
		else
			ray->dir = EAST;
	}
	else
	{
		if (ray->ray_dir.y < 0)
			ray->dir = NORTH;
		else
			ray->dir = SOUTH;
	}
}

void	check_wall_collision(t_data *data, t_raycaster *ray, \
		t_vector_double *map)
{
	while (!ray->hit)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			map->x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			map->y += ray->step.y;
			ray->side = 1;
		}
		set_direction(ray);
		if (is_wall_kind_tile(data->level.map[(int)map->y][(int)map->x]))
		{
			ray->hit = true;
			ray->door_hit = 0;
			ray->secret_hit = 0;
			if (is_door_tile(data->level.map[(int)map->y][(int)map->x]) || \
			is_secret_tile(data->level.map[(int)map->y][(int)map->x]))
				extend_ray(data, ray);
		}
	}
}

void	set_caster_variables(t_data *data, int x)
{
	data->caster.camera_x = 2 * x / (double)data->mlx.mlx_handle->width - 1;
	data->caster.ray_dir.x = data->cam.dir.x + \
		data->cam.plane.x * data->caster.camera_x;
	data->caster.ray_dir.y = data->cam.dir.y + \
		data->cam.plane.y * data->caster.camera_x;
	data->caster.map_pos.x = (int)(data->cam.pos.x);
	data->caster.map_pos.y = (int)(data->cam.pos.y);
	data->caster.delta_dist.x = fabs(1.0 / data->caster.ray_dir.x);
	data->caster.delta_dist.y = fabs(1.0 / data->caster.ray_dir.y);
	data->caster.hit = false;
	data->floor.x4 = x * 4;
}

void	set_step_direction(t_data *data, t_raycaster *ray)
{
	const t_vector_double	pos = data->cam.pos;

	if (ray->ray_dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (pos.x - ray->map_pos.x) * ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x = (ray->map_pos.x + 1.0 - pos.x) * ray->delta_dist.x;
	}
	if (ray->ray_dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (pos.y - ray->map_pos.y) * ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y = (ray->map_pos.y + 1.0 - pos.y) * ray->delta_dist.y;
	}
}

void	calculate_perpendicular_wall_distance(t_data *data, t_raycaster *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_pos.x - \
			data->cam.pos.x + (1 - ray->step.x) / 2) / \
			ray->ray_dir.x;
	else
		ray->perp_wall_dist = (ray->map_pos.y - \
			data->cam.pos.y + (1 - ray->step.y) / 2) / \
			ray->ray_dir.y;
	ray->line_height = \
		(int)(data->mlx.mlx_handle->height / ray->perp_wall_dist);
	ray->halve_line_height = ray->line_height / 2;
	ray->inv_line_height = 1.0 / (double)ray->line_height;
	ray->draw_start = -(ray->halve_line_height) + data->floor.halve_height;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = (ray->halve_line_height) + data->floor.halve_height;
	if (ray->draw_end >= data->mlx.mlx_handle->height)
		ray->draw_end = data->mlx.mlx_handle->height - 1;
	if (ray->draw_end < 0)
		ray->draw_end = 0;
}
