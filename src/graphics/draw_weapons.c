/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_weapons.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/10 09:26:45 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/15 14:32:51 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static void	init_weapon_anim(t_data *data)
{
	data->mlx.weapon_anim[PISTOL].tex0 = data->mlx.tex.wpn[PISTOL0_T];
	data->mlx.weapon_anim[PISTOL].tex1 = data->mlx.tex.wpn[PISTOL1_T];
	data->mlx.weapon_anim[PISTOL].tex2 = data->mlx.tex.wpn[PISTOL2_T];
	data->mlx.weapon_anim[PISTOL].tex3 = data->mlx.tex.wpn[PISTOL3_T];
	data->mlx.weapon_anim[KNIFE].tex0 = data->mlx.tex.wpn[KNIFE0_T];
	data->mlx.weapon_anim[KNIFE].tex1 = data->mlx.tex.wpn[KNIFE1_T];
	data->mlx.weapon_anim[KNIFE].tex2 = data->mlx.tex.wpn[KNIFE2_T];
	data->mlx.weapon_anim[KNIFE].tex3 = data->mlx.tex.wpn[KNIFE3_T];
	data->mlx.weapon_anim[MACHINEGUN].tex0 = data->mlx.tex.wpn[MACHINEGUN0_T];
	data->mlx.weapon_anim[MACHINEGUN].tex1 = data->mlx.tex.wpn[MACHINEGUN1_T];
	data->mlx.weapon_anim[MACHINEGUN].tex2 = data->mlx.tex.wpn[MACHINEGUN2_T];
	data->mlx.weapon_anim[MACHINEGUN].tex3 = data->mlx.tex.wpn[MACHINEGUN3_T];
}

void	init_weapons(t_data *data)
{
	data->mlx.weapon = mlx_new_image
		(data->mlx.mlx_handle, SCREEN_WIDTH, SCREEN_HEIGHT);
	init_weapon_anim(data);
	data->mlx.weapon_anim[PISTOL].frame = 0;
	data->mlx.weapon_anim[PISTOL].animate = false;
	data->mlx.weapon_anim[KNIFE].frame = 0;
	data->mlx.weapon_anim[KNIFE].animate = false;
	data->mlx.weapon_anim[MACHINEGUN].frame = 0;
	data->mlx.weapon_anim[MACHINEGUN].animate = false;
}

void	draw_weapons(t_data *data, mlx_texture_t *gun, mlx_image_t *weapon)
{
	t_vector_int	pos;
	t_vector_int	tex;
	uint8_t			*pixs[2];
	const int		pos_x = (SCREEN_WIDTH / 2) - \
						(gun->width * data->hud.scale / 2) - 1;
	const int		max = (int)((gun->width - 24) * data->hud.scale);

	pos.x = (int)(22 * data->hud.scale);
	pixs[0] = gun->pixels;
	while (++pos.x < max)
	{
		tex.x = pos.x * data->hud.inv_scale;
		pos.y = (int)(gun->height * data->hud.scale);
		pixs[1] = weapon->pixels + ((pos.x + pos_x) * 4) + ((weapon->height \
		- gun->height) * weapon->width * 4);
		while (--pos.y > (int)(8 * data->hud.scale))
		{
			tex.y = pos.y * data->hud.inv_scale;
			data->color = (*(int *)(pixs[0] + \
				((tex.y * gun->width + tex.x) * 4)));
			if (data->color)
				*(uint32_t *)pixs[1] = data->color;
			pixs[1] -= weapon->width * 4;
		}
	}
}

void	animate_weapon(t_data *data)
{
	int	activ;

	activ = data->player.active_weapon;
	if (data->mlx.weapon_anim[activ].frame == 2)
		draw_weapons(data, data->mlx.weapon_anim[activ].tex1, data->mlx.weapon);
	else if (data->mlx.weapon_anim[activ].frame == 4)
		draw_weapons(data, data->mlx.weapon_anim[activ].tex2, data->mlx.weapon);
	else if (data->mlx.weapon_anim[activ].frame == 6)
		draw_weapons(data, data->mlx.weapon_anim[activ].tex3, data->mlx.weapon);
	else if (data->mlx.weapon_anim[activ].frame > 8)
	{
		data->mlx.weapon_anim[activ].animate = false;
		data->mlx.weapon_anim[activ].frame = 0;
		if (data->player.ammo == 0)
		{
			data->player.active_weapon = KNIFE;
			activ = KNIFE;
		}
		draw_weapons(data, data->mlx.weapon_anim[activ].tex0, data->mlx.weapon);
	}
	data->mlx.weapon_anim[activ].frame++;
}
