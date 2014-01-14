uniform sampler2D tex0;
uniform bool useTexture;
uniform bool preMultiply;

float percent = 0.01041667;

void main()
{
    vec4 color = vec4(1.0, 1.0, 1.0, 1.0);

    vec2 uv = gl_TexCoord[0].st;
    
    if (useTexture) {
        color = texture2D( tex0, uv );
    }
    
    color *= gl_Color;
    
    if (preMultiply) {
        color.r *= color.a;
        color.g *= color.a;
        color.b *= color.a;
    }
    
    if (uv.x <= percent || uv.x >= 1.0 - percent ||
        uv.y <= percent || uv.y >= 1.0 - percent)
        color.rgb = vec3(1.0, 1.0, 1.0);
    
    gl_FragColor = color;
}