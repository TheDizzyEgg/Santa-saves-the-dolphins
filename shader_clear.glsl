
#ifdef GL_ES
precision mediump float;
#endif



uniform sampler2D al_tex;

uniform float tint;
varying vec4 varying_color;
varying vec2 varying_texcoord;
vec4 pixel;




void main()
{
     pixel = varying_color * texture2D(al_tex, varying_texcoord);

        //pixel.r = 1.0;
      // pixel.g = 0;
       // pixel.b = 0;
      pixel.a = pixel.a * tint;
	gl_FragColor = pixel;
}


