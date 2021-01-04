
#ifdef GL_ES
precision mediump float;
#endif

#define NUM_LIGHTS 32

uniform sampler2D al_tex;
uniform vec3 tint;
varying vec4 varying_color;
varying vec2 varying_texcoord;

//Light lights[NUM_LIGHTS];
uniform  float lightX[NUM_LIGHTS];
uniform float lightY[NUM_LIGHTS];
uniform float lightPower[NUM_LIGHTS];
uniform vec3 lightDiffuse[NUM_LIGHTS];
uniform bool lightAlive[NUM_LIGHTS];
uniform float daylight;

    vec2 normal_pos;
    float fdistance;
    float attenuation;
    float constant = 1.0;
    float flinear = 0.1;
    float quadratic = 0.012;

        float pixelX;
    float pixelY;
    vec2 normal_screen;
    vec3 diffuse;
    vec2 screen;
    vec4 pixel;



void main()
{

   pixel = varying_color * texture2D(al_tex, varying_texcoord);

    pixelX = (varying_texcoord.x * 1.0) / 1.0;
    pixelY = ((1.0 - varying_texcoord.y) * 1.0) / 1.0;

   // if(varying_texcoord.y > 0.95)
   // {
   //     gl_FragColor = pixel;
   //     return;
   // }

    pixelX = 1280.0 * pixelX;
    pixelY = 720.0 * pixelY;

	normal_screen = vec2(pixelX, pixelY);
	screen = vec2(1280.0, 720.0);

	normal_screen = normal_screen / screen;

	diffuse = vec3(0.1, 0.1, 0.1);



    for(int i=0;i<NUM_LIGHTS;i++)
    {
		if(lightAlive[i] == true)
        {
            normal_pos = vec2(lightX[i], lightY[i]) / screen;

            fdistance = length(normal_pos - normal_screen) * lightPower[i];

            attenuation = 1.0 / (constant + flinear * fdistance + quadratic * (fdistance *
            fdistance));

            diffuse += lightDiffuse[i] * attenuation;
        }
    }

	diffuse = clamp(diffuse * (1.0 + daylight), 0.0, 1.0);

	gl_FragColor = pixel * vec4(diffuse, 1.0);
}


