/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_minimap_utils.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/03 16:26:31 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/05/12 15:03:06 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

//norm function
void	wall_detection(t_data *data)
{
	clean_wall_map(data);
	check_for_walls(data, (t_vector_int) \
	{.x = (int)data->cam.pos.x, .y = (int)data->cam.pos.y});
	fill_corners(data);
}

//draws squares on minimap image
bool	draw_square(t_data *data, t_vector_int rec, \
t_vector_int wh, unsigned int c)
{
	uint8_t	*map;
	int		i;
	int		j;

	i = rec.y;
	map = data->mlx.minimap->pixels;
	if (i < 0)
		i = 0;
	while (i < rec.y + wh.y && i < (int)data->mlx.minimap->height)
	{
		j = rec.x;
		while (j < rec.x + wh.x && j < (int)data->mlx.minimap->width)
		{
			if (c == VIEW_LINE_COLOUR && *(uint32_t *) \
			(map + ((i * data->mlx.minimap->width + j) * 4)) == WALL_COLOUR)
				return (false);
			*(uint32_t *)(map + ((i * data->mlx.minimap->width + j) * 4)) = c;
			j++;
		}
		i++;
	}
	return (true);
}
