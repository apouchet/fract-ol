/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apouchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 16:04:20 by apouchet          #+#    #+#             */
/*   Updated: 2019/10/09 16:04:22 by apouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACT_H
# define FRACT_H

# include "mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <fcntl.h>
# include <unistd.h>

# define FENETRE_X 1500
# define FENETRE_Y 1286
# define R 0x00FF0000
# define G 0x0000FF00
# define B 0x000000FF

double a;
double b;

typedef struct	s_picture
{
	int			bpp;
	int			sl;
	int			endian;
}				t_picture;

typedef struct	s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*p_img;
	int			*img;
	double		zoom;
	double		move_x;
	double		move_y;
	int			scale;
	int			iteration_max;
	int			mode;
	int			fix;
	int			x;
	int			y;
	int			fract;
	
	double		x_a;
	double		x_b;
	double		y_a;
	double		y_b;
	
	double		c_r;
	double		c_i;
	double		z_r;
	double		z_i;
	double		size_x;
	double		size_y;
	t_picture	p;
}				t_data;

int		ft_mandelbrot(t_data *d, double size_x, double size_y);

#endif
