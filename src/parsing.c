/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floblanc <floblanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 12:24:48 by floblanc          #+#    #+#             */
/*   Updated: 2019/10/16 18:35:37 by floblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"

int		parsing(t_fract *fract, int ac, char **av)
{
	if (ac < 2)
		return (0);
	if (!(ft_strcmp("Mandelbrot", av[1])))
		fract->fract = 0;
	else if (!(ft_strcmp("Julia", av[1])))
		fract->fract = 1;
	else
		return (0);
	return (1);
}