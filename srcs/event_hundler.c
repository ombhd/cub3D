/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_hundler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 11:04:40 by obouykou          #+#    #+#             */
/*   Updated: 2020/10/15 11:19:34 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		key_pressed(int key, t_cub *cub)
{
	if (key == KEY_UP)
		cub->key.u = 1;
	if (key == KEY_DOWN)
		cub->key.d = 1;
	if (key == KEY_RIGHT)
		cub->key.r = 1;
	if (key == KEY_LEFT)
		cub->key.l = 1;
	if (key == ROT_R)
		cub->key.rot_r = 1;
	if (key == ROT_L)
		cub->key.rot_l = 1;
	if (key == EXIT_KEY)
		free_cub_exit(cub, END_GAME);
	return (0);
}

int		key_release(int key, t_keys *keys)
{
	if (key == KEY_UP)
		keys->u = 0;
	if (key == KEY_DOWN)
		keys->d = 0;
	if (key == KEY_RIGHT)
		keys->r = 0;
	if (key == KEY_LEFT)
		keys->l = 0;
	if (key == ROT_R)
		keys->rot_r = 0;
	if (key == ROT_L)
		keys->rot_l = 0;
	return (0);
}

int		close_window(t_cub *cub)
{
	free_cub_exit(cub, END_GAME);
	return (0);
}
