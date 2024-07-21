#include "Vector2D.hh"
#include <cmath>
//--------------------------------------------------------//

Vector2D::Vector2D(float x, float y) : m_x(x), m_y(y){}

//--------------------------------------------------------//

Vector2D::Vector2D(const Vector2D& other) : m_x(other.m_x), m_y(other.m_y){}

//--------------------------------------------------------//

Vector2D& Vector2D::operator=(const Vector2D& other){
    m_x = other.m_x;
    m_y = other.m_y;

    return *this;
}

//--------------------------------------------------------//

bool Vector2D::operator==(const Vector2D& other) const {

    const double epsilon = 1e-10;

    return (std::fabs(m_x - other.m_x) < epsilon) && (std::fabs(m_y - other.m_y) < epsilon);
}


//--------------------------------------------------------//

bool Vector2D::operator!=(const Vector2D& other) const{
    return !(*this == other);
}

//--------------------------------------------------------//

bool Vector2D::lexographycal_sort(const Vector2D& v1, const Vector2D& v2){

    // Check if x are almost equal
    if( fabs(v1.m_x - v2.m_x) < 1e-9 ){

        return v1.m_y < v2.m_y;
    }
    
    return v1.m_x < v2.m_x;
}

//--------------------------------------------------------//
