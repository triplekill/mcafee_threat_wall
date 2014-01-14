uniform sampler2D tex0;
uniform sampler2D tex1; // mask Texture
uniform float width;
uniform float height;

void main()
{
    vec2 st = vec2(gl_FragCoord.x / width, gl_FragCoord.y / height);
    if (texture2D( tex1, st ).a != 1.0)
        return;
    
    vec4 color = vec4(1.0, 1.0, 0.0, 1.0);

    color = texture2D( tex0, gl_TexCoord[0].st );
    
    color *= gl_Color; 
    
    gl_FragColor = color;
}