#pragma once
#include<math.h>

class Quaternion
{
public: // サブクラス
	float x;
	float y;
	float z;
	float w;

public:
	Quaternion();
	Quaternion(float x, float y, float z, float w);

	/// <summary>
	/// 積
	/// </summary>
	/// <param name="lhs"></param>
	/// <param name="rhs"></param>
	/// <returns></returns>
	Quaternion Multiply(const Quaternion& lhs, const Quaternion& rhs);

	/// <summary>
	/// 情報単位元
	/// </summary>
	/// <returns></returns>
	Quaternion IdentityQuaternion();

	/// <summary>
	/// 共役
	/// </summary>
	/// <param name="quaternion"></param>
	/// <returns></returns>
	Quaternion Conjugate(const Quaternion& quaternion);

	/// <summary>
	/// ノルム
	/// </summary>
	/// <param name="quaternion"></param>
	/// <returns></returns>
	float Norm(const Quaternion& quaternion);

	/// <summary>
	/// 単位Quaternion
	/// </summary>
	/// <param name="quaternion"></param>
	/// <returns></returns>
	Quaternion Normalize(const Quaternion& quaternion);

	/// <summary>
	/// 逆Quaternion
	/// </summary>
	/// <param name="quaternion"></param>
	/// <returns></returns>
	Quaternion Inverse(const Quaternion& quaternion);

private:
	float half = 0.5f;
};

const Quaternion operator / (const Quaternion& q, float s);
