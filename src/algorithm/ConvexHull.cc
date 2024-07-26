#include "algorithm/ConvexHull.hh"
#include "basic/edge.hh"
#include "basic/Vector2D.hh"
#include <algorithm>
#include <vector>
#include <iostream>

namespace cg{

namespace algorithm{


void ConvexHull(const std::vector<Vector2D>& set_of_points, 
                std::vector<Vector2D>& convex_hull_vertices, 
                CHTYPE implementation ){

    switch(implementation){
        case CHTYPE::SLOW:
            SlowConvexHull(set_of_points, convex_hull_vertices);
            break;
        case CHTYPE::GRAHAM:
            GrahamScanCH(set_of_points, convex_hull_vertices);
            break;
        case CHTYPE::JARVIS:
            JarvisMarch(set_of_points, convex_hull_vertices);
            break;
        default:
            break;
    }

    return ;
}

// ----------------------------------------------------------------- //
/*
Slow Convex Hull Implementation

Described in Chapter I of "Computational Geometry".
It has a time complexity of O(n^3)
*/
void SlowConvexHull(const std::vector<Vector2D>& set_of_points, 
                std::vector<Vector2D>& convex_hull_vertices){

    
    std::vector<Edge> edges;
    bool is_valid;
    float mean_x = 0.;
    float mean_y = 0.;

    for(std::size_t i = 0; i < set_of_points.size(); i++){

        for(std::size_t j = 0; j < set_of_points.size(); j++){

            // Skip same point
            if(i == j) continue;

            is_valid = true;

            for(std::size_t k = 0; k < set_of_points.size(); k++){

                if(i == k or j == k) continue;

                // Cross Product between p12 and pi
                auto cp = (set_of_points[j].m_x-set_of_points[i].m_x)*(set_of_points[k].m_y-set_of_points[i].m_y)-(set_of_points[k].m_x-set_of_points[i].m_x)*(set_of_points[j].m_y-set_of_points[i].m_y);
                
                if(cp < 0){
                    is_valid = false;
                    break;
                }

            }

            if(is_valid){                
                mean_x += (set_of_points[i].m_x + set_of_points[j].m_x);
                mean_y += (set_of_points[i].m_y + set_of_points[j].m_y);
                edges.push_back({ .origin=i, .destination=j});
            }

        }

    }

    convex_hull_vertices.push_back(set_of_points[edges.back().origin]);
    std::size_t current_destination = edges.back().destination;
    edges.pop_back();
    
    while(edges.size() > 0){

        for(std::size_t i = 0; i < edges.size(); i++){

            if(edges[i].origin == current_destination){
                convex_hull_vertices.push_back(set_of_points[edges[i].origin]);
                current_destination = edges[i].destination;
                edges.erase(edges.begin() + i);
                break;
            }
        }
    }


    return ;
}

// ----------------------------------------------------------------- //
/*
Graham Scan Convex Hull Algorithm

Described in Chapter I of "Computational Geometry".
It has a time complexity of O( n log(n) )
*/
void GrahamScanCH(const std::vector<Vector2D>& set_of_points, 
                 std::vector<Vector2D>& convex_hull_vertices){
                    
    // Copying input array
    const unsigned points_size = set_of_points.size();
    std::vector<Vector2D> points = set_of_points;

    // Lexicographycally Sort points
    sort(points.begin(), points.end(), Vector2D::lexographycal_sort);

    // Compute the upper hull
    std::vector<Vector2D> l_upper;
    l_upper.push_back(points[0]);
    l_upper.push_back(points[1]);

    for(int i = 2; i < points.size(); i++){
        
        l_upper.push_back(points[i]);

        while(l_upper.size() > 2 and (check_for_right_turn(l_upper) == false)) {

            l_upper.erase(l_upper.end() - 2);
        }

    }

    // Compute the lower hull
    std::vector<Vector2D> l_lower;
    l_lower.push_back(points[points_size-1]);
    l_lower.push_back(points[points_size-2]);

    for(int i = points_size-3; i >= 0 ; i--){
        
        l_lower.push_back(points[i]);

        while(l_lower.size() > 2 and !check_for_right_turn(l_lower)) {

            l_lower.erase(l_lower.end() - 2);
        }

    }
    
    // Removing the first and the last point from the lower hull to avoid duplication
    // of the points  where the upper and lower hull meet.
    l_lower.erase(l_lower.begin());
    l_lower.erase(l_lower.end());

    // Appending lower hull to upper hull
    l_upper.insert(l_upper.end(), l_lower.begin(), l_lower.end());

    // Move l_upper content to convex_hull_vertices
    convex_hull_vertices = std::move(l_upper);

    return ;
}

// ----------------------------------------------------------------- //
/*
Gift Wrapping Algorithm (Jarvis March)

It has a time complexity of O( n h )
where n is the number of given points and h is the number of 
convex hull points
*/
void JarvisMarch(const std::vector<Vector2D>& set_of_points, std::vector<Vector2D>& convex_hull_vertices){

    // Copying input array
    const unsigned points_size = set_of_points.size();
    std::vector<Vector2D> points = set_of_points;

    // Find leftmost index O(n)
    size_t leftmost_index = 0;
    for(size_t i = 0; i < points_size; i++){
        if(points[leftmost_index].m_x < points[i].m_x) leftmost_index = i;
    }

    // Initialize convex hull verteces with the leftmost point
    int selected_index = leftmost_index;
    int query_index;
    do {
        // Check if point already inserted      
        convex_hull_vertices.push_back(points[selected_index]);

        query_index = (selected_index+1)%points_size;
        
        for (size_t j = 0; j < points_size; j++) {
            
            if(j == query_index or j == selected_index) continue;
    
            if (check_for_right_turn({points[selected_index], points[query_index], points[j]})) {
                query_index = j;
            }
        }

        selected_index = query_index;

    } while (selected_index != leftmost_index);

    return ;
}

// ----------------------------------------------------------------- //
/*
Check if the given vectors make a right turn

p1\  / p3
   \/      : This should return false
    p2

It evaluates the sign of the z-component of the cross-product of P_21 x P_31 
where the two Vector2D are extended to 3D with 0 as z-component
It returns 0 if the point makes a left turn or are collinear otherwise
it will return 1.
*/
bool check_for_right_turn(const std::vector<Vector2D>& ps){

    // Ensure there are at least 3 points
    if (ps.size() < 3) {
        throw std::invalid_argument("At least 3 points are required.");
    }

    // Access points
    const Vector2D& p1 = ps[ps.size() - 3];
    const Vector2D& p2 = ps[ps.size() - 2];
    const Vector2D& p3 = ps[ps.size() - 1];

    // Compute the cross product
    double cross_product = (p2.m_x - p1.m_x) * (p3.m_y - p1.m_y) - (p3.m_x - p1.m_x) * (p2.m_y - p1.m_y);

    // Return true if the cross product is negative (right turn)
    return cross_product < 0;
}

}

}