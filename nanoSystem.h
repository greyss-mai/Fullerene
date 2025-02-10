#ifndef __NANOSYSTEM_H__
#define __NANOSYSTEM_H__

#include "particleSystem.h"
#include "nano_kernel.cuh"

// Nano system class
class NanoSystem : public ParticleSystem {
 public:

	using ParticleSystem::ParticleSystem;
	
	//void update(float deltaTime);
	void reset(ParticleConfig config);

	float getParticleRadius() { return m_params.particleRadius; }

	//set the current number of particles 
	void   setNumParticles(uint num) { m_numParticles = num; }

	//initialize structures
	void fromFile(char* path);
	void hex();

 protected:  // methods
	NanoSystem() {}

	void initGrid();
};
#endif  // __NANOSYSTEM_H__