/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 16:42:05 by obouykou          #+#    #+#             */
/*   Updated: 2020/10/15 10:43:48 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		max_hlen(char **tab)
{
	int l;
	int i;
	int max;

	i = -1;
	max = 0;
	while (tab[++i])
		if (max < (l = len_if(tab[i], 0)))
			max = l;
	return (max);
}

int		reverse_map(t_map *map)
{
	int		i;
	int		j;
	char	buff[map->form.y][map->form.x];

	i = -1;
	while (++i < map->form.y)
	{
		ft_memset(buff[i], ' ', map->form.x);
		buff[i][map->form.x] = 0;
	}
	j = -1;
	while (++j < map->form.y)
	{
		i = -1;
		while (++i < map->form.x)
			if (j < len_if(map->map[i], 0))
				buff[j][i] = map->map[i][j];
	}
	j = -1;
	map->step = 1;
	while (++j < map->form.y)
		if (check_map_hline(NULL, buff[j], map, 0))
			return (1);
	return (0);
}

int		verify_map(t_map *map, t_cub *cub)
{
	int i;

	if (!(map->map = ft_split(map->tmp_map, '\v')))
	{
		free(map->tmp_map);
		return (1);
	}
	free(map->tmp_map);
	if ((map->form.x = tb_len(map->map)) < 3 ||
		(map->form.y = max_hlen(map->map)) < 3 ||
		!is_set(map->map[0], "1 ") ||
		!is_set(map->map[map->form.x - 1], "1 "))
		return (1);
	i = 0;
	map->step = 0;
	while (++i < map->form.x - 1)
		if (check_map_hline(cub, map->map[i], map, i))
			return (1);
		else if (map->dir_count == 1 && !map->in_pos.x)
			map->in_pos.x = (double)i;
	if (reverse_map(map))
		return (1);
	return (map->dir_count != 1);
}

int		verify_eof(int fd, char *line, t_cub *cub)
{
	int r;

	if (is_set(line, " ") && !close(fd))
	{
		free(line);
		free_cub_exit(cub, MAP_ERROR);
	}
	r = 1;
	while (r > 0)
	{
		if ((r = get_next_line(fd, &line)) == -1 && !close(fd))
			free_cub_exit(cub, GNL_ERROR);
		if (line && *line)
		{
			close(fd);
			free(line);
			free_cub_exit(cub, MAP_ERROR);
		}
		free(line);
	}
	return (r != 0 ? 1 : 0);
}

void	get_verify_map(int fd, char *line, t_map *map, t_cub *cub)
{
	int		r;
	char	*tmp;

	r = 1;
	map->tmp_map = line;
	while (r > 0)
	{
		if ((r = get_next_line(fd, &line)) == -1 && !close(fd))
		{
			free(line);
			free_cub_exit(cub, GNL_ERROR);
		}
		if (line && (!*line || is_set(line, " ")) && verify_eof(fd, line, cub)
			&& !close(fd))
			break ;
		tmp = ft_strjoin(map->tmp_map, "\v");
		free(map->tmp_map);
		map->tmp_map = ft_strjoin(tmp, line);
		free(tmp);
		free(line);
	}
	if (verify_map(map, cub))
		free_cub_exit(cub, MAP_ERROR);
}
