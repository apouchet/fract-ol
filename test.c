#include <stdio.h>
#include <math.h>
#include <fcntl.h>
#include <unistd.h>
// int		ft_calcul_mandelbrot(double z_r, double z_i, double c_r, double c_i, int max)
// {
// 	double tmp;
// 	double pow_r;
// 	double pow_i;
// 	int i;

// 	i = 0;
// 	tmp = z_r;
	
// 	z_r = z_r * z_r - z_i * z_i + c_r;
// 	z_i = 2 * z_i * tmp + c_i;
// 	pow_r = z_r * z_r;
// 	pow_i = z_i * z_i;
// 		// tmp = pow((pow(z_r, 2) - pow(z_i, 2) + c_r), 2) + pow((2 * z_r * z_i), 2);
// 		// if 
// 	while (pow_r + pow_i < 4 && ++i < max)
// 	{
// 		// i++;
// 		// i++;
// 		tmp = z_r;
// 		z_r = pow_r - pow_i + c_r;
// 		z_i = 2 * z_i * tmp + c_i;
// 		pow_r = z_r * z_r;
// 		pow_i = z_i * z_i;
// 	}
// 	return (i);
// }

// int	main()
// {
// 	int i = 0;

// 	for (int x = 0; x < 5; x++)
// 	{
// 		for (int y = 0; y < 5; y++)
// 		{
// 			i = ft_calcul_mandelbrot(0, 0, x, x, 20);
// 			printf("i = %d\n", i);
// 		}
// 	}
// 	return (0);
// }

// z_r = (z_r * z_r) - (z_i * z_i) + c_r;

// z_i = 2 * z_i * tmp + c_i;


// z_r = (z_r * z_r) - (z_i * z_i) + c_r;

int		main(void)
{
	int fd;

	fd = open("b.tga", O_WRONLY | O_APPEND | O_CREAT, 0644);
	return (0);
}


// int		ft_mandelbrot(t_data *d)
// {
// 	// mode 0 == normal
// 	// mode 1 == semi opti
// 	// mode 2 == opti
// 	int mode = 0;
// 	double zoom_x = FENETRE_X/((0.6 + 2.1) * d->zoom);
// 	double zoom_y = FENETRE_Y/((1.2 + 1.2) * d->zoom);
// 	int i;
// 	int x;
// 	int y;
// 	int x_step;
// 	int y_step;

// 	x = 0;
// 	x_step = (mode == 2 ? 2 : 1);
// 	y_step = (mode == 0 ? 1 : 2);
// 	while (x < FENETRE_X)
// 	{
// 		y = (mode == 1 ? x % 2 : 0);
// 		// y = 0;
// 		while (y < FENETRE_Y)
// 		{
// 			i = ft_calcul_mandelbrot(0, 0, (x / zoom_x - 2.1) * d->zoom,
// 				(y / zoom_y - 1.2) * d->zoom, d->iteration_max);
// 			if (i != d->iteration_max)
// 				d->img[d->p.sl * y + x] = ft_color(i, d->iteration_max);
// 			else
// 				d->img[d->p.sl * y + x] = 0;
// 			y += y_step;
// 		}
// 		x += x_step;
// 	}
// 	if (mode == 2)
// 		ft_mandelbrot_opti(d, 1, 1, zoom_x, zoom_y);
// 	if (mode > 0)
// 		ft_mandelbrot_semi_opti(d, 0, 0, zoom_x, zoom_y);
// 	// for (int x = 1; x < FENETRE_X; x += 2)
// 	// {
// 	// 	for (int y = 1; y < FENETRE_Y; y += 2)
// 	// 	{
// 	// 		if (x != 0 && y != 0 && x != FENETRE_X - 1 && y != FENETRE_Y - 1 && data->img[data->p.sl * (y - 1) + x - 1] == data->img[data->p.sl * (y - 1) + x + 1] && data->img[data->p.sl * (y + 1) + x - 1] == data->img[data->p.sl * (y + 1) + x + 1] && data->img[data->p.sl * (y - 1) + x + 1] == data->img[data->p.sl * (y + 1) + x + 1])
// 	// 		{
// 	// 			data->img[data->p.sl * y + x] = data->img[data->p.sl * (y - 1) + x + 1];
// 	// 		}
// 	// 		else
// 	// 		{
// 	// 			i = ft_calcul_mandelbrot(0, 0, (x / zoom_x - 2.1) * data->zoom, (y / zoom_y - 1.2) * data->zoom, data->iteration_max);
// 	// 			if (i != data->iteration_max)
// 	// 				data->img[data->p.sl * y + x] =  ft_color(i, data->iteration_max);
// 	// 			else
// 	// 				data->img[data->p.sl * y + x] = 0;
// 	// 		}
// 	// 	}
// 	// }
// 	// for (int x = 0; x < FENETRE_X; x++)
// 	// {
// 	// 	for (int y = (x + 1) % 2; y < FENETRE_Y; y += 2)
// 	// 	{
// 	// 		if (x != 0 && y != 0 && x != FENETRE_X - 1 && y != FENETRE_Y - 1 && data->img[data->p.sl * y + x - 1] == data->img[data->p.sl * y + x + 1] && data->img[data->p.sl * y + x - 1] == data->img[data->p.sl * (y - 1) + x] && data->img[data->p.sl * y + x + 1] == data->img[data->p.sl * (y - 1) + x])
// 	// 		{
// 	// 			data->img[data->p.sl * y + x] = data->img[data->p.sl * (y - 1) + x];
// 	// 		}
// 	// 		else
// 	// 		{
// 	// 			i = ft_calcul_mandelbrot(0, 0, (x / zoom_x - 2.1) * data->zoom, (y / zoom_y - 1.2) * data->zoom, data->iteration_max);
// 	// 			if (i != data->iteration_max)
// 	// 				data->img[data->p.sl * y + x] =  ft_color(i, data->iteration_max);
// 	// 			else
// 	// 				data->img[data->p.sl * y + x] = 0;
// 	// 		}
// 	// 	}
// 	// }
// 	mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, d->p_img, 0, 0);
// 	return (0);