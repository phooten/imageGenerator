#ifndef VERTEX_ARRAY_OBJECT_CLASS_H
#define VERTEX_ARRAY_OBJECT_CLASS_H

#include<glad/glad.h>
#include"VertexBufferObjectClass.h"

class VertexArrayObject{
	public:
		GLuint ID;

		VertexArrayObject();
	
		void LinkVertexBufferObject(VertexBufferObject& VertexBufferObject, GLuint layout);
		void Bind();
		void Unbind();
		void Delete();

	private:
};

#endif // !VERTEX_ARRAY_OBJECT_CLASS_H

