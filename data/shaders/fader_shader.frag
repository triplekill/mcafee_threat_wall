uniform sampler2D tex0;
uniform bool useTexture;
uniform bool preMultiply;

uniform ivec2 size;

// Top, Right, Bottom, Left fade-out percentages
uniform vec4 trbl_fade;

// Relative transformation of this element to the containing fader element
uniform mat4  rel_trans;

varying vec4 p_o;

vec4 offset = rel_trans * vec4(0,0,0,1);

void main()
{
    vec4 color = vec4(1.0, 1.0, 1.0, 1.0);
    if (useTexture) {
        color = texture2D( tex0, gl_TexCoord[0].st );
    }
    color *= gl_Color;

	vec2 p = (p_o.xy + offset.xy) / vec2(size.xy);
	color.a *= smoothstep( 0.0, trbl_fade.w, p.x ) - smoothstep( 1.0-trbl_fade.y, 1.0, p.x );
	color.a *= smoothstep( 0.0, trbl_fade.x, p.y ) - smoothstep( 1.0-trbl_fade.z, 1.0, p.y );

    if (preMultiply) {
        color.r *= color.a;
        color.g *= color.a;
        color.b *= color.a;
    }    

    gl_FragColor = color;
}