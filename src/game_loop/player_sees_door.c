/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player_sees_door.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/18 14:48:11 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/18 14:56:42 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

bool	is_player_facing_door(t_data *data, int x, int y)
{
	const double	angle = get_angle_of_attack((t_vector_double) \
		{x, y}, data->cam.pos, data->cam.dir);

	return (angle < 0.4 || (2 * M_PI - angle) < 0.4);
}
