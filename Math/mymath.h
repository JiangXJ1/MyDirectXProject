#pragma once
#define pi 3.14159265f
//角度转换为弧度
inline float Angle2Radian(float angle) {
	return angle / 180 * pi;
}
//弧度转换为角度
inline float Radian2Angle(float radian) {
	return radian / pi * 180;
}
//计算cot
inline float cot(float radian) {
	return tan(pi / 2 - radian);
}
namespace Math {
	class myMath 
	{
	public:

	};
}