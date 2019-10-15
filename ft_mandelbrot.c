/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mandelbrot.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apouchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 16:04:23 by apouchet          #+#    #+#             */
/*   Updated: 2019/10/13 21:22:21 by apouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"
#include <strings.h>

static void	ft_switch(t_data *data, int x, int y, double zoom_x, double zoom_y)
{
	if (data->fract == 0)
	{
		data->z_r = 0;
		data->z_i = 0;
		data->c_r = x / zoom_x + data->x_a;
		data->c_i = y / zoom_y + data->y_a;

	}
	else if (data->fract == 1)
	{
		data->z_r = x / zoom_x + data->x_a;
		data->z_i = y / zoom_y + data->y_a;
	}
}

static int		ft_calcul_mandelbrot(t_data *data)
{
	double tmp;
	double pow_r;
	double pow_i;
	int i;

	i = 0;
	tmp = data->z_r;
	data->z_r = data->z_r * data->z_r - data->z_i * data->z_i + data->c_r;
	data->z_i = 2 * data->z_i * tmp + data->c_i;

	pow_r = data->z_r * data->z_r;
	pow_i = data->z_i * data->z_i;
	
	while (pow_r + pow_i < 4 && ++i < data->iteration_max)
	{
		tmp = data->z_r;
		data->z_r = pow_r - pow_i + data->c_r;
		data->z_i = 2 * data->z_i * tmp + data->c_i;
		pow_r = data->z_r * data->z_r;
		pow_i = data->z_i * data->z_i;
	}
	return (i);
}

static  int		ft_color(int i, int len, t_data *d)
{
	int		color;

	if (i % (d->div) <= d->div / 6)
		color = B + R - ((R * i * 6 / d->div) & R);
	else if (i % (d->div) <= d->div / 3)
		color = B + ((G * i * 3 / d->div) & G);
	else if (i % (d->div) <= d->div / 2)
		color = G + B - ((B * i * 2 / d->div) & B);
	else if (i % (d->div) <= 2 * d->div / 3)
		color = G + ((R *  2 * (1 - i / d->div)) & R);
	else if (i % (d->div) <= 5 * d->div / 6)
		color = R + G - ((G * 3 * (1 - i / d->div)) & G);
	else
		color = R + ((B * 6 * (1 - i / d->div)) & B);
	return(color);
}

static  int		ft_check_opti(t_data *d, int x, int y, int type)
{

	if (type == 1) // semi opti
		return (x != 0 && y != 0 && x != FENETRE_X - 1 && y != FENETRE_Y - 1
				&& d->img[d->p.sl * y + x - 1] == d->img[d->p.sl * y + x + 1]
				&& d->img[d->p.sl * y + x - 1] == d->img[d->p.sl * (y - 1) + x]
				&& d->img[d->p.sl * y + x - 1] == d->img[d->p.sl * (y + 1) + x]);
	else // opti
		return (x != 0 && y != 0 && x != FENETRE_X - 1 && y != FENETRE_Y - 1
				&& d->img[d->p.sl * (y - 1) + x - 1] == d->img[d->p.sl * (y - 1) + x + 1]
				&& d->img[d->p.sl * (y - 1) + x - 1] == d->img[d->p.sl * (y + 1) + x + 1]
				&& d->img[d->p.sl * (y - 1) + x - 1] == d->img[d->p.sl * (y + 1) + x - 1]);

}

static void		ft_mandelbrot_semi_opti(t_data *d, double zoom_x, double zoom_y)
{
	int i;
	int x;
	int y;

	x = 0;
	while (x < FENETRE_X)
	{
		y = (x + 1) % 2;
		while (y < FENETRE_Y)
		{
			if (ft_check_opti(d, x, y, 1))
				d->img[d->p.sl * y + x] = d->img[d->p.sl * (y - 1) + x];
			else
			{
				ft_switch(d, x, y, zoom_x, zoom_y);
				i = ft_calcul_mandelbrot(d);
				if (i != d->iteration_max)
					d->img[d->p.sl * y + x] =  ft_color(i, d->iteration_max, d);
				else
					d->img[d->p.sl * y + x] = 0; /// ????????
			}
			y += 2;
		}
		x++;
	}
}



static void	ft_mandelbrot_opti(t_data *d, double zoom_x, double zoom_y)
{
	int i;
	int x;
	int y;

	x = 1;
	while (x < FENETRE_X)
	{
		y = 1;
		while (y < FENETRE_Y)
		{
			if (ft_check_opti(d, x, y, 0))
				d->img[d->p.sl * y + x] = d->img[d->p.sl * (y - 1) + x + 1];
			else
			{
				ft_switch(d, x, y, zoom_x, zoom_y);
				i = ft_calcul_mandelbrot(d);
				if (i != d->iteration_max)
					d->img[d->p.sl * y + x] =  ft_color(i, d->iteration_max, d);
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
	double zoom_x = (FENETRE_X / (d->x_b - d->x_a));// * d->zoom;
	double zoom_y = (FENETRE_Y / (d->y_b - d->y_a));// * d->zoom;
	// printf("zoom x = %lf\n", zoom_x);
	int i;
	int x;
	int y;
	int x_step;
	int y_step;

	x = 0;
	x_step = (d->mode >= 2? 2 : 1);
	y_step = (d->mode == 0 ? 1 : 2);
	if (d->mode == 3)
	{
		bzero(d->img, FENETRE_X * FENETRE_Y * 4);
	}
	while (x < FENETRE_X)
	{
		y = (d->mode == 1 ? x % 2 : 0);
		// y = 0;
		while (y < FENETRE_Y)
		{
			ft_switch(d, x, y, zoom_x, zoom_y);
			i = ft_calcul_mandelbrot(d);//d->z_r, d->z_i, d->c_r, d->c_i, d->iteration_max);
			if (i != d->iteration_max)
				d->img[d->p.sl * y + x] = ft_color(i, d->iteration_max, d);
			else if (d->mode != 3)
				d->img[d->p.sl * y + x] = 0;//xFF000000;
			y += y_step;
		}
		x += x_step;
	}
	if (d->mode == 2)
		ft_mandelbrot_opti(d, zoom_x, zoom_y);
	if (d->mode == 1 || d->mode == 2)
		ft_mandelbrot_semi_opti(d, zoom_x, zoom_y);
	return (0);
}