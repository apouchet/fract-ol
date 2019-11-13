/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_other_fract.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apouchet <apouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 16:39:18 by apouchet          #+#    #+#             */
/*   Updated: 2019/11/13 16:40:27 by apouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"

void	newtons_calc(t_fract *f)
{
	double	tmp;
	double	pow_r;
	double	pow_i;
	double	div;

	pow_r = f->z_r * f->z_r;
	pow_i = f->z_i * f->z_i;
	div = 3.0 * (pow_r + pow_i) * (pow_r + pow_i);
	tmp = f->z_r;
	f->z_r -= (pow_r * pow_r * f->z_r + 2.0 * pow_r * f->z_r
			* pow_i + f->z_r * pow_i * pow_i - pow_r + pow_i) / div;
	f->z_i -= (pow_i * pow_i * f->z_i + pow_r * pow_r * f->z_i + 2
			* pow_r * pow_i * f->z_i + 2 * tmp * f->z_i) / div;
}

int		ft_calcul_newton(t_fract f, int x, int y)
{
	int		i;

	i = 0;
	ft_switch(&f, x, y);
	while (++i < f.iteration_max)
	{
		newtons_calc(&f);
		if (sqrt(pow(f.z_r - 1, 2) + pow(f.z_i, 2)) < 0.0001)
			return (R - (int)(((double)i / f.iteration_max) * (double)R) & R);
		else if (sqrt(pow(f.z_r + 0.5, 2)
					+ pow(f.z_i - sqrt(3) / 2, 2)) < 0.0001)
			return (G - (int)(((double)i / f.iteration_max) * (double)G) & G);
		else if (sqrt(pow(f.z_r + 0.5, 2)
					+ pow(f.z_i + sqrt(3) / 2, 2)) < 0.0001)
			return (B - (int)(((double)i / f.iteration_max) * (double)B) & B);
	}
	return (i);
}

int		ft_calcul_bns_juliabns(t_fract fract, int x, int y)
{
	double	tmp;
	double	pow_r;
	double	pow_i;
	int		i;

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
