/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_highest_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 10:44:28 by obouykou          #+#    #+#             */
/*   Updated: 2020/10/15 12:45:05 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		is_dir(char c)
{
	return (c == 'N' || c == 'E' || c == 'S' || c == 'W');
}

int		find_dir_sp(t_cub *cub, char *line, t_map *map, int x)
{
	int i;

	i = len_if(line, 0);
	while (i--)
	{
		if (is_dir(line[i]))
		{
			map->orient = line[i];
			map->in_pos.y = (double)i;
			map->dir_count++;
		}
		else if (line[i] == '2')
		{
			cub->sprite.pos[cub->sprite.count].x = (double)x + 0.5;
			cub->sprite.pos[cub->sprite.count].y = (double)i + 0.5;
			cub->sprite.count++;
		}
	}
	return (map->dir_count > 1);
}

int		check_map_hline(t_cub *cub, char *line, t_map *map, int x)
{
	int		i;
	char	**table;

	if (!map->step && !is_set(line, "012 NESW"))
		return (1);
	table = ft_split(line, ' ');
	i = -1;
	while (table[++i])
		if (table[i][0] != '1' || table[i][len_if(table[i], 0) - 1] != '1')
		{
			free_str_table(table, tb_len(table));
			return (1);
		}
	free_str_table(table, tb_len(table));
	return (map->step == 1 ? 0 : find_dir_sp(cub, line, map, x));
}
