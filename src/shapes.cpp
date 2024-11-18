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
AABB Polygon::GetSweptAABB(Vector2 Movement) {
	double MinX, MaxX, MinY, MaxY;
	for (int i = 0; i < Points.size(); i++) {
		MinX = std::min(MinX, Points.at(i).X);
		MinY = std::min(MinY, Points.at(i).Y);
		MaxX = std::max(MaxX, Points.at(i).X);
		MaxY = std::max(MaxY, Points.at(i).Y);
	}
	AABB Box;
	Box.X = MinX;
	Box.Y = MinY;
	Box.Width = MaxX - MinX;
	Box.Height = MaxY - MaxY;

	if (Movement.X > 0) {
		Box.Width += Movement.X;
	}
	if (Movement.X < 0) {
		Box.X += Movement.X;
	}
	if (Movement.Y > 0) {
		Box.Height += Movement.Y;
	}
	if (Movement.Y < 0) {
		Box.Y += Movement.Y;
	}
	return Box;
}
