/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mandelbro.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apouchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 16:04:23 by apouchet          #+#    #+#             */
/*   Updated: 2019/10/09 16:04:26 by apouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"

static int		ft_calcul_mandelbrot(double z_r, double z_i, double c_r, double c_i, int max)
{
	double tmp;
	double pow_r;
	double pow_i;
	int i;

	i = 0;
	tmp = z_r;
	
	z_r = z_r * z_r - z_i * z_i + c_r;
	z_i = 2 * z_i * tmp + c_i;
	pow_r = z_r * z_r;
	pow_i = z_i * z_i;
	while (pow_r + pow_i < 4 && ++i < max)
	{
		tmp = z_r;
		z_r = pow_r - pow_i + c_r;
		z_i = 2 * z_i * tmp + c_i;
		pow_r = z_r * z_r;
		pow_i = z_i * z_i;
	}
	return (i);
}

static  int		ft_color(int i, int len)
{
	int color;

	if (i <= len / 6)
		color = B + R - ((R * i * 6 / len) & R);
	else if (i <= len / 3)
		color = B + ((G * i * 3 / len) & G);
	else if (i <= len / 2)
		color = G + B - ((B * i * 2 / len) & 2);
	else if (i <= 2 * len / 3)
		color = G + ((R * (1 - i * 2 / len)) & R);
	else if (i <= 5 * len / 6)
		color = R + G - ((G * (1 - i  * 3 / len)) & G);
	else
		color = R + ((B * (1 - i * 6 / len)) & B);
	return(color);
}

static  int		ft_check_opti(t_data *d, int x, int y, int type)
{

	if (type == 1) // semi opti
		return (x != 0 && y != 0 && x != FENETRE_X - 1 && y != FENETRE_Y - 1
				&& d->img[d->p.sl * y + x - 1] == d->img[d->p.sl * y + x + 1]
				&& d->img[d->p.sl * y + x - 1] == d->img[d->p.sl * (y - 1) + x]
				&& d->img[d->p.sl * y + x + 1] == d->img[d->p.sl * (y - 1) + x]);
	else // opti
		return (x != 0 && y != 0 && x != FENETRE_X - 1 && y != FENETRE_Y - 1
				&& d->img[d->p.sl * (y - 1) + x - 1]
				== d->img[d->p.sl * (y - 1) + x + 1]
				&& d->img[d->p.sl * (y + 1) + x - 1]
				== d->img[d->p.sl * (y + 1) + x + 1]
				&& d->img[d->p.sl * (y - 1) + x + 1]
				== d->img[d->p.sl * (y + 1) + x + 1]);

}

static void		ft_mandelbrot_semi_opti(t_data *d, int x, int y, double zoom_x, double zoom_y)
{
	int i;

	while (x < FENETRE_X)
	{
		y = (x + 1) % 2;
		while (y < FENETRE_Y)
		{
			if (ft_check_opti(d, x, y, 1))
				d->img[d->p.sl * y + x] = d->img[d->p.sl * (y - 1) + x];
			else
			{
				i = ft_calcul_mandelbrot(0, 0, ((x + d->move_x) / zoom_x - 2.1) * d->zoom,
					((y + d->move_y) / zoom_y - 1.2) * d->zoom, d->iteration_max);
				if (i != d->iteration_max)
					d->img[d->p.sl * y + x] =  ft_color(i, d->iteration_max);
				else
					d->img[d->p.sl * y + x] = 0;
			}
			y += 2;
		}
		x++;
	}
}



static void	ft_mandelbrot_opti(t_data *d, int x, int y, double zoom_x, double zoom_y)
{
	int i;

	while (x < FENETRE_X)
	{
		y = 1;
		while (y < FENETRE_Y)
		{
			if (ft_check_opti(d, x, y, 0))
				d->img[d->p.sl * y + x] = d->img[d->p.sl * (y - 1) + x + 1];
			else
			{
				i = ft_calcul_mandelbrot(0, 0, ((x + d->move_x) / zoom_x - 2.1) * d->zoom,
					((y + d->move_y) / zoom_y - 1.2) * d->zoom, d->iteration_max);
				if (i != d->iteration_max)
					d->img[d->p.sl * y + x] =  ft_color(i, d->iteration_max);
				else
					d->img[d->p.sl * y + x] = 0;
			}
			y += 2;
		}
		x += 2;
	}
}

int		ft_mandelbrot(t_data *d, double size_x, double size_y)
{
	double zoom_x = FENETRE_X / size_x ;
	double zoom_y = FENETRE_Y / size_y ;
	int i;
	int x;
	int y;
	int x_step;
	int y_step;

// c_r = 0.285
// c_i = 0.01
// z_r = x / zoom - 1
// z_i = y / zoom - 1.2
	x = 0;
	x_step = (d->mode == 2 ? 2 : 1);
	y_step = (d->mode == 0 ? 1 : 2);
	while (x < FENETRE_X)
	{
		y = (d->mode == 1 ? x % 2 : 0);
		// y = 0;
		while (y < FENETRE_Y)
		{
			i = ft_calcul_mandelbrot(0, 0, ((x + d->move_x) / zoom_x - 2.1) * d->zoom,
				((y + d->move_y) / zoom_y - 1.2) * d->zoom, d->iteration_max);
			if (i != d->iteration_max)
				d->img[d->p.sl * y + x] = ft_color(i, d->iteration_max);
			else
				d->img[d->p.sl * y + x] = 0;
			y += y_step;
		}
		x += x_step;
	}
	if (d->mode == 2)
		ft_mandelbrot_opti(d, 1, 1, zoom_x, zoom_y);
	if (d->mode == 1 || d->mode == 2)
		ft_mandelbrot_semi_opti(d, 0, 0, zoom_x, zoom_y);
	mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, d->p_img, 0, 0);
	return (0);
}
