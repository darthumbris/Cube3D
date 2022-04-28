/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_transparency.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/25 11:19:52 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/04/28 14:16:49 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	draw_transparency(t_data *data, int x)
{
	int			y;
	uint8_t		*fg;
	int			xfour;

	y = 0;
	xfour = x * 4;
	fg = data->mlx.fg->pixels + (y * data->floor.width4 + xfour);
	while (y < data->caster.draw_start)
	{
		*(unsigned int *)fg = 0;
		fg += data->floor.width4;
		y++;
	}
	y = data->caster.draw_end;
	fg = data->mlx.fg->pixels + (y * data->floor.width4 + xfour);
	while (y < data->mlx.mlx_handle->height)
	{
		*(unsigned int *)fg = 0;
		fg += data->floor.width4;
		y++;
	}
}
