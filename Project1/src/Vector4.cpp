// ----------------------------------------------------------------------------
// Project Name		:	Assigment 1
// File Name		:	Vector4.cpp
// Author			:	Eduardo de vega
// Creation Date	:	1/16/2020
// PurmPose			:	Set of manipulations with vectors
// ----------------------------------------------------------------------------
#include "Vector4.h"   
#include "math.h"     
#include "MathUtilities.h"
        // Default constructor, initializes x,y,z to zeroes, w to defined value
        Vector4::Vector4(void):x(0),y(0),z(0),w(0){}

        // Copy constructor, copies every component from the other Vector4
        Vector4::Vector4(const Vector4& rhs):x(rhs.x),y(rhs.y),z(rhs.z),w(rhs.w){}

        // Non-Default constructor, self explanatory
        Vector4::Vector4(float xx, float yy, float zz, float ww ):x(xx),y(yy),z(zz),w(ww){}

        // Assignment operator, does not need to handle self assignment
        Vector4& Vector4::operator=(const Vector4& rhs){
            for(int i = 0; i < 4;i++)
                v[i] = rhs.v[i];
            return *this;    
        }
        // Unary negation operator, negates all components and returns a copy
        Vector4 Vector4::operator-(void) const{
            Vector4 vec;
            //Make it negative
            for(int i = 0; i < 4;i++)
                vec.v[i] = -v[i];
                return vec;
        }

        // Basic Vector math operations. Add Vector to Vector B, or Subtract Vector A from
        // Vector B, or multiply a vector with a scalar, or divide a vector by that scalar
        Vector4 Vector4::operator+(const Vector4& rhs) const{
            Vector4 vec (x + rhs.x , y + rhs.y, z + rhs.z , w + rhs.w);
            return vec;
        }
        Vector4 Vector4::operator-(const Vector4& rhs) const{
            Vector4 vec (x - rhs.x , y - rhs.y, z - rhs.z , w - rhs.w);
            return vec;
        }
        Vector4 Vector4::operator*(const float rhs) const{
            Vector4 vec (x * rhs , y * rhs, z * rhs , w * rhs);
            return vec;
        }
        Vector4 Vector4::operator/(const float rhs) const{
            Vector4 vec (x / rhs , y / rhs, z / rhs , w / rhs);
            return vec;
        }
        // Same as above, just stores the result in the original vector
        Vector4& Vector4::operator+=(const Vector4& rhs){
            x = x + rhs.x;
            y = y + rhs.y;
            z = z + rhs.z;
            w = w + rhs.w;
            return *this;
        }
        Vector4& Vector4::operator-=(const Vector4& rhs){
            x = x - rhs.x;
            y = y - rhs.y;
            z = z - rhs.z;
            w = w - rhs.w;
            return *this;
        }
        Vector4& Vector4::operator*=(const float rhs){
            x = x * rhs;
            y = y * rhs;
            z = z * rhs;
            w = w * rhs;
            return *this;
        }
        Vector4& Vector4::operator/=(const float rhs){
            x = x / rhs;
            y = y / rhs;
            z = z / rhs;
            w = w / rhs;
            return *this;
        }
        // Comparison operators which should use an epsilon defined in
        // MathUtilities.h to see if the value is within a certain range
        // in which case we say they are equivalent.
        bool Vector4::operator==(const Vector4& rhs) const{
            bool yes;
           for(int i = 0; i < 4; i++ ){
               //Check the result if it is equal or not
                yes = isEqual(v[i],rhs.v[i]);
                if(!yes)
                    return 0;
           }    
           return 1;
        }
        bool Vector4::operator!=(const Vector4& rhs) const{
            //Using the function above
            return!(rhs == *this);
        }

        // Computes the dot product with the other vector. Treat it as 3D vector.
        float Vector4::Dot(const Vector4& rhs) const{
            float dotProd = x * rhs.x + y * rhs.y + z * rhs.z;
            return dotProd;
        }
        // Computes the cross product with the other vector. Treat it as a 3D vector.
        Vector4 Vector4::Cross(const Vector4& rhs) const{
            Vector4 vec (y * rhs.z - z * rhs.y,z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x);    
            return vec;                
            
        }
        // Computes the true length of the vector
        float Vector4::Length(void) const{
             
            return (float)sqrt(x*x+y*y+z*z+w*w);
        }
        // Computes the squared length of the vector
        float Vector4::LengthSq(void) const{
            return x*x + y*y + z*z + w*w;
        }
        // Normalizes the vector to make the final vector be of length 1. If the length is zero
        // then this function should not modify anything.
        void Vector4::Normalize(void){
            float leng = Length();
            if(leng == 0)
                return;
            for(int i = 0; i < 4;i++)
                v[i] /=leng; 

        }
        // Sets x,y,z to zeroes, w to defined value
        void Vector4::Zero(void){
            x = 0;
            y = 0;
            z = 0;
            w = 0;
        }