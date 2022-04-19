/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/19 17:37:19 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/04/19 17:37:24 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"
#include <stdio.h>
#include <sys/time.h>

void	raycaster(t_data *data)
{
	int				x;

	x = 0;
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
}
