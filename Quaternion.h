#pragma once
#include"vector3.h"
#include"Matrix4.h"
class Quaternion
{
public:
	float x;
	float y;
	float z;
	float w;

	Quaternion();
	Quaternion(float x, float y, float z, float w);

	//Quaternion�̐�
	Quaternion Multiply(Quaternion quaternion);
	//�P��Quaternion��Ԃ�
	Quaternion IdentityQuaternion();
	//����Quaternion��Ԃ�
	Quaternion Conjugate();
	//Quaternion��norm��Ԃ�
	float Norm() const;
	//���K������Quaternion��Ԃ�
	Quaternion Normalize();
	//�tQuaternion��Ԃ�
	Quaternion Inverse();
	//�x�N�g����Quaternion�ŉ�]���������ʂ̃x�N�g�������߂�
	Vector3 RotateVector(const Vector3& vector);
	//Quaternion�����]�s������߂�
	Matrix4 MakeRotateMatrix();

	//�P�����Z�q�I�[�o�[���[�h
	Quaternion operator+() const;
	Quaternion operator-() const;

	//������Z�q�I�[�o�[���[�h
	Quaternion& operator+=(const Quaternion& v);
	Quaternion& operator-=(const Quaternion& v);
	Quaternion& operator*=(float s);
	Quaternion& operator/=(float s);


};

Vector3 MatVector(const Vector3& vector, const Matrix4& matrix);

//�C�ӎ���]��\��Quaternion�̐���
Quaternion MakeAxisAngle(const Vector3& axis, float radian);

//
Quaternion Slerp(const Quaternion& q0, const Quaternion& q1, float t);

//2�����Z�q�I�[�o�[���[�h
//�����Ȉ���(�����̌^�Ə���)�̃p�^�[���ɑΉ����邽�߁A�ȉ��̂悤�ɏ������Ă���
const Quaternion operator+(const Quaternion& v1, const Quaternion& v2);
const Quaternion operator-(const Quaternion& v1, const Quaternion& v2);
const Quaternion operator*(const Quaternion& v, float s);
const Quaternion operator*(float s, const Quaternion& v);

const Quaternion operator/(const Quaternion& v, float s);