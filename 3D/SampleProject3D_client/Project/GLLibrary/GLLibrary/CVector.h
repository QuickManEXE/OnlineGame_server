#pragma once
#include "GL.h"
class CVector3D;
class CVector4D;
class CMatrix;
//�x�N�g���̒�`�Ɗe��v�Z
struct SVector2D{
	union {
		float v[2];
		struct {
			float x;
			float y;
		};
		struct {
			int ix;
			int iy;
		};
	};
};
class CVector2D : public SVector2D{
public:
	CVector2D(){}
	CVector2D( float x, float y) {this->x = x; this->y = y;}
	CVector2D( const CVector2D& v ) { x = v.x; y = v.y; }
	
	//�P�����Z�q-
	CVector2D operator - () const { return CVector2D(-x,- y); }

	//�x�N�g�������Z( this - v )
	CVector2D operator - ( const CVector2D& v ) const { return CVector2D( x - v.x, y - v.y ); }
	//�x�N�g�������Z( this - v )
	void operator -= ( const CVector2D& v )  { x -= v.x; y -= v.y;  }
	
	//�x�N�g�������Z( this + v )
	CVector2D operator + ( const CVector2D& v ) const { return CVector2D( x + v.x, y + v.y); }
	
	//�x�N�g�������Z( this + v )
	void operator += ( const CVector2D& v )  {  x += v.x; y += v.y; }

	//�x�N�g���|���Z( this * f )
	CVector2D operator * ( const float& f ) const { return CVector2D( x * f, y * f); }
	//�x�N�g���|���Z( this * f )
	void operator *= ( const float& f ) { x *= f; y *= f; }
	//�x�N�g������Z( this * f )
	CVector2D operator / ( const float& f ) const { return CVector2D( x / f, y / f); }
	
	//�x�N�g���̓���
	float Dot(const CVector2D& v)const{
		return x*v.x + y*v.y;
	}
	static float Dot(const CVector2D& v1,const CVector2D& v2) {
		return v1.x*v2.x + v1.y*v2.y;
	}
	//�x�N�g���̊O��
	float Cross(const CVector2D& v)const {
		return x*v.y - y*v.x;
	}
	static float Cross(const CVector2D& v1, const CVector2D& v2) {
		return v1.x*v2.y - v1.y*v2.x;
	}


	//�x�N�g���̑傫��
	float Length() const {
		return powf( ( x * x ) + ( y * y ), 0.5f );//�x�N�g���̒���;
	}
	//�x�N�g���̑傫���̂Q��
	float LengthSq() const {
		return ( x * x ) + ( y * y );
	}
	//���g��P�ʃx�N�g���ɂ���
	void Normalize() {
		float length = Length();
		x /= length;
		y /= length;
	}
	//�P�ʃx�N�g����ԋp
	CVector2D GetNormalize() const {
		CVector2D out = *this;
		out.Normalize();
		return out;
	}

	const static CVector2D up;
	const static CVector2D down;
	const static CVector2D left;
	const static CVector2D right;
	const static CVector2D zero;
};

typedef struct SVector3D{
	union {
		float v[3];
		struct {
			float x;
			float y;
			float z;
		};
		struct {
			float r;
			float g;
			float b;
		};
		struct {
			long ix;
			long iy;
			long iz;
		};
	};
}SColorRGB;
class CVector3D : public SVector3D{
public:
	
	CVector3D(){}
	CVector3D( float x, float y, float z) {this->x = x; this->y = y; this->z = z; }
	CVector3D(const CVector3D& v) { x = v.x; y = v.y; z = v.z; }
	CVector3D(const SVector3D& v) { x = v.x; y = v.y; z = v.z; }
	CVector3D(const SVector2D& v) { x = v.x; y = v.y; z = 0; }
	CVector3D(const CVector4D&);
	CVector3D operator = (const CVector4D&);

	//�x�N�g�������Z( this - v )
	CVector3D operator - () const { return CVector3D(-x,-y,-z); }


	//�x�N�g�������Z( this - v )
	CVector3D operator - ( const CVector3D& v ) const { return CVector3D( x - v.x, y - v.y, z - v.z ); }
	//�x�N�g�������Z( this - v )
	void operator -= ( const CVector3D& v )  { x -= v.x; y -= v.y; z -= v.z;  }
	
	//�x�N�g�������Z( this + v )
	CVector3D operator + ( const CVector3D& v ) const { return CVector3D( x + v.x, y + v.y, z + v.z ); }
	
	//�x�N�g�������Z( this + v )
	void operator += ( const CVector3D& v )  {  x += v.x; y += v.y; z += v.z; }

	//�x�N�g���|���Z( this * f )
	CVector3D operator * ( const float& f ) const { return CVector3D( x * f, y * f, z * f ); }
	//�x�N�g���|���Z( this * f )
	void operator *= ( const float& f ) { x *= f; y *= f; z *= f; }
	//�x�N�g������Z( this * f )
	CVector3D operator / ( const float& f ) const { return CVector3D( x / f, y / f, z / f ); }
	
	//�x�N�g���O��( this �~ vr )
	CVector3D operator * ( const CVector3D& vr ) const { return CVector3D( (y * vr.z) - (z * vr.y), (z * vr.x) - (x * vr.z), (x * vr.y) - (y * vr.x) ); }
	
	//�x�N�g���̓���
	float Dot(const CVector3D& v)const{
		return x*v.x + y*v.y + z*v.z;
	}
	static float Dot(const CVector3D& v1,const CVector3D& v2) {
		return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
	}
	//�x�N�g���̊O��
	CVector3D Cross(CVector3D& v)const {
		return CVector3D(y*v.z-z*v.y, z*v.x - x*v.z , x*v.y - y*v.x);
	}
	static CVector3D Cross(const CVector3D& v1,const CVector3D& v2) {
		return CVector3D(v1.y*v2.z-v1.z*v2.y, v1.z*v2.x - v1.x*v2.z , v1.x*v2.y - v1.y*v2.x);
	}
	//�x�N�g���̑傫��
	float Length() const {
		return powf( ( x * x ) + ( y * y ) + ( z * z ), 0.5f );//�x�N�g���̒���;
	}
	//�x�N�g���̑傫���̂Q��
	float LengthSq() const {
		return ( x * x ) + ( y * y ) + ( z * z );
	}
	static CVector3D Leap(const CVector3D& s, const CVector3D& e, float t);
	/*
	CVector3D GetEuler() {
		CVector3D ret(0, 0, 0);
		ret.x = -asin(y);
		ret.y = atan2(x,z);
		return ret;
	}
	void SetDir(CVector3D v) {
		x = sin(v.y) * cos(v.x);
		y = -sin(v.x);
		z = cos(v.y) * cos(v.x);

	}
	*/
	//���g��P�ʃx�N�g���ɂ���
	void Normalize() {
		float length = Length();
		if (length == 0) return;
		x /= length;
		y /= length;
		z /= length;
	}
	//�P�ʃx�N�g����ԋp
	CVector3D GetNormalize() const {
		CVector3D out = *this;
		out.Normalize();
		return out;
	}

	const static CVector3D up;
	const static CVector3D down;
	const static CVector3D left;
	const static CVector3D right;
	const static CVector3D front;
	const static CVector3D back;
	const static CVector3D zero;

};
typedef struct SVector4D{
	union {
		float v[4];
		struct {
			float x;
			float y;
			float z;
			float w;
		};
		struct {
			float r;
			float g;
			float b;
			float a;
		};
	};
}SColorRGBA;

class CVector4D : public SVector4D{
public:
	CVector4D(){}
	CVector4D( float x, float y, float z, float w) {this->x = x; this->y = y; this->z = z; this->w = w; }
	CVector4D(const CVector3D& v, float w) { this->x = v.x; this->y = v.y; this->z = v.z; this->w = w; }
	//�x�N�g�������Z( this - v )
	CVector4D operator - (const CVector4D& v) const { return CVector4D(x - v.x, y - v.y, z - v.z,w-v.w); }
	//�x�N�g�������Z( this - v )
	void operator -= (const CVector4D& v)  { x -= v.x; y -= v.y; z -= v.z; w -= v.w; }

	//�x�N�g�������Z( this + v )
	CVector4D operator + (const CVector4D& v) const { return CVector4D(x + v.x, y + v.y, z + v.z,w+v.w); }

	//�x�N�g�������Z( this + v )
	void operator += (const CVector4D& v)  { x += v.x; y += v.y; z += v.z; w += v.w; }

};
typedef CVector4D CColorRGBA; 


class CQuaternion : public SVector4D {
public:
	//�R���X�g���N�^
	CQuaternion() {
		x = 0; y = 0; z = 0; w = 1;
	}
	//�x�N�g���Ƃ̐�
	CVector3D operator* (const CVector3D &v) const;
	//�N�H�[�^�j�I�����m�̐�
	CQuaternion operator *(const CQuaternion &a) const;
	//X����]
	void RotationX(float a);
	//Y����]
	void RotationY(float a);
	//Z����]
	void RotationZ(float a);
	//�C�ӎ���]
	void RotationAxis(float ax, float ay, float az, float angle);
	//��]�s�񂩂�N�H�[�^�j�I����ݒ�
	void SetRotateMatrix(const CMatrix &m);
	//�����x�N�g������N�H�[�^�j�I����ݒ�
	void SetVecter(CVector3D &v);
	//�w��̏ꏊ�ւ̃N�H�[�^�j�I�����쐬
	void LookAt(CVector3D &p, CVector3D &at);
	//�傫�����擾
	float Length() {
		return sqrtf(x * x + y * y + z * z + w * w);
	}
	//���K��
	void Normalize();
	//�I�C���[�p����N�H�[�^�j�I���ݒ�
	void SetEuler(float ax, float ay, float az);
	void SetEuler(CVector3D e);
	//�I�C���[�p���擾
	CVector3D GetEuler(int type) const;
	//����
	static float Dot(const CQuaternion &q0, const CQuaternion &q1);
	//���`���
	static CQuaternion Slerp(const CQuaternion &q0, const CQuaternion &q1, float t);
};