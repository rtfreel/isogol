#ifndef GLOBALS_H
#define GLOBALS_H

#include <math.h>

namespace global{
    // OpenGL
    const char MAGOR_V = 3;
    const char MINOR_V = 1;

    // Window
    const int SCREEN_WIDTH = 1000;
    const int SCREEN_HEIGHT = 800;

    // Group
    const int G_COUNT = 3;
    const int G_SIZE = 1000;

    // Particle
    const float P_RADIUS = 2.0f;
    const float MU = 0.02f;

    // Force
    
}

struct Vector2 {
	float x, y;
	Vector2() : x(0), y(0) {}
	Vector2(float x, float y) : x(x), y(y) {}
	Vector2(const Vector2 &vec) : x(vec.x), y(vec.y) {}

	Vector2 operator+(Vector2 &vec) { return Vector2(x + vec.x, y + vec.y); }
    Vector2 operator-(Vector2 &vec) { return Vector2(x - vec.x, y - vec.y); }
    Vector2 operator*(Vector2 &vec) { return Vector2(x * vec.x, y * vec.y); }
    Vector2 operator*(float scalar) { return Vector2(x * scalar, y * scalar); }
    Vector2 operator/(float scalar) { return Vector2(x / scalar, y / scalar); }

    void operator+=(Vector2 &vec) { x += vec.x; y += vec.y; }
    void operator-=(Vector2 &vec) { x -= vec.x; y -= vec.y; }
    void operator*=(Vector2 &vec) { x *= vec.x; y *= vec.y; }
    void operator*=(float scalar) { x *= scalar; y *= scalar; }
    void operator/=(float scalar) { x /= scalar; y /= scalar; }

	void setMag(float mag) {
		float multiplier = mag / sqrtf((x * x) + (y * y));
		x *= multiplier;
		y *= multiplier;
	}

	float mag() {
		return sqrtf((x * x) + (y * y));
	}
};

#endif