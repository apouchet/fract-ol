#version 400

uniform float MaxIterations;
uniform float zoom;
uniform float x;
uniform float y;

out vec4 pixelColor;
in vec2 coord;

void main()
{

    float   real  = (coord.x + x) * zoom;
    float   imag  = (coord.y + y) * zoom;
    float   Creal = real;  
    float   Cimag = imag;  
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
        color = vec3(float(iter) / 10.0, float(iter) / 50.0, float(iter) / 100.0);

    pixelColor = vec4(color, 1.0);
}
