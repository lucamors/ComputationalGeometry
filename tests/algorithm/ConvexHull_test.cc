#include <algorithm/ConvexHull.hh>
#include <basic/Vector2D.hh>
#include <vector>
#include <algorithm>
#include <gtest/gtest.h>

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

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}