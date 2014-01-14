uniform sampler2D tex0;
uniform sampler2D tex1; // mask Texture

// Perform a rounded corner masking on the top left and right corners.
// Clients can provide an x border for the left and right sides, and a
// y border for the top side, a radius for the corner, and an offset_x
// to account for horizontal scrolling of the source image.

// Current pixel position
varying vec4 p_o;

// The total width of my containing area
uniform float width;
// A border from the sides of my area that gets completely masked
uniform float x_border;
uniform float y_border;
// The radius of the corner masking
uniform float radius;
// The offset to apply to the x position, to account for scrolling
uniform float offset_x;

// Distance between two points
float			dist(float x0, float y0, float x1, float y1);

void main()
{
    vec4 color = vec4(0.0, 0.0, 0.0, 0.0);
    color = texture2D( tex0, gl_TexCoord[0].st );
	float x = p_o.x + offset_x;
	float y = p_o.y;
	float left = x_border;
	float top = y_border;
	float right = width-x_border;
	if (y < top) {
		color[3] = 0.0;
	} else if (x < left || x > right) {
		color[3] = 0.0;
	} else if (y < top + radius) {
		if (x < left + radius) {
			// Either mask to alpha or antialias
			float a = 1.0;
			float d = dist(left + radius, top + radius, x, y);
			if (d >= radius) {
				a = 0.0;
			} else if (d > radius - 1) {
				a = radius-d;
			}
			color[3] *= a;
		} else if (x > right - radius) {
			float a = 1.0;
			float d = dist(right - radius, top + radius, x, y);
			if (d >= radius) {
				a = 0.0;
			} else if (d > radius - 1) {
				a = radius-d;
			}
			color[3] *= a;
		}
	}
	
    gl_FragColor = color;
}

float			dist(float x0, float y0, float x1, float y1)
{
	float		vx = x0-x1;
	float		vy = y0-y1;
	return sqrt(vx*vx + vy*vy);
}
