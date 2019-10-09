#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>


#define FENETRE_X 1500
#define FENETRE_Y 1286
#define R 0x00FF0000
#define G 0x0000FF00
#define B 0x000000FF

typedef struct	s_picture
{
	int			bpp;
	int			s_l;
	int			endian;
}				t_picture;

typedef struct	s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*p_image;
	int			*image;
	double		zoom;
	double		move_x;
	double		move_y;
	int			scale;
	t_picture	p;
}				t_data;

int		ft_calcul_mandelbrot(double z_r, double z_i, double c_r, double c_i, int max)
{
	double tmp;
	double pow_r;
	double pow_i;
	int i;

	i = 0;
	tmp = z_r;
	
	z_r = z_r * z_r - z_i * z_i + c_r;
	z_i = 2 * z_i * tmp + c_i;
	pow_r = z_r * z_r;
	pow_i = z_i * z_i;
	while (pow_r + pow_i < 4 && ++i < max)
	{
		tmp = z_r;
		z_r = pow_r - pow_i + c_r;
		z_i = 2 * z_i * tmp + c_i;
		pow_r = z_r * z_r;
		pow_i = z_i * z_i;
	}
	return (i);
}

int		ft_color(int i, int len)
{
	int color;

	if (i <= len / 6)
		color = B + R - ((R * i * 6 / len) & R);
	else if (i <= len / 3)
		color = B + ((G * i * 3 / len) & G);
	else if (i <= len / 2)
		color = G + B - ((B * i * 2 / len) & 2);
	else if (i <= 2 * len / 3)
		color = G + ((R * (1 - i * 2 / len)) & R);
	else if (i <= 5 * len / 6)
		color = R + G - ((G * (1 - i  * 3 / len)) & G);
	else
		color = R + ((B * (1 - i * 6 / len)) & B);
	return(color);
}

int		ft_mandelbrot(t_data *data)
{
	int iteration_max = 20 + data->scale;
	double c_r;
	double c_i;
	int i;
	// on calcule la taille de l'image :
	double zoom_x = FENETRE_X/((0.6 + 2.1) * data->zoom);
	double zoom_y = FENETRE_Y/((1.2 + 1.2) * data->zoom);
	
	if (i > iteration_max)
		data->c = 0;
	for (int x = 0; x < FENETRE_X; x++)
	{
		for (int y = 0; y < FENETRE_Y; y++)
		{
			// c_r = (x / zoom_x - 2.1) * data->zoom ;//+ data->move_x * data->zoom;
			// c_i = (y / zoom_y - 1.2) * data->zoom ;//+ data->move_y * data->zoom;
			i = ft_calcul_mandelbrot(0, 0, (x / zoom_x - 2.1) * data->zoom, (y / zoom_y - 1.2) * data->zoom, iteration_max);
			if (i != iteration_max)
				data->image[data->p.s_l * y + x] =  ft_color(i, iteration_max);
			else
				data->image[data->p.s_l * y + x] = 0;
		}
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->p_image, 0, 0);
	return (0);
}

int		ft_key(int key,	t_data *data)
{
	printf("key = %d\n", key);
	if (key == 53)
		exit(0);
	if (key == 126)
		data->move_y -= 0.1;
	if (key == 125)
		data->move_y += 0.1;
	if (key == 123)
		data->move_x -= 0.1;
	if (key == 124)
		data->move_x += 0.1;
	if (key == 78)
		data->zoom *= 1.1;
	if (key == 69)
		data->zoom *= 0.9;
	if (key == 83)
		data->scale++;
	if (key == 82)
		data->scale--;
	ft_mandelbrot(data);
	return (1);
}

int		main(int argc, char **argv)
{
	t_data		data;

	data.mlx_ptr = mlx_init();
	data.win_ptr = mlx_new_window(data.mlx_ptr, FENETRE_X, FENETRE_Y, "mlx");
	data.p_image = mlx_new_image(data.mlx_ptr, FENETRE_X, FENETRE_Y);
	data.image = (int*)mlx_get_data_addr(data.p_image, &data.p.bpp, &data.p.s_l, &data.p.endian);
	data.p.bpp /= 4;
	data.p.s_l /= 4;
	data.zoom = 1;
	data.move_x = 0;
	data.move_y = 0;
	data.scale = 0;
	// ft_base(argv[1], &val);
	// mlx_hook(val.mlx[1], 2, 0, &ft_key_on, &val);
	mlx_hook(data.win_ptr, 2, 0, &ft_key, &data);
	mlx_loop_hook(data.mlx_ptr, &ft_mandelbrot, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}

// -lmlx -framework OpenGL -framework AppKit
// man /usr/share/man/man3/