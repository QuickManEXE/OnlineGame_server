#pragma once


#include "GL.h"
#include <map>
#include <string>
class CShader {
public:
	enum {
		eVertexLocation,
		eNormalLocation,
		eTexcoordlLocation,
		eWeightsLocation,
		eIndicesLocation,
	};

private:
	GLuint vertexShader;
	GLuint flagShader;

	GLuint program;
	GLint compiled;
	GLint linked;
	
	static std::map<std::string, CShader*> m_instances;

	bool readFile(GLuint program,GLuint shader, const char *file);


	bool readRaw(GLuint program, GLuint shader, const char* code);

	bool loadraw(const char* vertexcode, const char* flagcode);
public:
	static CShader* GetInstance(std::string type) {
		if (!m_instances[type]) m_instances[type] = new CShader(type);
		return m_instances[type];
	}
	CShader();
	CShader(std::string type);
	CShader(const char* vertexPath,const char*  flagPath);
	~CShader();
	bool load(const char* vertexPath,const char*  flagPath);
	bool load(const char* path,GLuint type);
	void enable();
	void disable();
	GLuint GetProgram() const{
		return program;
	}


};