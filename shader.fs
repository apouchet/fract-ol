#version 400

uniform float MaxIterations;
uniform float zoom;
uniform float x;
uniform float y;
uniform float c_r;
uniform float c_i;
uniform float fractal;


out vec4 pixelColor;
in vec2 coord;

void main()
{

    float   real  = coord.x * zoom + x;
    float   imag  = coord.y * zoom + y;
    float   Creal;
    float   Cimag;

    if (fractal == 0)
    {
    	Creal = real;
		Cimag = imag;
    }
    else
    {
    	Creal = c_r;
		Cimag = c_i;
	}
    float iter = 0.0;
    float r2 = 0.0;

    for (; iter < MaxIterations && r2 < 4.0; ++iter)
    {
        float tempreal = real;

        real = (tempreal * tempreal) - (imag * imag) + Creal;
        imag = 2.0 * tempreal * imag + Cimag;
        r2   = (real * real) + (imag * imag);
    }

    vec3 color;

    if (r2 < 4.0)
        color = vec3(0.0f, 0.0f, 0.0f);
    else
        color = vec3(float(iter) / (MaxIterations), float(iter) / (MaxIterations / 2), float(iter) / (MaxIterations / 10));

    pixelColor = vec4(color, 1.0);
}
