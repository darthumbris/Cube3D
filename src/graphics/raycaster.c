#include "cubed.h"
#include <stdio.h>
#include <sys/time.h>

// Because the map is always surrounded by walls
// it should always hit a wall before it can go outside
// the map and overflow.
void	raycaster(t_data *data)
{
	int				x;
	struct timeval	timev;
	long			ms_before;
	long			ms_after;

	x = 0;
	gettimeofday(&timev, NULL);
	ms_before = timev.tv_sec * 1000 + timev.tv_usec / 1000;
	while (x < data->mlx.mlx_handle->width)
	{
		set_caster_variables(data, x);
		set_step_direction(data);
		while (!data->caster.hit)
			check_wall_collision(data);
		calculate_perpendicular_wall_distance(data);
		set_draw_values(data);
		draw_walls(data, x);
		draw_transparency(data, x);
		x++;
	}
	gettimeofday(&timev, NULL);
	ms_after = timev.tv_sec * 1000 + timev.tv_usec / 1000;
	printf("\r%ld\n", ms_after - ms_before);
}
