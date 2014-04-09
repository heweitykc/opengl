#include <math.h>

class Vector3{
public:
	float x,y,z;
	Vector3(){}
	Vector3(const Vector3 &a) : x(a.x),y(a.y),z(a.z) {}
	Vector3(float nx, float ny, float nz): x(nx),y(ny),z(nz) {}

	Vector3 &operator =(const Vector3 &a) {
		x = a.x;
		y = a.y;
		z = a.z;
		return *this;
	}

	bool operator ==(const Vector3 &a) const{
		return x==a.x && y == a.y && z==a.z;
	}

	bool operator !=(const Vector3 &a) const{
		return x!=a.x || y != a.y || z!=a.z;
	}

	void zero() { x=y=z=0.0f;}

	Vector3 operator -() const{
		return Vector3(-x,-y,-z);
	}

	Vector3 operator +(const Vector3 &a) const{
		return Vector3(x+a.x,y+a.y,z+a.z);
	}

	Vector3 operator -(const Vector3 &a) const{
		return Vector3(x-a.x,y-a.y,z-a.z);
	}

	Vector3 operator *(const float a) const{
		return Vector3(x*a, y*a, z*a);
	}

	Vector3 operator /(const float a) const{
		float oneOverA = 1.0f/a;
		return Vector3(x*oneOverA, y*oneOverA, z*oneOverA);
	}

	Vector3 &operator +=(const Vector3 &a){
		x += a.x; y += a.y; z += a.z;
		return *this;
	}

	Vector3 &operator -=(const Vector3 &a){
		x -= a.x; y -= a.y; z -= a.z;
		return *this;
	}

	Vector3 &operator *=(const float a){
		x *= a; y *= a; z *= a;
		return *this;
	}

	Vector3 &operator /=(const float a){
		float oneOverA = 1.0f/a;
		x *= oneOverA; y *= oneOverA; z *= oneOverA;
		return *this;
	}

	void normalize(){
		float maqSq = x*x + y*y + z*z;
		if(maqSq > 0.0f){ //������
			float oneOverMag = 1.0f /sqrt(maqSq);
			x *= oneOverMag;
			y *= oneOverMag;
			z *= oneOverMag;
		}
	}

	float dotProduct(const Vector3 a)
	{
		return x*a.x+y*a.y+z*a.z;
	}
};

