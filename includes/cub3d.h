/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 21:31:32 by obouykou          #+#    #+#             */
/*   Updated: 2020/10/17 19:33:50 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include <errno.h>
# include <math.h>
# include <mlx.h>

# define NO_ARG 			1
# define FILE_ERROR 		-1
# define EXTENSION_ERROR 	-2
# define MAP_ERROR			-3
# define GNL_ERROR			-4
# define EXEC_ERROR			-5
# define MAP_ELM_REP		-6
# define SAVING_BMP_ERROR	-7
# define END_GAME			0
# define BUFFER_SIZE		4
# define KEY_UP				13
# define KEY_DOWN			1
# define KEY_RIGHT			2
# define KEY_LEFT			0
# define ROT_R				124
# define ROT_L				123
# define EXIT_KEY			53
# define NUM_SP				4096

typedef struct	s_form
{
	int x;
	int y;
}				t_form;

typedef	struct	s_point
{
	double	x;
	double	y;
}				t_point;

typedef	struct	s_ipoint
{
	int		x;
	int		y;
}				t_ipoint;

typedef	struct	s_seg
{
	int		a;
	int		b;
}				t_seg;

typedef	struct	s_dir
{
	char *no;
	char *so;
	char *ea;
	char *we;
}				t_dir;

typedef	struct	s_rgb
{
	int r;
	int g;
	int b;
	int	a;
}				t_rgb;

typedef	struct	s_map
{
	t_form	form;
	char	*tmp_map;
	char	**map;
	char	dir_count;
	t_point in_pos;
	char	orient;
	int		step;
}				t_map;

typedef struct	s_line
{
	int h;
	int	lpix;
	int hpix;
	int	color;
}				t_line;

typedef	struct	s_control
{
	t_point		pos;
	t_point		plane;
	t_point		old_plane;
	t_point		dir;
	t_point		old_dir;
	t_point		cam;
	t_point		ray;
	t_ipoint	map;
	t_point		side_dist;
	t_point		delta_d;
	t_ipoint	step;
	int			hit;
	int			side_dir;
	double		wall_d;
}				t_control;

typedef	struct	s_keys
{
	int		u;
	int		d;
	int		l;
	int		r;
	int		rot_r;
	int		rot_l;
	int		exit;
}				t_keys;

typedef	struct	s_sp
{
	double	move;
	double	root;
}				t_sp;

typedef struct	s_img
{
	void		*ptr;
	int			*data;
	int			*buff;
	int			size_l;
	int			bpp;
	int			endian;
}				t_img;

typedef	struct	s_tex
{
	void		*ptr;
	int			*data;
	int			num;
	t_ipoint	dir;
	int			w;
	int			h;
	double		pos;
	double		step;
}				t_tex;

typedef struct	s_sprite
{
	char		*path;
	int			w;
	int			h;
	int			count;
	double		inv_d;
	t_seg		draw_x;
	t_seg		draw_y;
	double		x;
	double		y;
	int			sc_x;
	int			seg;
	t_tex		tex;
	t_point		tr_form;
	t_point		pos[NUM_SP];
	int			sp_ord[NUM_SP];
	double		sp_dist[NUM_SP];
}				t_sprite;

typedef	struct	s_bmp
{
	int				w;
	int				h;
	unsigned short	bitcount;
	int				w_in_bytes;
	unsigned int	img_size;
	unsigned int	bi_size;
	unsigned int	bfi_size;
	unsigned int	file_size;
	unsigned short	bi_planes;
	unsigned char	header[54];
	int				*buff;
}				t_bmp;

typedef struct	s_cub
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_form		rsl;
	t_dir		dirs;
	t_sprite	sprite;
	double		*zbuff;
	t_rgb		floor;
	t_rgb		ceil;
	t_map		map;
	t_control	ctrl;
	t_line		line;
	t_sp		sp;
	t_keys		key;
	t_point		wall;
	t_tex		tex[4];
	int			texnum;
	t_img		img;
	short		is_save;
	t_bmp		bmp;
}				t_cub;

void			ft_putstr_fd(char *s, int fd);
int				len_if(char *s, int nl);
char			*ft_dup_free(char *src, char **to_free);
char			*ft_strjoin(char *s1, char *s2);
char			*ft_strchr(char *s, int c);
int				build_line(char **line, char **buff, char **buff_s, char step);
int				get_next_line(int fd, char **line);
int				ft_atoi(const char *str);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_strdup(const char *src);
void			hundle_error(int err);
void			check_map(char *map, t_cub *cub);
void			get_resolution(char *line, t_cub *cub);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			**ft_split(char const *s, char c);
void			get_verify_path(char *line, t_cub *cub);
void			get_verify_color(char *line, t_cub *cub);
int				char_count(char *str, char c);
void			get_verify_map(int fd, char *line, t_map *map, t_cub *cub);
char			**free_str_table(char **tab, int size);
char			*free_cub_exit(t_cub *cub, int err);
int				tb_len(char **table);
int				is_color(int color_code);
int				is_set(char *target, char *set);
void			*ft_memset(void *b, int c, size_t len);
void			raycast_sprite(t_cub *cub);
int				check_map_hline(t_cub *cub, char *line, t_map *map, int x);
void			tex_extractor(t_cub *cub);
int				key_pressed(int key, t_cub *cub);
int				key_release(int key, t_keys	*keys);
int				close_window(t_cub *cub);
int				hundle_key(t_cub *cub);
void			ray_calcs(t_cub *cub, int x);
void			step_dir(t_cub	*cub);
void			dda(t_cub *cub);
void			init_map(t_cub *cub);
void			init_player(t_cub *cub);
void			init_cub(t_cub *cub);
int				calc_draw(t_cub *cub);
int				save_bmp(t_cub *cub, int *buff);
void			*ft_memcpy(void *dst, const void *src, size_t n);

#endif
