#pragma once
#include "GL.h"
#include <map>
#include <string>
class CFont {
private:
	HFONT Hfont;
	HDC Hdc;
	int height;
	static std::map<std::string, CFont*> m_instances;
public:
	CFont(const char *font = "‚l‚rƒSƒVƒbƒN", int size=24);
	void Draw(int x,int y,float r,float g,float b, const char *format, ...);
	void Draw(int x, int y, float r, float g, float b, const wchar_t *format, ...);

	void Release();

	static CFont* GetInstance(std::string name) {
		if (m_instances.count(name) == 0) m_instances[name] = new CFont();
		return m_instances[name];
	}
	static void CreateInstance(std::string name,const char *font = "‚l‚rƒSƒVƒbƒN", int size = 24) {
		m_instances[name] = new CFont(font,size);
	}
};

#define FONT_T()	CFont::GetInstance("default")
#define FONT(name)	CFont::GetInstance(name)
#define CREATE_FONT(name)	CFont::CreateInstance(name)
#define CREATE_FONT_F(name,font,size)	CFont::CreateInstance(name,font,size)