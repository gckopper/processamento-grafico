#include "twod.h"
#include <numbers>

namespace twod {
    /**
     * Rotates this vertex by angle degrees
     */
    void Vertex::rotate(float angle) {
        // convert degrees to radians
        angle = angle/180.0f * std::numbers::pi;
        const float co = std::cos(angle);
        const float si = std::sin(angle);
        const float x = this->x*co - this->y*si;
        const float y = this->y*co + this->x*si;
        this->x = x;
        this->y = y;
    }
    void Vertex::add(float x, float y) {
        this->x += x;
        this->y += y;
    }
    void Vertex::move(float dist, float angle) {
        // convert degrees to radians
        angle = angle/180.0f * std::numbers::pi;
        this->x += dist * std::cos(angle);
        this->y += dist * std::sin(angle);
    }
    Vertex Vertex::clone() {
        return Vertex(this->x, this->y);
    }
    bool Vertex::operator==(const Vertex &other) {
        return this->x == other.x && this->y == other.y;
    }
    Vertex Vertex::operator+(const Vertex &other) {
        return Vertex(this->x+other.x, this->y+other.y);
    }

    std::vector<Vertex> make_convex_regular_polygon(uint32_t num_vert, float radius, Vertex middle) {
        return make_star_regular_polygon(num_vert, radius, radius, middle);
    }
    std::vector<Vertex> make_star_regular_polygon(uint32_t num_vert, float small_radius, float big_radius, Vertex middle) {
        const float angle = 360.0f / num_vert;
        return make_regular_polygon(num_vert, angle, small_radius, big_radius, middle);
    }
    std::vector<Vertex> make_regular_polygon(uint32_t num_vert, float angle, float small_radius, float big_radius, Vertex middle) {
        std::vector<Vertex> result;
        result.reserve(num_vert+2);
        result.push_back(middle);
        float binary_star[2] = {big_radius, small_radius};
        for (uint32_t i = 0; i < num_vert; ++i) {
            result.push_back(middle);
            result[i+1].move(binary_star[i & 1], angle*i);
        }
        if (angle * num_vert > 355) {
            result.push_back(result[1]);
        }
        return result;
    }
}
