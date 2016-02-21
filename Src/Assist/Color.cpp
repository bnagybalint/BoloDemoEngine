#include "Color.h"

/*static*/ Color Color::BLACK         = Color(0,0,0,1);
/*static*/ Color Color::RED           = Color(1,0,0,1);
/*static*/ Color Color::GREEN         = Color(0,1,0,1);
/*static*/ Color Color::BLUE          = Color(0,0,1,1);
/*static*/ Color Color::WHITE         = Color(1,1,1,1);
/*static*/ Color Color::BLACK_NOALPHA = Color(0,0,0,0);
/*static*/ Color Color::RED_NOALPHA   = Color(1,0,0,0);
/*static*/ Color Color::GREEN_NOALPHA = Color(0,1,0,0);
/*static*/ Color Color::BLUE_NOALPHA  = Color(0,0,1,0);
/*static*/ Color Color::WHITE_NOALPHA = Color(1,1,1,0);


Color::Color() :Vector4(), r(c[0]), g(c[1]), b(c[2]), a(c[3]) {
}

Color::Color(const Color& other) : Vector4(other), r(c[0]), g(c[1]), b(c[2]), a(c[3]) {
}

Color::Color(Coordtype r, Coordtype g, Coordtype b, Coordtype a/* = Coordtype(1.0)*/) : Vector4(r, g, b, a), r(c[0]), g(c[1]), b(c[2]), a(c[3]) {
}

Color::~Color() {
}

Color Color::operator + (const Color& other) const {
	return Color(r + other.r, g + other.g, b + other.b, a + other.a);
}

Color Color::operator - (const Color& other) const {
	return Color(r - other.r, g - other.g, b - other.b, a - other.a);
}

Color Color::operator * (const Color& other) const {
	return Color(r * other.r, g * other.g, b * other.b, a * other.a);
}

Color Color::operator / (const Color& other) const {
	return Color(r / other.r, g / other.g, b / other.b, a / other.a);
}

Color Color::operator * (const Coordtype& scalar) const {
	return Color(r * scalar, g * scalar, b * scalar, a * scalar);
}

Color Color::operator / (const Coordtype& scalar) const {
	return Color(r / scalar, g / scalar, b / scalar, a / scalar);
}

Coordtype  Color::operator [] (int i) const {
	return c[i];
}

Coordtype& Color::operator [] (int i) {
	return c[i];
}

Color::operator Coordtype* () {
	return c;
}

Color::operator const Coordtype* () const {
	return c;
}

Color operator * (const Coordtype& scalar, const Color& color) {
	return Color(color.r * scalar, color.g * scalar, color.b * scalar, color.a * scalar);
}

Color operator / (const Coordtype& scalar, const Color& color) {
	return Color(color.r / scalar, color.g / scalar, color.b / scalar, color.a / scalar);
}
