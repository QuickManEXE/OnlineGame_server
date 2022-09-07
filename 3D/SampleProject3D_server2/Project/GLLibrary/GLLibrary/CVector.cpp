#include "CVector.h"
#include "CMatrix.h"


const CVector2D CVector2D::up(0, -1);
const CVector2D CVector2D::down(0, 1);
const CVector2D CVector2D::left(-1, 0);
const CVector2D CVector2D::right(1, 0);
const CVector2D CVector2D::zero(0, 0);


const CVector3D CVector3D::up(0, 1, 0);
const CVector3D CVector3D::down(0, -1, 0);
const CVector3D CVector3D::left(1, 0, 0);
const CVector3D CVector3D::right(-1, 0, 0);
const CVector3D CVector3D::front(0, 0, 1);
const CVector3D CVector3D::back(0, 0, -1);
const CVector3D CVector3D::zero(0, 0,0);



CVector3D::CVector3D(const CVector4D& v) { x = v.x; y = v.y; z = v.z; }
CVector3D CVector3D::operator = (const CVector4D& v) { x = v.x; y = v.y; z = v.z; return *this; }

CVector3D CVector3D::Leap(const CVector3D& s, const CVector3D& e, float t) {
	return s + (e - s) * t;
}
CVector3D CQuaternion::operator* (const CVector3D &v) const {

	float qx = x, qy = y, qz = z, qw = w;

	// calculate quat * vector

	float ix = qw * v.x + qy * v.z - qz * v.y;
	float iy = qw * v.y + qz * v.x - qx * v.z;
	float iz = qw * v.z + qx * v.y - qy * v.x;
	float iw = -qx * v.x - qy * v.y - qz * v.z;

	// calculate result * inverse quat
	CVector3D ret;
	ret.x = ix * qw + iw * -qx + iy * -qz - iz * -qy;
	ret.y = iy * qw + iw * -qy + iz * -qx - ix * -qz;
	ret.z = iz * qw + iw * -qz + ix * -qy - iy * -qx;

	return ret;

}
CQuaternion CQuaternion::operator *(const CQuaternion &a) const {
	CQuaternion ret;
	ret.w = w*a.w - x*a.x - y*a.y - z*a.z;
	ret.x = w*a.x + x*a.w + z*a.y - y*a.z;
	ret.y = w*a.y + y*a.w + x*a.z - z*a.x;
	ret.z = w*a.z + z*a.w + y*a.x - x*a.y;

	return ret;
}

void CQuaternion::RotationX(float a) {
	float a2 = a / 2;
	w = cosf(a2);
	x = sinf(a2);
	y = 0.0f;
	z = 0.0f;
}
void CQuaternion::RotationY(float a) {
	float a2 = a / 2;
	w = cosf(a2);
	x = 0.0f;
	y = sinf(a2);
	z = 0.0f;
}
void CQuaternion::RotationZ(float a) {
	float a2 = a / 2;
	w = cosf(a2);
	x = 0.0f;
	y = 0.0f;
	z = sinf(a2);
}
void CQuaternion::Normalize() {
	float l = Length();

	if (l == 0) {
		x = 0;
		y = 0;
		z = 0;
		w = 1;

	} else {
		x = x / l;
		y = y / l;
		z = z / l;
		w = w / l;

	}
}

void CQuaternion::SetEuler(float ax, float ay, float az) {
	float ch = cosf(ay / 2.f);
	float sh = sinf(ay / 2.f);
	float cp = cosf(ax / 2.f);
	float sp = sinf(ax / 2.f);
	float cb = cosf(az / 2.f);
	float sb = sinf(az / 2.f);

	w = ch*cp*cb + sh*sp*sb;
	x = ch*sp*cb + sh*cp*sb;
	y = -ch*sp*sb + sh*cp*cb;
	z = -sh*sp*cb + ch*cp*sb;
}
void CQuaternion::SetEuler(CVector3D e) {
	SetEuler(e.x, e.y, e.z);
}
void CQuaternion::RotationAxis(float ax, float ay, float az, float angle) {
	float a2 = angle / 2;
	float s = sinf(a2);
	w = cosf(a2);
	x = ax * s;
	y = ay * s;
	z = az * s;
}
float CQuaternion::Dot(const CQuaternion &q0, const CQuaternion &q1) {
	return q0.w*q1.w + q0.x*q1.x + q0.y*q1.y + q0.z*q1.z;
}
CQuaternion CQuaternion::Slerp(const CQuaternion &q0, const CQuaternion &q1, float t) {
	if (t >= 1) return q1;
	if (t <= 0) return q0;
	float cosOmega = Dot(q0, q1);
	float q1w = q1.w;
	float q1x = q1.x;
	float q1y = q1.y;
	float q1z = q1.z;
	if (cosOmega < 0.0f) {
		q1w = -q1w;
		q1x = -q1x;
		q1y = -q1y;
		q1z = -q1z;
		cosOmega = -cosOmega;
	}
	float k0, k1;
	if (cosOmega > 0.9999f) {
		k0 = 1.0f - t;
		k1 = t;
	}
	else {
		float sinOmega = sqrtf(1.0f - cosOmega*cosOmega);
		float omega = atan2f(sinOmega, cosOmega);
		float iv = 1.0f / sinOmega;
		k0 = sinf((1.0f - t)*omega)*iv;
		k1 = sinf(t*omega)*iv;
	}
	CQuaternion ret;
	ret.x = k0*q0.x + k1*q1x;
	ret.y = k0*q0.y + k1*q1y;
	ret.z = k0*q0.z + k1*q1z;
	ret.w = k0*q0.w + k1*q1w;
	return ret;
}

void CQuaternion::SetVecter(CVector3D &v) {

	float dot = CVector3D::Dot(CVector3D(0, 0, 1), v);

	if (fabsf(dot - (-1.0f)) < 0.000001f)
	{
		x = 0;
		y = 1;
		z = 0;
		w = (float)M_PI;
	}
	if (fabsf(dot - (1.0f)) < 0.000001f)
	{
		x = 0;
		y = 0;
		z = 0;
		w = 1;
	}
	else {

		float rotAngle = acosf(dot);
		CVector3D rotAxis = CVector3D::Cross(CVector3D(0, 0, 1), v);
		rotAxis = rotAxis.GetNormalize();

		RotationAxis(rotAxis.x, rotAxis.y, rotAxis.z, rotAngle);
	}

}
void CQuaternion::LookAt(CVector3D &p, CVector3D &at) {
	CVector3D forwardVector = (at - p).GetNormalize();
	SetVecter(forwardVector);
}
void CQuaternion::SetRotateMatrix(const CMatrix &m) {
	float m11 = m.m00, m12 = m.m01, m13 = m.m02,
		m21 = m.m10, m22 = m.m11, m23 = m.m12,
		m31 = m.m20, m32 = m.m22, m33 = m.m23,
		trace = m11 + m22 + m33,
		s;

	if (trace > 0) {

		s = 0.5f / sqrtf(trace + 1.0f);

		w = 0.25f / s;
		x = (m32 - m23) * s;
		y = (m13 - m31) * s;
		z = (m21 - m12) * s;

	}
	else if (m11 > m22 && m11 > m33) {

		s = 2.0f * sqrtf(1.0f + m11 - m22 - m33);

		w = (m32 - m23) / s;
		x = 0.25f * s;
		y = (m12 + m21) / s;
		z = (m13 + m31) / s;

	}
	else if (m22 > m33) {

		s = 2.0f * sqrtf(1.0f + m22 - m11 - m33);

		w = (m13 - m31) / s;
		x = (m12 + m21) / s;
		y = 0.25f * s;
		z = (m23 + m32) / s;

	}
	else {

		s = 2.0f * sqrtf(1.0f + m33 - m11 - m22);

		w = (m21 - m12) / s;
		x = (m13 + m31) / s;
		y = (m23 + m32) / s;
		z = 0.25f * s;

	}
}

CVector3D CQuaternion::GetEuler(int type) const {
	CMatrix m;
	m.SetQuaternion(x,y,z,w);

	return m.GetEuler(type);

	/*
	CVector3D ret;
	float sp = -2.0f*(y*z - w*x);
	if (fabs(sp) > 0.9999f) {
		ret.x = M_PI_2*sp;
		ret.y = atan2(-x*z + w*y, 0.5f - y*y - z*z);
		ret.z = 0;
	}
	else {
		ret.x = asin(sp);
		ret.y = atan2(x*z + w*y, 0.5f - x*x - y*y);
		ret.z = atan2(x*y + w*z, 0.5f - x*x - z*z);
	}
	return ret;
	}*/
}
