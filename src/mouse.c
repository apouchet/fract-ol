/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floblanc <floblanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 14:31:35 by apouchet          #+#    #+#             */
/*   Updated: 2019/10/16 13:44:56 by floblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"

int		mouse_release_hook(int x, int y, t_fract *data)
{
	static int x_prec;
	static int y_prec;
	double tmp;

	if (data->mouse_button == 1)
	{
		tmp = (x - x_prec) / (FENETRE_X / (data->x_b - data->x_a));
		data->x_a -= (x - x_prec) / (FENETRE_X / (data->x_b - data->x_a));
		data->x_b -= tmp;
		tmp = (y - y_prec) / (FENETRE_Y / (data->y_b - data->y_a));
		data->y_a -= (y - y_prec) / (FENETRE_Y / (data->y_b - data->y_a));
		data->y_b -= tmp;
	}
	x_prec = x;
	y_prec = y;
	if (data->mouse_button == 2)
	{
		data->c_r = (x - FENETRE_X / 2) / (FENETRE_X / (data->x_b - data->x_a));
		data->c_i = (y - FENETRE_Y / 2) / (FENETRE_Y / (data->y_b - data->y_a));
	}
	data->mouse_x = (x - FENETRE_X / 2) / (FENETRE_X / (data->x_b - data->x_a));
	data->mouse_y = (y - FENETRE_Y / 2) / (FENETRE_Y / (data->y_b - data->y_a));
	return (0);
}


int		mouse_hook(int button, int x, int y, t_fract *data)
{
	// if (button == 1)
	// printf("button = %d\n", button);
	// printf("x = %d, y = %d\n", x, y);
	x++;
	y++;
	data->mouse_button = button;
	if (button == 5 || button == 4)
		ft_key(-button, data);
	return (0);
}

int		mouse_release(int button, int x, int y, t_fract *data)
{
	x++;
	y++;
	button++;
	data->mouse_button = 0;
	return (0);
}
