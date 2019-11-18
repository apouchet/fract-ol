/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_opti.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apouchet <apouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 16:35:57 by apouchet          #+#    #+#             */
/*   Updated: 2019/11/18 15:36:17 by apouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"

static int	ft_check_opti(t_fract *f, int x, int y, int type)
{
	int sl;

	sl = f->p.sl;
	if (type == 0)
		return (x != 0 && y != 0 && x != FENETRE_X - 1 && y != FENETRE_Y - 1
				&& f->img[sl * y + x - 1] == f->img[sl * (y - 1) + x]
				&& f->img[sl * y + x - 1] == f->img[sl * (y + 1) + x]
				&& f->img[sl * y + x - 1] == f->img[sl * y + x + 1]);
	else if (type == 1)
		return (x != 0 && y != 0 && x != FENETRE_X - 1 && y != FENETRE_Y - 1
				&& f->img[sl * (y - 1) + x - 1] == f->img[sl * (y - 1) + x + 1]
				&& f->img[sl * (y - 1) + x - 1] == f->img[sl * (y + 1) + x + 1]
				&& f->img[sl * (y - 1) + x - 1]
				== f->img[sl * (y + 1) + x - 1]);
	else if (type == 2)
		return (x != 0 && y != 0 && x < FENETRE_X - 2 && y < FENETRE_Y - 2
				&& f->img[sl * (y - 2) + x - 2] == f->img[sl * (y - 2) + x + 2]
				&& f->img[sl * (y - 2) + x - 2] == f->img[sl * (y + 2) + x + 2]
				&& f->img[sl * (y - 2) + x - 2]
				== f->img[sl * (y + 2) + x - 2]);
	else
		return (x != 0 && y != 0 && x < FENETRE_X - 2 && y < FENETRE_Y - 2
				&& f->img[sl * y + x - 2] == f->img[sl * (y - 2) + x]
				&& f->img[sl * y + x - 2] == f->img[sl * (y + 2) + x]
				&& f->img[sl * y + x - 2] == f->img[sl * y + x + 2]);
}

static void	ft_mdb_julia_over_opti2(t_fract *f)
{
	int x;
	int y;

	x = 0;
	while (x < FENETRE_X)
	{
		y = 2 - (x % 4);
		while (y < FENETRE_Y)
		{
			if (ft_check_opti(f, x, y, 3))
				f->img[f->p.sl * y + x] = f->img[f->p.sl * y + x - 2];
			else
				f->img[f->p.sl * y + x] = select_calc(f, x, y);
			y += 4;
		}
		x += 2;
	}
}

static void	ft_mdb_julia_over_opti(t_fract *f)
{
	int x;
	int y;

	x = 2;
	while (x < FENETRE_X)
	{
		y = 2;
		while (y < FENETRE_Y)
		{
			if (f->mode == 4 && ft_check_opti(f, x, y, 2))
				f->img[f->p.sl * y + x] = f->img[f->p.sl * (y - 2) + x - 2];
			else
				f->img[f->p.sl * y + x] = select_calc(f, x, y);
			y += 4;
		}
		x += 4;
	}
	ft_mdb_julia_over_opti2(f);
}

static void	ft_mdb_julia_opti(t_fract *f)
{
	int x;
	int y;

	x = 1;
	if (f->mode == 3 || f->mode == 4)
		ft_mdb_julia_over_opti(f);
	while (x < FENETRE_X)
	{
		y = 1;
		while (y < FENETRE_Y)
		{
			if (ft_check_opti(f, x, y, 1))
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

	if (f->mode == 2 || f->mode == 3 || f->mode == 4)
		ft_mdb_julia_opti(f);
	x = 0;
	while (x < FENETRE_X)
	{
		y = ((x + 1) % 2);
		while (y < FENETRE_Y)
		{
			if (ft_check_opti(f, x, y, 0))
				f->img[f->p.sl * y + x] = f->img[f->p.sl * (y - 1) + x];
			else
				f->img[f->p.sl * y + x] = select_calc(f, x, y);
			y += 2;
		}
		x++;
	}
}
