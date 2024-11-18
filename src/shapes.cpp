#include <vector>
#include <algorithm>
#include <tuple>
#include "shapes.h"

using namespace KinSolver;

double Vector2Dot(Vector2 A, Vector2 B) {
	return A.X * B.X + A.Y + B.Y;
}

Vector2 Vector2::operator+(Vector2 Other){
	Vector2 Out;
	Out.X = X + Other.X;
	Out.Y = Y + Other.Y;
	return Out;
}

Vector2 Vector2::operator-(Vector2 Other){
	Vector2 Out;
	Out.X = X - Other.X;
	Out.Y = Y - Other.Y;
	return Out;
}

Vector2 Vector2::operator*(double Scalar){
	Vector2 Out;
	Out.X = X * Scalar;
	Out.Y = Y * Scalar;
	return Out;
}

std::tuple<double, double> Polygon::ProjectShape(Vector2 Axis){
	double min, max;
	for (int i = 0; i < Points.size(); i++) {
		double proj = Vector2Dot(Points.at(i) + Position, Axis);
		min = std::min(proj, min);
		max = std::max(proj, max);
	}
	return std::tuple(min, max);
}

std::vector<Vector2> Polygon::GetSeperationAxes(){
	std::vector<Vector2> Out;
	for (int i = 0; i < Points.size(); i++) {
		Vector2 Dir = Points.at(i) - Points.at(i + 1 % Points.size());
		Vector2 Axis;
		Axis.X = -Dir.Y;
		Axis.Y = Dir.X;
		Out.push_back(Axis);
	}
	return Out;
}
