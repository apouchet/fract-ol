/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mandelbrot.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floblanc <floblanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 16:04:23 by apouchet          #+#    #+#             */
/*   Updated: 2019/10/21 16:21:07 by floblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"

static void	ft_switch(t_fract *fract, int x, int y)
{
	if (fract->fract == 0  || fract->fract == 2 || fract->fract == 4)
	{
		fract->z_r = 0;
		fract->z_i = 0;
		fract->c_r = x / fract->ratio_x + fract->x_a;
		fract->c_i = y / fract->ratio_y + fract->y_a;
	}
	else if (fract->fract == 1 || fract->fract == 3)
	{
		fract->z_r = x / fract->ratio_x + fract->x_a;
		fract->z_i = y / fract->ratio_y + fract->y_a;
	}
}

#include <complex.h>

static int	ft_calcul_newton(t_fract fract, int x, int y)
{
	complex double	z;
	complex double	r1;
	complex double	r2;
	complex double	r3;
	int i;
	
	i = 0;
	ft_switch(&fract, x, y);

	z = fract.c_r + fract.c_i * I;
	r1 = 1;
	r2 = -0.5 + sin(2 * M_PI / 3) * I;
	r3 = -0.5 - sin(2 * M_PI / 3) * I;
	while (++i < fract.iteration_max)
	{
		 z = z-(z*z*z-1.0)/(z*z*3.0);
		 if (cabs(z - r1) < 0.0001)
		 	return (R - (int)(((double)i / fract.iteration_max) * (double)R) & R);
		else if (cabs(z - r2) < 0.0001)
		 	return (G - (int)(((double)i / fract.iteration_max) * (double)G) & G);
		else if (cabs(z - r3) < 0.0001) 
		 	return (B - (int)(((double)i / fract.iteration_max) * (double)B) & B);
	}
	return (i);
}

static int	ft_calcul_bns_juliabns(t_fract fract, int x, int y)
{
	double tmp;
	double pow_r;
	double pow_i;
	int i;

	i = 0;
	ft_switch(&fract, x, y);
	tmp = fract.z_r;
	fract.z_r = fract.z_r * fract.z_r - fract.z_i * fract.z_i + fract.c_r;
	fract.z_i = 2 * ft_abs_double(fract.z_i * tmp) + fract.c_i;

	pow_r = fract.z_r * fract.z_r;
	pow_i = fract.z_i * fract.z_i;
	while (pow_r + pow_i < 4 && ++i < fract.iteration_max)
	{
		tmp = fract.z_r;
		fract.z_r = pow_r - pow_i + fract.c_r;
		fract.z_i = 2 * ft_abs_double(fract.z_i * tmp) + fract.c_i;
		pow_r = fract.z_r * fract.z_r;
		pow_i = fract.z_i * fract.z_i;
	}
	return (i);
}

static int	ft_calcul_mdb_julia(t_fract fract, int x, int y)
{
	double tmp;
	double pow_r;
	double pow_i;
	int i;

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

int		ft_color(int i, t_fract f, int x, int y)
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
			color = ((int)((color & R) * 0.3) & R)
		+ ((int)((color & G) * 0.3) & G) + ((int)((color & B) * 0.3) & B);
	return (color);
}

int		select_calc(t_fract *f, int x, int y)
{
	if (f->fract < 2)
		return (ft_color(ft_calcul_mdb_julia(*f, x, y), *f, x, y));
	else if (f->fract < 4)
		return (ft_color(ft_calcul_bns_juliabns(*f, x, y), *f, x, y));
	else
		return (ft_calcul_newton(*f, x, y));
}

static int	ft_check_opti(t_fract *f, int x, int y, int type)
{

	if (type == 1) // semi opti
		return (x != 0 && y != 0 && x != FENETRE_X - 1 && y != FENETRE_Y - 1
				&& f->img[f->p.sl * y + x - 1] == f->img[f->p.sl * (y - 1) + x]
				&& f->img[f->p.sl * y + x - 1] == f->img[f->p.sl * (y + 1) + x]
				&& f->img[f->p.sl * y + x - 1] == f->img[f->p.sl * y + x + 1]);
	else // opti
		return (x != 0 && y != 0 && x != FENETRE_X - 1 && y != FENETRE_Y - 1
				&& f->img[f->p.sl * (y - 1) + x - 1]
				== f->img[f->p.sl * (y - 1) + x + 1]
				&& f->img[f->p.sl * (y - 1) + x - 1]
				== f->img[f->p.sl * (y + 1) + x + 1]
				&& f->img[f->p.sl * (y - 1) + x - 1]
				== f->img[f->p.sl * (y + 1) + x - 1]);

}

static void	ft_mdb_julia_opti(t_fract *f)
{
	int x;
	int y;

	x = 1;
	while (x < FENETRE_X)
	{
		y = 1;
		while (y < FENETRE_Y)
		{
			if (ft_check_opti(f, x, y, 0))
				f->img[f->p.sl * y + x] = f->img[f->p.sl * (y - 1) + x + 1];
			else
				f->img[f->p.sl * y + x] = select_calc(f, x, y);
			y += 2;
		}
		x += 2;
	}
}

void		ft_mdb_julia_semi_opti(t_fract *f)
{
	int x;
	int y;

	if (f->mode == 2)
		ft_mdb_julia_opti(f);
	x = 0;
	while (x < FENETRE_X)
	{
		y = ((x + 1) % 2);
		while (y < FENETRE_Y)
		{
			if (ft_check_opti(f, x, y, 1))
				f->img[f->p.sl * y + x] = f->img[f->p.sl * (y - 1) + x];
			else
				f->img[f->p.sl * y + x] = select_calc(f, x, y);
			y += 2;
		}
		x++;
	}
}

void		*ft_mandelbrot_julia(void *fract)
{
	int x;
	int y;
	int x_step;
	int y_step;
	t_fract *f;

	f = (t_fract*)fract;
	x = f->x++;
	x *= (f->mode >= 2 ? 2 : 1);
	x_step = (f->mode >= 2 ? 2 : 1) * f->nb_thread;
	y_step = (f->mode == 0 ? 1 : 2);
	if (f->mode == 3)
		bzero(f->img, FENETRE_X * FENETRE_Y * 4);
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
