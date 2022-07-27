#pragma once
#include "CVector.h"
class CRect {
public:
	union {
		struct {
			float m_left;
			float m_top;
			float m_right;
			float m_bottom;
		};
		struct {
			float m_x;
			float m_y;
			float m_width;
			float m_height;
		};
		struct {
			CVector2D m_pos;
			CVector2D m_size;
		};
	};
	CRect() {
	}
	CRect(float l,float t,float r,float b){
		m_left = l;
		m_top = t;
		m_right = r;
		m_bottom = b;
	}
	CRect(const CVector2D& pos, const CVector2D& size) {
		m_pos = pos;
		m_size = size;
	}
	CRect(const CRect& rect) {
		m_left = rect.m_left;
		m_top = rect.m_top;
		m_right = rect.m_right;
		m_bottom = rect.m_bottom;
	}
};