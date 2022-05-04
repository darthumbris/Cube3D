/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_minimap_utils.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/03 16:26:31 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/05/04 10:25:29 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

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
			if (c != WALL_COLOUR && *(uint32_t *)(map + ((i * data->mlx.minimap->width + j) * 4)) == WALL_COLOUR)
				return(false);
			*(uint32_t *)(map + ((i * data->mlx.minimap->width + j) * 4)) = c;
			j++;
		}
		i++;
	}
	return (true);
}
