#ifndef VERTEX_BUFFER_OBJECT_CLASS_H
#define VERTEX_BUFFER_OBJECT_CLASS_H

#include<glad/glad.h>


class VertexBufferObject {
	public:
		GLuint ID;
		VertexBufferObject(GLfloat* vertices, GLsizeiptr size);

		void Bind();
		void Unbind();
		void Delete();

	private:
};

#endif // !VERTEX_BUFFER_OBJECT_CLASS_H
