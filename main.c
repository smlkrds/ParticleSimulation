#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

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

    glPointSize(5.0f); 
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 

    Particle p = create_particle(0.0f, 0.9f, 0.0f, 0.0f);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        float dt = 0.01f; 
        update_particle(&p, dt);

        draw_particle(&p);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

