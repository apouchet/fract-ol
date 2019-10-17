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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <strings.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

typedef struct		s_gl
{
	GLuint			vertex_id;
	GLuint			fragment_id;
	GLuint			program_id;
	GLint			attribute_id;
	GLint			log_size;
	GLchar			*log;
}					t_gl;

typedef struct		s_shd
{
	GLchar			*vertex_s;
	GLchar			*fragment_s;
	GLint			program_state;
	GLint			vertex_size;
	GLint			fragment_size;
}					t_shd;

int		ft_size_file(char *name)
{
	int		fd;
	int		rd;
	long	len;
	char	buff[1001];

	len = 0;
	if ((fd = open(name, O_RDONLY)) < 0)
		return (-1);
	while ((rd = read(fd, buff, 1000)) > 0)
		len += rd;
	close(fd);
	return (rd < 0 ? rd : len);
}

char	*ft_get_file(char *name, char *file)
{
	int		fd;
	int		rd;
	int		j;

	if (!(file = (char*)malloc(ft_size_file(name) + 1)) ||
		(fd = open(name, O_RDONLY)) < 0)
		return (NULL);
	j = 0;
	while ((rd = read(fd, &file[j], 1000)) > 0)
		j += rd;
	file[j] = '\0';
	close(fd);
	if (rd < 0)
		return (NULL);
	return (file);
}

int				ft_delete_shader(t_gl *gl)
{
	glUseProgram(0);
	glDetachShader(gl->program_id, gl->fragment_id);
	glDetachShader(gl->program_id, gl->vertex_id);
	glDeleteProgram(gl->program_id);
	glDeleteShader(gl->fragment_id);
	glDeleteShader(gl->vertex_id);
	return (-1);
}

static int		ft_check_shader_compilation(GLuint shader_id, t_gl *gl)
{
	GLint compilation_status;

	compilation_status = 0;
	glGetShaderiv(gl->vertex_id, GL_COMPILE_STATUS, &compilation_status);
	if (compilation_status != GL_TRUE)
	{
		glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &gl->log_size);
		if (!(gl->log = (GLchar*)malloc(gl->log_size)))
		{
			printf("Error malloc for log of shader compilation\n");
			return (0);
		}
		glGetShaderInfoLog(shader_id, gl->log_size, &gl->log_size, gl->log);
		printf("Compilation error :\n%s", gl->log);
		free(gl->log);
		return (0);
	}
	return (1);
}

int				ft_shader_start(t_gl *gl, t_shd *shd)
{
	shd->vertex_size = strlen(shd->vertex_s);
	shd->fragment_size = strlen(shd->fragment_s);
	glShaderSource(gl->vertex_id, 1, (const GLchar**)(&shd->vertex_s),
		&shd->vertex_size);
	glShaderSource(gl->fragment_id, 1, (const GLchar**)(&shd->fragment_s),
		&shd->fragment_size);
	glCompileShader(gl->vertex_id);
	glCompileShader(gl->fragment_id);
	if (!ft_check_shader_compilation(gl->vertex_id, gl)
		|| !ft_check_shader_compilation(gl->fragment_id, gl))
		return (ft_delete_shader(gl));
	gl->program_id = glCreateProgram();
	glAttachShader(gl->program_id, gl->vertex_id);
	glAttachShader(gl->program_id, gl->fragment_id);
	glLinkProgram(gl->program_id);
	glGetProgramiv(gl->program_id, GL_LINK_STATUS, &shd->program_state);
	free(shd->vertex_s);
	free(shd->fragment_s);
	return (1);
}

int				ft_shaders(char *name_vs, char *name_fs, t_gl *gl)
{
	t_shd	shd;

	bzero(&shd, sizeof(t_shd));
	gl->vertex_id = glCreateShader(GL_VERTEX_SHADER);
	gl->fragment_id = glCreateShader(GL_FRAGMENT_SHADER);
	if (!(shd.vertex_s = (GLchar*)ft_get_file(name_vs, shd.vertex_s)) ||
		!(shd.fragment_s = (GLchar*)ft_get_file(name_fs, shd.fragment_s)))
		return (ft_delete_shader(gl));
	if (ft_shader_start(gl, &shd) < 0)
		return (-1);
	if (shd.program_state != GL_TRUE)
	{
		glGetProgramiv(gl->program_id, GL_INFO_LOG_LENGTH, &gl->log_size);
		if (!(gl->log = (GLchar*)malloc(gl->log_size)))
		{
			printf("Error malloc for log of program compilation\n");
			return (ft_delete_shader(gl));
		}
		glGetProgramInfoLog(gl->program_id, gl->log_size,
			&gl->log_size, gl->log);
		printf("Erreur lors du liage du shader:\n%s", gl->log);
		free(gl->log);
		return (ft_delete_shader(gl));
	}
	return (0);
}

void	ft_control(GLFWwindow* window, float *zoom, float *x, float *y)
{
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		*zoom = *zoom * 1.01;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		*zoom = *zoom / 1.01;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		*x = *x - 0.01;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		*x = *x + 0.01;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		*y = *y + 0.01;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		*y = *y - 0.01;
	printf("zoom = %f\n", *zoom);
	printf("x = %f\n", *y);
	printf("y = %f\n", *x);
}

int main()
{
	GLFWwindow* window;
	t_gl gl;
	// Initialize GLFW
	glfwInit();

	// Define version and compatibility settings
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1); 
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create OpenGL window and context
	window = glfwCreateWindow(1500, 1286, "OpenGL", NULL, NULL);
	glfwMakeContextCurrent(window);

	// Check for window creation failure
	if (!window) 
	{
		// Terminate GLFW
		dprintf(2, "Error while opening windows\n");
		glfwTerminate();
		return 0;
	}

	// Initialize GLEW
	glewExperimental = GL_TRUE;
	glewInit();
	printf("OpenGL version: %s\n", glGetString(GL_VERSION));
	printf("Shader version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	// Event loop
	
	// GL_NEAREST();

	float points[] = {
		1.0f,  1.0f,  0.0f,
		-1.0f,  1.0f,  0.0f,
		-1.0f, -1.0f,  0.0f,
		1.0f, -1.0f,  0.0f
	};

	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), points, GL_STATIC_DRAW);

	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	unsigned int	gl_texture;

	gl_texture = glGetUniformLocation(gl.program_id, "Texture");
	glGenTextures(1, &gl_texture);
	glBindTexture(GL_TEXTURE_2D, gl_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// GLuint programID = LoadShaders("shader.vs", "shader.fs");
	if (ft_shaders("shader.vs", "shader.fs", &gl) < 0)
		return (-1);
	float maxIt = 100.0f;
	float zoom = 2.0f;
	float x = 0;
	float y = 0;
	while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(window))
	{
		// wipe the drawing surface clear
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(gl.program_id);
		glActiveTexture(GL_TEXTURE2);

		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
			points[0] += 1;
		printf("point 0 = %f\n", points[0]);

		unsigned int matloc;
		matloc = glGetUniformLocation(gl.program_id, "MaxIterations");
		glUniform1f(matloc, maxIt);
		matloc = glGetUniformLocation(gl.program_id, "zoom");
		glUniform1f(matloc, zoom);
		matloc = glGetUniformLocation(gl.program_id, "x");
		glUniform1f(matloc, x);
		matloc = glGetUniformLocation(gl.program_id, "y");
		glUniform1f(matloc, y);
		ft_control(window, &zoom, &x, &y);
		glBindVertexArray(vao);
		// draw points 0-3 from the currently bound VAO with current in-use shader
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
		// glDrawArrays(GL_TRIANGLES, 1, 3);
		// update other events like input handling 
		glfwPollEvents();
		// put the stuff we've been drawing onto the display
		glfwSwapBuffers(window);
}

	// Terminate GLFW
	glfwTerminate(); return 0;
}

// gcc -I ~/.brew/include/ -L/Users/apouchet/.brew/lib -lglfw -lglew opengl.c -framework AppKit -framework OpenGl
