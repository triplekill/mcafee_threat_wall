uniform sampler2D tex0;
uniform bool useTexture;
uniform bool preMultiply;

uniform ivec2 size;

// Top, Right, Bottom, Left glow percentages
uniform vec4 trbl_glow;

varying vec4 p_o;

void main()
{
	vec2 p = p_o.xy / float(size.y);
    vec2 fsize = vec2( size );

	float glow = 0.0;

    float ht = max( trbl_glow.x * fsize.y, 0.0001);
    float wt = fsize.x/2.0;
    float Rt = (wt*wt + ht*ht)/(2.0*ht);
    float rt = Rt - ht;

    float hr = max( trbl_glow.y * fsize.x, 0.0001);
    float wr = fsize.y/2.0;
    float Rr = (wr*wr + hr*hr)/(2.0*hr);
    float rr = Rr - hr;

    float hb = max( trbl_glow.z * fsize.y, 0.0001);
    float wb = fsize.x/2.0;
    float Rb = (wb*wb + hb*hb)/(2.0*hb);
    float rb = Rb - hb;

    float hl = max( trbl_glow.w * fsize.x, 0.0001);
    float wl = fsize.y/2.0;
    float Rl = (wl*wl + hl*hl)/(2.0*hl);
    float rl = Rl - hl;

    glow += 1.0 - smoothstep( 0.6*Rt, Rt+30.0, length(p_o.xy - vec2(           wt,         0 - rt )) );
    glow += 1.0 - smoothstep( 0.6*Rr, Rr+30.0, length(p_o.xy - vec2( fsize.x + rr,             wr )) );
    glow += 1.0 - smoothstep( 0.6*Rb, Rb+30.0, length(p_o.xy - vec2(           wb,   fsize.y + rb )) );
    glow += 1.0 - smoothstep( 0.6*Rl, Rl+30.0, length(p_o.xy - vec2(       0 - rl,             wl )) );

    vec4 color = vec4(1.0, 1.0, 1.0, 1.0);
    if (useTexture) {
        color = texture2D( tex0, gl_TexCoord[0].st );
    }
    color *= gl_Color;
    color.a *= glow;
    
    if (preMultiply) {
        color.r *= color.a;
        color.g *= color.a;
        color.b *= color.a;
    }    
    
    gl_FragColor = color;
}