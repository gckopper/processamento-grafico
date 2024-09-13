#include "vaoBuilder.h"

VAOBuilder::VAOBuilder(GLuint shader) {
    GLint result = 0;
    glGetProgramiv(shader, GL_ACTIVE_ATTRIBUTES, &result);
    // fazer algo quando falha
    if (result == 0) {
        std::cerr << "Shader has no attributes yet the code tries to build a VAO\n";
        exit(-2);
    }
    GLint max_size = 0;
    glGetProgramiv(shader,GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &max_size);
    // fazer algo quando falha
    std::string name(' ', max_size+2);
    GLint name_end = 0;
    GLint size = 0;
    GLint len = 0;
    GLenum type = 0;
    size_t offset = 0;
    for (int i = 0; i < result; ++i) {
        glGetActiveAttrib(shader, i, max_size, &name_end, &size, &type, name.data());
        if (name.starts_with("gl_")) {
            continue;
        }
        std::string local_name = name.substr(0, name_end);
        
        GLint loc = glGetAttribLocation(shader, local_name.c_str());

        len = size * glprimitive_to_size(type);
        size = glprimitive_to_size(type) / glprimitive_to_size(glprimitive_decay(type));
        VertElem new_elem;
        new_elem.primitive = glprimitive_decay(type);
        new_elem.len = len;
        new_elem.offset = offset;
        new_elem.id = loc;
        new_elem.size = size;
        
        offset += len;
        atributts[local_name] = new_elem;
    }
    vertex_size = offset;
}

GLuint VAOBuilder::build() {
    GLuint VBO, VAO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, this->vbo.size(), this->vbo.data(), GL_STATIC_DRAW);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    for (auto elem : atributts) {
        glVertexAttribPointer(elem.second.id,
                elem.second.size,
                elem.second.primitive,
                GL_FALSE,
                vertex_size,
                (void*)(elem.second.offset % vertex_size));
        glEnableVertexAttribArray(elem.second.id);
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    return VAO;
}
