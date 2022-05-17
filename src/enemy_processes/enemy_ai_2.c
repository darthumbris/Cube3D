/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   enemy_ai_2.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/17 14:15:04 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/17 14:24:15 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	sound_alerts_enemies(t_data *data)
{
	t_sprite_lst	*lst;

	lst = data->sprite_lst;
	while (lst)
	{
		if (is_enemy_kind(lst->sprite_data.kind) && \
			lst->sprite_data.en_dat.player_detected == false && \
			sprite_dist(lst->sprite_data.map_pos, data->cam.pos) < \
			ENEMY_HEARING_DIST)
		{
			if (DEBUG_MODE)
				printf("enemy heard a sound now tracking player\n");
			track_player(data, &lst->sprite_data);
		}
		lst = lst->next;
	}
}
