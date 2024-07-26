#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <chrono>
#include "include/algorithm/ConvexHull.hh"
#include "include/basic/Vector2D.hh"

int main(int argc, char* argv[]){
    
    if(argc < 2){
        std::cout << "Error. No input provided.\n";
        return 1;
    }
    
    const int N = std::stoi(argv[1]);

    if(N == 1){
        std::cout << "Input number should be greater than 1.\n";
        return 2;
    }

    // Generating a set of random vertices in the domain [0,10]x[0,10]
    std::vector<Vector2D> vertices;
    vertices.reserve(N);

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_real_distribution<float> uniform(0,10);

    for(size_t i = 0; i < N; i++){
        vertices.push_back(Vector2D(uniform(rng),uniform(rng)));
    }

    std::vector<Vector2D> convex_hull_vertices;

    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

    auto t1 = high_resolution_clock::now();
    cg::algorithm::ConvexHull(vertices, convex_hull_vertices, cg::algorithm::CHTYPE::GRAHAM);
    auto t2 = high_resolution_clock::now();

    /* Getting number of milliseconds as an integer. */
    auto ms_int = duration_cast<milliseconds>(t2 - t1);

    /* Getting number of milliseconds as a double. */
    duration<double, std::milli> ms_double = t2 - t1;

    std::cout << " -> " << ms_double.count()  << "ms" << std::endl;

    std::ofstream of("of.csv");
    of << "x,y\n";
    for(auto vertex : vertices) of << vertex.m_x << "," << vertex.m_y << "\n";

    std::ofstream res("res.csv");
    res << "x,y\n";
    for(auto vertex : convex_hull_vertices) res << vertex.m_x << "," << vertex.m_y << "\n";

    return 0;
}