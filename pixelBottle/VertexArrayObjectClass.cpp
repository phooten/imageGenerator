#include"VertexArrayObjectClass.h"

VertexArrayObject::VertexArrayObject() {
	glGenVertexArrays(1, &ID);
}

void VertexArrayObject::LinkVertexBufferObject(VertexBufferObject& VertexBufferObject, GLuint layout) {
	VertexBufferObject.Bind();
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
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