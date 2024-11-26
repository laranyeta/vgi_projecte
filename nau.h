#pragma once

#ifndef NAU_H
#define NAU_H

#define NAU_CLASS_DECL     __declspec(dllexport)

#include "stdafx.h"
#include "camera.h"
#include "objLoader.h"

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
	COBJModel* m_model;

	float m_fuel;
	float m_life;
	float m_potencia;
	// combustible, particulas, efectos, etc.

public:
	// BASIQUES
	Nau(){
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

	void setModel(COBJModel* obj) { m_model = obj; }

	vec3 getN() const { return m_n; }
	vec3 getV() const { return m_v; }
	vec3 getU() const { return m_u; }
	vec3 getO() const { return m_o; }
	COBJModel* getModel() const {
		return m_model;
	}
	Camera getCam() const {
		return m_cam;
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
	void moveS(double delta) { move((float)(m_s * delta)*m_n);  }
};

#endif