/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_zoom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apouchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:33:42 by apouchet          #+#    #+#             */
/*   Updated: 2019/10/15 15:33:43 by apouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"

static void		ft_zoom_out(t_data *d)
{
	double tmp;

	tmp = (((d->x_a - d->x_b) / (1 - (0.1 * 2))) - (d->x_a - d->x_b)) / 2;
	d->x_a -= -tmp;
	d->x_b -= tmp;
	tmp = (((d->y_a - d->y_b) / (1 - (0.1 * 2))) - (d->y_a - d->y_b)) / 2;
	d->y_a -= -tmp;
	d->y_b -= tmp;
}

static void		ft_zoom_in(int key, t_data *data)
{
	double tmp;
	double tmp2;

	tmp2 = 2 * data->mouse_x / (data->x_b - data->x_a);
	tmp = (data->x_a - data->x_b) * 0.1;
	data->x_a += -tmp;
	data->x_b += tmp;
	if (key == -5)
	{
		tmp = (data->x_b - data->x_a) / 2;
		data->x_a -=  tmp2 * tmp - data->mouse_x;
		data->x_b -=  tmp2 * tmp - data->mouse_x;
		data->mouse_x +=  tmp2 * tmp - data->mouse_x;
	}
	tmp2 = 2 * data->mouse_y / (data->y_b - data->y_a);
	tmp = (data->y_a - data->y_b) * 0.1;
	data->y_a += -tmp;
	data->y_b += tmp;
	if (key == -5)
	{
		tmp = (data->y_b - data->y_a) / 2;
		data->y_a -=  tmp2 * tmp - data->mouse_y;
		data->y_b -=  tmp2 * tmp - data->mouse_y;
		data->mouse_y +=  tmp2 * tmp - data->mouse_y;
	}
}

void			ft_zoom(int key, t_data *data)
{
	if ((key == -5 || key == 24 || key == 69) && data->zoom < 150)
	{
		if (data->iteration_max < 130)
			data->iteration_max++;
		data->zoom++;
		ft_zoom_in(key, data);
		data->step_x = (data->x_b - data->x_a) * 0.01;
		data->step_y = (data->y_b - data->y_a) * 0.01;
	}
	else if ((key == -4 || key == 27 || key == 78)
		&& (data->x_b - data->x_a) <= (0.6 + 2.1) * 2)
	{
		if (data->iteration_max > 21 && data->zoom + 20 < data->iteration_max)
			data->iteration_max--;
		data->zoom--;
		ft_zoom_out(data);
		data->step_x = (data->x_b - data->x_a) * 0.01;
		data->step_y = (data->y_b - data->y_a) * 0.01;
	}
	else
		return ;
}
