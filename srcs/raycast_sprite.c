/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_sprite.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 17:01:02 by obouykou          #+#    #+#             */
/*   Updated: 2020/10/15 09:51:14 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	r_sp_calc(t_cub *cub, int i, t_sprite *sp, t_control *ct)
{
	sp->x = sp->pos[sp->sp_ord[i]].x - ct->pos.x;
	sp->y = sp->pos[sp->sp_ord[i]].y - ct->pos.y;
	sp->inv_d = 1.0 / (ct->plane.x * ct->dir.y - ct->dir.x * ct->plane.y);
	sp->tr_form.x = sp->inv_d * (ct->dir.y * sp->x - ct->dir.x * sp->y);
	sp->tr_form.y = sp->inv_d * (-ct->plane.y * sp->x + ct->plane.x * sp->y);
	sp->sc_x = (int)((cub->rsl.x / 2) * (1 + sp->tr_form.x / sp->tr_form.y));
	sp->h = abs((int)(cub->rsl.y / sp->tr_form.y));
	sp->draw_y.a = -sp->h / 2 + cub->rsl.y / 2;
	if (sp->draw_y.a < 0)
		sp->draw_y.a = 0;
	sp->draw_y.b = sp->h / 2 + cub->rsl.y / 2;
	if (sp->draw_y.b >= cub->rsl.y)
		sp->draw_y.b = cub->rsl.y - 1;
	sp->w = abs((int)(cub->rsl.y / sp->tr_form.y));
	sp->draw_x.a = -sp->w / 2 + sp->sc_x;
	if (sp->draw_x.a < 0)
		sp->draw_x.a = 0;
	sp->draw_x.b = sp->w / 2 + sp->sc_x;
	if (sp->draw_x.b >= cub->rsl.x)
		sp->draw_x.b = cub->rsl.x - 1;
}

void	fill_if(t_cub *cub, t_sprite *sp)
{
	int j;
	int d;
	int clr;

	sp->seg = sp->draw_x.a - 1;
	while (++sp->seg < sp->draw_x.b)
	{
		sp->tex.dir.x = (int)((256 * (sp->seg - (-sp->w / 2 + sp->sc_x)) *
								sp->tex.w / sp->w) / 256);
		if (sp->tr_form.y > 0 && sp->seg > 0 && sp->seg < cub->rsl.x &&
			sp->tr_form.y < cub->zbuff[sp->seg])
		{
			j = sp->draw_y.a - 1;
			while (++j < sp->draw_y.b)
			{
				d = j * 256 - cub->rsl.y * 128 + sp->h * 128;
				sp->tex.dir.y = ((d * sp->tex.h) / sp->h) / 256;
				clr = sp->tex.data[(sp->tex.w * sp->tex.dir.y) + sp->tex.dir.x];
				if (clr != 0x980088)
					cub->img.buff[j * cub->rsl.x + sp->seg] = clr;
			}
		}
	}
}

void	sort_sprites(int *order, double *sp_dist, int size)
{
	int		i;
	double	tmp;
	int		t_o;
	int		is_sorted;

	is_sorted = 0;
	while (!is_sorted)
	{
		i = 0;
		is_sorted = 1;
		while (i < size - 1)
		{
			if (sp_dist[i] < sp_dist[i + 1])
			{
				is_sorted = 0;
				t_o = order[i];
				order[i] = order[i + 1];
				order[i + 1] = t_o;
				tmp = sp_dist[i];
				sp_dist[i] = sp_dist[i + 1];
				sp_dist[i + 1] = tmp;
			}
			i++;
		}
	}
}

void	raycast_sprite(t_cub *cub)
{
	int			i;
	t_control	*ct;
	t_sprite	*sp;

	sp = &cub->sprite;
	ct = &cub->ctrl;
	i = -1;
	while (++i < sp->count)
	{
		sp->sp_ord[i] = i;
		sp->sp_dist[i] = pow(ct->pos.x - sp->pos[i].x, 2) +
							pow(ct->pos.y - sp->pos[i].y, 2);
	}
	sort_sprites(sp->sp_ord, sp->sp_dist, sp->count);
	i = -1;
	while (++i < sp->count)
	{
		r_sp_calc(cub, i, sp, ct);
		fill_if(cub, sp);
	}
}
