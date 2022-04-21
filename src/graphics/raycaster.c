/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/19 17:37:19 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/04/21 16:00:46 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"
#include <stdio.h>
#include <sys/time.h>

static void	set_start_draw_variables(t_data *data)
{
	data->floor.ray_dir0.x = data->cam.dir.x - data->cam.plane.x;
	data->floor.ray_dir0.y = data->cam.dir.y - data->cam.plane.y;
	data->floor.ray_dir1.x = data->cam.dir.x + data->cam.plane.x;
	data->floor.ray_dir1.y = data->cam.dir.y + data->cam.plane.y;
	data->floor.pos_z = 0.5 * data->mlx.mlx_handle->height;
}

void	raycaster(t_data *data)
{
	int				x;

	x = 0;
	set_start_draw_variables(data);
	draw_background(data);
	while (x < data->mlx.mlx_handle->width)
	{
		set_caster_variables(data, x);
		set_step_direction(data);
		while (!data->caster.hit)
			check_wall_collision(data);
		calculate_perpendicular_wall_distance(data);
		set_draw_values(data);
		draw_transparency(data, x);
		draw_walls(data, x);
		x++;
	}
	//mlx_image_to_window(data->mlx.mlx_handle, data->mlx.fg, 0, 0);
}
