uniform sampler2D tex0;
uniform bool useTexture;
uniform bool preMultiply;

// Current pixel position
varying vec4 p_o;

// Width of the bar, in pixels
uniform float bar_width;

// Value to scale the unplayed area by, 0 - 1
uniform float offOpacity;

// Currently playback position, 0 - 1
uniform float position;

void main()
{
    vec4 color = vec4(1.0, 1.0, 1.0, 1.0);
    if (useTexture) {
        color = texture2D( tex0, gl_TexCoord[0].st );
    }
    color *= gl_Color;

	float playback_pos = position * bar_width;
	if (p_o.x > playback_pos) {
		color.a *= offOpacity;
	}

    if (preMultiply) {
        color.r *= color.a;
        color.g *= color.a;
        color.b *= color.a;
    }    

    gl_FragColor = color;
}