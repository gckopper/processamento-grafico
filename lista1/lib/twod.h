#include <cmath>
#include <cstdint>
#include <vector>

#pragma once

namespace twod {
    class Vertex {
        private:
            float x;
            float y;
        public:
            Vertex(float x, float y): x(x), y(y) {}
            void rotate(float angle);
            void add(float x, float y);
            void move(float dist, float angle);
            Vertex clone();
            float getX();
            float getY();
            bool operator==(const Vertex &other);
            Vertex operator+(const Vertex &other);
    };
    bool operator==(Vertex a, Vertex b);
    std::vector<Vertex> make_convex_regular_polygon(uint32_t num_vert, float radius, Vertex middle);
    std::vector<Vertex> make_star_regular_polygon(uint32_t num_vert, float small_radius, float big_radius, Vertex middle);
    std::vector<Vertex> make_regular_polygon(uint32_t num_vert, float angle, float small_radius, float big_radius, Vertex middle);
}
