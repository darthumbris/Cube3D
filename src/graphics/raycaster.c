#include "cubed.h"
#include <stdio.h>
#include <sys/time.h>

// Because the map is always surrounded by walls
// it should always hit a wall before it can go outside
// the map and overflow.
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

//TODO: would fixed point be faster?