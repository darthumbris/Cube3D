/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_weapons.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/10 09:26:45 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/10 14:27:09 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	init_weapons(t_data *data)
{
	data->mlx.weapon = mlx_new_image
		(data->mlx.mlx_handle, SCREEN_WIDTH, SCREEN_HEIGHT);
	data->mlx.weapon_anim[PISTOL].tex0 = mlx_load_png("assets/weapons/pistol0.png");
	data->mlx.weapon_anim[PISTOL].tex1 = mlx_load_png("assets/weapons/pistol1.png");
	data->mlx.weapon_anim[PISTOL].tex2 = mlx_load_png("assets/weapons/pistol2.png");
	data->mlx.weapon_anim[PISTOL].tex3 = mlx_load_png("assets/weapons/pistol3.png");
	data->mlx.weapon_anim[KNIFE].tex0 = mlx_load_png("assets/weapons/knife0.png");
	data->mlx.weapon_anim[KNIFE].tex1 = mlx_load_png("assets/weapons/knife1.png");
	data->mlx.weapon_anim[KNIFE].tex2 = mlx_load_png("assets/weapons/knife2.png");
	data->mlx.weapon_anim[KNIFE].tex3 = mlx_load_png("assets/weapons/knife3.png");
	data->mlx.weapon_anim[MACHINEGUN].tex0 = mlx_load_png("assets/weapons/machinegun0.png");
	data->mlx.weapon_anim[MACHINEGUN].tex1 = mlx_load_png("assets/weapons/machinegun1.png");
	data->mlx.weapon_anim[MACHINEGUN].tex2 = mlx_load_png("assets/weapons/machinegun2.png");
	data->mlx.weapon_anim[MACHINEGUN].tex3 = mlx_load_png("assets/weapons/machinegun3.png");
	data->mlx.weapon_anim[PISTOL].frame = 0;
	data->mlx.weapon_anim[PISTOL].animate = false;
	data->mlx.weapon_anim[KNIFE].frame = 0;
	data->mlx.weapon_anim[KNIFE].animate = false;
	data->mlx.weapon_anim[MACHINEGUN].frame = 0;
	data->mlx.weapon_anim[MACHINEGUN].animate = false;
}

void	draw_weapons(t_data *data, mlx_texture_t *gun)
{
	t_vector_int	pos;
	t_vector_int	tex;
	uint8_t			*pixs[2];
	const int		pos_x = (SCREEN_WIDTH / 2) - (gun->width * 2) - 1;

	pos.x = -1;
	pixs[0] = gun->pixels;
	while (++pos.x < (int)gun->width * data->hud.scale)
	{
		tex.x = pos.x * data->hud.inv_scale;
		pos.y = gun->height * data->hud.scale;
		pixs[1] = data->mlx.weapon->pixels + ((pos.x + pos_x) * 4) + \
		((data->mlx.weapon->height - 113) * data->mlx.weapon->width * 4);
		while (--pos.y > 0)
		{
			tex.y = pos.y * data->hud.inv_scale;
			data->color = (*(int *)(pixs[0] + \
				((tex.y * gun->width + tex.x) * 4)));
			if (data->color)
				*(uint32_t *)pixs[1] = data->color;
			pixs[1] -= data->mlx.weapon->width * 4;
		}
	}
}

void	animate_weapon(t_data *data)
{
	int	active;

	active = data->player.active_weapon;
	if (data->mlx.weapon_anim[active].frame == 2)
		draw_weapons(data, data->mlx.weapon_anim[active].tex1);
	else if (data->mlx.weapon_anim[active].frame == 4)
		draw_weapons(data, data->mlx.weapon_anim[active].tex2);
	else if (data->mlx.weapon_anim[active].frame == 6)
		draw_weapons(data, data->mlx.weapon_anim[active].tex3);
	else if (data->mlx.weapon_anim[active].frame > 8)
	{
		data->mlx.weapon_anim[active].animate = false;
		data->mlx.weapon_anim[active].frame = 0;
		if (data->player.ammo == 0)
		{
			data->player.active_weapon = KNIFE;
			active = KNIFE;
		}
		draw_weapons(data, data->mlx.weapon_anim[active].tex0);
	}
	data->mlx.weapon_anim[active].frame++;
}
