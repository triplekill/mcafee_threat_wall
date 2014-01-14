uniform sampler2D tex0;
uniform bool useTexture;
uniform bool preMultiply;

uniform vec2 pos;
uniform float width;
uniform float height;
uniform float fadeSize;
uniform float percent;

float lerp(float a, float b, float t)
{
  return a + (b - a) * t;
}

float getAlphaTop(float y, float p)
{
    return (pos.y - y) / (fadeSize * p);
}

float getAlphaBottom(float y, float p)
{
    return (y - (pos.y-height)) / (fadeSize * p);
}

void main()
{
    float bottom = 0.05;
    float topPercent = lerp(bottom, 1.0, percent);
    float bottomPercent = lerp(bottom, 1.0, 1.0 - percent);
	
    vec4 color = vec4(1.0, 1.0, 1.0, 1.0);

    if (useTexture) {
        color = texture2D( tex0, gl_TexCoord[0].st );
    }
    
    color *= gl_Color;
    
    if (preMultiply) {
        color.r *= color.a;
        color.g *= color.a;
        color.b *= color.a;
    }    
    
    if (gl_FragCoord.x > pos.x && gl_FragCoord.x < pos.x + width)
    {
	if (gl_FragCoord.y < pos.y && gl_FragCoord.y > pos.y - fadeSize * topPercent)
	{
	    color.a *= getAlphaTop(gl_FragCoord.y, topPercent);
	}
	else if (gl_FragCoord.y > pos.y - height && gl_FragCoord.y < pos.y - height + fadeSize * bottomPercent)
	{
	    color.a *= getAlphaBottom(gl_FragCoord.y, bottomPercent);
	}
    }
    
    gl_FragColor = color;
}