/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_minimap.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/29 13:55:37 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/05/03 12:19:37 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

	// bool	is_walkable(char c)
	// {
	// 	if (is_sprite_tile(c))
	// 		return (is_nonblocking_kind(get_sprite_kind(c)));
	// 	return (is_empty_tile(c) || c == 'D');
	// }

void	draw_square(t_data *data, t_vector_int rec, \
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
		while (j < rec.x + wh.x)
		{
			*(uint32_t *)(map + ((i * data->mlx.minimap->width + j) * 4)) = c;
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_data *data)
{
	int							i;
	const t_vector_int			wh = {.y = data->mlx.minimap->height \
		/ 2, .x = data->mlx.minimap->width / 2};
	//const t_vector_double		playerpos = data->cam.pos;

	i = -1;
	ft_memset(data->mlx.minimap->pixels, 255, data->mlx.minimap->width \
		* data->mlx.minimap->height * sizeof(int));
	while (++i < 5 * data->mlx.hud_scale)
		draw_square(data, (t_vector_int){.y = wh.y + (i * data->cam.dir.y), \
.x = wh.x + (i * data->cam.dir.x)}, (t_vector_int){.y = data->mlx.hud_scale, \
	.x = data->mlx.hud_scale}, 0xD7FFFFFF);
	draw_square(data, wh, (t_vector_int) \
	{.y = data->mlx.hud_scale, .x = data->mlx.hud_scale}, 0x000000FF);
}
