#pragma once
#define pi 3.14159265f
//�Ƕ�ת��Ϊ����
inline float Angle2Radian(float angle) {
	return angle / 180 * pi;
}
//����ת��Ϊ�Ƕ�
inline float Radian2Angle(float radian) {
	return radian / pi * 180;
}
//����cot
inline float cot(float radian) {
	return tan(pi / 2 - radian);
}
namespace Math {
	class myMath 
	{
	public:

	};
}