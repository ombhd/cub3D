/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 22:46:10 by obouykou          #+#    #+#             */
/*   Updated: 2020/10/17 18:32:44 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	get_resolution(char *line, t_cub *cub)
{
	char **rsl;
	char *s;

	s = "0123456789 ";
	if (cub->rsl.x != -1 || cub->rsl.y != -1)
		free_cub_exit(cub, MAP_ELM_REP);
	rsl = ft_split(line + 1, ' ');
	if (!rsl || tb_len(rsl) != 2 || !is_set(rsl[0], s) || !is_set(rsl[1], s))
	{
		free_str_table(rsl, tb_len(rsl));
		free_cub_exit(cub, MAP_ERROR);
	}
	cub->rsl.x = ft_atoi(rsl[0]);
	cub->rsl.y = ft_atoi(rsl[1]);
	free_str_table(rsl, 2);
	if (cub->rsl.x > 2880 || cub->rsl.y > 1576)
	{
		cub->rsl.x = 2880;
		cub->rsl.y = 1576;
	}
}

void	get_verify_path(char *line, t_cub *cub)
{
	char *path;

	if (!(path = ft_strtrim(line + 2, " ")))
		free_cub_exit(cub, EXEC_ERROR);
	if (open(path, O_RDONLY) == -1)
	{
		free(path);
		free_cub_exit(cub, FILE_ERROR);
	}
	if (!ft_strncmp(line, "NO", 2))
		cub->dirs.no = cub->dirs.no ? free_cub_exit(cub, MAP_ELM_REP) : path;
	else if (!ft_strncmp(line, "SO", 2))
		cub->dirs.so = cub->dirs.so ? free_cub_exit(cub, MAP_ELM_REP) : path;
	else if (!ft_strncmp(line, "WE", 2))
		cub->dirs.we = cub->dirs.we ? free_cub_exit(cub, MAP_ELM_REP) : path;
	else if (!ft_strncmp(line, "EA", 2))
		cub->dirs.ea = cub->dirs.ea ? free_cub_exit(cub, MAP_ELM_REP) : path;
	else if (!ft_strncmp(line, "S ", 2))
		cub->sprite.path = cub->sprite.path ? free_cub_exit(cub, MAP_ELM_REP)
							: path;
}

void	verify_color(t_rgb color, t_cub *cub, char c)
{
	if (!is_color(color.r) || !is_color(color.g) || !is_color(color.b))
		free_cub_exit(cub, MAP_ERROR);
	if (c == 'F')
	{
		if (cub->floor.r != -1 || cub->floor.g != -1 || cub->floor.b != -1)
			free_cub_exit(cub, MAP_ELM_REP);
		cub->floor = color;
	}
	else if (c == 'C')
	{
		if (cub->ceil.r != -1 || cub->ceil.g != -1 ||
			cub->ceil.b != -1)
			free_cub_exit(cub, MAP_ELM_REP);
		cub->ceil = color;
	}
}

int		verify_str_clr(char **clr)
{
	char	*trimmed;
	int		i;

	if (!clr || tb_len(clr) != 3)
		return (0);
	i = -1;
	while (++i < 3)
	{
		trimmed = ft_strtrim(clr[i], " ");
		if (!is_set(trimmed, "0123456789"))
		{
			free(trimmed);
			return (0);
		}
		free(trimmed);
	}
	return (1);
}

void	get_verify_color(char *line, t_cub *cub)
{
	t_rgb	color;
	char	**clr;
	char	*s;
	int		l;

	s = line;
	l = 0;
	if (s)
		while (*s)
			if (*s++ == ',')
				l++;
	l != 2 ? free_cub_exit(cub, MAP_ERROR) : 0;
	clr = ft_split(line + 2, ',');
	if (!verify_str_clr(clr))
	{
		free_str_table(clr, tb_len(clr));
		free_cub_exit(cub, MAP_ERROR);
	}
	color.r = ft_atoi(clr[0]);
	color.g = ft_atoi(clr[1]);
	color.b = ft_atoi(clr[2]);
	free_str_table(clr, 3);
	verify_color(color, cub, *line);
}
