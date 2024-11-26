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
	Camera(vec3 o, vec3 p, vec3 v)
	{
		m_o = o;
		m_p = p;

		m_n = normalize(p - o);
		m_v = v;
		m_u = cross(m_n, m_v);
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

	// MOVIMENT
	void move(vec3 move) { m_o += move; m_p += move; }

	// ROTACI� SOBRE SI MATEIX
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

	// ROTACI� AL VOLTANT OBJECTE
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
};

#endif