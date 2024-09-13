#include <glad/gl.h>
#include <twod.h>
#include <vector>

#pragma once

class SimpleTwodVAOBuilder {
    public:
        void addVertexArray(const std::vector<twod::Vertex> &arr);
        GLuint build();
    private:
        std::vector<twod::Vertex> data;
};
