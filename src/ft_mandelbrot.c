/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mandelbrot.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apouchet <apouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 16:04:23 by apouchet          #+#    #+#             */
/*   Updated: 2019/11/13 16:44:03 by apouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"

void		ft_switch(t_fract *fract, int x, int y)
{
	if (fract->fract == 0 || fract->fract == 2)
	{
		fract->z_r = 0;
		fract->z_i = 0;
		fract->c_r = x / fract->ratio_x + fract->x_a;
		fract->c_i = y / fract->ratio_y + fract->y_a;
	}
	else if (fract->fract == 1 || fract->fract == 3 || fract->fract == 4)
	{
		fract->z_r = x / fract->ratio_x + fract->x_a;
		fract->z_i = y / fract->ratio_y + fract->y_a;
	}
}

static int	ft_calcul_mdb_julia(t_fract fract, int x, int y)
{
	double	tmp;
	double	pow_r;
	double	pow_i;
	int		i;

	i = 0;
	ft_switch(&fract, x, y);
	tmp = fract.z_r;
	fract.z_r = fract.z_r * fract.z_r - fract.z_i * fract.z_i + fract.c_r;
	fract.z_i = 2 * fract.z_i * tmp + fract.c_i;
	pow_r = fract.z_r * fract.z_r;
	pow_i = fract.z_i * fract.z_i;
	while (pow_r + pow_i < 4 && ++i < fract.iteration_max)
	{
		tmp = fract.z_r;
		fract.z_r = pow_r - pow_i + fract.c_r;
		fract.z_i = 2 * fract.z_i * tmp + fract.c_i;
		pow_r = fract.z_r * fract.z_r;
		pow_i = fract.z_i * fract.z_i;
	}
	return (i);
}

int			ft_color(int i, t_fract f, int x, int y)
{
	int		color;

	if (f.fdf)
		return (i);
	if (i == f.iteration_max)
		color = 0;
	else if (i % (f.div) <= f.div / 6)
		color = B + R - ((R * i * 6 / f.div) & R);
	else if (i % (f.div) <= f.div / 3)
		color = B + ((G * i * 3 / f.div) & G);
	else if (i % (f.div) <= f.div / 2)
		color = G + B - ((B * i * 2 / f.div) & B);
	else if (i % (f.div) <= 2 * f.div / 3)
		color = G + ((R * 2 * (1 - i / f.div)) & R);
	else if (i % (f.div) <= 5 * f.div / 6)
		color = R + G - ((G * 3 * (1 - i / f.div)) & G);
	else
		color = R + ((B * 6 * (1 - i / f.div)) & B);
	if (f.info == 2 && ((x > FENETRE_X - 475 && y > FENETRE_Y - 210)
				|| (x < 175 && y > FENETRE_Y - 90)))
		color = ((int)((color & R) * 0.3) & R) + ((int)((color & G) * 0.3) & G)
			+ ((int)((color & B) * 0.3) & B);
	return (color);
}

int			select_calc(t_fract *f, int x, int y)
{
	if (f->fract < 2)
		return (ft_color(ft_calcul_mdb_julia(*f, x, y), *f, x, y));
	else if (f->fract < 4)
		return (ft_color(ft_calcul_bns_juliabns(*f, x, y), *f, x, y));
	else
		return (ft_calcul_newton(*f, x, y));
}

void		*ft_mandelbrot_julia(void *fract)
{
	int		x;
	int		y;
	int		x_step;
	int		y_step;
	t_fract	*f;

	f = (t_fract*)fract;
	x = f->x++;
	x *= (f->mode == 2 ? 2 : 1);
	x *= (f->mode >= 3 ? 4 : 1);
	x_step = (f->mode >= 2 ? 2 : 1) * f->nb_thread;
	y_step = (f->mode == 0 ? 1 : 2);
	x_step = (f->mode >= 3 ? x_step * 2 : x_step);
	y_step = (f->mode >= 3 ? 4 : y_step);
	while (x < FENETRE_X)
	{
		y = (f->mode == 1 ? x % 2 : 0);
		while (y < FENETRE_Y)
		{
			f->img[f->p.sl * y + x] = select_calc(f, x, y);
			y += y_step;
		}
		x += x_step;
	}
	return (NULL);
}
