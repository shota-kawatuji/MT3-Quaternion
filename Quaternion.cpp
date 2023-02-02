#include "Quaternion.h"
#include<cmath>

Quaternion::Quaternion()
{
	this->w = 1;
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Quaternion::Quaternion(float x, float y, float z, float w)
{
	this->w = w;
	this->x = x;
	this->y = y;
	this->z = z;
}

Quaternion Quaternion::Multiply(Quaternion quaternion)
{
	Quaternion result;

	result.w = w * quaternion.w - x * quaternion.x - y * quaternion.y - z * quaternion.z;
	result.x = y * quaternion.z - z * quaternion.y + quaternion.w * x + w * quaternion.x;
	result.y = z * quaternion.x - x * quaternion.z + quaternion.w * y + w * quaternion.y;
	result.z = x * quaternion.y - y * quaternion.x + quaternion.w * z + w * quaternion.z;

	return result;
}

Quaternion Quaternion::IdentityQuaternion()
{
	Quaternion iden(0, 0, 0, 1);

	return iden;
}

Quaternion Quaternion::Conjugate()
{
	Quaternion mul;

	mul.x = -x;
	mul.y = -y;
	mul.z = -z;
	mul.w = w;

	return mul;
}

float Quaternion::Norm() const
{
	float norm = sqrt(x * x + y * y + z * z + w * w);

	return norm;
}

Quaternion Quaternion::Normalize()
{
	Quaternion result = *this;

	float len = Norm();

	if (len != 0)
	{

		result.x /= len;
		result.y /= len;
		result.z /= len;
		result.w /= len;

		return result;
	}

}

Quaternion Quaternion::Inverse()
{
	Quaternion result = this->Conjugate() / (Norm() * Norm());

	return result;
}



Vector3 Quaternion::RotateVector(const Vector3& vector)
{

	Quaternion result;

	Quaternion VecterQuaternion;

	Quaternion conjQuaternion = Conjugate();

	VecterQuaternion.w = 0;
	VecterQuaternion.x = vector.x;
	VecterQuaternion.y = vector.y;
	VecterQuaternion.z = vector.z;


	result = Multiply(VecterQuaternion);

	result = result.Multiply(conjQuaternion);

	return { result.x,result.y,result.z };
}


Matrix4 Quaternion::MakeRotateMatrix()
{
	Matrix4 result = identity();

	result.m[0][0] = this->w * this->w + this->x * this->x - this->y * this->y - this->z * this->z;
	result.m[0][1] = 2 * (this->x * this->y + this->w * this->z);
	result.m[0][2] = 2 * (this->x * this->z - this->w * this->y);
	result.m[1][0] = 2 * (this->x * this->y - this->w * this->z);
	result.m[1][1] = this->w * this->w - this->x * this->x + this->y * this->y - this->z * this->z;
	result.m[1][2] = 2 * (this->y * this->z + this->w * this->x);
	result.m[2][0] = 2 * (this->x * this->z + this->w * this->y);
	result.m[2][1] = 2 * (this->y * this->z - this->w * this->x);
	result.m[2][2] = this->w * this->w - this->x * this->x - this->y * this->y + this->z * this->z;

	return result;
}

Quaternion Quaternion::operator+() const
{
	return *this;
}

Quaternion Quaternion::operator-() const
{
	return Quaternion(-x, -y, -z, -w);
}

Quaternion& Quaternion::operator+=(const Quaternion& v)
{
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
	this->w += v.w;
	return *this;
	// TODO: return �X�e�[�g�����g�������ɑ}�����܂�
}

Quaternion& Quaternion::operator-=(const Quaternion& v)
{
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
	this->w -= v.w;
	return *this;
	// TODO: return �X�e�[�g�����g�������ɑ}�����܂�
}

Quaternion& Quaternion::operator*=(float s)
{
	this->x *= s;
	this->y *= s;
	this->z *= s;
	this->w *= s;
	return *this;
	// TODO: return �X�e�[�g�����g�������ɑ}�����܂�
}

Quaternion& Quaternion::operator/=(float s)
{
	this->x /= s;
	this->y /= s;
	this->z /= s;
	this->w /= s;
	return *this;
	// TODO: return �X�e�[�g�����g�������ɑ}�����܂�
}



Vector3 MatVector(const Vector3& vector, const Matrix4& matrix)
{
	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + matrix.m[3][3];

	Vector3 result
	{
		(vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + matrix.m[3][0] * 0.0f) / w,
		(vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + matrix.m[3][1] * 0.0f) / w,
		(vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + matrix.m[3][2] * 0.0f) / w
	};

	return result;
}

Quaternion MakeAxisAngle(const Vector3& axis, float radian)
{
	Quaternion quaternion;
	Vector3 vector;

	quaternion.w = cosf(radian / 2);
	vector = axis * sinf(radian / 2);

	quaternion.x = vector.x;
	quaternion.y = vector.y;
	quaternion.z = vector.z;

	quaternion.Normalize();

	return quaternion;
}

Quaternion Slerp(const Quaternion& q0, const Quaternion& q1, float t)
{

	Quaternion r0 = q0;
	Quaternion r1 = q1;
	float epsilon = 0.0005f;

	//����
	float dot = (r0.x * r1.x) + (r0.y * r1.y) + (r0.z * r1.z) + (r0.w * r1.w);
	//���]����
	if (dot < 0)
	{
		r0 = -r0;//�����Е��̉�]�𗘗p����
		dot = -dot;//���ς����]
	}
	//�Ȃ��p�����߂�
	float theta = std::acos(dot);

	float scale0;
	float scale1;


	//���w�̌��� sin(1-t)*�� / sin��*q0 + sin(t��) / sin�� * q1;

	//theta��sin���g���ĕ�ԌW�������߂�
	scale0 = sinf((1 - t) * theta) / sinf(theta);

	scale1 = sinf(t * theta) / sinf(theta);

	if (dot >= 1.0f - epsilon)
	{
		return (1.0 - t) * r0 + t * r1;
	}

	//��Ԍ��Quaternion�����߂�
	return scale0 * r0 + scale1 * r1;
}

const Quaternion operator+(const Quaternion& v1, const Quaternion& v2)
{
	Quaternion temp(v1);
	return temp += v2;//v1+v2
}

const Quaternion operator-(const Quaternion& v1, const Quaternion& v2)
{
	Quaternion temp(v1);
	return temp -= v2;//v1+v2
}

const Quaternion operator*(const Quaternion& v, float s)
{
	Quaternion temp(v);
	return temp *= s;//v*s
}

const Quaternion operator*(float s, const Quaternion& v)
{
	return v * s;//v*s
}

const Quaternion operator/(const Quaternion& v, float s)
{
	Quaternion temp(v);
	return temp /= s;
}