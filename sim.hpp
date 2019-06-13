#ifndef SIM_HPP
#define SIM_HPP

#include <iostream>
#include <cmath>
#include <array>

#include "vec.hpp"

#define N_PARTICLES 256

class Particle {
public:
    Particle();
    Particle(float rho, vec2f x, vec2f vh, vec2f v, vec2f a);

    float rho;
    vec2f x, // Position
          vh, // Half-step calculation of velocity
          v,  // Velocity after full-step
          a;  // Acceleration

    float d_squared(Particle& other);
};

class Simulation {
public:
    Simulation(unsigned int n_frames, unsigned int steps_per_frame,
            float time_step, float h, float m, float rho0, float k,
            float mu, vec2f g);

    // == Simulation constants ==

    unsigned int n_frames; // Number of frames to simulate
    unsigned int steps_per_frame;

    float dt;

    float h; // Interaction radius of a particle
    float m; // Mass of a particle
    float rho0; // Reference mass density
    float k; // Bulk modulus
    float mu; // Viscosity

    vec2f g; // Gravity

    float density_coefficient; // 4m/(pi*h^8)
    float h_2; // h^2
    float h_4; // h^4

    float xmin, xmax, ymin, ymax;

    void calculate_densities();
    vec2f f_interact(Particle& i, Particle& j);
    void calculate_accelerations();
    void time_step();
    void time_start();
    void reflect_particles();

    // == Simulation:tabe state ==
    
    std::array<Particle, N_PARTICLES> particles;
};

#endif
