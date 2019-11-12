/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_control_gl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apouchet <apouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 18:40:39 by apouchet          #+#    #+#             */
/*   Updated: 2019/11/12 18:07:36 by apouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl.h"

static void		ft_send_data(t_gl *gl, t_gldata *data, int color)
{
	unsigned int matloc;

	matloc = glGetUniformLocation(gl->program_id, "MaxIterations");
	glUniform1f(matloc, data->max_it);
	matloc = glGetUniformLocation(gl->program_id, "zoom");
	glUniform1f(matloc, data->zoom);
	matloc = glGetUniformLocation(gl->program_id, "x");
	glUniform1f(matloc, data->x);
	matloc = glGetUniformLocation(gl->program_id, "y");
	glUniform1f(matloc, data->y);
	matloc = glGetUniformLocation(gl->program_id, "c_r");
	glUniform1f(matloc, data->c_r);
	matloc = glGetUniformLocation(gl->program_id, "c_i");
	glUniform1f(matloc, data->c_i);
	matloc = glGetUniformLocation(gl->program_id, "fractal");
	glUniform1f(matloc, data->fractal);
	matloc = glGetUniformLocation(gl->program_id, "color_switch");
	glUniform1f(matloc, color);
	matloc = glGetUniformLocation(gl->program_id, "info");
	glUniform1f(matloc, data->info);
}

static void		ft_color_fractal(t_gl *gl, t_gldata *data)
{
	static int	color = 0;
	int			fract_pre;

	fract_pre = data->fractal;
	if (glfwGetKey(gl->w, GLFW_KEY_R) == GLFW_PRESS)
		color = 0;
	else if (glfwGetKey(gl->w, GLFW_KEY_B) == GLFW_PRESS)
		color = 1;
	else if (glfwGetKey(gl->w, GLFW_KEY_G) == GLFW_PRESS)
		color = 2;
	else if (glfwGetKey(gl->w, GLFW_KEY_1) || glfwGetKey(gl->w, GLFW_KEY_KP_1))
		data->fractal = 0;
	else if (glfwGetKey(gl->w, GLFW_KEY_2) || glfwGetKey(gl->w, GLFW_KEY_KP_2))
		data->fractal = 1;
	else if (glfwGetKey(gl->w, GLFW_KEY_3) || glfwGetKey(gl->w, GLFW_KEY_KP_3))
		data->fractal = 2;
	else if (glfwGetKey(gl->w, GLFW_KEY_4) || glfwGetKey(gl->w, GLFW_KEY_KP_4))
		data->fractal = 3;
	else if (glfwGetKey(gl->w, GLFW_KEY_5) || glfwGetKey(gl->w, GLFW_KEY_KP_5))
		data->fractal = 4;
	if (fract_pre != data->fractal || glfwGetKey(gl->w, GLFW_KEY_SPACE))
		ft_init_data(data, NULL, gl);
	ft_send_data(gl, data, color);
}

static void		ft_mouse_info(t_gl *gl, t_gldata *data)
{
	static double	x_prec;
	static double	y_prec;
	static double	x;
	static double	y;
	static int		key = 0;

	if (glfwGetMouseButton(gl->w, GLFW_MOUSE_BUTTON_1))
	{
		glfwGetCursorPos(gl->w, &x, &y);
		data->x -= (x - x_prec) * data->step / 3.2;
		data->y -= (y - y_prec) * data->step / 3.2;
	}
	else if (glfwGetMouseButton(gl->w, GLFW_MOUSE_BUTTON_2))
	{
		glfwGetCursorPos(gl->w, &data->c_r, &data->c_i);
		data->c_r = (data->c_r - FENETRE_X / 2) / (FENETRE_X / 2);
		data->c_i = (data->c_i - FENETRE_X / 2) / (FENETRE_X / 2);
	}
	glfwGetCursorPos(gl->w, &x_prec, &y_prec);
	if (key == 0 && glfwGetKey(gl->w, GLFW_KEY_I))
			data->info = (data->info + 1) % 2;
	key = glfwGetKey(gl->w, GLFW_KEY_I);
}

static void		ft_move_zoom(t_gl *gl, t_gldata *data)
{
	if ((data->nb_zoom > 0 || (data->nb_zoom > -1000 && data->fractal == 4))
		&& glfwGetKey(gl->w, GLFW_KEY_S))
	{
		data->zoom = data->zoom * 1.01;
		data->step *= 1.01;
		data->nb_zoom--;
	}
	else if (data->nb_zoom < 1200 && glfwGetKey(gl->w, GLFW_KEY_W))
	{
		data->zoom = data->zoom / 1.01;
		data->step /= 1.01;
		data->nb_zoom++;
	}
	else if (glfwGetKey(gl->w, GLFW_KEY_LEFT))
		data->x = data->x - data->step;
	else if (glfwGetKey(gl->w, GLFW_KEY_RIGHT))
		data->x = data->x + data->step;
	else if (glfwGetKey(gl->w, GLFW_KEY_UP))
		data->y = data->y - data->step;
	else if (glfwGetKey(gl->w, GLFW_KEY_DOWN))
		data->y = data->y + data->step;
}

void			ft_control(t_gl *gl, t_gldata *data)
{
	char		*buf;
	static int	tmp_info;

	if (glfwGetKey(gl->w, GLFW_KEY_D))
	{
		ft_printf("MaxIterations = %f\n", data->max_it);
		data->max_it++;
	}
	else if (data->max_it > 2
		&& glfwGetKey(gl->w, GLFW_KEY_A))
	{
		ft_printf("MaxIterations = %f\n", data->max_it);
		data->max_it--;
	}
	else if (glfwGetKey(gl->w, GLFW_KEY_P) || data->info == -1)
	{
		if (data->info >= 0)
		{
			tmp_info = data->info;
			data->info = -1;
		}
		else
		{
			buf = (char*)malloc(sizeof(char) * (FENETRE_X * FENETRE_X * 3));
			glReadPixels(0, 0, FENETRE_X, FENETRE_X, GL_BGR, GL_UNSIGNED_BYTE, buf);
			ft_screen_gl(buf);
			free(buf);
			data->info = tmp_info;
		}
	}
	ft_mouse_info(gl, data);
	ft_move_zoom(gl, data);
	ft_color_fractal(gl, data);
	if (glfwGetKey(gl->w, GLFW_KEY_ENTER))
		data->exit = 1;
}