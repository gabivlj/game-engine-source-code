//
//  Vector.hpp
//  Engine19
//
//  Created by Gabriel Villalonga Simón on 11/11/2019.
//  Copyright © 2019 Gabriel Villalonga Simón. All rights reserved.
//

#ifndef Vector_hpp
#define Vector_hpp

#include <stdio.h>
#include <cmath>

struct vec2{
    float x;
    float y;

	vec2& operator= (const vec2& a) {
		x = a.x;
		y = a.y;
		return *this;
	}

	vec2 operator+ (const vec2& a) const {
		vec2 ret = { a.x + x, a.y + y };
		return ret;
	}

	vec2 operator- (const vec2& a) const {
		vec2 ret = { a.x - x, a.y - y };
		return ret;
	}

	bool operator== (const vec2& a) const {
		return (a.x == x && a.y == y);
	}

	vec2 operator/ (const float& a) const {
		vec2 ret = { x / a, y / a };
		return ret;
	}
	
	vec2 operator* (const float& a) const {
		vec2 ret = { x * a, y * a };
		return ret;
	}

	vec2 operator*(const int& a) const {
		vec2 ret = { x * a, y * a };
		return ret;
	}

	float magnitudeSqr() {
		return (x * x) + (y * y);
	}

	float magnitude() {
		return std::sqrt(magnitudeSqr());
	}
};

struct dimensions{
    float width;
    float height;
};

struct transform{
    vec2 position;
	vec2 scale;
    dimensions dimension;
    float rotation;
};


typedef struct {
    vec2 point1;
    vec2 point2;
} line;

#endif /* Vector_hpp */
