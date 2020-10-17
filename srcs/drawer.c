/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 13:00:13 by obouykou          #+#    #+#             */
/*   Updated: 2020/10/17 19:09:13 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_bzero(void *b, size_t len)
{
	size_t			i;
	unsigned char	*tmp;

	tmp = (unsigned char*)b;
	i = 0;
	while (i < len)
		tmp[i++] = 0;
}

void	get_tex(t_cub *cub)
{
	int *n;

	n = &cub->texnum;
	if (cub->ctrl.side_dir == 1 && cub->ctrl.ray.y < 0)
		*n = 3;
	if (cub->ctrl.side_dir == 0 && cub->ctrl.ray.x > 0)
		*n = 1;
	if (cub->ctrl.side_dir == 1 && cub->ctrl.ray.y > 0)
		*n = 2;
	if (cub->ctrl.side_dir == 0 && cub->ctrl.ray.x < 0)
		*n = 0;
	cub->tex[*n].dir.x = (int)(cub->wall.x * (double)cub->tex[*n].w);
	if (*n == 3)
		cub->tex[*n].dir.x = cub->tex[*n].w - cub->tex[*n].dir.x - 1;
	if (*n == 1)
		cub->tex[*n].dir.x = cub->tex[*n].w - cub->tex[*n].dir.x - 1;
	if (*n == 2)
		cub->tex[*n].dir.x = cub->tex[*n].w - cub->tex[*n].dir.x - 1;
	if (*n == 0)
		cub->tex[*n].dir.x = cub->tex[*n].w - cub->tex[*n].dir.x - 1;
}

void	fill_buff(t_cub *cub, int x)
{
	int		y;
	int		clr;
	int		num;
	t_tex	*tex;

	y = -1;
	tex = cub->tex;
	num = cub->texnum;
	while (++y < cub->line.lpix)
		cub->img.buff[y * cub->rsl.x + x] = cub->ceil.a;
	while (y < cub->line.hpix)
	{
		tex[num].dir.y = (int)tex[num].pos & (tex[num].h - 1);
		tex[num].pos += tex[num].step;
		clr = tex[num].data[tex[num].h * tex[num].dir.y + tex[num].dir.x];
		cub->img.buff[y * cub->rsl.x + x] = clr;
		y++;
	}
	y--;
	while (++y < cub->rsl.y)
		cub->img.buff[y * cub->rsl.x + x] = cub->floor.a;
	cub->zbuff[x] = cub->ctrl.wall_d;
}

void	line_calcs(t_cub *cub, int x)
{
	if (cub->ctrl.side_dir == 0)
		cub->ctrl.wall_d = (cub->ctrl.map.x - cub->ctrl.pos.x +
								(1 - cub->ctrl.step.x) / 2) / cub->ctrl.ray.x;
	else
		cub->ctrl.wall_d = (cub->ctrl.map.y - cub->ctrl.pos.y +
								(1 - cub->ctrl.step.y) / 2) / cub->ctrl.ray.y;
	cub->line.h = (int)(cub->rsl.y / cub->ctrl.wall_d);
	cub->line.lpix = -cub->line.h / 2 + cub->rsl.y / 2;
	cub->line.lpix = cub->line.lpix < 0 ? 0 : cub->line.lpix;
	cub->line.hpix = cub->line.h / 2 + cub->rsl.y / 2;
	if (cub->line.hpix >= cub->rsl.y)
		cub->line.hpix = cub->rsl.y - 1;
	if (!cub->ctrl.side_dir)
		cub->wall.x = cub->ctrl.pos.y + cub->ctrl.wall_d * cub->ctrl.ray.y;
	else
		cub->wall.x = cub->ctrl.pos.x + cub->ctrl.wall_d * cub->ctrl.ray.x;
	cub->wall.x -= floor(cub->wall.x);
	get_tex(cub);
	cub->tex[cub->texnum].step = 1.0 * cub->tex[cub->texnum].h / cub->line.h;
	cub->tex[cub->texnum].pos = (cub->line.lpix -
			cub->rsl.y / 2 + cub->line.h / 2) * cub->tex[cub->texnum].step;
	fill_buff(cub, x);
}

int		calc_draw(t_cub *cub)
{
	int x;

	x = 0;
	hundle_key(cub);
	while (x < cub->rsl.x)
	{
		ray_calcs(cub, x);
		step_dir(cub);
		cub->ctrl.hit = 0;
		dda(cub);
		line_calcs(cub, x);
		x++;
	}
	raycast_sprite(cub);
	if (cub->is_save == 1)
	{
		cub->is_save = 0;
		save_bmp(cub, cub->bmp.buff);
	}
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->img.ptr, 0, 0);
	ft_bzero(cub->img.buff, cub->rsl.x * cub->rsl.y * sizeof(int));
	return (0);
}
