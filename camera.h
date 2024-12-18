#pragma once

#ifndef CAMERA_H
#define CAMERA_H

#define CAMERA_CLASS_DECL     __declspec(dllexport)

#include "stdafx.h"
const float ANG = radians(15.0f);
const float RAD = 1.0f;

void rotation_axis(vec3& p, float angle, vec3 axis, vec3 x);

void rotation_axis(vec3& vec, float angle, vec3 axis);

float module(vec3 vec);

class Camera {
private:
	vec3 m_n; //normal vector
	vec3 m_v; //vertical vector
	vec3 m_u; //lateral vector
	vec3 m_o; //coord origin
	vec3 m_p; //coord looking point
public:
	// BASIQUES
	Camera() { 
	m_o = RAD*vec3(cos(ANG), 0, sin(ANG));
	m_p = vec3(0, 0, sin(ANG));

	m_n = -m_o/RAD;
	m_u = vec3( 0, 1, 0);
	m_v = cross(m_u, m_n);
	}
	Camera(vec3 o)
	{
		m_o = o + RAD * vec3(cos(ANG), 0, sin(ANG));
		m_p = o + vec3(0, 0, sin(ANG));

		m_n = -m_o / RAD;
		m_u = vec3(0, 1, 0);
		m_v = cross(m_u, m_n);
	}

	~Camera() {}

	void setN(vec3 n) { m_n = n; }
	void setV(vec3 v) { m_v = v; }
	void setU(vec3 u) { m_u = u; }
	void setO(vec3 o) { m_o = o; }
	void setP(vec3 p) { m_p = p; }

	vec3 getN() { return m_n; }
	vec3 getV() { return m_v; }
	vec3 getU() { return m_u; }
	vec3 getO() { return m_o; }
	vec3 getP() { return m_p; }
	float getAngle() {
		vec2 n = vec2(m_n.x, m_n.y); // Vector normal
		vec2 v = vec2(m_v.x, m_v.y); // Vector de referència

		// Angle entre els vectors
		float angle = acos(dot(normalize(n), normalize(v)));

		float cross = n.x * v.y - n.y * v.x;

		if (cross < 0) {
			angle = 2.0f * PI - angle;
		}

		return angle; // Retorna l’angle entre 0 i 2π
	}


	// MOVIMENT
	void move(vec3 move) { m_o += move; m_p += move; }

	// ROTACIÓ SOBRE SI MATEIX
	void rotN(float angle) {
		rotation_axis(m_v, angle, m_n);
		rotation_axis(m_u, angle, m_n);
	}
	void rotV(float angle) {
		rotation_axis(m_n, angle, m_v);
		rotation_axis(m_u, angle, m_v);

		rotation_axis(m_p, angle, m_v, m_o);
	}	
	void rotU(float angle) {
		rotation_axis(m_n, angle, m_u);
		rotation_axis(m_v, angle, m_u);

		rotation_axis(m_p, angle, m_u, m_o);
	}
	void rotA(float angle, vec3 axis) {
		rotation_axis(m_n, angle, axis);
		rotation_axis(m_v, angle, axis);
		rotation_axis(m_u, angle, axis);
	}

	// ROTACIÓ AL VOLTANT OBJECTE
	void orbX(float angle, vec3 axis, vec3 x) {
		rotation_axis(m_o, angle, axis, x);
		rotation_axis(m_p, angle, axis, x);

		rotation_axis(m_n, angle, axis);
		rotation_axis(m_v, angle, axis);
		rotation_axis(m_u, angle, axis);
	}

	//Extra
	void zoom(float zoom)
	{
		/*TO DO*/
	}

	//
	// 
	// 
	// 
	// 
	// 
	// ANGLE CAMERA
	Camera(vec3 pos, vec3 n, vec3 v, vec3 u)
	{
		m_o = pos;
		m_p = pos + n;

		m_n = n;
		m_u = u;
		m_v = v;
	}
	// END ANGLE CAMERA
};

#endif