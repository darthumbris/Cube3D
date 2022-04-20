/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/19 17:37:19 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/04/20 16:47:56 by shoogenb      ########   odam.nl         */
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
}

void	raycaster(t_data *data)
{
	int				x;

	x = 0;
	set_start_draw_variables(data);
	while (x < data->mlx.mlx_handle->width)
	{
		set_caster_variables(data, x);
		set_step_direction(data);
		while (!data->caster.hit)
			check_wall_collision(data);
		calculate_perpendicular_wall_distance(data);
		set_draw_values(data);
		draw_walls(data);
		draw_transparency(data, x);
		x++;
	}
}
