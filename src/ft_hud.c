/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hud.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floblanc <floblanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 14:32:06 by floblanc          #+#    #+#             */
/*   Updated: 2019/11/01 18:31:49 by floblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"

static void	ft_put(t_fract *fract, int x, int y, char *str)
{
	mlx_string_put(fract->mlx_ptr, fract->win_ptr, x, y, W, str);
}

static void	ft_hud_info(t_fract *fract)
{
	ft_put(fract, 5, FENETRE_Y - 88, "Mandelbrot: 1");
	ft_put(fract, 5, FENETRE_Y - 71, "Julia: 2");
	ft_put(fract, 5, FENETRE_Y - 54, "Burning Ship: 3");
	ft_put(fract, 5, FENETRE_Y - 37, "Burning Julia: 4");
	ft_put(fract, 5, FENETRE_Y - 20, "Newton: 5");
	ft_put(fract, FENETRE_X - 275, FENETRE_Y - 207, "Controls");
	ft_put(fract, FENETRE_X - 465, FENETRE_Y - 190
	, "Swap Mlx/Open GL: enter/return");
	ft_put(fract, FENETRE_X - 465, FENETRE_Y - 173, "Reset: r");
	ft_put(fract, FENETRE_X - 465, FENETRE_Y - 156,
		"Zoom: w/s or +/- or point and scroll");
	ft_put(fract, FENETRE_X - 465, FENETRE_Y - 139, "Accuracy: a/d");
	ft_put(fract, FENETRE_X - 465, FENETRE_Y - 122, "Screenshot: p");
	ft_put(fract, FENETRE_X - 465, FENETRE_Y - 105, "Convert to .fdf: f");
	ft_put(fract, FENETRE_X - 465, FENETRE_Y - 88,
		"Opti rank: none/semi/full/over: 7, 8, 9, 0");
	ft_put(fract, FENETRE_X - 465, FENETRE_Y - 71, "Change color: c/v");
	ft_put(fract, FENETRE_X - 465, FENETRE_Y - 54, "Thread number: q/e");
	ft_put(fract, FENETRE_X - 465, FENETRE_Y - 37,
		"Move: Arrows or Left clic + Mouse");
	if (fract->fract == 1 || fract->fract == 3)
		ft_put(fract, FENETRE_X - 465, FENETRE_Y - 20,
			"Unlock Mouvements: Space or Right clic pressed");
}

void		ft_hud(t_fract *fract)
{
	char *tmp;

	if (fract->info)
	{
		ft_put(fract, FENETRE_X - 250, 10, "Press i for informations");
		tmp = ft_itoa(fract->iteration_max);
		ft_put(fract, 5, 5, "Accuracy:");
		ft_put(fract, 100, 5, tmp);
		ft_strdel(&tmp);
		tmp = ft_itoa(fract->nb_thread);
		ft_put(fract, 5, 22, "Thread number:");
		ft_put(fract, 150, 22, tmp);
		ft_strdel(&tmp);
		ft_put(fract, 5, 39, "Opti rank:");
		if (fract->mode == 0)
			ft_put(fract, 110, 39, "none");
		else if (fract->mode == 1)
			ft_put(fract, 110, 39, "semi");
		else if (fract->mode == 2)
			ft_put(fract, 110, 39, "full");
		else if (fract->mode == 3)
			ft_put(fract, 110, 39, "over");
	}
	if (fract->info == 2)
		ft_hud_info(fract);
}
