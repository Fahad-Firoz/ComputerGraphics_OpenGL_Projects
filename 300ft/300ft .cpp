// dhaka_300ft_view.c
// Beautiful 300ft city view in GLUT (C)
// Compile (Windows):  gcc dhaka_300ft_view.c -o dhaka_300ft_view -lopengl32 -lglu32 -lglut32
// Compile (Linux):    gcc dhaka_300ft_view.c -o dhaka_300ft_view -lGL -lGLU -lglut

#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

float carZ = -800.0f;   // Car moves vertically along road (Z-axis)
float cloudX = -800.0f;
float sunAngle = 0.0f;
int animate = 1;

float camY = 300.0f, camZ = 900.0f;
float rotation = 0.0f;
float buildingOffset = 0.0f;  // New variable for building movement

// --- Sky Gradient ---
void drawSky() {
    glDisable(GL_LIGHTING);
    glBegin(GL_QUADS);
        glColor3f(0.3f, 0.6f, 0.9f); glVertex3f(-2000, 1000, -1500);
        glColor3f(0.8f, 0.9f, 1.0f); glVertex3f(2000, 1000, -1500);
        glColor3f(0.9f, 0.95f, 1.0f); glVertex3f(2000, 0, -1500);
        glColor3f(0.9f, 0.95f, 1.0f); glVertex3f(-2000, 0, -1500);
    glEnd();
    glEnable(GL_LIGHTING);
}

// --- Ground & Road ---
void drawGround() {
    glDisable(GL_LIGHTING);
    glColor3f(0.25f, 0.7f, 0.25f);
    glBegin(GL_QUADS);
        glVertex3f(-2000, 0, -2000);
        glVertex3f(2000, 0, -2000);
        glVertex3f(2000, 0, 2000);
        glVertex3f(-2000, 0, 2000);
    glEnd();

    // Road
    glColor3f(0.15f, 0.15f, 0.18f);
    glBegin(GL_QUADS);
        glVertex3f(-200, 1, -2000);
        glVertex3f(200, 1, -2000);
        glVertex3f(200, 1, 2000);
        glVertex3f(-200, 1, 2000);
    glEnd();

    // Center line
    glColor3f(1.0f, 1.0f, 0.4f);
    glLineWidth(4);
    glBegin(GL_LINES);
        for (int i = -2000; i < 2000; i += 80) {
            glVertex3f(0, 2, i);
            glVertex3f(0, 2, i + 40);
        }
    glEnd();
    glEnable(GL_LIGHTING);
}

// --- Buildings ---
void drawBuilding(float x, float z, float w, float h) {
    glPushMatrix();
    glTranslatef(x, h/2, z);
    glScalef(w, h, w);
    glColor3f(0.4f, 0.6f, 0.9f);
    glutSolidCube(1);
    glPopMatrix();

    // window shimmer
    glDisable(GL_LIGHTING);
    glColor3f(0.9f, 0.95f, 1.0f);
    glBegin(GL_QUADS);
        glVertex3f(x - w/2, h - 2, z + w/2 + 0.2);
        glVertex3f(x + w/2, h - 2, z + w/2 + 0.2);
        glVertex3f(x + w/2, h - 4, z + w/2 + 0.2);
        glVertex3f(x - w/2, h - 4, z + w/2 + 0.2);
    glEnd();
    glEnable(GL_LIGHTING);
}

void drawCity() {
    for (int i = -8; i <= 8; i++) {
        float z = i * 180.0f + buildingOffset;  // Add buildingOffset for movement
        drawBuilding(-350, z, 100, 150 + (rand() % 120));
        drawBuilding(350, z, 100, 150 + (rand() % 120));
    }
}

// --- Car ---
void drawCar() {
    glPushMatrix();
    glTranslatef(0, 15, carZ);   // Car moves vertically (Z-axis)
    glScalef(60, 20, 30);        // Bigger car
    glColor3f(0.9f, 0.1f, 0.1f);
    glutSolidCube(1);
    glPopMatrix();
}

// --- Clouds ---
void drawCloud(float x, float y, float z) {
    glPushMatrix();
    glDisable(GL_LIGHTING);
    glColor3f(1, 1, 1);
    glTranslatef(x, y, z);
    glutSolidSphere(20, 20, 20);
    glTranslatef(25, 5, 0);
    glutSolidSphere(18, 20, 20);
    glTranslatef(-45, -3, 0);
    glutSolidSphere(16, 20, 20);
    glEnable(GL_LIGHTING);
    glPopMatrix();
}

// --- Sun ---
void drawSun() {
    glDisable(GL_LIGHTING);
    float sunX = -600 * cos(sunAngle * 3.14 / 180);
    float sunY = 500 + 100 * sin(sunAngle * 3.14 / 180);
    glColor3f(1.0f, 0.9f, 0.2f);
    glPushMatrix();
    glTranslatef(sunX, sunY, -1000);
    glutSolidSphere(60, 30, 30);
    glPopMatrix();
    glEnable(GL_LIGHTING);
}

// --- Lighting ---
void setupLights() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat pos[] = { 0.0f, 500.0f, 500.0f, 1.0f };
    GLfloat ambient[]  = { 0.4f, 0.4f, 0.4f, 1.0f };
    GLfloat diffuse[]  = { 0.9f, 0.9f, 0.9f, 1.0f };
    GLfloat specular[] = { 0.6f, 0.6f, 0.6f, 0.6f };

    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT,  ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}

// --- Display ---
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(0, camY, camZ, 0, 100, 0, 0, 1, 0);
    glRotatef(rotation, 0, 1, 0);

    drawSky();
    setupLights();
    drawSun();
    drawGround();
    drawCity();
    drawCar();

    drawCloud(cloudX, 400, -400);
    drawCloud(cloudX + 300, 450, -600);
    drawCloud(cloudX - 200, 420, 100);

    glutSwapBuffers();
}

// --- Animation ---
void idle() {
    if (!animate) return;

    // Move car vertically (Z-axis) - SLOWER MOVEMENT
    carZ += 0.5f; // Reduced from 1.0f to 0.5f for slower movement
    if (carZ > 900) carZ = -900;

    // Move buildings in opposite direction for parallax effect - SLOWER
    buildingOffset -= 0.2f; // Buildings move slowly in opposite direction
    if (buildingOffset < -180) buildingOffset = 0;

    cloudX += 0.3f;
    if (cloudX > 900) cloudX = -900;

    sunAngle += 0.1f;
    if (sunAngle > 360) sunAngle = 0;

    glutPostRedisplay();
}

// --- Controls ---
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 27: exit(0);
        case ' ': animate = !animate; break;
        case 'a': rotation += 5; break;
        case 'd': rotation -= 5; break;
        case 'w': camY += 20; break;
        case 's': camY -= 20; if (camY < 50) camY = 50; break;
        case 'z': camZ -= 50; break;
        case 'x': camZ += 50; break;
    }
    glutPostRedisplay();
}

// --- Init ---
void init() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.6f, 0.8f, 1.0f, 1.0f);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float)w/h, 1.0, 4000.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1200, 700);
    glutCreateWindow("Beautiful Dhaka 300ft View (Slow Moving Car & Buildings)");

    init();
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}