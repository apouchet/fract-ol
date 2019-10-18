/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opengl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apouchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 13:39:00 by apouchet          #+#    #+#             */
/*   Updated: 2019/10/17 13:39:04 by apouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl.h"


int		ft_init_glfw_gl(t_gl *gl)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1); 
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	gl->window = glfwCreateWindow(1500, 1286, "OpenGL", NULL, NULL);
	glfwMakeContextCurrent(gl->window);
	if (!(gl->window)) 
	{
		dprintf(2, "Error while opening windows\n");
		glfwTerminate();
		return (-1);
	}
	glewExperimental = GL_TRUE;
	glewInit();
	printf("OpenGL version: %s\n", glGetString(GL_VERSION));
	printf("Shader version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	return (ft_shaders("shader.vs", "shader.fs", gl));
}

void	ft_gl_buffer(t_gl *gl)
{
	float points[] = {
	1.0f,  1.0f,  0.0f,
	-1.0f,  1.0f,  0.0f,
	-1.0f, -1.0f,  0.0f,
	1.0f, -1.0f,  0.0f
	};

	gl->vbo = 0;
	gl->vao = 0;
	glGenBuffers(1, &gl->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, gl->vbo);
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), points, GL_STATIC_DRAW);

	glGenVertexArrays(1, &gl->vao);
	glBindVertexArray(gl->vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, gl->vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

}

void	ft_control(t_gl *gl, t_gldata *data)
{
	if (data->nb_zoom > 0 && glfwGetKey(gl->window, GLFW_KEY_A) == GLFW_PRESS)
	{
		data->zoom = data->zoom * 1.01;
		data->step *= 1.01;
		data->nb_zoom--;
	}
	if (data->nb_zoom < 1200 && glfwGetKey(gl->window, GLFW_KEY_S) == GLFW_PRESS)
	{
		data->zoom = data->zoom / 1.01;
		data->step /= 1.01;
		data->nb_zoom++;
	}
	if (glfwGetKey(gl->window, GLFW_KEY_LEFT) == GLFW_PRESS)
		data->x = data->x - data->step;
	if (glfwGetKey(gl->window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		data->x = data->x + data->step;
	if (glfwGetKey(gl->window, GLFW_KEY_UP) == GLFW_PRESS)
		data->y = data->y + data->step;
	if (glfwGetKey(gl->window, GLFW_KEY_DOWN) == GLFW_PRESS)
		data->y = data->y - data->step;
	if (glfwGetKey(gl->window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		printf("MaxIterations = %f\n", data->maxIt);
		data->maxIt++;
	}
	if (data->maxIt > 2 && glfwGetKey(gl->window, GLFW_KEY_W) == GLFW_PRESS)
	{
		printf("MaxIterations = %f\n", data->maxIt);
		data->maxIt--;
	}
	if (glfwGetKey(gl->window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		if (glfwGetKey(gl->window, GLFW_KEY_SPACE) == GLFW_RELEASE)
		data->mouse = (data->mouse + 1) % 2;
		printf("mouse = %d\n", data->mouse);
	}
	glfwGetCursorPos(gl->window, &data->c_r, &data->c_i);
	data->c_r = (data->c_r - 1500 / 2) / (1500 / 2);
	data->c_i = (data->c_i - 1286 / 2) / (1286 / 2);
	printf("c_r = %lf, c_i = %lf\n", data->c_r, data->c_i);
	// printf("zoom = %f\n", *zoom);
	// printf("x = %f\n", *y);
	// printf("y = %f\n", *x);
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
	glUniform1f(matloc, 1);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// printf("key = %d, scancode = %d, action = %d, mods = %d\n", key, scancode, action, mods);
}

int main()
{
	t_gl gl;
	t_gldata data;

	if (ft_init_glfw_gl(&gl) < 0)
		return (-1);
	ft_gl_buffer(&gl);
	data.maxIt = 100.0f;
	data.zoom = 2.0f;
	data.x = 0;
	data.y = 0;
	data.step = 0.01;
	data.nb_zoom = 2;
	data.mouse = 0;
	while(glfwGetKey(gl.window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(gl.window))
	{
		glUseProgram(gl.program_id);
		glfwSetKeyCallback(gl.window, key_callback);
		ft_control(&gl, &data);
		glBindVertexArray(gl.vao);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
		glfwPollEvents();
		glfwSwapBuffers(gl.window);
	}
	glfwTerminate();
	return (0);
}

// gcc -I ~/.brew/include/ -L/Users/apouchet/.brew/lib -lglfw -lglew -framework AppKit -framework OpenGl opengl.c ft_shader_opengl.c file.c
