#include "Rasterizer.h"

int Ceiling(float f)
{
    int i = static_cast<int>(f);

    if (static_cast<float>(i) == f)
        return i;

    return i + 1;
}

void DrawMidpointLine(sf::Image &FrameBuffer, const sf::Vector2f & p1, const sf::Vector2f & p2, sf::Color color)
{
    int x = (int)floor(p1.x);
    int y = (int)ceil(p1.y);

    int dx    = (int)ceil(p2.x) - x;
    int dy    = (int)ceil(p2.y) - y;
    int xStep = 1, yStep = 1;

    if (dx < 0)
    {
        xStep = -1;
        dx    = -dx;
    }
    if (dy < 0)
    {
        yStep = -1;
        dy    = -dy;
    }
    if (x > 0 && x < (int)FrameBuffer.getSize().x && y > 0 && y < (int)FrameBuffer.getSize().y)
	FrameBuffer.setPixel(x, y, color);

    if (abs(dy) > abs(dx)) // |m|>1
    {
        int dstart, dn, dne;
        dstart = 2 * dx - dy;
        dn     = dx;
        dne    = dx - dy;

        while (dy--)
        {
            y += yStep;

            if (dstart > 0)
            {
                dstart += dne;
                x += xStep;
            }
            else
                dstart += dn;
            if (x > 0 && x < (int)FrameBuffer.getSize().x && y > 0 && y < (int)FrameBuffer.getSize().y)
			FrameBuffer.setPixel(x, y, color);
        }
    }
    else // |m|<1
    {
        int dstart, de, dne;
        dstart = 2 * dy - dx;
        de     = dy;
        dne    = dy - dx;

        while (dx--)
        {
            x += xStep;

            if (dstart > 0)
            {
                dstart += dne;
                y += yStep;
            }
            else
                dstart += de;
            if (x > 0 && x < (int)FrameBuffer.getSize().x && y > 0 && y < (int)FrameBuffer.getSize().y)
            FrameBuffer.setPixel(x, y, sf::Color::Yellow);
        }
    }
}

void DrawTriangleSolid(sf::Image &FrameBuffer, const sf::Vector2f & p0, const sf::Vector2f & p1, const sf::Vector2f & p2 , sf::Color color )
{
    // Select TOP, MIDDLE and BOTTOM vertices
    // --------------------------------------
    const sf::Vector2f *top, *middle, *bottom;
    bool           middle_is_left = false;

    if (p0.y < p1.y) // case 4, 5, or 6
    {
        if (p2.y < p0.y) // case 4
        {
            top            = &p2;
            middle         = &p0;
            bottom         = &p1;
            middle_is_left = true;
        }
        else
        {
            top = &p0;
            if (p1.y < p2.y) // case 5
            {
                middle         = &p1;
                bottom         = &p2;
                middle_is_left = true;
            }
            else // case 6
            {
                middle         = &p2;
                bottom         = &p1;
                middle_is_left = false;
            }
        }
    }
    else // case 1, 2 or 3
    {
        if (p2.y < p1.y) // case 2
        {
            top    = &p2;
            middle = &p1;

            bottom         = &p0;
            middle_is_left = false;
        }
        else
        {
            top = &p1;
            if (p0.y < p2.y) // case 3
            {
                middle         = &p0;
                bottom         = &p2;
                middle_is_left = false;
            }
            else // case 1
            {
                middle         = &p2;
                bottom         = &p0;
                middle_is_left = true;
            }
        }
    }

    // TOP to MIDDLE
    // -------------
    // Select LEFT and RIGHT edge endpoints to use from the top to the middle
    // ----------------------------------------------------------------------
    const sf::Vector2f *left, *right;
    if (middle_is_left)
    {
        left  = middle;
        right = bottom;
    }
    else
    {
        right = middle;
        left  = bottom;
    }

    // Calculate the x increments along the LEFT and RIGHT edges (the inverse of the slope
    float xIncLeft  = (left->x - top->x) / (left->y - top->y);
    float xIncRight = (right->x - top->x) / (right->y - top->y);

    // Initial values
    int   y    = (int)Ceiling(top->y);
    int   yMax = (int)Ceiling(middle->y) - 1;
    float xL   = top->x; // xL MUST ALWAYS be a double, the ceiling is applied to x and xMax
    float xR   = top->x; // xL MUST ALWAYS be a double, the ceiling is applied to x and xMax
    int   x;
    int   xMax = (int)floor(xR) - 1;

  

    // Start the loop, from the y_top to y_middle
    while (y <= yMax)
    {
        // Loop along the scanline, from left to right
        x    = (int)floor(xL);
        xMax = (int)floor(xR) - 1;


        while (x <= xMax)
        {
			if (x > 0 && x < (int) FrameBuffer.getSize().x && y > 0 && y < (int)FrameBuffer.getSize().y)
            FrameBuffer.setPixel(x, y,color);

            ++x;

        }

        xL += xIncLeft;
        xR += xIncRight;
        ++y;

  
    }

    // MIDDLE to BOTTOM
    // ----------------
    // Select LEFT and RIGHT edge endpoints to use from the top to the middle
    // ----------------------------------------------------------------------
    // Initial values
    y    = Ceiling(middle->y);
    yMax = Ceiling(bottom->y) - 1;

    if (middle_is_left)
    {
        xIncLeft = (bottom->x - left->x) / (bottom->y - left->y);
        xL       = left->x;

        
    }
    else
    {
        xIncRight = (bottom->x - right->x) / (bottom->y - right->y);
        xR        = right->x;
    }

    // Start the loop, from the y_top to y_middle
    while (y <= yMax)
    {
        x    = (int)floor(xL);
        xMax = (int)floor(xR) - 1;

      

        // Loop along the scanline, from left to right
        while (x <= xMax)
        {
			if(x > 0 && x < (int)FrameBuffer.getSize().x && y > 0 && y < (int)FrameBuffer.getSize().y )
            FrameBuffer.setPixel(x, y,color);

            ++x;
        }

        xL += xIncLeft;
        xR += xIncRight;
        ++y;

     
    }
}
