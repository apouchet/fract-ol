/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_zoom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floblanc <floblanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:33:42 by apouchet          #+#    #+#             */
/*   Updated: 2019/10/23 14:41:20 by floblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"

static void		ft_zoom_out(t_fract *f)
{
	double tmp;

	tmp = (((f->x_a - f->x_b) / (1 - (0.1 * 2))) - (f->x_a - f->x_b)) / 2;
	f->x_a -= -tmp;
	f->x_b -= tmp;
	tmp = (((f->y_a - f->y_b) / (1 - (0.1 * 2))) - (f->y_a - f->y_b)) / 2;
	f->y_a -= -tmp;
	f->y_b -= tmp;
}

static void		ft_zoom_in(int key, t_fract *fract)
{
	double tmp;
	double tmp2;

	tmp2 = 2 * fract->mouse_x / (fract->x_b - fract->x_a);
	tmp = (fract->x_a - fract->x_b) * 0.1;
	fract->x_a += -tmp;
	fract->x_b += tmp;
	if (key == -5)
	{
		tmp = (fract->x_b - fract->x_a) / 2;
		fract->x_a -= tmp2 * tmp - fract->mouse_x;
		fract->x_b -= tmp2 * tmp - fract->mouse_x;
		fract->mouse_x += tmp2 * tmp - fract->mouse_x;
	}
	tmp2 = 2 * fract->mouse_y / (fract->y_b - fract->y_a);
	tmp = (fract->y_a - fract->y_b) * 0.1;
	fract->y_a += -tmp;
	fract->y_b += tmp;
	if (key == -5)
	{
		tmp = (fract->y_b - fract->y_a) / 2;
		fract->y_a -= tmp2 * tmp - fract->mouse_y;
		fract->y_b -= tmp2 * tmp - fract->mouse_y;
		fract->mouse_y += tmp2 * tmp - fract->mouse_y;
	}
}

void			ft_zoom(int key, t_fract *fract)
{
	if ((key == -5 || key == 24 || key == 69 || key == 13) && fract->zoom < 150)
	{
		if (fract->iteration_max < 130)
			fract->iteration_max++;
		fract->zoom++;
		ft_zoom_in(key, fract);
		fract->step_x = (fract->x_b - fract->x_a) * 0.01;
		fract->step_y = (fract->y_b - fract->y_a) * 0.01;
	}
	else if ((key == -4 || key == 27 || key == 78 || key == 1)
		&& (fract->x_b - fract->x_a) <= (0.6 + 2.1) * 2)
	{
		if (fract->iteration_max > 21
			&& fract->zoom + 20 < fract->iteration_max)
			fract->iteration_max--;
		fract->zoom--;
		ft_zoom_out(fract);
		fract->step_x = (fract->x_b - fract->x_a) * 0.01;
		fract->step_y = (fract->y_b - fract->y_a) * 0.01;
	}
	else
		return ;
}
