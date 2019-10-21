/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_control_gl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apouchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 18:40:39 by apouchet          #+#    #+#             */
/*   Updated: 2019/10/21 02:59:41 by apouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl.h"

static void		ft_send_data(t_gl *gl, t_gldata *data, int color)
{
	unsigned int matloc;

	matloc = glGetUniformLocation(gl->program_id, "MaxIterations");
	glUniform1f(matloc, data->maxIt);
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
}

static void		ft_color_fractal(t_gl *gl, t_gldata *data)
{
	static int color = 0;

	if (glfwGetKey(gl->window, GLFW_KEY_R) == GLFW_PRESS)
		color = 0;
	else if (glfwGetKey(gl->window, GLFW_KEY_B) == GLFW_PRESS)
		color = 1;
	else if (glfwGetKey(gl->window, GLFW_KEY_G) == GLFW_PRESS)
		color = 2;
	else if (glfwGetKey(gl->window, GLFW_KEY_1) == GLFW_PRESS)
		data->fractal = 0;
	else if (glfwGetKey(gl->window, GLFW_KEY_2) == GLFW_PRESS)
		data->fractal = 1;
	else if (glfwGetKey(gl->window, GLFW_KEY_3) == GLFW_PRESS)
		data->fractal = 2;
	else if (glfwGetKey(gl->window, GLFW_KEY_4) == GLFW_PRESS)
		data->fractal = 3;
	if (glfwGetKey(gl->window, GLFW_KEY_1) == GLFW_PRESS 
		|| glfwGetKey(gl->window, GLFW_KEY_2) == GLFW_PRESS
		|| glfwGetKey(gl->window, GLFW_KEY_3) == GLFW_PRESS
		|| glfwGetKey(gl->window, GLFW_KEY_4) == GLFW_PRESS
		|| glfwGetKey(gl->window, GLFW_KEY_SPACE) == GLFW_PRESS)
		ft_init_data(data, NULL, gl);
	ft_send_data(gl, data, color);
}

static void		ft_mouse(t_gl *gl, t_gldata *data)
{
	static double x_prec;
	static double y_prec;
	static double x;
	static double y;

	if (glfwGetMouseButton(gl->window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
	{
		glfwGetCursorPos(gl->window, &x, &y);
		data->x -= (x - x_prec) * data->step / 3.2;
		data->y += (y - y_prec) * data->step / 3.2;
	}
	else if (glfwGetMouseButton(gl->window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS)
	{
		glfwGetCursorPos(gl->window, &data->c_r, &data->c_i);
		data->c_r = (data->c_r - FENETRE_X / 2) / (FENETRE_X / 2);
		data->c_i = (data->c_i - FENETRE_X / 2) / (FENETRE_X / 2);
	}
	glfwGetCursorPos(gl->window, &x_prec, &y_prec);
		printf("data->c_r = %lf, data->c_i = %lf\n", data->c_r, data->c_i);
}

static void		ft_move_zoom(t_gl *gl, t_gldata *data)
{
	if (data->nb_zoom > 0 && glfwGetKey(gl->window, GLFW_KEY_S) == GLFW_PRESS)
	{
		data->zoom = data->zoom * 1.01;
		data->step *= 1.01;
		data->nb_zoom--;
	}
	else if (data->nb_zoom < 1200
		&& glfwGetKey(gl->window, GLFW_KEY_W) == GLFW_PRESS)
	{
		data->zoom = data->zoom / 1.01;
		data->step /= 1.01;
		data->nb_zoom++;
	}
	else if (glfwGetKey(gl->window, GLFW_KEY_LEFT) == GLFW_PRESS)
		data->x = data->x - data->step;
	else if (glfwGetKey(gl->window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		data->x = data->x + data->step;
	else if (glfwGetKey(gl->window, GLFW_KEY_UP) == GLFW_PRESS)
		data->y = data->y - data->step;
	else if (glfwGetKey(gl->window, GLFW_KEY_DOWN) == GLFW_PRESS)
		data->y = data->y + data->step;
}

void		ft_control(t_gl *gl, t_gldata *data)
{
	if (glfwGetKey(gl->window, GLFW_KEY_D) == GLFW_PRESS)
	{
		ft_printf("MaxIterations = %f\n", data->maxIt);
		data->maxIt++;
	}
	else if (data->maxIt > 2
		&& glfwGetKey(gl->window, GLFW_KEY_A) == GLFW_PRESS)
	{
		ft_printf("MaxIterations = %f\n", data->maxIt);
		data->maxIt--;
	}
	ft_mouse(gl, data);
	ft_move_zoom(gl, data);
	ft_color_fractal(gl, data);
	if (glfwGetKey(gl->window, GLFW_KEY_ENTER) == GLFW_PRESS)
		data->exit = 1;
}
