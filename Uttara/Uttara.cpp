#include <GL/glut.h>
#include <math.h>
#include <string>
#include <iostream>

enum TimeOfDay { DAY, NIGHT };
TimeOfDay current_time = DAY;

// Window dimensions defined as constants
const int WINDOW_WIDTH = 1280; // Width of the rendering window
const int WINDOW_HEIGHT = 720; // Height of the rendering window
const int WINDOW_X_START = 0;  // Starting X-coordinate of the window (left edge)
const int WINDOW_Y_START = 0;  // Starting Y-coordinate of the window (bottom edge)

///ID101
float car_x_pos_road1 = 0.0f, car_speed_road1 = 1.0f;
float bus_x_pos_road1 = -200.0f, bus_speed_road1 = 0.7f;
float school_bus_x_pos_road1 = -400.0f, school_bus_speed_road1 = 0.6f;

float train_x_pos = -270.0f, train_speed = 0.6f;
float boat_x_pos_lake = 0.0f, boat_speed_lake = 0.4f;
float airplane_x_pos = -100.0f;
float airplane_y_pos = 0.0f;
float airplane_speed = 0.5f;
float cloud_x_pos = 0.0f, cloud_speed = 0.2f;
bool enable_animation = true;
bool enable_car_animation = true;

///ID102
void renderText(float x, float y, const char* text) {
    glColor3ub(255, 255, 255);
    glRasterPos2f(x, y);
    for (const char* c = text; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}

///ID103
void drawCircle(float radius, float xc, float yc, GLubyte r, GLubyte g, GLubyte b) {
    glColor3ub(r, g, b);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float degInRad = i * M_PI / 180;
        glVertex2f(xc + cos(degInRad) * radius, yc + sin(degInRad) * radius);
    }
    glEnd();
}

///ID201
void drawSky() {
    if (current_time == DAY) {
        glBegin(GL_POLYGON);
        glColor3ub(135, 206, 250); glVertex2f(0, 720);
        glColor3ub(135, 206, 250); glVertex2f(1280, 720);
        glColor3ub(173, 216, 230); glVertex2f(1280, 324);
        glColor3ub(173, 216, 230); glVertex2f(0, 324);
        glEnd();
    } else {
        glBegin(GL_POLYGON);
        glColor3ub(0, 0, 0); glVertex2f(0, 720);
        glColor3ub(0, 0, 0); glVertex2f(1280, 720);
        glColor3ub(0, 0, 0); glVertex2f(1280, 324);
        glColor3ub(0, 0, 0); glVertex2f(0, 324);
        glEnd();
        glColor3ub(25, 25, 112); glVertex2f(0, 720);
        glColor3ub(25, 25, 112); glVertex2f(1280, 720);
        glColor3ub(30, 0, 50); glVertex2f(1280, 324);
        glColor3ub(30, 0, 50); glVertex2f(0, 324);
        glEnd();

    }
}

///ID202
void drawSunMoon() {
    if (current_time == DAY) {
        drawCircle(50, 192, 612, 255, 255, 0);
        glColor3ub(255, 255, 150);
        glLineWidth(2);
        glBegin(GL_LINES);
        for (int i = 0; i < 360; i += 30) {
            float degInRad = i * M_PI / 180;
            glVertex2f(192, 612);
            glVertex2f(192 + cos(degInRad) * 60, 612 + sin(degInRad) * 60);
        }
        glEnd();
        glLineWidth(1);
    } else {
        drawCircle(40, 192, 612, 200, 200, 200);
        glColor3ub(30, 0, 50);
        drawCircle(38, 202, 617, 30, 0, 50);
    }
}

///ID203
void drawCloud(float x, float y) {
    glColor3ub(255, 255, 255);
    drawCircle(25, x, y, 255, 255, 255);
    drawCircle(30, x + 40, y, 255, 255, 255);
    drawCircle(20, x + 20, y + 20, 255, 255, 255);
    drawCircle(28, x + 60, y + 10, 255, 255, 255);
}

///ID204
void drawGround() {
    glColor3ub(51, 150, 15);
    glBegin(GL_POLYGON);
    glVertex2f(0, 324);
    glVertex2f(1280, 324);
    glVertex2f(1280, 252);
    glVertex2f(0, 252);
    glEnd();
}

///ID205
void drawRailwayTracks(float y_position) {
    glColor3ub(255, 255, 0);
    glBegin(GL_POLYGON);
    glVertex2f(0, y_position - 20);
    glVertex2f(1280, y_position - 20);
    glVertex2f(1280, y_position + 40);
    glVertex2f(0, y_position + 40);
    glEnd();

    glColor3ub(200, 200, 0);
    glLineWidth(4);
    for (float x = 0; x < 1280; x += 50) {
        glBegin(GL_LINES);
        glVertex2f(x, y_position + 5);
        glVertex2f(x + 35, y_position + 30);
        glEnd();
    }

    glColor3ub(150, 150, 0);
    glLineWidth(6);
    glBegin(GL_LINES);
    glVertex2f(0, y_position + 10);
    glVertex2f(1280, y_position + 10);
    glVertex2f(0, y_position + 25);
    glVertex2f(1280, y_position + 25);
    glEnd();
    glLineWidth(1);
}

///ID206
void drawRoad(float y_bottom, float height) {
    glColor3ub(70, 70, 70);
    glBegin(GL_POLYGON);
    glVertex2f(0, y_bottom);
    glVertex2f(1280, y_bottom);
    glVertex2f(1280, y_bottom + height);
    glVertex2f(0, y_bottom + height);
    glEnd();

    glLineWidth(3);
    glColor3ub(255, 255, 0);
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x00F0);
    glBegin(GL_LINES);
    glVertex2f(0, y_bottom + height / 2);
    glVertex2f(1280, y_bottom + height / 2);
    glEnd();
    glDisable(GL_LINE_STIPPLE);

    glLineWidth(4);
    glColor3ub(255, 255, 255);
    glBegin(GL_LINES);
    glVertex2f(0, y_bottom);
    glVertex2f(1280, y_bottom);
    glVertex2f(0, y_bottom + height);
    glVertex2f(1280, y_bottom + height);
    glEnd();
}

///ID207
void drawLake(float x_start, float y_bottom, float width, float height) {
    glColor3ub(50, 150, 200);
    glBegin(GL_POLYGON);
    glVertex2f(x_start, y_bottom);
    glVertex2f(x_start + width, y_bottom);
    glVertex2f(x_start + width, y_bottom + height);
    glVertex2f(x_start, y_bottom + height);
    glEnd();

    glColor3ub(60, 180, 20);
    glBegin(GL_POLYGON);
    glVertex2f(x_start, y_bottom + height);
    glVertex2f(x_start + width, y_bottom + height);
    glVertex2f(x_start + width, y_bottom + height + 15);
    glVertex2f(x_start, y_bottom + height + 15);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(x_start, y_bottom);
    glVertex2f(x_start + width, y_bottom);
    glVertex2f(x_start + width, y_bottom - 15);
    glVertex2f(x_start, y_bottom - 15);
    glEnd();
}

///ID208
void drawBridge(float x_start, float y_bottom, float width, float height) {
    glColor3ub(120, 120, 120);
    glBegin(GL_POLYGON);
    glVertex2f(x_start, y_bottom);
    glVertex2f(x_start + width, y_bottom);
    glVertex2f(x_start + width, y_bottom + height);
    glVertex2f(x_start, y_bottom + height);
    glEnd();

    glColor3ub(100, 100, 100);
    float support_width = 15;
    float support_height = y_bottom - 36;
    for (int i = 0; i < 3; ++i) {
        float sx = x_start + (width / 3) * i + (width / 3 - support_width) / 2;
        glBegin(GL_POLYGON);
        glVertex2f(sx, y_bottom);
        glVertex2f(sx + 15, y_bottom);
        glVertex2f(sx + 15, y_bottom - support_height);
        glVertex2f(sx, y_bottom - support_height);
        glEnd();
    }

    glLineWidth(5);
    glColor3ub(80, 80, 80);
    glBegin(GL_LINES);
    glVertex2f(x_start, y_bottom + height);
    glVertex2f(x_start + width, y_bottom + height);
    glVertex2f(x_start, y_bottom + height * 0.7);
    glVertex2f(x_start + width, y_bottom + height * 0.7);
    glEnd();
    glLineWidth(1);
}

///ID209
void drawBuilding(float x, float y, float width, float height, GLubyte r, GLubyte g, GLubyte b, int type = 0) {
    glColor3ub(r, g, b);
    glBegin(GL_POLYGON);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();

    if (type == 0) {
        glColor3ub(r * 0.7, g * 0.7, b * 0.7);
        glBegin(GL_POLYGON);
        glVertex2f(x, y + height);
        glVertex2f(x + width, y + height);
        glVertex2f(x + width, y + height + 10);
        glVertex2f(x, y + height + 10);
        glEnd();
    } else if (type == 1) {
        glColor3ub(r * 0.7, g * 0.7, b * 0.7);
        glBegin(GL_POLYGON);
        glVertex2f(x, y + height);
        glVertex2f(x + width, y + height);
        glVertex2f(x + width / 2, y + height + width * 0.3);
        glEnd();
    } else if (type == 2) {
        glColor3ub(r * 0.7, g * 0.7, b * 0.7);
        glBegin(GL_POLYGON);
        glVertex2f(x, y + height);
        glVertex2f(x + width, y + height);
        glVertex2f(x + width, y + height + 10);
        glVertex2f(x + width * 0.7, y + height + 10);
        glVertex2f(x + width * 0.7, y + height + 20);
        glVertex2f(x + width * 0.3, y + height + 20);
        glVertex2f(x + width * 0.3, y + height + 10);
        glVertex2f(x, y + height + 10);
        glEnd();
    }

    glColor3ub(75, 89, 98);
    float window_width = width * 0.10;
    float window_height = height * 0.07;
    float window_spacing_x = width * 0.07;
    float window_spacing_y = height * 0.07;

    for (int row = 0; row < (height / (window_height + window_spacing_y)) - 1; ++row) {
        for (int col = 0; col < (width / (window_width + window_spacing_x)) - 1; ++col) {
            float win_x = x + window_spacing_x + col * (window_width + window_spacing_x);
            float win_y = y + window_spacing_y + row * (window_height + window_spacing_y);
            if (win_x + window_width < x + width - window_spacing_x && win_y + window_height < y + height - window_spacing_y) {
                glBegin(GL_POLYGON);
                glVertex2f(win_x, win_y);
                glVertex2f(win_x + window_width, win_y);
                glVertex2f(win_x + window_width, win_y + window_height);
                glVertex2f(win_x, win_y + window_height);
                glEnd();
            }
        }
    }
}

///ID210
void drawTrainStation(float x, float y, float width, float height) {
    glColor3ub(160, 120, 80);
    glBegin(GL_POLYGON);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();

    glColor3ub(100, 80, 60);
    glBegin(GL_POLYGON);
    glVertex2f(x - 15, y + height + 5);
    glVertex2f(x + width + 400, y + height + 5);
    glVertex2f(x + width + 400, y + height + 30);
    glVertex2f(x - 15, y + height + 30);
    glEnd();

    glColor3ub(200, 200, 200);
    glBegin(GL_POLYGON);
    glVertex2f(x - 30, y - 5);
    glVertex2f(x + width + 415, y - 5);
    glVertex2f(x + width + 415, y - 65);
    glVertex2f(x - 30, y - 65);
    glEnd();

    glColor3ub(75, 89, 98);
    glBegin(GL_POLYGON);
    glVertex2f(x + width * 0.4, y);
    glVertex2f(x + width * 0.6, y);
    glVertex2f(x + width * 0.6, y + height * 0.6);
    glVertex2f(x + width * 0.4, y + height * 0.6);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(x + width * 0.1, y + height * 0.4);
    glVertex2f(x + width * 0.25, y + height * 0.4);
    glVertex2f(x + width * 0.25, y + height * 0.7);
    glVertex2f(x + width * 0.1, y + height * 0.7);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(x + width * 0.75, y + height * 0.4);
    glVertex2f(x + width * 0.9, y + height * 0.4);
    glVertex2f(x + width * 0.9, y + height * 0.7);
    glVertex2f(x + width * 0.75, y + height * 0.7);
    glEnd();

    renderText(x + width * 0.35, y + height + 35, "Train Station");
}

///ID211
void drawCar(float x, float y, GLubyte r, GLubyte g, GLubyte b, const char* type = "car") {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);

    if (strcmp(type, "school_bus") == 0) {
        glColor3ub(255, 215, 0);
        glBegin(GL_POLYGON);
        glVertex2f(0, 0);
        glVertex2f(150, 0);
        glVertex2f(150, 50);
        glVertex2f(0, 50);
        glEnd();

        glColor3ub(100, 100, 100);
        glBegin(GL_POLYGON); glVertex2f(10, 30); glVertex2f(35, 30); glVertex2f(35, 40); glVertex2f(10, 40); glEnd();
        glBegin(GL_POLYGON); glVertex2f(45, 30); glVertex2f(70, 30); glVertex2f(70, 40); glVertex2f(45, 40); glEnd();
        glBegin(GL_POLYGON); glVertex2f(80, 30); glVertex2f(105, 30); glVertex2f(105, 40); glVertex2f(80, 40); glEnd();
        glBegin(GL_POLYGON); glVertex2f(115, 30); glVertex2f(140, 30); glVertex2f(140, 40); glVertex2f(115, 40); glEnd();

        drawCircle(18, 30, 0, 0, 0, 0);
        drawCircle(18, 120, 0, 0, 0, 0);

        glColor3ub(120, 120, 120);
        glBegin(GL_POLYGON);
        glVertex2f(0, 30); glVertex2f(-20, 30); glVertex2f(-20, 35); glVertex2f(0, 35); glEnd();

        glColor3ub(255, 0, 0);
        glBegin(GL_POLYGON);
        glVertex2f(-20, 35);
        glVertex2f(-25, 37);
        glVertex2f(-25, 45);
        glVertex2f(-20, 47);
        glVertex2f(-12, 47);
        glVertex2f(-7, 45);
        glVertex2f(-7, 37);
        glVertex2f(-12, 35);
        glEnd();

    } else if (strcmp(type, "diim_bus") == 0) {
        glColor3ub(0, 0, 200);
        glBegin(GL_POLYGON);
        glVertex2f(0, 0);
        glVertex2f(150, 0);
        glVertex2f(150, 50);
        glVertex2f(0, 50);
        glEnd();

        glColor3ub(100, 100, 100);
        glBegin(GL_POLYGON); glVertex2f(10, 30); glVertex2f(40, 30); glVertex2f(40, 40); glVertex2f(10, 40); glEnd();
        glBegin(GL_POLYGON); glVertex2f(50, 30); glVertex2f(80, 30); glVertex2f(80, 40); glVertex2f(50, 40); glEnd();
        glBegin(GL_POLYGON); glVertex2f(90, 30); glVertex2f(120, 30); glVertex2f(120, 40); glVertex2f(90, 40); glEnd();

        drawCircle(18, 30, 0, 0, 0, 0);
        drawCircle(18, 120, 0, 0, 0, 0);

    } else if (strcmp(type, "police") == 0) {
        glColor3ub(0, 0, 255);
        glBegin(GL_POLYGON);
        glVertex2f(0, 20);  glVertex2f(90, 20); glVertex2f(100, 30); glVertex2f(80, 45); glVertex2f(20, 45); glVertex2f(10, 30);
        glEnd();
        glColor3ub(100, 100, 100);
        glBegin(GL_POLYGON); glVertex2f(25, 30); glVertex2f(45, 42); glVertex2f(40, 42); glVertex2f(20, 30); glEnd();
        glBegin(GL_POLYGON); glVertex2f(50, 42); glVertex2f(75, 42); glVertex2f(80, 30); glVertex2f(55, 30); glEnd();
        drawCircle(15, 25, 20, 0, 0, 0); drawCircle(15, 75, 20, 0, 0, 0);
        glColor3ub(255, 255, 0);
        glBegin(GL_POLYGON); glVertex2f(45, 47); glVertex2f(55, 47); glVertex2f(55, 50); glVertex2f(45, 50); glEnd();
    } else if (strcmp(type, "truck") == 0) {
        glColor3ub(255, 255, 255);
        glBegin(GL_POLYGON);
        glVertex2f(0, 20); glVertex2f(50, 20); glVertex2f(50, 40); glVertex2f(0, 40); glEnd();
        glColor3ub(180, 180, 180);
        glBegin(GL_POLYGON);
        glVertex2f(50, 20); glVertex2f(120, 20); glVertex2f(120, 40); glVertex2f(50, 40); glEnd();
        drawCircle(15, 20, 20, 0, 0, 0); drawCircle(15, 100, 20, 0, 0, 0);
    } else {
        glColor3ub(r, g, b);
        glBegin(GL_POLYGON);
        glVertex2f(0, 20);
        glVertex2f(100, 20);
        glVertex2f(95, 40);
        glVertex2f(70, 50);
        glVertex2f(30, 50);
        glVertex2f(5, 40);
        glEnd();

        glColor3ub(75, 89, 98);
        glBegin(GL_POLYGON); glVertex2f(15, 40); glVertex2f(35, 48); glVertex2f(32, 48); glVertex2f(12, 40); glEnd();
        glBegin(GL_POLYGON); glVertex2f(40, 48); glVertex2f(65, 48); glVertex2f(68, 40); glVertex2f(43, 40); glEnd();

        drawCircle(15, 25, 20, 0, 0, 0);
        drawCircle(15, 75, 20, 0, 0, 0);
    }

    glPopMatrix();
}

///ID212
void drawTrain(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);

    glColor3ub(255, 255, 255);
    glBegin(GL_POLYGON);
    glVertex2f(0, 0); glVertex2f(100, 0); glVertex2f(100, 50); glVertex2f(0, 50); glEnd();
    glColor3ub(0, 0, 200);
    glBegin(GL_POLYGON); glVertex2f(10, 25); glVertex2f(90, 25); glVertex2f(90, 35); glVertex2f(10, 35); glEnd();
    drawCircle(15, 25, 0, 0, 0, 0); drawCircle(15, 75, 0, 0, 0, 0);

    for (int i = 1; i <= 3; ++i) {
        glColor3ub(0, 0, 200);
        glBegin(GL_POLYGON);
        glVertex2f(110 + i * 100, 0);
        glVertex2f(110 + i * 100 + 90, 0);
        glVertex2f(110 + i * 100 + 90, 45);
        glVertex2f(110 + i * 100, 45);
        glEnd();
        drawCircle(15, 110 + i * 100 + 20, 0, 0, 0, 0);
        drawCircle(15, 110 + i * 100 + 70, 0, 0, 0, 0);
    }

    glPopMatrix();
}

///ID213
void drawBoat(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);

    glColor3ub(64, 224, 208);
    glBegin(GL_POLYGON);
    glVertex2f(0, 0);
    glVertex2f(110, 0);
    glVertex2f(105, 15);
    glVertex2f(5, 15);
    glEnd();

    glColor3ub(20, 20, 100);
    glBegin(GL_POLYGON);
    glVertex2f(5, 15);
    glVertex2f(105, 15);
    glVertex2f(105, 45);
    glVertex2f(5, 45);
    glEnd();

    glColor3ub(255, 255, 255);
    glBegin(GL_POLYGON);
    glVertex2f(60, 45);
    glVertex2f(95, 45);
    glVertex2f(95, 75);
    glVertex2f(60, 75);
    glEnd();

    glColor3ub(144, 238, 144);
    glBegin(GL_POLYGON);
    glVertex2f(65, 55);
    glVertex2f(75, 55);
    glVertex2f(75, 65);
    glVertex2f(65, 65);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(80, 55);
    glVertex2f(90, 55);
    glVertex2f(90, 65);
    glVertex2f(80, 65);
    glEnd();

    glColor3ub(255, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2f(58, 75);
    glVertex2f(97, 75);
    glVertex2f(97, 80);
    glVertex2f(58, 80);
    glEnd();

    glPopMatrix();
}

///ID214
void drawAirplane(float x, float y) {
    // tail
    glBegin(GL_POLYGON);
        glColor3ub(35, 50, 64);
        glVertex2i(x + 70, y + 20);
        glVertex2i(x + 100, y + 20);
        glVertex2i(x + 100, y + 40);
        glVertex2i(x + 90, y + 30);
        glVertex2i(x + 80, y + 30);
        glVertex2i(x + 80, y + 30);
    glEnd();

    // body
    glBegin(GL_POLYGON);
        glColor3ub(65, 86, 111);
        glVertex2i(x, y);
        glVertex2i(x + 80, y);
        glVertex2i(x + 100, y + 20);
        glVertex2i(x + 30, y + 20);
        glVertex2i(x + 30, y + 10);
        glVertex2i(x + 10, y + 10);
    glEnd();

    // cockpit
    glBegin(GL_POLYGON);
        glColor3ub(166, 214, 252);
        glVertex2i(x + 20, y + 10);
        glVertex2i(x + 30, y + 10);
        glVertex2i(x + 30, y + 20);
    glEnd();

    // backline
    glLineWidth(8);
    glBegin(GL_LINES);
        glColor3ub(166, 214, 252);
        glVertex2f(x + 80, y + 20);
        glVertex2f(x + 110, y + 20);
    glEnd();

    // fan
    glBegin(GL_POLYGON);
        glColor3ub(35, 50, 64);
        glVertex2i(x + 40, y - 10);
        glVertex2i(x + 60, y - 10);
        glVertex2i(x + 70, y);
        glVertex2i(x + 60, y + 10);
        glVertex2i(x + 40, y + 10);
    glEnd();
}


///ID215
void drawTree(float x, float y, int type = 0) {
    glColor3ub(116, 80, 64);
    glBegin(GL_POLYGON);
    glVertex2f(x - 8, y);
    glVertex2f(x + 8, y);
    glVertex2f(x + 8, y + 40);
    glVertex2f(x - 8, y + 40);
    glEnd();

    if (type == 0) {
        glColor3ub(78, 207, 33);
        drawCircle(25, x, y + 50, 78, 207, 33);
        drawCircle(20, x - 15, y + 45, 78, 207, 33);
        drawCircle(20, x + 15, y + 45, 78, 207, 33);
    } else if (type == 1) {
        glColor3ub(34, 139, 34);
        glBegin(GL_TRIANGLES);
        glVertex2f(x, y + 70);
        glVertex2f(x + 30, y + 40);
        glVertex2f(x - 30, y + 40);
        glEnd();
        glBegin(GL_TRIANGLES);
        glVertex2f(x, y + 55);
        glVertex2f(x + 25, y + 30);
        glVertex2f(x - 25, y + 30);
        glEnd();
    } else if (type == 2) {
        glColor3ub(0, 128, 0);
        drawCircle(35, x, y + 60, 0, 128, 0);
    }
}

///ID216
void drawLamppost(float x, float y) {
    glColor3ub(100, 100, 100);
    glBegin(GL_POLYGON);
    glVertex2f(x - 4, y);
    glVertex2f(x + 4, y);
    glVertex2f(x + 4, y + 70);
    glVertex2f(x - 4, y + 70);
    glEnd();

    glColor3ub(60, 60, 60);
    glBegin(GL_POLYGON);
    glVertex2f(x + 4, y + 65);
    glVertex2f(x + 40, y + 65);
    glVertex2f(x + 40, y + 60);
    glVertex2f(x + 4, y + 60);
    glEnd();

    if (current_time == DAY) {
        drawCircle(7, x + 40, y + 62.5, 255, 255, 255);
    } else {
        drawCircle(7, x + 40, y + 62.5, 255, 243, 0);
    }
}

///ID301
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 1280, 0, 720);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    drawSky();
    drawSunMoon();
    drawCloud(cloud_x_pos, 612);
    drawCloud(cloud_x_pos + 350, 576);
    drawCloud(cloud_x_pos + 700, 561.6);
    drawCloud(cloud_x_pos + 1050, 597.6);

    drawAirplane(airplane_x_pos, 630 + airplane_y_pos);

    drawGround();

    drawBuilding(50, 324, 150, 220, 180, 180, 180, 0);
    drawBuilding(220, 324, 120, 190, 200, 100, 100, 1);
    drawBuilding(360, 324, 180, 260, 150, 150, 150, 0);
    drawBuilding(560, 324, 100, 170, 220, 180, 180, 2);
    drawBuilding(690, 324, 130, 200, 100, 150, 200, 0);
    drawBuilding(840, 324, 160, 240, 120, 120, 120, 1);
    drawBuilding(1020, 324, 80, 150, 255, 200, 0, 0);

   drawBuilding(30, 324, 100, 160, 160, 160, 160, 0);
drawBuilding(180, 324, 90, 180, 190, 190, 190, 2);
drawBuilding(300, 324, 110, 150, 170, 130, 130, 1);
drawBuilding(480, 324, 140, 210, 130, 180, 130, 0);
drawBuilding(650, 324, 95, 175, 210, 160, 160, 0);
drawBuilding(810, 324, 120, 220, 140, 140, 200, 1);
drawBuilding(980, 324, 70, 140, 240, 180, 80, 0);


    drawTree(100, 324, 0);
    drawTree(350, 324, 1);
    drawTree(550, 324, 0);
    drawTree(800, 324, 2);
    drawTree(1100, 324, 0);

    float upper_road_y_bottom = 180;
    drawRoad(upper_road_y_bottom, 90);

    float lower_road_y_bottom = 0;
    drawRoad(lower_road_y_bottom, 90);

    float lake_y_bottom = 90;
    float lake_height = 90;
    drawLake(0, lake_y_bottom, 1280, lake_height);

    drawBridge(128, 180, 320, 40);
    drawBridge(832, 180, 320, 40);


     drawLamppost(150, 270);
    drawLamppost(450, 270);
    drawLamppost(750, 270);
    drawLamppost(1050, 270);

    drawCar(car_x_pos_road1, 240, 255, 0, 0, "car");
    drawCar(bus_x_pos_road1, 240, 0, 0, 0, "diim_bus");
    drawCar(school_bus_x_pos_road1, 240, 0, 0, 0, "school_bus");

    float railway_track_y = 55;
    drawRailwayTracks(railway_track_y);

    drawTrain(108 + train_x_pos, 72);

    drawTrainStation(128, 100, 200, 80);

    float boat_y_on_lake = 110;
    drawBoat(boat_x_pos_lake + 640, boat_y_on_lake);





    glutSwapBuffers();
}

///ID401
void update(int value) {
if (enable_animation) {
    if (enable_car_animation) {
                car_x_pos_road1 += car_speed_road1;
                if (car_x_pos_road1 > 1280 + 50) {
                    car_x_pos_road1 = -200;
                }

                bus_x_pos_road1 += bus_speed_road1;
                if (bus_x_pos_road1 > 1280 + 50) {
                    bus_x_pos_road1 = -200;
                }

                school_bus_x_pos_road1 += school_bus_speed_road1;
                if (school_bus_x_pos_road1 > 1280 + 50) {
                    school_bus_x_pos_road1 = -200;
                }

    }
        train_x_pos += train_speed;
        if (train_x_pos > 1280 + 100) {
            train_x_pos = -400;
        }

        boat_x_pos_lake += boat_speed_lake;
        if (boat_x_pos_lake > 1280 + 50) {
            boat_x_pos_lake = -200;
        }

       airplane_x_pos -= airplane_speed;
       airplane_y_pos += airplane_speed * 0.05;
    if (airplane_x_pos < -200) {
    airplane_x_pos = 1280 + 200;
    airplane_y_pos = 0;
                   }


        cloud_x_pos += cloud_speed;
        if (cloud_x_pos > 1280 + 150) {
            cloud_x_pos = -250;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

///ID501
void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

///ID601

void handleKeypress(unsigned char key, int x, int y) {
    if (key == 'n') current_time = NIGHT;
    else if (key == 'd') current_time = DAY;
    glutPostRedisplay();
}


void handleMouse(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        if (button == GLUT_LEFT_BUTTON) {
            // Increase speed
            car_speed_road1 *= 1.2f;
            bus_speed_road1 *= 1.2f;
            school_bus_speed_road1 *= 1.2f;
            train_speed *= 1.2f;
            boat_speed_lake *= 1.2f;
            airplane_speed *= 1.2f;
            cloud_speed *= 1.2f;
        } else if (button == GLUT_RIGHT_BUTTON) {
            // Decrease speed
            car_speed_road1 *= 0.8f;
            bus_speed_road1 *= 0.8f;
            school_bus_speed_road1 *= 0.8f;
            train_speed *= 0.8f;
            boat_speed_lake *= 0.8f;
            airplane_speed *= 0.8f;
            cloud_speed *= 0.8f;
        }
        glutPostRedisplay();
    }
}



int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Nikuja Scene - OpenGL/GLUT");

    init();

    glutDisplayFunc(display);
    glutMouseFunc(handleMouse);
    glutKeyboardFunc(handleKeypress);
    glutReshapeFunc(NULL);
    glutTimerFunc(0, update, 0);

    glutMainLoop();

    return 0;
}
