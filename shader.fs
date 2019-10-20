#version 400

uniform float MaxIterations;
uniform float zoom;
uniform float x;
uniform float y;
uniform float c_r;
uniform float c_i;
uniform float fractal;
uniform float color_switch;


out vec4 pixelColor;
in vec2 coord;

void main()
{

	float   real  = coord.x * zoom + x;
	float   imag  = coord.y * zoom + y;
	float   Creal;
	float   Cimag;

	if (fractal == 0 || fractal == 2)
	{
		Creal = real;
		Cimag = imag;
	}
	else if (fractal == 1 || fractal == 3)
	{
		Creal = c_r;
		Cimag = c_i;
	}
	float iter = 0.0;
	float power_r = 0.0;
	float power_i = 0.0;

	for (; iter < MaxIterations && (power_i + power_r) < 4.0; ++iter)
	{
		float tempreal = real;

		real = (tempreal * tempreal) - (imag * imag) + Creal;
		if (fractal > 1)
			imag = 2.0 * abs(tempreal * imag) + Cimag;
		else
			imag = 2.0 * tempreal * imag + Cimag;
		power_r = (real * real);
		power_i = (imag * imag);
	}

	vec3 color;

	if ((power_i + power_r) < 4.0)
		color = vec3(0.0f, 0.0f, 0.0f);
	else if (color_switch == 0)
		color = vec3(float(iter) / (MaxIterations / 10), float(iter) / (MaxIterations / 2), float(iter) / MaxIterations);
	else if (color_switch == 1)
		color = vec3(float(iter) / (MaxIterations / 2), float(iter) / (MaxIterations / 10), float(iter) / (MaxIterations));
	else if (color_switch == 2)
		color = vec3(float(iter) / MaxIterations, float(iter) / (MaxIterations / 2), float(iter) / (MaxIterations / 10));

	pixelColor = vec4(color, 1.0);
}
