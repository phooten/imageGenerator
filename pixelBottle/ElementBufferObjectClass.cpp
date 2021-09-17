#include"ElementBufferObjectClass.h"

ElementBufferObject::ElementBufferObject(GLuint* windingOrder, GLsizeiptr size) {
	// Setting up Element Buffer (winding order)	-> Gets linked to VertexArrayBuffer
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, windingOrder, GL_STATIC_DRAW);
}

void ElementBufferObject::Bind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void ElementBufferObject::Unbind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void ElementBufferObject::Delete() {
	glDeleteBuffers(1, &ID);
}