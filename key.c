/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apouchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 14:31:32 by apouchet          #+#    #+#             */
/*   Updated: 2019/10/15 14:31:35 by apouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"

void	reset_data(t_data *data)
{
	data->zoom = 5;
	data->move_x = 0;
	data->move_y = 0;
	data->iteration_max = 20;
	data->mode = 0;
	data->fix = 0;
	data->x = 0;
	data->y = 0;
	data->x_a = -2.1;
	data->x_b = 0.6;
	data->y_a = -1.2;
	data->y_b = 1.2;
	data->div_q = 1;
	data->div = data->iteration_max / data->div_q;
}

int		ft_key(int key,	t_data *data)
{
	printf("key = %d\n", key);
	printf("iteration_max = %d\n", data->iteration_max);
	printf("zoom = %d\n", data->zoom);
	// printf("zr = %.100lf, zi = %.100lf\n", data->z_r, data->z_i);
	if (key == 35)
		ft_screen(data);
	if (key == 53)
		exit(0);
	
	if (key == 126)
	{
		data->y_a -= data->step_y;
		data->y_b -= data->step_y;
	}
	if (key == 125)
	{
		data->y_a += data->step_y;
		data->y_b += data->step_y;
	}
	if (key == 123)
	{
		data->x_a -= data->step_x;
		data->x_b -= data->step_x;
	}
	if (key == 124)
	{
		data->x_a += data->step_x;
		data->x_b += data->step_x;
	}

	if ((key == -4 || key == 27 || key == 78) && (data->x_b - data->x_a) <= (0.6 + 2.1) * 2) // touch -
	{
		if (data->iteration_max > 21 && data->zoom + 20 < data->iteration_max)
			data->iteration_max--;
		data->zoom--;
		double tmp;
		tmp = (((data->x_a - data->x_b) / (1 - (0.1 * 2))) - (data->x_a - data->x_b)) / 2;
		data->x_a -= -tmp;
		data->x_b -= tmp;

		tmp = (((data->y_a - data->y_b) / (1 - (0.1 * 2))) - (data->y_a - data->y_b)) / 2;
		data->y_a -= -tmp;
		data->y_b -= tmp;

		data->step_x = (data->x_b - data->x_a) * 0.01;
		data->step_y = (data->y_b - data->y_a) * 0.01;
	}
	if ((key == -5 || key == 24 || key == 69) && data->zoom < 150) // touch +
	{
		if (data->iteration_max < 130)
			data->iteration_max++;
		data->zoom++;
		double tmp;
		double tmp2;

			tmp2 = 2 * data->mouse_x / (data->x_b - data->x_a);
			tmp = (data->x_a - data->x_b);
			data->x_a += (data->x_b - data->x_a) * 0.1;
			data->x_b += tmp * 0.1;
			if (key == -5)
			{
				tmp = (data->x_b - data->x_a) / 2;
				data->x_a -=  tmp2 * tmp - data->mouse_x;
				data->x_b -=  tmp2 * tmp - data->mouse_x;
				data->mouse_x +=  tmp2 * tmp - data->mouse_x;
			}

			tmp2 = 2 * data->mouse_y / (data->y_b - data->y_a);
			tmp = (data->y_a - data->y_b);
			data->y_a += (data->y_b - data->y_a) * 0.1;
			data->y_b += tmp * 0.1;
			if (key == -5)
			{
				tmp = (data->y_b - data->y_a) / 2;
				data->y_a -=  tmp2 * tmp - data->mouse_y;
				data->y_b -=  tmp2 * tmp - data->mouse_y;
				data->mouse_y +=  tmp2 * tmp - data->mouse_y;
			}

			data->step_x = (data->x_b - data->x_a) * 0.01;
			data->step_y = (data->y_b - data->y_a) * 0.01;
	}
	if (key == 257)
		data->iteration_max += 1;
	if (key == 256 && data->iteration_max > 1)
		data->iteration_max -= 1;

	if (key == 18)
		data->mode = 0;
	if (key == 19)
		data->mode = 1;
	if (key == 20)
		data->mode = 2;
	if (key == 21)
		data->mode = 3;
	if (key == 22 && data->fract != 0)
	{
		data->fract = 0;
		data->x_a = -2.1;
		data->x_b = 0.6;
		data->y_a = -1.2;
		data->y_b = 1.2;
	}
	if (key == 23  && data->fract != 1)
	{
		data->fract = 1;
		data->x_a = -1.5;
		data->x_b = 1.5;
		data->y_a = -1.2;
		data->y_b = 1.2;
	}

	if (key == 8 && data->div_q < data->iteration_max)
	{
		data->div_q++;
		data->div = data->iteration_max / data->div_q;
	}
	if (key == 9 && data->div_q > 1)
	{
		data->div_q--;
		data->div = data->iteration_max / data->div_q;
	}

	if (key == 15)
		reset_data(data);
	ft_affich(data);
	return (1);
}
