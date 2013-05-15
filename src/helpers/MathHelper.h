#pragma once

class MathHelper  {
public:
	static bool isAnlgeBetween(float _angle, float _startAngle, float _endAngle);
	static float cleanAngle(float _dirtyAngle);
	static int minInt(int a, int b);	
	static float minFloat(float a, float b);
	static int maxInt(int a, int b);	
	static float maxFloat(float a, float b);
};
