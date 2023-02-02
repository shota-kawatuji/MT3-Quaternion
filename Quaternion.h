#pragma once
#include<math.h>

class Quaternion
{
public: // �T�u�N���X
	float x;
	float y;
	float z;
	float w;

public:
	Quaternion();
	Quaternion(float x, float y, float z, float w);

	/// <summary>
	/// ��
	/// </summary>
	/// <param name="lhs"></param>
	/// <param name="rhs"></param>
	/// <returns></returns>
	Quaternion Multiply(const Quaternion& lhs, const Quaternion& rhs);

	/// <summary>
	/// ���P�ʌ�
	/// </summary>
	/// <returns></returns>
	Quaternion IdentityQuaternion();

	/// <summary>
	/// ����
	/// </summary>
	/// <param name="quaternion"></param>
	/// <returns></returns>
	Quaternion Conjugate(const Quaternion& quaternion);

	/// <summary>
	/// �m����
	/// </summary>
	/// <param name="quaternion"></param>
	/// <returns></returns>
	float Norm(const Quaternion& quaternion);

	/// <summary>
	/// �P��Quaternion
	/// </summary>
	/// <param name="quaternion"></param>
	/// <returns></returns>
	Quaternion Normalize(const Quaternion& quaternion);

	/// <summary>
	/// �tQuaternion
	/// </summary>
	/// <param name="quaternion"></param>
	/// <returns></returns>
	Quaternion Inverse(const Quaternion& quaternion);

private:
	float half = 0.5f;
};

const Quaternion operator / (const Quaternion& q, float s);
