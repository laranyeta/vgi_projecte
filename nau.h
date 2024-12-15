#pragma once

#ifndef NAU_H
#define NAU_H

#define NAU_CLASS_DECL     __declspec(dllexport)

#include "stdafx.h"
#include "camera.h"
#include "objLoader.h"
#include "ImGui\nfd.h" // Native File Dialog
class Nau {
private:
	//position
	vec3 m_o; //coord origin

	//orientation
	vec3 m_n; //normal vector
	vec3 m_v; //vertical vector
	vec3 m_u; //lateral vector
	mat4 m_q; //quaternio de rotacions

	//linear movment
	vec3 m_m; //movment vector
	double m_s; //linear velocity
	double m_a; //linear acceleration

	//angular movment
	vec3 m_r; //rotation axis
	double m_w; //angular velocity
	double m_aw; //angular acceleration

	//objects owned by nau
	Camera m_cam; //camera
	COBJModel** m_model;
	nfdchar_t* rutaOBJ;
	nfdchar_t* rutaOBJNGlass;

	float m_fuel;
	float m_life;
	float m_potencia;
	// combustible, particulas, efectos, etc.

public:
	// BASIQUES
	Nau() {
		m_o = vec3(0, 0, 0);

		m_n = vec3(-1, 0, 0);
		m_v = vec3(0, 0, 1);
		m_u = vec3(0, 1, 0);

		m_q = rotate(mat4(1), radians(180.0f), m_v = vec3(0, 0, 1));

		m_m = vec3(0, 0, 0);
		m_s = 0.0;
		m_a = 0.0;

		m_r = vec3(0, 0, 0);
		m_w = 0.0;
		m_aw = 0.0;

		m_cam = Camera();
		m_model = nullptr;

		m_fuel = 1.00f;
		m_life = 1.00;
		m_potencia = 0.00f;
	}

	Nau operator=(Nau n) {
		m_o = n.m_o;

		m_n = n.m_n;
		m_v = n.m_v;
		m_u = n.m_u;

		m_q = n.m_q;

		m_m = n.m_m;
		m_s = n.m_s;
		m_a = n.m_a;

		m_r = n.m_r;
		m_w = n.m_w;
		m_aw = n.m_aw;

		m_cam = n.m_cam;;
		m_model = n.m_model;

		return *this;
	}

	~Nau() {}

	void setModel(COBJModel** obj) { 
		m_model = obj; 
	}

	vec3 getN() const { return m_n; }
	vec3 getV() const { return m_v; }
	vec3 getU() const { return m_u; }
	vec3 getO() const { return m_o; }
	COBJModel* getModel() const {
		return *m_model;
	}
	Camera getCam() const {
		return m_cam;
	}

	void setPosition(vec3 temp) {
		m_cam = Camera(temp);
		m_o = temp;
	}

	mat4 getR() const { return m_q; }

	//MOVIMENT
	void move(vec3 move) { m_o += move; m_cam.move(move); }

	// ROTACIÓ SOBRE SI MATEIX
	void rotN(float angle) {
		m_q = rotate(mat4(1), radians(angle), m_n) * m_q;

		rotation_axis(m_v, angle, m_n);
		rotation_axis(m_u, angle, m_n);

		m_cam.orbX(angle, m_n, m_o);
	}
	void rotV(float angle) {
		m_q = rotate(mat4(1), radians(angle), m_v) * m_q;

		rotation_axis(m_n, angle, m_v);
		rotation_axis(m_u, angle, m_v);

		m_cam.orbX(angle, m_v, m_o);
	}
	void rotU(float angle) {
		m_q = rotate(mat4(1), radians(angle), m_u) * m_q;

		rotation_axis(m_n, angle, m_u);
		rotation_axis(m_v, angle, m_u);

		m_cam.orbX(angle, m_u, m_o);
	}
	void rotA(float angle, vec3 axis) {
		m_q = rotate(mat4(1), radians(angle), axis) * m_q;

		rotation_axis(m_n, angle, axis);
		rotation_axis(m_v, angle, axis);
		rotation_axis(m_u, angle, axis);

		m_cam.orbX(angle, axis, m_o);
	}

	void incPotencia() {
		if (m_potencia < 1.0f) {
			m_potencia += 0.01f;
		}
		else {
			m_potencia = 1.0f;
		}
	}
	void decPotencia() {
		if (m_potencia > 0.0f) {
			m_potencia -= 0.005f;
		}
		else {
			m_potencia = 0.0f;
		}
	}
	void incFuel(float temp) {
		m_fuel += temp;
	}
	void decFuel() {
		m_fuel -= 0.00001f;
	}
	float getPotencia() { return m_potencia; }
	float getFuel() { return m_fuel; }
	float getLife() { return m_life; }


	//Extra
	void increaseSpeed(double s) { m_s = m_s + s > 25 ? 25 : m_s + s < -25 ? -25 : m_s + s; }
	void moveS(double delta) { move((float)(m_s * delta) * m_n); }



	//
	// 
	// 
	// 
	// 
	// 
	// ANGLE CAMERA
	void setCamAngle(int i)
	{
		vec3 pos;
		vec3 n;
		vec3 v;
		vec3 u;

		switch (i)
		{
			case 1:	//posem camera primera persona
				pos = m_o - vec3(m_q * vec4(vec3(-0.14f, 0, -0.06), 1.0f));
				n = m_n;
				v = m_v;
				u = m_u;

				m_cam = Camera(pos, n, v, u);
				break;
			case 2:
				pos = m_o - vec3(m_q * vec4(RAD * vec3(-cos(ANG), 0, -sin(ANG)), 1.0f));
				n = -m_n;
				v = m_v;
				u = -m_u;

				m_cam = Camera(pos, n, v, u);
				break;

			case 3:
				pos = m_o - vec3(m_q * vec4(RAD*vec3(cos(ANG), 0, -sin(ANG)), 1.0f));
				n = m_n;
				v = m_v;
				u = m_u;

				m_cam = Camera(pos, n, v, u);
				break;

			default:
				break;
		}
	}
	// END ANGLE CAMERA
	// ANGLE MAP
	float getAngle() {
		vec2 n = vec2(m_n.x, m_n.y); // Vector normal
		vec2 v = vec2(1.0, 0.0); // Vector de referència

		// Angle entre els vectors
		float angle = acos(dot(normalize(n), normalize(v)));

		float cross = n.x * v.y - n.y * v.x;

		if (cross < 0) {
			angle = 2.0f * PI - angle;
		}

		return angle; // Retorna l’angle entre 0 i 2π
	}
	float getAngleV() {
		vec2 n = vec2(m_v.y, m_v.z); // Vector normal
		vec2 v = vec2(0.0, 1.0); // Vector de referència

		// Angle entre els vectors
		float angle = acos(dot(normalize(n), normalize(v)));

		float cross = n.x * v.y - n.y * v.x;

		if (cross < 0) {
			angle = 2.0f * PI - angle;
		}

		return angle; // Retorna l’angle entre 0 i 2π
	}
	// END ANGLE MAP
	//
	// 
	// 
	// 
	// 
	// 
};

#endif