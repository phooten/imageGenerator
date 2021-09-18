#include"VertexArrayObjectClass.h"

VertexArrayObject::VertexArrayObject() {
	glGenVertexArrays(1, &ID);
}

void VertexArrayObject::LinkAttrib(VertexBufferObject& VertexBufferObject, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset) {
	VertexBufferObject.Bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);

	VertexBufferObject.Unbind();
}

void VertexArrayObject::Bind() {
	glBindVertexArray(ID);
}

void VertexArrayObject::Unbind() {
	glBindVertexArray(0);
}

void VertexArrayObject::Delete() {
	glDeleteVertexArrays(1, &ID);
}