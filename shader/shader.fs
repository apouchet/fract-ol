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
	vec3 color;

	if (fractal == 0 || fractal == 2 || fractal == 4)
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
	float div;
	float tmp;
	if (fractal != 4)
	{
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
		if ((power_i + power_r) < 4.0)
			color = vec3(0.0f, 0.0f, 0.0f);
		else if (color_switch == 0)
			color = vec3(float(iter) / (MaxIterations / 10), float(iter) / (MaxIterations / 2), float(iter) / MaxIterations);
		else if (color_switch == 1)
			color = vec3(float(iter) / MaxIterations, float(iter) / (MaxIterations / 2), float(iter) / (MaxIterations / 10));
		else if (color_switch == 2)
			color = vec3(float(iter) / (MaxIterations / 2), float(iter) / (MaxIterations / 10), float(iter) / (MaxIterations));
	}
	else if (fractal == 4)
	{
		while (++iter < MaxIterations)
		{
			power_r = Creal * Creal;
			power_i = Cimag * Cimag;
			div = 3.0 * (power_r + power_i) * (power_r + power_i);
			tmp = Creal;
			Creal -= (power_r * power_r * Creal + 2.0 * power_r * Creal * power_i + Creal * power_i * power_i - power_r + power_i) / div;
			Cimag -= (power_i * power_i * Cimag + power_r * power_r * Cimag + 2 * power_r * power_i * Cimag + 2 * tmp * Cimag) / div;
			if (sqrt((Creal - 1) * (Creal - 1) + power_i) < 0.0001)
			{
				color = vec3(1 - float(iter) / MaxIterations, 0, 0);
				// color = vec3(float(iter) / (MaxIterations / 10), float(iter) / (MaxIterations / 2), float(iter) / MaxIterations);
				break ;
			}
			else if (sqrt((Creal + 0.5) * (Creal + 0.5)
				+ (Cimag - sqrt(3) / 2) * (Cimag - sqrt(3) / 2)) < 0.0001)
			{
				// color = vec3(0, 1 - float(iter) / MaxIterations, 0);
				color = vec3(0, MaxIterations / iter, 0);
				// color = vec3(float(iter) / MaxIterations, float(iter) / (MaxIterations / 2), float(iter) / (MaxIterations / 10));
				break ;
			}
			else if (sqrt(pow(Creal + 0.5, 2)
				+ (Cimag + sqrt(3) / 2) * (Cimag + sqrt(3) / 2)) < 0.0001)
			{
				color = vec3(0, 0, float(float(1) - (float(iter) / float(MaxIterations))));
				// color = vec3(float(iter) / (MaxIterations / 2), float(iter) / (MaxIterations / 10), float(iter) / (MaxIterations));
				break ;
			}
			else
				color = vec3(0.0f, 0.0f, 0.0f);
		}
	}
	pixelColor = vec4(color, 1.0);
}
