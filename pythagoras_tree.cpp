#include <graphics.h>

class Rectangle_
{
public:
	long double left_top_x, left_top_y,
		  right_top_x, right_top_y,
		  left_bottum_x, left_bottum_y,
		  right_bottum_x, right_bottum_y;
};

void draw_rectangle(Rectangle_ r)
{
	// Draw a rectangle by x and y of four-point
	line(r.left_top_x, r.left_top_y, r.right_top_x, r.right_top_y);
	line(r.left_top_x, r.left_top_y, r.left_bottum_x, r.left_bottum_y);
	line(r.left_bottum_x, r.left_bottum_y, r.right_bottum_x, r.right_bottum_y);
	line(r.right_bottum_x, r.right_bottum_y, r.right_top_x, r.right_top_y);
}

void pythagoras_tree(Rectangle_ r, char step)
{
	// In the first step, we have to draw the root rectangle
	draw_rectangle(r);

	// Calculate the x and y of the centre of the rectangle
	long double centre_x = (r.right_top_x + r.left_top_x + r.left_bottum_x + r.right_bottum_x) / 4.0,
			    centre_y = (r.right_top_y + r.left_top_y + r.left_bottum_y + r.right_bottum_y) / 4.0;
	
	// Create the right and left rectangle child of this rectangle object named 'r'
	Rectangle_ rrect, lrect;

	rrect.left_bottum_x = centre_x + (r.left_top_x - r.left_bottum_x);
	rrect.left_bottum_y = centre_y + (r.left_top_y - r.left_bottum_y);
	rrect.right_bottum_x = r.right_top_x, rrect.right_bottum_y = r.right_top_y;
	rrect.left_top_x = rrect.left_bottum_x + (rrect.left_bottum_x - r.left_top_x);
	rrect.left_top_y = rrect.left_bottum_y + (rrect.left_bottum_y - r.left_top_y);
	rrect.right_top_x = rrect.right_bottum_x + (rrect.right_bottum_x - centre_x);
	rrect.right_top_y = rrect.right_bottum_y + (rrect.right_bottum_y - centre_y);

	lrect.right_bottum_x = centre_x + (r.left_top_x - r.left_bottum_x);
	lrect.right_bottum_y = centre_y + (r.left_top_y - r.left_bottum_y);
    lrect.left_bottum_x = r.left_top_x, lrect.left_bottum_y = r.left_top_y;
    lrect.left_top_x = lrect.left_bottum_x + (lrect.left_bottum_x - centre_x);
    lrect.left_top_y = lrect.left_bottum_y + (lrect.left_bottum_y - centre_y);
    lrect.right_top_x = lrect.right_bottum_x + (lrect.right_bottum_x - r.right_top_x);
    lrect.right_top_y = lrect.right_bottum_y + (lrect.right_bottum_y - r.right_top_y);

	if (step > 0)
	{
		// Draw two child rectangles
		draw_rectangle(rrect);
		draw_rectangle(lrect);

		// And draw two children for each rectangle drawn
		pythagoras_tree(rrect, step - 1);
		pythagoras_tree(lrect, step - 1);
	}
}

int main()
{
	// Create graphical window
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);

    // Create a rectangle object
    Rectangle_ r;
	r.left_top_x = 270;
	r.left_top_y = 350;
	r.right_top_x = 370;
	r.right_top_y = 350;
	r.left_bottum_x = 270;
	r.left_bottum_y = 450;
	r.right_bottum_x = 370;
	r.right_bottum_y = 450;

	// Draw a Pythagorean tree of a rectangle object with a custom step
	pythagoras_tree(r, 10);

	// Wait for the user to enter any key to destroy the graphical window and exit the program
    getch();
    closegraph();
    return 0;
}

