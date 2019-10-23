/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floblanc <floblanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 14:31:35 by apouchet          #+#    #+#             */
/*   Updated: 2019/10/23 14:51:16 by floblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"

int		mouse_release_hook(int x, int y, t_fract *f)
{
	static int	x_prec;
	static int	y_prec;
	double		tmp;

	if (f->mouse_button == 1 && f->fix)
	{
		tmp = (x - x_prec) / (FENETRE_X / (f->x_b - f->x_a));
		f->x_a -= (x - x_prec) / (FENETRE_X / (f->x_b - f->x_a));
		f->x_b -= tmp;
		tmp = (y - y_prec) / (FENETRE_Y / (f->y_b - f->y_a));
		f->y_a -= (y - y_prec) / (FENETRE_Y / (f->y_b - f->y_a));
		f->y_b -= tmp;
	}
	x_prec = x;
	y_prec = y;
	if (f->mouse_button == 2 || !(f->fix))
	{
		f->c_r = (x - FENETRE_X / 2) / (FENETRE_X / (f->x_b - f->x_a));
		f->c_i = (y - FENETRE_Y / 2) / (FENETRE_Y / (f->y_b - f->y_a));
	}
	f->mouse_x = (x - FENETRE_X / 2) / (FENETRE_X / (f->x_b - f->x_a));
	f->mouse_y = (y - FENETRE_Y / 2) / (FENETRE_Y / (f->y_b - f->y_a));
	return (0);
}

int		mouse_hook(int button, int x, int y, t_fract *fract)
{
	x++;
	y++;
	fract->mouse_button = button;
	if (button == 5 || button == 4)
		ft_key(-button, fract);
	return (0);
}

int		mouse_release(int button, int x, int y, t_fract *fract)
{
	x++;
	y++;
	button++;
	fract->mouse_button = 0;
	return (0);
}
