// ----------------------------------------------------------------------------
// Project Name		:	Assigment 1
// File Name		:	Point.cpp
// Author			:	Eduardo de vega
// Creation Date	:	1/16/2020
// PurmPose			:	Set of manipulations with Points
// ----------------------------------------------------------------------------
    #include "Point4.h"
    #include "MathUtilities.h"

        // Default constructor, sets x,y,z to zero and w to the defined value
        Point4::Point4(void):x(0),y(0),z(0),w(1){}

        // Copy constructor, copies every component from the other Point4
         Point4::Point4(const Point4& rhs):x(rhs.x),y(rhs.y),z(rhs.z),w(rhs.w){}

        // Non-Default constructor, self-explanatory
         Point4::Point4(float xx, float yy, float zz, float ww ):x(xx),y(yy),z(zz),w(ww){}

        // Assignment operator, copies every component from the other Point4
        Point4&  Point4::operator=(const Point4& rhs){
            for(int i = 0; i < 4;i++)
                v[i] = rhs.v[i];
            return *this;    
        }

        // Unary negation operator, negates every component and returns a copy
        Point4  Point4::operator-(void) const{
            Point4 point;
             for(int i = 0; i < 4;i++)
                point.v[i] = -v[i];
            return point;    
        }

        // Binary subtraction operator, Subtract two Point4s and you get a Vector4
        Vector4  Point4::operator-(const Point4& rhs) const{
            Vector4 vec( x-rhs.x , y - rhs.y , z - rhs.z ,w - rhs.w );
            return vec;
        }

        // Basic vector math operations with points, you can add a Vector4 to a Point4, or
        // subtract a Vector4 from a Point4
        Point4  Point4::operator+ (const Vector4& rhs) const{
            Point4 point (x + rhs.x , y + rhs.y, z + rhs.z , w + rhs.w);
            return point;
        }

        Point4  Point4::operator- (const Vector4& rhs) const{
            Point4 point (x - rhs.x , y - rhs.y, z - rhs.z , w - rhs.w);
            return point;
        }

        // Same as previous two operators, just modifies the original instead of returning a
        // copy
        Point4&  Point4::operator+=(const Vector4& rhs){
            x = x + rhs.x;
            y = y + rhs.y;
            z = z + rhs.z;
            w = w + rhs.w;
            return *this;
        }

        Point4& Point4::operator-=(const Vector4& rhs){
            x = x - rhs.x;
            y = y - rhs.y;
            z = z - rhs.z;
            w = w - rhs.w;
            return *this;

        }

        // Comparison operators which should use an epsilon defined in
        // MathUtilities.h to see if the value is within a certain range
        // in which case we say they are equivalent.
        bool Point4::operator==(const Point4& rhs) const{
            //For returning
            bool yes;
            //Check the whole point
           for(int i = 0; i < 4; i++ ){
               //Using IsEqual
                yes = isEqual(v[i],rhs.v[i]);
                //If not return 0
                if(!yes)
                    return 0;
           }    
           return 1;
        }

        bool Point4::operator!=(const Point4& rhs) const{
            //Using the function above
            return!(rhs == *this);
        }

        // Sets x,y,z to zeroes, w to defined value
        void Point4::Zero(void){
            x = 0;
            y = 0;
            z = 0;
            w = 1;
        }