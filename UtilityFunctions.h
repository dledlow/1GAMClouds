#pragma once
#include <random>

template <typename T> int sgn(T val) {
	return (T(0) < val) - (val < T(0));
}

template <typename T> int sgn2(T val) {
	return (T(0) < val) - (val < T(0)) == 0 ? 1 : (T(0) < val) - (val < T(0));
}

static float randf() {	
	return static_cast <float> (std::rand()) / static_cast <float> (RAND_MAX); 
}

static sf::Vector2i closestV2i(sf::Vector2i o, sf::Vector2i p1, sf::Vector2i p2) {
	double d1 = pow(o.x - p1.x, 2) + pow(o.y - p1.y, 2);
	double d2 = pow(o.x - p2.x, 2) + pow(o.y - p2.y, 2);
	return d1 > d2 ? p2 : p1;
}

static float dotf(sf::Vector2f v1, sf::Vector2f v2){
	return v1.x * v2.x + v1.y * v2.y;
}

static sf::Vector2i collideCircleWithLine(sf::Vector2i circlePos, float circleRadius, sf::Vector2i lineP1, sf::Vector2i lineP2) {
	//http://stackoverflow.com/questions/1073336/circle-line-segment-collision-detection-algorithm
	// compute the euclidean distance between A and B
	double LAB = sqrt(pow(lineP1.x - lineP2.x, 2) + pow(lineP1.y - lineP2.y, 2));

	// compute the direction vector D from A to B
	double Dx = (lineP1.x - lineP2.x) / LAB;
	double Dy = (lineP1.y - lineP2.y) / LAB;

	// Now the line equation is x = Dx*t + Ax, y = Dy*t + Ay with 0 <= t <= 1.

	// compute the value t of the closest point to the circle center (Cx, Cy)
	double t = abs(Dx*(circlePos.x - lineP2.x) + Dy*(circlePos.y - lineP2.y));

	// This is the projection of C on the line from A to B.

	// compute the coordinates of the point E on line and closest to C
	double Ex = t*Dx + lineP2.x;
	double Ey = t*Dy + lineP2.y;

	// compute the euclidean distance from E to C
	double LEC = sqrt(pow(Ex - circlePos.x, 2) + pow(Ey - circlePos.y, 2));

	sf::Vector2i F;
	// test if the line intersects the circle
	if (LEC < circleRadius)
	{
		// compute distance from t to circle intersection point
		double dt = sqrt(circleRadius*circleRadius - LEC*LEC);

		// compute first intersection point
		F.x = int((t - dt)*Dx + lineP2.x);
		F.y = int((t - dt)*Dy + lineP2.y);

		sf::Vector2i G;
		// compute second intersection point
		G.x = int((t + dt)*Dx + lineP2.x);
		G.y = int((t + dt)*Dy + lineP2.y);

		F = closestV2i(lineP2, F, G);
	}

	// else test if the line is tangent to circle
	else if (LEC == circleRadius){
		// tangent point to circle is E
		F.x = int(Ex);
		F.y = int(Ey);
	}
	else{
		// line doesn't touch circle
		F.x = -1;
		F.y = -1;
	}
	return F;
}