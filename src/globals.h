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
    const int G_SIZE = 333;

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

struct RGBColor {
    int r, g, b;
    RGBColor() : r(255), g(255), b(255) {}
    RGBColor(int r, int g, int b) :
        r(r), g(g), b(b) {}
    RGBColor(int hue) {
        float X = 1 - abs(fmod(hue/60.0, 2)-1);
        r = 255;
        g = 255;
        b = 255;
        if(hue >= 0 && hue < 60){
            r *= 1, g *= X, b *= 0;
        }
        else if(hue >= 60 && hue < 120){
            r *= X, g *= 1, b *= 0;
        }
        else if(hue >= 120 && hue < 180){
            r *= 0, g *= 1, b *= X;
        }
        else if(hue >= 180 && hue < 240){
            r *= 0, g *= X, b *= 1;
        }
        else if(hue >= 240 && hue < 300){
            r *= X, g *= 0, b *= 1;
        }
        else{
            r *= 1, g *= 0, b *= X;
        }
    }
};

#endif