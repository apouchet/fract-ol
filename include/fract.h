/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floblanc <floblanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 16:04:20 by apouchet          #+#    #+#             */
/*   Updated: 2019/10/21 16:31:23 by floblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACT_H
# define FRACT_H

# include "../mlx/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <fcntl.h>
# include <unistd.h>
# include <pthread.h>
# include <strings.h>
# include <math.h>
# include "libprintf.h"
# include <time.h>

# define FENETRE_X 1500
# define FENETRE_Y 1286
# define SCREENSHOT "Desktop"
# define R 0x00FF0000
# define G 0x0000FF00
# define B 0x000000FF
# define W 0x00FFFFFF

typedef struct	s_picture
{
	int			bpp;
	int			sl;
	int			endian;
}				t_picture;

typedef struct		s_tga
{
	char			id_length;
	char			colour_map;
	char			data_type;
	short int		colour_origin;
	short int		colour_length;
	char			colour_depth;
	short int		x_origin;
	short int		y_origin;
	short int		width;
	short int		height;
	char			bpp;
	char			imagedescriptor;
}					t_tga;

typedef struct	s_fract
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*p_img;
	int			*img;
	double		move_x;
	double		move_y;
	int			zoom;
	int			scale;
	int			iteration_max;
	int			mode;
	int			fix;
	int			fdf;
	double		mouse_x;
	double		mouse_y;
	double		step_x;
	double		step_y;
	int			fract;
	int			size;
	int			info;
	int			opengl;
	
	double		x_a;
	double		x_b;
	double		y_a;
	double		y_b;
	double		ratio_x;
	double		ratio_y;
	int			nb_thread;
	int			x;
	
	double		c_r;
	double		c_i;
	double		z_r;
	double		z_i;
	int			div;
	int			div_q;
	int			mouse_button;
	t_picture	p;
}				t_fract;

int		parsing(t_fract *fract, int ac, char ** av);

void	*ft_mandelbrot_julia(void *fract);

void	reset_fract(t_fract *fract);

int		ft_key(int key,	t_fract *fract);

int		mouse_release_hook(int x, int y, t_fract *fract);

int		mouse_hook(int button, int x, int y, t_fract *fract);

int		mouse_release(int button, int x, int y, t_fract *fract);

int		ft_affich(t_fract *fract);

void	ft_screen(t_fract *fract);

void	ft_zoom(int key, t_fract *fract);

void	ft_init_mandelbrot(t_fract *fract);

void	ft_init_julia(t_fract *fract);

void	ft_init_newton(t_fract *fract);

void	ft_mdb_julia_semi_opti(t_fract *f);

void	ft_start_fract(t_fract *fract);

int		main_mlx(t_fract *fract);

int		main_opengl(t_fract *fract);

int		ft_color(int i, t_fract f, int x, int y);

void		ft_hud(t_fract *fract);

void	ft_init_screenshot(t_tga *tga, t_fract *fract);

void	ft_screen_gl(char *buff);

char	*ft_create_path(char *target, char *type, char *name, int offset);


#endif
