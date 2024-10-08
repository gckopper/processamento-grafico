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
    float Vertex::getX() {
        return this->x;
    }
    float Vertex::getY() {
        return this->y;
    }
    bool operator==(Vertex a, Vertex b) {
        return a.getX() == b.getX();
    }
    Vertex Vertex::operator+(const Vertex &other) {
        return Vertex(this->x+other.x, this->y+other.y);
    }

    std::vector<Vertex> make_convex_regular_polygon(uint32_t num_vert, float radius, Vertex middle) {
        return make_star_regular_polygon(num_vert, radius, radius, middle);
    }
    std::vector<Vertex> make_elipse(uint32_t num_vert, float radius, float ratioX, float ratioY, Vertex middle) {
        std::vector<Vertex> result = make_convex_regular_polygon(num_vert, radius, middle);
        for (uint32_t i = 0; i < result.size(); ++i) {
            result[i].add(result[i].getX()*(ratioX-1), result[i].getY()*(ratioY-1));
        }
        return result;
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
    std::vector<Vertex> make_spiral(float radius, float decay, Vertex middle) {
        std::vector<Vertex> result;
        const uint32_t dots = radius/decay * 72.0f;
        result.reserve(dots);
        for (uint32_t i = 0; i < dots; ++i) {
            Vertex dot = middle;
            dot.move(radius-(i*decay/72.0f), 5*i);
            result.push_back(dot);
        }
        return result;
    }
}
