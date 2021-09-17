#include"VertexBufferObjectClass.h"

VertexBufferObject::VertexBufferObject(GLfloat* vertices, GLsizeiptr size) {
	// Setting up Vertices Buffer
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void VertexBufferObject::Bind() {
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VertexBufferObject::Unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBufferObject::Delete() {
	glDeleteBuffers(1, &ID);
}