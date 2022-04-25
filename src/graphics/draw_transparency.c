/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_transparency.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/25 11:19:52 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/04/25 11:20:18 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	draw_transparency(t_data *data, int x)
{
	int			y;
	uint8_t		*fg;

	y = 0;
	fg = data->mlx.fg->pixels + ((y * data->mlx.fg->width + x) * 4);
	while (y < data->caster.draw_start)
	{
		*(unsigned int *)fg = 0;
		fg += data->mlx.mlx_handle->width * 4;
		y++;
	}
	y = data->caster.draw_end + 1;
	fg = data->mlx.fg->pixels + ((y * data->mlx.fg->width + x) * 4);
	while (y < data->mlx.mlx_handle->height)
	{
		*(unsigned int *)fg = 0;
		fg += data->mlx.mlx_handle->width * 4;
		y++;
	}
}
