#include <helper_gl.h>

#include "nanoSystem.h"
#include "particleSystem.cuh"

#include <cuda_runtime.h>

#include <helper_cuda.h>

inline float frand()
{
	return rand() / (float)RAND_MAX;
}

void
NanoSystem::hex() {

	float a = 1.4 / 60; //bond length
	float hx[6], hy[6], hz[6];
	float pi = M_PI;
	int i;

	//definition of a hexagon
	hx[0] = a;  hy[0] = 0.0; hz[0] = 0.0;

	for (i = 1; i < 6; i++) {
		hx[i] = hx[i - 1] * cos(pi / 3) - hy[i - 1] * sin(pi / 3);
		hy[i] = hx[i - 1] * sin(pi / 3) + hy[i - 1] * cos(pi / 3);
		hz[i] = 0.0;
	}

	for (i = 0; i < 6; i++) {

		m_hPos[(i) * 4] = hx[i];
		m_hPos[(i) * 4 + 1] = hy[i];
		m_hPos[(i) * 4 + 2] = hz[i];
		m_hPos[(i) * 4 + 3] = 12;

		m_hVel[i * 4] = 0.0;
		m_hVel[i * 4 + 1] = 0.0;
		m_hVel[i * 4 + 2] = 0.0;
		m_hVel[i * 4 + 3] = 0.0f;
	}

	setNumParticles(6);
}

void
NanoSystem::fromFile(char* path) {
	FILE* stream;
	stream = fopen(path, "r");
	if (stream == NULL) return;

	int i, j, n, k, l, m, p;
	char str[100];
	float x, y, z;

	fscanf(stream, " %d ", &n);


	for (i = 0; i < n; i++) {

		fscanf(stream, " %s", str);
		fscanf(stream, " %d %f %f %f %d %d %d %d", &j, &x, &y, &z, &l, &m, &k, &p);

		m_hPos[i * 4] = x / 60;
		m_hPos[i * 4 + 1] = y / 60;
		m_hPos[i * 4 + 2] = z / 60;
		if (str[0] == 'C') m_hPos[i * 4 + 3] = 12;

		m_hVel[i * 4] = -0 + frand() * 0.0f;
		m_hVel[i * 4 + 1] = -0 + frand() * 0.0f;
		m_hVel[i * 4 + 2] = -0 + frand() * 0.0f;
		m_hVel[i * 4 + 3] = 0.0f;
	}

	fclose(stream);

	setNumParticles(n);
}

void
NanoSystem::initGrid()
{
	hex();
	fromFile("nano\\C60-Ih.cc1");
}
void
NanoSystem::reset(ParticleConfig config)
{
	switch (config)
	{
	default:
	case CONFIG_GRID:
	{
		initGrid();
	}
	break;
	}

	setArray(POSITION, m_hPos, 0, m_numParticles);
	setArray(VELOCITY, m_hVel, 0, m_numParticles);
}