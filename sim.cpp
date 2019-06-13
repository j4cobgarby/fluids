#include "sim.hpp"

Particle::Particle() {}

Particle::Particle(float rho, vec2f x, vec2f vh, vec2f v, vec2f a) :
    rho(rho), x(x), vh(vh), v(v), a(a) {}

float Particle::d_squared(Particle& other) {
    float dx = (other.x.x - x.x),
          dy = (other.x.y - x.y);
    return (dx * dx) + (dy * dy);
}

Simulation::Simulation(unsigned int n_frames, unsigned int steps_per_frame,
            float time_step, float h, float m, float rho0, float k,
            float mu, vec2f g) :
    n_frames(n_frames), steps_per_frame(steps_per_frame), dt(dt),
    h(h), m(m), rho0(rho0), k(k), mu(mu), g(g) {
    density_coefficient = (4.f * m) / (M_PI * powf(h, 8.f));
    h_2 = powf(h, 2);
    h_4 = powf(h, 4);
    xmin = 0;
    xmax = 1;
    ymin = 0;
    ymax = 1;

    for (unsigned int i = 0; i < N_PARTICLES; i++) { // Initialise all particles
        particles.at(i) = Particle(0, 
                vec2f(0,0), vec2f(0,0), vec2f(0,0), vec2f(0,0));
    }
}

void Simulation::calculate_densities() {
    for (int i = 0; i < N_PARTICLES; i++) particles.at(i).rho = 0;

    // Sum(j in N_i) (h^2 - r^2)^3
    for (int i = 0; i < N_PARTICLES; i++) {
        for (int j = i+1; j < N_PARTICLES; j++) {
            float r_2 = particles.at(i).d_squared(particles.at(j));
            float h_2_sub_r_2 = h_2 - r_2;
            if (h_2_sub_r_2 > 0) {
                float delta_rho = powf(h_2_sub_r_2, 3);
                particles.at(i).rho += delta_rho;
                particles.at(j).rho += delta_rho;
            }
        }
    }

    // Then multiply every density by 4m/pi*h^8
    for (int i = 0; i < N_PARTICLES; i++) {
        particles.at(i).rho *= density_coefficient;
    }
}

// f_interact(i, j) == -f_interact(j, i)
vec2f Simulation::f_interact(Particle& i, Particle& j) {
    float scalar = m/(M_PI * h_4 * j.rho);
    float q_ij = (i.x - j.x).magnitude() / h;
    scalar *= (1-q_ij);

    vec2f vector_part = i.x - j.x;; // == r_ij at the moment
    vector_part *= 15 * k * (i.rho + j.rho - 2 * rho0);
    vector_part -= (i.v - j.v) * (40 * mu);

    return vector_part * scalar;
}

void Simulation::calculate_accelerations() {
    for (int i = 0; i < N_PARTICLES; i++) {
        for (int j = i+1; j < N_PARTICLES; j++) {
            vec2f f_int = f_interact(particles.at(i), particles.at(j));
            particles.at(i).a = f_int;
            particles.at(j).a = f_int * -1;
        }
    }

    for (int i = 0; i < N_PARTICLES; i++) {
        particles.at(i).a *= (1/particles.at(i).rho);
        particles.at(i).a += g;
    }
}

void Simulation::time_step() {
    for (int i = 0; i < N_PARTICLES; i++) {
        particles.at(i).vh += particles.at(i).a * dt;
        particles.at(i).v = particles.at(i).vh + particles.at(i).a * dt / 2;
        particles.at(i).x += particles.at(i).vh * dt;
    }

    reflect_particles();
}

void Simulation::time_start() {
    for (int i = 0; i < N_PARTICLES; i++) {
        particles.at(i).vh = particles.at(i).v + particles.at(i).a * dt / 2;
        particles.at(i).v += particles.at(i).a * dt;
        particles.at(i).x += particles.at(i).vh * dt;
    }

    reflect_particles();
}

void reflect_particles() {
    for (Particle& p : particles)
}
