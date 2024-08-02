#include <algorithm/ConvexHull.hh>
#include <basic/Vector2D.hh>
#include <ctime>
#include <vector>
#include <memory>
#include <random>
#include <iostream>
#include <algorithm>
#include <gtest/gtest.h>
#include <geos/geom/Coordinate.h>
#include <geos/geom/GeometryFactory.h>
#include <geos/geom/Point.h>
#include <geos/geom/MultiPoint.h>
#include <geos/algorithm/ConvexHull.h>

TEST(ConvexHullTest, input_vector_with_low_dimension)
{
    std::vector<Vector2D> vertices = { 
        { 2, 1 },
        { 5, 2 },
        { 2, 5 },
        { 3, 3 },
    };

    std::vector<Vector2D> convex_hull_vertices;
    cg::algorithm::ConvexHull(vertices, convex_hull_vertices, cg::algorithm::CHTYPE::GRAHAM);

    // Sort output array
    std::sort(convex_hull_vertices.begin(), convex_hull_vertices.end(),Vector2D::lexographycal_sort);

    // Declare and sort expected array
    std::vector<Vector2D> expected = { 
        { 2, 1 },
        { 5, 2 },
        { 2, 5 },
    };
    std::sort(expected.begin(), expected.end(),Vector2D::lexographycal_sort);

    ASSERT_EQ(convex_hull_vertices, expected);
}

TEST(ConvexHullTest, uniform_distributed_points)
{
    // Initialize rng
    std::random_device rd;
    std::mt19937 generator(rd());

    // Define the distribution range
    std::uniform_real_distribution<float> distribution(0.0, 100.0);

    // Creating points along circonference
    const size_t vertices_number = 5000;
    std::vector<Vector2D> vertices;
    vertices.reserve(vertices_number);

    for(auto i = 0; i < vertices_number; i++)
        vertices.push_back({ distribution(generator), distribution(generator) });

    // Convex Hull Computation using cglib
    std::vector<Vector2D> convex_hull_vertices;
    cg::algorithm::ConvexHull(vertices, convex_hull_vertices, cg::algorithm::CHTYPE::GRAHAM);
    
    // Convex Hull Computation using GEOS
    // Step 1: Create the GeometryFactory
    const geos::geom::GeometryFactory* factory = geos::geom::GeometryFactory::getDefaultInstance();

    // Step 2: Define the points
    std::vector<geos::geom::Coordinate> coordinates;
    for(const auto& point : vertices) coordinates.emplace_back(point.m_x, point.m_y);

    // Step 4: Create a MultiPoint collection
    auto multipoint = factory->createMultiPoint(coordinates);

    // Step 5: Compute the Convex Hull
    auto hull = multipoint->convexHull();

    // Retrieve the coordinates from the hull
    auto hullCoordinates = hull->getCoordinates();

    // Prepare the result vector
    std::vector<Vector2D> expected;
    expected.reserve(vertices_number);

    for (size_t i = 1; i < hullCoordinates->getSize(); ++i) {
        const geos::geom::Coordinate& coord = hullCoordinates->getAt(i);
        expected.push_back({(float)coord.x, (float)coord.y});
    }

    // Sorting result in lexographycal order for avoiding different ordering
    // How GEOS order to vertices of the Hull?
    sort(convex_hull_vertices.begin(),convex_hull_vertices.end(),Vector2D::lexographycal_sort);
    sort(expected.begin(),expected.end(),Vector2D::lexographycal_sort);
    
    ASSERT_EQ(convex_hull_vertices, expected);
}


TEST(ConvexHullTest, points_along_circonference)
{
    // Creating points along circonference
    const size_t vertices_number = 5000;
    std::vector<Vector2D> vertices;
    vertices.reserve(vertices_number);

    for(auto i = 0; i < vertices_number; i++){

        const float angle = (i*1.0)/100*2*M_PI;
        const float radius = 5.0;
        vertices.push_back({ radius * ((float)cos(angle)), radius*((float)sin(angle)) });
    }

    // Convex Hull Computation using cglib
    std::vector<Vector2D> convex_hull_vertices;
    cg::algorithm::ConvexHull(vertices, convex_hull_vertices, cg::algorithm::CHTYPE::GRAHAM);
    
    // Convex Hull Computation using GEOS
    // Step 1: Create the GeometryFactory
    const geos::geom::GeometryFactory* factory = geos::geom::GeometryFactory::getDefaultInstance();

    // Step 2: Define the points
    std::vector<geos::geom::Coordinate> coordinates;
    for(const auto& point : vertices) coordinates.emplace_back(point.m_x, point.m_y);

    // Step 4: Create a MultiPoint collection
    auto multipoint = factory->createMultiPoint(coordinates);

    // Step 5: Compute the Convex Hull
    auto hull = multipoint->convexHull();

    // Retrieve the coordinates from the hull
    auto hullCoordinates = hull->getCoordinates();

    // Prepare the result vector
    std::vector<Vector2D> expected;
    expected.reserve(vertices_number);

    for (size_t i = 1; i < hullCoordinates->getSize(); ++i) {
        const geos::geom::Coordinate& coord = hullCoordinates->getAt(i);
        expected.push_back({(float)coord.x, (float)coord.y});
    }

    // All points should be on the hull
    ASSERT_EQ(convex_hull_vertices.size(), expected.size());
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}