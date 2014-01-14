uniform sampler2D tex0;
uniform bool useTexture;
uniform bool preMultiply;

uniform ivec2 size;

varying vec4 p_o;


// Shader to make JCI panel shape: all rounded edges except the bottom right corner
// 		-- 	It can only deal with rectangles that have a height greater than their
// 			width right now, so I'll have to make it more general.
//		-- 	Csb is the smoothing effect that makes the curves not look pixelated.
// 			Increasing the csb will make the edges look more blurry.
//		-- 	Cs the size you'd like your curves to be.
//		-- 	I'll make sure to make cs and csb uniforms so that the user of the shader
//			can pass that in instead of editting the shader code.


void main()
{
	float dim = float(size.y) / float(size.x); //dimensions
	float cs = 0.07f; // curve size
	float csb = 0.004f; // the curved edges are actually blurred to create a smoother look. this paramter sets how blurry they are.
	vec2 p = vec2 ( (float(p_o.x) / float(size.x)), (float(p_o.y) / float(size.x)));

    vec4 color = vec4(1.0, 1.0, 1.0, 1.0);
    
	//if (useTexture) {
    //    color = texture2D( tex0, gl_TexCoord[0].st );
    //}
    //color = gl_Color;
	
	if (p.x < cs && p.y < cs) //upper left corner
	{
		if (length ( vec2( (p.x - cs), (p.y - cs) )) < (cs-csb))
		{
			color = gl_Color;
		} else if (length ( vec2( (p.x - cs), (p.y - cs) )) < cs)
		{
			color.a = smoothstep (cs, (cs-csb), length ( vec2( (p.x - cs), (p.y - cs) )));
		} else
		{
			color.a = 0.0f;
		}
	} else if (p.x > (1-cs) && p.y < cs) // upper right corner
	{
		if (length ( vec2( (p.x - (1-cs)), (p.y - cs) )) < (cs-csb))
		{
			color = gl_Color;
		} else if (length ( vec2( (p.x - (1-cs)), (p.y - cs) )) < cs)
		{
			color.a = smoothstep (cs, (cs-csb), length ( vec2( (p.x - (1-cs)), (p.y - cs) )));
		} else
		{
			color.a = 0.0f;
		}
	} else if (p.x < cs && p.y > (dim - cs)) // lower left corner
	{
		if (length ( vec2( (p.x - cs), (p.y - (dim-cs)) )) < (cs-csb))
		{
			color = gl_Color;
		} else if (length ( vec2( (p.x - cs), (p.y - (dim-cs)) )) < cs)
		{
			color.a = smoothstep (cs, (cs-csb), length ( vec2( (p.x - cs), (p.y - (dim-cs)) )));
		} else
		{
			color.a = 0.0f;
		}
	} else if (p.x > (1.0-csb) && p.y > (dim-csb)) //smoothing out the bottom right corner
	{
		color.a = smoothstep (csb, 0, length( vec2((p.x - (1.0-csb)), (p.y - (dim-csb)))));
		//smoothstepping the sides in the following if/elses
	} else if (p.x < csb) // left
	{
		color.a = smoothstep (0.0f, csb, p.x);
	} else if (p.y < csb) //top
	{
		color.a = smoothstep (0.0f, csb, p.y);
	} else if (p.y > (dim-csb)) //bottom
	{
		color.a = smoothstep (dim,(dim-csb), p.y);
	} else if (p.x > (1.0-csb)) //right
	{
		color.a = smoothstep (1.0,(1.0-csb), p.x);
	} else
	{
		color = gl_Color;
	}
	
    
    //if (preMultiply) {
    //    color.r *= color.a;
    //    color.g *= color.a;
    //    color.b *= color.a;
    //}    
    
    gl_FragColor = color;
}