
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    float x, y;
    float vx, vy;
} Particle;

Particle create_particle(float x, float y, float vx, float vy) {
    Particle p;
    p.x = x;
    p.y = y;
    p.vx = vx;
    p.vy = vy;
    return p;
}

Particle * create_particles(int N) {
    Particle *particles;
    particles = (Particle *) malloc(N * sizeof(Particle));
    if (!particles) {
        fprintf(stderr, "Failed to allocate memory for particles\n");
        exit(1);
    }

    for (int i = 0; i < N; ++i) {
        particles[i] = create_particle((float)i / N * 2.0f - 1.0f, 0.9f, 0.0f, 0.0f); 
    }

    return particles;
}

void update_particle(Particle* p, float dt) {
    p->vy -= 9.81f * dt; 
    p->x += p->vx * dt;
    p->y += p->vy * dt;

    if (p->y < -1.0f) {
        p->y = -1.0f;
        p->vy = 0.0f;
        p->vx = 0.0f;
    }
}

void draw_particle(Particle* p) {
    glBegin(GL_POINTS);
    glVertex2f(p->x, p->y);
    glEnd();
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main() {
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "Particle Simulation", NULL, NULL);
    if (!window) {
        fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }

    glfwSetKeyCallback(window, key_callback);

    int numberOfParticles = 5;
    Particle *particles = create_particles(numberOfParticles);

    glPointSize(5.0f); 
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        float dt = 0.01f; 

        for (int i = 0; i < numberOfParticles; ++i) {
            update_particle(&particles[i], dt);
            draw_particle(&particles[i]);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    free(particles);
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
