#ifndef CG_HH
#define CG_HH

#include <vector>
#include "Vector2D.hh"


namespace cg{

enum class CHTYPE { SLOW, GRAHAM, JARVIS };

void ConvexHull(const std::vector<Vector2D>& set_of_points, std::vector<Vector2D>& convex_hull_vertices, CHTYPE implementation );

/*
Slow Convex Hull Implementation

Described in Chapter I of "Computational Geometry".
It has a time complexity of O(n^3)
*/
void SlowConvexHull(const std::vector<Vector2D>& set_of_points, std::vector<Vector2D>& convex_hull_vertices);

/*
Graham Scan Implementation

Described in Chapter I of "Computational Geometry".
It has a time complexity of O(n log(n) )
*/
void GrahamScanCH(const std::vector<Vector2D>& set_of_points, std::vector<Vector2D>& convex_hull_vertices);

/*
Gift Wrapping Algorithm (Jarvis March)

It has a time complexity of O( n h )
where n is the number of given points and h is the number of 
convex hull points
*/
void JarvisMarch(const std::vector<Vector2D>& set_of_points, std::vector<Vector2D>& convex_hull_vertices);

/*
Check if the given vectors make a right turn

p1\  / p3
   \/      : This should return true
    p2

It evaluates the sign of the z-componenet of the cross-product of P_21 x P_31 
where the two Vector2D are extended to 3D with 0 as z-component
*/
bool check_for_right_turn(const std::vector<Vector2D>& ps);

}

#endif