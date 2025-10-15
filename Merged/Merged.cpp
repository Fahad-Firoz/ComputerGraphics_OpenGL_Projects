#include <GL/glut.h>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#define PI 3.14159265358979323846

// ========================= Window and scene manager =========================

float airportSpeedFactor = 0.15f;
const int WINDOW_WIDTH  = 1280;
const int WINDOW_HEIGHT = 720;
const int WINDOW_X_START = 0;  // Starting X-coordinate of the window (left edge)
const int WINDOW_Y_START = 0;  // Starting Y-coordinate of the window (bottom edge)


enum Scene { SCENE_AIRPORT = 1, SCENE_UTTARA = 2, SCENE_300FT = 3 };
;
int currentScene = SCENE_AIRPORT;

// Forward declarations
void initUnified();
void displayUnified();
void updateUnified(int value);
void handleKeypressUnified(unsigned char key, int x, int y);
void handleMouseUnified(int button, int state, int x, int y);

// Scene-specific functions
void drawAirportScene();
void updateAirport(int value);
void handleKeypressAirport(unsigned char key, int x, int y);
void handleMouseAirport(int button, int state, int x, int y);

void drawUttaraScene();
void updateUttara(int value);
void handleKeypressUttara(unsigned char key, int x, int y);
void handleMouseUttara(int button, int state, int x, int y);

void draw300ftScene();
void update300ft(int value);
void handleKeypress300ft(unsigned char key, int x, int y);
void handleMouse300ft(int button, int state, int x, int y);

// Optional overlay label
void drawOverlayText(const char* label);

// ========================= Unified init and loop =========================

void initUnified() {
    glClearColor(0.0, 0.0, 0.0, 1.0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void displayUnified() {
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if (currentScene == SCENE_AIRPORT) {
        glPushMatrix();
        // Airport scene is 160x90; scale it up to 1280x720
        glScalef(8.0f, 8.0f, 1.0f);
        drawAirportScene();
        glPopMatrix();

        drawOverlayText("Scene: Airport (press 2 = Uttara, press 3 = 300ft)");
    }
    else if (currentScene == SCENE_UTTARA) {
        // Uttara is already in 1280x720 space
        drawUttaraScene();

        drawOverlayText("Scene: Uttara (press 1 = Airport, press 3 = 300ft)");
    }
    else if (currentScene == SCENE_300FT) {
        glPushMatrix();
        // 300ft scene is also 160x90; scale it up to 1280x720
        glScalef(8.0f, 8.0f, 1.0f);
        draw300ftScene();
        glPopMatrix();

        drawOverlayText("Scene: 300ft (press 1 = Airport, 2 = Uttara)");
    }

    glutSwapBuffers();
}

void updateUnified(int value) {

    if (currentScene == SCENE_AIRPORT) {
        updateAirport(value);}
    else if (currentScene == SCENE_UTTARA) {
    updateUttara(value);
    }else if (currentScene == SCENE_300FT) {
    update300ft(value);
}

    glutPostRedisplay();
    glutTimerFunc(16, updateUnified, 0); // ~60 FPS
}

void handleKeypressUnified(unsigned char key, int x, int y) {
   if (key == '1') currentScene = SCENE_AIRPORT;
else if (key == '2') currentScene = SCENE_UTTARA;
else if (key == '3') currentScene = SCENE_300FT;

if (currentScene == SCENE_AIRPORT) {
    handleKeypressAirport(key, x, y);
}
else if (currentScene == SCENE_UTTARA) {
    handleKeypressUttara(key, x, y);
}
else if (currentScene == SCENE_300FT) {
    handleKeypress300ft(key, x, y);
}



    glutPostRedisplay();
}

void handleMouseUnified(int button, int state, int x, int y) {
    if (currentScene == SCENE_AIRPORT) {
    handleMouseAirport(button, state, x, y);
}
else if (currentScene == SCENE_UTTARA) {
    handleMouseUttara(button, state, x, y);
}
else if (currentScene == SCENE_300FT) {
    handleMouse300ft(button, state, x, y);
}


}

// ========================= Overlay text =========================

void drawOverlayText(const char* label) {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glColor3ub(255, 255, 255);
    glRasterPos2f(20, WINDOW_HEIGHT - 30);
    for (const char* c = label; *c; ++c) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}
// ========================= AIRPORT SCENE (Project 1) =========================
// Globals renamed for Airport isolation and conflict-avoidance

int airportScenePhase = 0;

// Movement toggles
bool airport_plane_moving = true;
bool airport_bus_moving = true;
bool airport_car_moving = true;

// Positions and speeds
float airport_bus_position = 0.0f, airport_car_position = 0.0f;
float airport_bus_speed = 0.1f, airport_car_speed = 0.1f;

float airport_plane_4_pos = 0.0f, airport_plane_5_pos = 0.0f;

// Plane runway animation pos
float airport_plane_x_1 = 0.0f, airport_plane_y_1 = 0.0f;

// Wheel rotation
float airport_angle1 = 0.0f;

// Environment
float airport_sun_position = -18.0f;
float airport_grass_movement = 0.0f;
float airport_move_Cloud = 0.0f;

enum WeatherStateAirport { SUNNY_AIRPORT, OVERCAST_AIRPORT, RAINY_AIRPORT };
WeatherStateAirport airportWeather = SUNNY_AIRPORT;

// Raindrops
struct AirportRaindrop {
    float x, y;
    float speed;
};
std::vector<AirportRaindrop> airportRaindrops;
// Geometry helpers
void airportCircle(float radius, float xc, float yc, float r, float g, float b) {
    glLineWidth(7.5);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 200; i++) {
        glColor3f(r, g, b);
        float A = (i * 2 * PI) / 200.0f;
        float x = radius * cos(A);
        float y = radius * sin(A);
        glVertex2f(x + xc, y + yc);
    }
    glEnd();
}

void airportWheel(float radius, float xc, float yc) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < 200; i++) {
        glColor3ub(0, 0, 0);
        float A = (i * 2 * PI) / 200.0f;
        float x = radius * cos(A);
        float y = radius * sin(A);
        glVertex2f(x + xc, y + yc);
    }
    glEnd();

    glBegin(GL_POLYGON);
    for (int i = 0; i < 200; i++) {
        glColor3ub(255, 255, 255);
        float A = (i * 2 * PI) / 200.0f;
        float inner = radius - 0.6f;
        float x = inner * cos(A);
        float y = inner * sin(A);
        glVertex2f(x + xc, y + yc);
    }
    glEnd();

    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(xc - radius + 0.6f, yc);
    glVertex2f(xc + radius - 0.6f, yc);
    glVertex2f(xc, yc + radius - 0.6f);
    glVertex2f(xc, yc - radius + 0.6f);
    glEnd();
}

// Text helpers
void airportRenderTextTerminal(float x, float y, const char* text) {
    glRasterPos2f(x, y);
    for (const char* c = text; *c != '\0'; ++c) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}

void airportRenderTextAviation(float x, float y, const char* text) {
    glRasterPos2f(x, y);
    for (const char* c = text; *c != '\0'; ++c) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
    }
}

// Rain helpers
void initializeAirportRaindrops(int count) {
    airportRaindrops.clear();
    airportRaindrops.reserve(count);
    for (int i = 0; i < count; i++) {
        AirportRaindrop drop;
        drop.x = static_cast<float>(rand() % 160);
        drop.y = static_cast<float>(rand() % 90 + 90);
        drop.speed = static_cast<float>((rand() % 10 + 12) * 0.1f);
        airportRaindrops.push_back(drop);
    }
}

void drawAirportRaindrops() {
    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(1.5);
    glBegin(GL_LINES);
    for (const auto& d : airportRaindrops) {
        glVertex2f(d.x, d.y);
        glVertex2f(d.x, d.y - 2.0f);
    }
    glEnd();
}

void updateAirportRaindrops(int /*unused*/) {
    for (auto& d : airportRaindrops) {
        d.y -= d.speed;
        if (d.y < 0) {
            d.y = static_cast<float>(rand() % 45 + 90);
            d.x = static_cast<float>(rand() % 160);
        }
    }
}
void Cloud(bool rain) {
    float r = 1.0, g = 1.0, b = 1.0;
    if (rain) r = g = b = 0.65;

    // Cloud 1
    airportCircle(1.5, 81, 87, r, g, b);
    airportCircle(2.8, 75.0, 87.0, r, g, b);
    airportCircle(2.5, 79.0, 87.0, r, g, b);
    airportCircle(2.2, 72.0, 87, r, g, b);
    airportCircle(1.2, 69.8, 87, r, g, b);

    // Cloud 2
    airportCircle(1.5, 131, 87, r, g, b);
    airportCircle(2.8, 125.0, 87.0, r, g, b);
    airportCircle(2.5, 121.0, 87.0, r, g, b);
    airportCircle(2.0, 129.0, 87.0, r, g, b);
    airportCircle(1.5, 119, 87, r, g, b);
}

void Sun(float radius, float xc, float yc) {
    glPushMatrix();
    glTranslatef(0.0f, airport_sun_position, 0.0f);

    glBegin(GL_POLYGON);
    if (airportWeather == RAINY_AIRPORT)
        glColor3f(0.4, 0.4, 0.4);
    else
        glColor4ub(253, 255, 50, 255);

    for (int i = 0; i < 200; i++) {
        float angle = (i * 2 * PI) / 200;
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex2f(x + xc, y + yc);
    }
    glEnd();
    glPopMatrix();
}

// Grass, Catkin, Lake, Runways1, Runways2, Taxiways1, Taxiways2, Taxiways3,

void Grass()
{
    ///Background area for grass
    glBegin(GL_POLYGON);
    glColor4ub(40,60,4,255);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(160.0f, 0.0f);
    glVertex2f(160.0f, 8.0f);
    glVertex2f(0.0f, 8.0f);
    glEnd();



    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    for(int i=0; i<5; i++)
    {

        glBegin(GL_POLYGON);
        glColor4ub(163,219,0,255);
        glVertex2f(4.0f, 0.0f);
        glVertex2f(2.0f, 3.0f);
        glVertex2f(6.0f, 0.0f);
        glEnd();

        glBegin(GL_POLYGON);
        glColor4ub(57,181,74,255);
        glVertex2f(4.0f, 0.0f);
        glVertex2f(3.0f, 6.0f);
        glVertex2f(6.0f, 0.0f);
        glEnd();

        glBegin(GL_POLYGON);
        glColor4ub(163,219,0,255);
        glVertex2f(4.0f, 0.0f);
        glVertex2f(6.0f, 6.0f);
        glVertex2f(6.0f, 0.0f);
        glEnd();

        glBegin(GL_POLYGON);
        glColor4ub(57,181,74,255);
        glVertex2f(4.0f, 0.0f);
        glVertex2f(8.0f, 4.0f);
        glVertex2f(6.0f, 0.0f);
        glEnd();

        glTranslatef(38.0f, 0.0f, 0.0f);

    }

    glPopMatrix();

}

///ID102
///Catkin

void Catkin()
{


    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(airport_grass_movement, 0.0, 0.0);
    glPushMatrix();
    for(int i=0; i<5; i++)
    {

        glLineWidth(2);
        glBegin(GL_LINES);
        glColor4ub(63,255,9,255);
        glVertex2f(9.0f, 0.0f);
        glVertex2f(10.0f, 3.0f);
        glEnd();

        glBegin(GL_POLYGON);
        glColor4ub(255,255,255,255);
        glVertex2f(9.5f, 5.0f);
        glVertex2f(11.50f, 8.0f);
        glVertex2f(11.3f, 5.0f);
        glVertex2f(10.0f, 3.0f);
        glEnd();

        ///Grass1
        glBegin(GL_POLYGON);
        glColor4ub(50,129,35,255);
        glVertex2f(15.9838448237412, 0);
        glVertex2f(16.8821608132169, 0);
        glVertex2f(12.0102361995158, 4.8453976576681);
        glEnd();

        ///Grass2
        glBegin(GL_POLYGON);
        glColor4ub(50,129,35,255);
        glVertex2f(15.9838448237412, 0);
        glVertex2f(16.8821608132169, 0);
        glVertex2f(12.7124013356394, 5.381678260384);
        glEnd();

        ///Grass3
        glBegin(GL_POLYGON);
        glColor4ub(50,129,35,255);
        glVertex2f(17.4849858595596, 0);
        glVertex2f(18.745640466851, 0);
        glVertex2f(21.4978565706798, 5.3241693519912);
        glEnd();

        ///Grass4
        glBegin(GL_POLYGON);
        glColor4ub(50,129,35,255);
        glVertex2f(17.6837631757812, 0);
        glVertex2f(19.2330120685707, 0);
        glVertex2f(24.3360794277533, 5.5535206939769);
        glEnd();

        ///Catkin1
        glLineWidth(1);
        glBegin(GL_LINES);
        glColor4ub(50,129,35,255);
        glVertex2f(13.1313735814001, 0);
        glVertex2f(14.4914810062797, 4.7715001277844);
        glEnd();

        glBegin(GL_POLYGON);
        glColor4ub(255,255,255,255);
        glVertex2f(14.4914810062797, 4.7715001277844);
        glVertex2f(15.612650640302, 5.2493757094988);
        glVertex2f(16.3846035030714, 7.5100948076093);
        glVertex2f(13.8114272938399, 5.3045151996966);
        glEnd();

        ///Catkin2
        glLineWidth(1);
        glBegin(GL_LINES);
        glColor4ub(50,129,35,255);
        glVertex2f(16.8821608132169, 0);
        glVertex2f(18.1707344607221, 4.1240993969183);
        glEnd();

        glBegin(GL_POLYGON);
        glColor4ub(255,255,255,255);
        glVertex2f(18.1707344607221, 4.1240993969183);
        glVertex2f(19.2013795060992, 4.6647656502308);
        glVertex2f(19.8434206819079, 6.9457014063933);
        glVertex2f(17.4442141828333, 4.6647656502308);
        glEnd();

        ///Catkin2
        glLineWidth(1);
        glBegin(GL_LINES);
        glColor4ub(50,129,35,255);
        glVertex2f(19.7669990931676, 3.1405884671103);
        glVertex2f(20.2996078331404, 4.833723854391);
        glEnd();

        glBegin(GL_POLYGON);
        glColor4ub(255,255,255,255);
        glVertex2f(20.2996078331404, 4.833723854391);
        glVertex2f(21.3197913534084, 5.2858837758213);
        glVertex2f(21.372098978954, 7.5560347244988);
        glVertex2f(19.5561917348356, 5.3237026464555);
        glEnd();


        ///phase2
        ///Grass1
        glBegin(GL_POLYGON);
        glColor4ub(50,129,35,255);
        glVertex2f(28.0148063974647, 0);
        glVertex2f(29.3767716599134, 0);
        glVertex2f(24.9971186590978, 5.2340922253486);
        glEnd();

        ///Grass2
        glBegin(GL_POLYGON);
        glColor4ub(50,129,35,255);
        glVertex2f(30.7120317211377, 0);
        glVertex2f(32.3677541970558, 0);
        glVertex2f(27.1602399582811, 5.6880806461648);
        glEnd();

        ///Grass3
        glBegin(GL_POLYGON);
        glColor4ub(50,129,35,255);
        glVertex2f(34.6644015023616, 0);
        glVertex2f(36.3735343807287, 0);
        glVertex2f(34.5941946794785, 5.9994145869291);
        glEnd();

///Grass4
        glBegin(GL_POLYGON);
        glColor4ub(50,129,35,255);
        glVertex2f(37.3776247024785, 0);
        glVertex2f(38.9372336982794, 0);
        glVertex2f(40.6997769790954, 4.9937454143282);
        glEnd();

///Grass5
        glBegin(GL_POLYGON);
        glColor4ub(50,129,35,255);
        glVertex2f(39.0876930500414, 0);
        glVertex2f(40.3634859998787, 0);
        glVertex2f(35.4687409768925, 5.4585972274816);
        glEnd();

        ///Catkin1
        glLineWidth(1);
        glBegin(GL_LINES);
        glColor4ub(50,129,35,255);
        glVertex2f(24.7464040170119, 0);
        glVertex2f(25.7500245036646, 5.4283688158694);
        glEnd();

        glBegin(GL_POLYGON);
        glColor4ub(255,255,255,255);
        glVertex2f(25.7500245036646, 5.4283688158694);
        glVertex2f(26.5565685958438, 5.9257376727133);
        glVertex2f(26.5565685958438, 8.1571763277425);
        glVertex2f(25, 6);
        glEnd();

        ///Catkin2
        glLineWidth(1);
        glBegin(GL_LINES);
        glColor4ub(50,129,35,255);
        glVertex2f(23.4744664270763, 0);
        glVertex2f(25.9516605267094, 4.5277279129359);
        glEnd();

        glBegin(GL_POLYGON);
        glColor4ub(255,255,255,255);
        glVertex2f(25.9516605267094, 4.5277279129359);
        glVertex2f(26.8884826928471, 4.9863239493329);
        glVertex2f(27.5109791049226, 7.1893234171274);
        glVertex2f(25.4811764729382, 4.9847695651708);
        glEnd();

///Catkin3
        glLineWidth(1);
        glBegin(GL_LINES);
        glColor4ub(50,129,35,255);
        glVertex2f(27.1930957674825, 0);
        glVertex2f(28.4922744170741, 4.7159215344444);
        glEnd();

        glBegin(GL_POLYGON);
        glColor4ub(255,255,255,255);
        glVertex2f(28.4922744170741, 4.7159215344444);
        glVertex2f(29.2988185092533, 5.2536175958972);
        glVertex2f(29.2181641000354, 6.9070329848647);
        glVertex2f(27.7663847341127, 5.1864055882156);
        glEnd();

        ///Catkin4
        glLineWidth(1);
        glBegin(GL_LINES);
        glColor4ub(50,129,35,255);
        glVertex2f(31.8513579646326, 0);
        glVertex2f(30.3876530336953, 5.1864055882156);
        glEnd();

        glBegin(GL_POLYGON);
        glColor4ub(255,255,255,255);
        glVertex2f(30.3876530336953, 5.1864055882156);
        glVertex2f(31.0732155120477, 5.6703320435232);
        glVertex2f(28.9762008723816, 7.8748858954798);
        glVertex2f(29.6348785476614, 5.6703320435232);
        glEnd();

        ///Catkin5
        glLineWidth(1);
        glBegin(GL_LINES);
        glColor4ub(50,129,35,255);
        glVertex2f(33.8503384007099, 0);
        glVertex2f(32.8744973179147, 5.0385391713161);
        glEnd();

        glBegin(GL_POLYGON);
        glColor4ub(255,255,255,255);
        glVertex2f(32.8744973179147, 5.0385391713161);
        glVertex2f(33.5735021978034, 5.5090232250873);
        glVertex2f(32.1082804303444, 7.3237474324906);
        glVertex2f(32.1217228318808, 5.5090232250873);
        glEnd();

        ///Catkin5
        glLineWidth(1);
        glBegin(GL_LINES);
        glColor4ub(50,129,35,255);
        glVertex2f(33.1731108372654, 0);
        glVertex2f(34.2874865470734, 5.2447585485502);
        glEnd();

        glBegin(GL_POLYGON);
        glColor4ub(255,255,255,255);
        glVertex2f(34.2874865470734, 5.2447585485502);
        glVertex2f(34.9903699760299, 5.7169441649802);
        glVertex2f(35, 8);
        glVertex2f(33.6422478616563, 5.7326219448412);
        glEnd();

        ///Catkin6
        glLineWidth(1);
        glBegin(GL_LINES);
        glColor4ub(50,129,35,255);
        glVertex2f(30.7120317211377, 0);
        glVertex2f(35.1466994345673, 5.3793846778984);
        glEnd();

        glBegin(GL_POLYGON);
        glColor4ub(255,255,255,255);
        glVertex2f(35.1466994345673, 5.3793846778984);
        glVertex2f(36.583838605132, 5.8314425390619);
        glVertex2f(38, 8);
        glVertex2f(35.3583777525857, 6.0476564990874);
        glEnd();

        ///Catkin7
        glLineWidth(1);
        glBegin(GL_LINES);
        glColor4ub(50,129,35,255);
        glVertex2f(35.5127849813881, 0);
        glVertex2f(36.8248057877892, 4.4802630355317);
        glEnd();

        glBegin(GL_POLYGON);
        glColor4ub(255,255,255,255);
        glVertex2f(36.8248057877892, 4.4802630355317);
        glVertex2f(37.4211788816078, 4.9335065868339);
        glVertex2f(37.4688887291133, 6.6749160207844);
        glVertex2f(36.1568679227122, 5.0289262818449);
        glEnd();

        glTranslatef(32.87f,0.0f,0.0f);
    }
    glPopMatrix();


    glPopMatrix();


}

///ID103
///Lake

void Lake()
{
    ///Lake Area
    glBegin(GL_POLYGON);
    glColor3f(0.08f,0.33f,0.14);
    glVertex2f(0.0f, 20.0f);
    glVertex2f(32.0f, 20.0f);
    glVertex2f(32.0f, 44.0f);
    glVertex2f(0.0f, 44.0f);
    glEnd();
///water of lake
    glBegin(GL_POLYGON);
    glColor4ub(62,154,174,255);
    glVertex2f(0.0f, 41.0f);
    glVertex2f(20.0f, 41.0f);
    glVertex2f(24.0f, 39.0f);
    glVertex2f(27.0f, 35.0f);

    glVertex2f(27.0f, 29.0f);
    glVertex2f(24.0f, 25.0f);
    glVertex2f(20.0f, 22.0f);
    glVertex2f(0.0f, 22.0f);
    glEnd();

    glLineWidth(8);
    glBegin(GL_LINES);
    glColor4ub(192,136,52,255);
    glVertex2f(0.0f, 41.0f);
    glVertex2f(20.0f, 41.0f);
    glVertex2f(20.0f, 41.0f);
    glVertex2f(24.0f, 39.0f);
    glVertex2f(24.0f, 39.0f);
    glVertex2f(27.0f, 35.0f);

    glVertex2f(27.0f, 35.0f);
    glVertex2f(27.0f, 29.0f);

    glVertex2f(27.0f, 29.0f);
    glVertex2f(24.0f, 25.0f);
    glVertex2f(24.0f, 25.0f);
    glVertex2f(20.0f, 22.0f);

    glVertex2f(20.0f, 22.0f);
    glVertex2f(0.0f, 22.0f);


    glEnd();



    //line for outside lake
    glLineWidth(6);
    glBegin(GL_LINES);
    glColor4ub(151,149,160,255);

    glVertex2f(32.0f, 20.0f);
    glVertex2f(32.0f, 44.0f);
    glVertex2f(32.0f, 44.0f);
    glVertex2f(0.0f, 44.0f);
    glEnd();

}


///ID104
///Runways1
void Runways1()
{
    //Full Runway
    glBegin(GL_POLYGON);
    glColor4ub(49,40,45,255);
    glVertex2f(0.0f, 8.0f);
    glVertex2f(160.0f, 8.0f);
    glVertex2f(160.0f, 20.0f);
    glVertex2f(0.0f, 20.0f);
    glEnd();
    //Runways line
    glLineWidth(7.5);
    glBegin(GL_LINES);
    glColor4ub(237,169,16,255);
    glVertex2f(15.0f, 8.0f);
    glVertex2f(15.0f, 20.0f);
    glEnd();

    glLineWidth(7.5);
    glBegin(GL_LINES);
    glColor4ub(237,169,16,255);
    glVertex2f(145.0f, 8.0f);
    glVertex2f(145.0f, 20.0f);
    glEnd();
//Runways Row line
    glLineWidth(4);
    glBegin(GL_LINES);
    glColor3f(1.0f,1.0f,1.0f);
    glVertex2f(25.0f, 9.0f);
    glVertex2f(25.0f, 19.0f);
    glEnd();

    glLineWidth(4);
    glBegin(GL_LINES);
    glColor3f(1.0f,1.0f,1.0f);
    glVertex2f(135.0f, 9.0f);
    glVertex2f(135.0f, 19.0f);
    glEnd();

    glLineWidth(4);
    glBegin(GL_LINES);
    glColor3f(1.0f,1.0f,1.0f);
    glVertex2f(25.0f, 9.0f);
    glVertex2f(135.0f, 9.0f);
    glEnd();

    glLineWidth(4);
    glBegin(GL_LINES);
    glColor3f(1.0f,1.0f,1.0f);
    glVertex2f(25.0f, 19.0f);
    glVertex2f(135.0f, 19.0f);
    glEnd();

    glLineWidth(4);
    glBegin(GL_LINES);
    glColor3f(1.0f,1.0f,1.0f);
    glVertex2f(35.0f, 19.0f);
    glVertex2f(35.0f, 9.0f);
    glEnd();



    glLineWidth(4);
    glBegin(GL_LINES);
    glColor3f(1.0f,1.0f,1.0f);
    glVertex2f(125.0f, 19.0f);
    glVertex2f(125.0f, 9.0f);
    glEnd();

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    for(int i=0; i<14; i++)
    {

        glLineWidth(4);
        glBegin(GL_LINES);
        glColor3f(1.0f,1.0f,1.0f);
        glVertex2f(38.0f, 14.0f);
        glVertex2f(43.0f, 14.0f);
        glEnd();
        glTranslatef(6.0f, 0.0f, 0.0f);

    }

    glPopMatrix();



    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    for(int i=0; i<5; i++)
    {

        glLineWidth(6);
        glBegin(GL_LINES);
        glColor4ub(237,169,16,255);
        glVertex2f(8.0f, 8.0f);
        glVertex2f(15.0f, 14.0f);
        glEnd();

        glLineWidth(6);
        glBegin(GL_LINES);
        glColor4ub(237,169,16,255);
        glVertex2f(15.0f, 14.0f);
        glVertex2f(8.0f, 20.0f);
        glEnd();
        glTranslatef(-3.0f, 0.0f, 0.0f);

    }

    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    for(int i=0; i<5; i++)
    {

        glLineWidth(6);
        glBegin(GL_LINES);
        glColor4ub(237,169,16,255);
        glVertex2f(152.0f, 8.0f);
        glVertex2f(145.0f, 14.0f);
        glEnd();

        glLineWidth(6);
        glBegin(GL_LINES);
        glColor4ub(237,169,16,255);
        glVertex2f(145.0f, 14.0f);
        glVertex2f(152.0f, 20.0f);
        glEnd();
        glTranslatef(3.0f, 0.0f, 0.0f);

    }

    glPopMatrix();


    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    for(int i=0; i<4; i++)
    {

        glLineWidth(5);
        glBegin(GL_LINES);
        glColor3f(1.0f,1.0f,1.0f);
        glVertex2f(16.0f,12.0f);
        glVertex2f(18.0f, 14.0f);
        glEnd();

        glLineWidth(5);
        glBegin(GL_LINES);
        glColor3f(1.0f,1.0f,1.0f);
        glVertex2f(18.0f, 14.0f);
        glVertex2f(16.0f, 16.0f);
        glEnd();
        glTranslatef(2.0f, 0.0f, 0.0f);

    }

    glPopMatrix();


    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    for(int i=0; i<5; i++)
    {

        glLineWidth(7);
        glBegin(GL_LINES);
        glColor3f(1.0f,1.0f,1.0f);
        glVertex2f(26.0f,18.0f);
        glVertex2f(34.0f, 18.0f);
        glEnd();


        glTranslatef(0.0f, -2.0f, 0.0f);

    }

    glPopMatrix();


    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    for(int i=0; i<5; i++)
    {

        glLineWidth(7);
        glBegin(GL_LINES);
        glColor3f(1.0f,1.0f,1.0f);
        glVertex2f(126.0f,18.0f);
        glVertex2f(134.0f, 18.0f);
        glEnd();


        glTranslatef(0.0f, -2.0f, 0.0f);

    }

    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    for(int i=0; i<2; i++)
    {

        glLineWidth(6);
        glBegin(GL_LINES);
        glColor3f(1.0f,1.0f,1.0f);
        glVertex2f(142.0f,9.0f);
        glVertex2f(137.0f, 11.0f);
        glEnd();
        glLineWidth(6);
        glBegin(GL_LINES);
        glColor3f(1.0f,1.0f,1.0f);
        glVertex2f(137.0f, 11.0f);
        glVertex2f(142.0f, 13.0f);
        glEnd();
        glTranslatef(0.0f, 5.0f, 0.0f);


    }

    glPopMatrix();




}

///ID105
///Runways2
void Runways2()
{
    ///Runway Area
    glBegin(GL_POLYGON);
    glColor3ub(49,40,45);
    glVertex2f(32.0f, 35.0f);
    glVertex2f(160.0f, 35.0f);
    glVertex2f(160.0f, 44.0f);
    glVertex2f(32.0f, 44.0f);
    glEnd();

    glLineWidth(4);
    glBegin(GL_LINES);
    glColor3f(1.0f,1.0f,1.0f);
    glVertex2f(33.0f, 36.0f);
    glVertex2f(33.0f, 43.0f);
    glEnd();

    glLineWidth(4);
    glBegin(GL_LINES);
    glColor3f(1.0f,1.0f,1.0f);
    glVertex2f(33.0f, 43.0f);
    glVertex2f(159.0f, 43.0f);
    glEnd();

    glLineWidth(4);
    glBegin(GL_LINES);
    glColor3f(1.0f,1.0f,1.0f);
    glVertex2f(159.0f, 43.0f);
    glVertex2f(159.0f, 36.0f);
    glEnd();

    glLineWidth(4);
    glBegin(GL_LINES);
    glColor3f(1.0f,1.0f,1.0f);
    glVertex2f(159.0f, 36.0f);
    glVertex2f(33.0f, 36.0f);
    glEnd();


    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    for(int i=0; i<20; i++)
    {

        glLineWidth(4);
        glBegin(GL_LINES);
        glColor3f(1.0f,1.0f,1.0f);
        glVertex2f(34.0f, 39.50f);
        glVertex2f(39.0f, 39.50f);
        glEnd();
        glTranslatef(7.0f, 0.0f, 0.0f);

    }

    glPopMatrix();


}

///ID106
///Taxiways1
void Taxiways1()
{
    glBegin(GL_POLYGON);
    glColor3ub(49,40,45);
    glVertex2f(32.0f, 20.0f);
    glVertex2f(44.0f, 20.0f);
    glVertex2f(40.0f, 23.0f);
    glVertex2f(40.0f, 32.0f);
    glVertex2f(44.0f, 35.0f);
    glVertex2f(32.0f, 35.0f);
    glVertex2f(32.0f, 20.0f);
    glEnd();

    glLineWidth(4);
    glBegin(GL_LINES);
    glColor3f(1.0f,1.0f,1.0f);
    glVertex2f(36.0f, 25.0f);
    glVertex2f(36.0f, 30.0f);
    glEnd();

    glLineWidth(4);
    glBegin(GL_LINES);
    glColor3f(1.0f,1.0f,1.0f);
    glVertex2f(38.0f, 34.0f);
    glVertex2f(36.0f, 32.0f);
    glEnd();

    glLineWidth(4);
    glBegin(GL_LINES);
    glColor3f(1.0f,1.0f,1.0f);
    glVertex2f(38.0f, 21.0f);
    glVertex2f(36.0f, 23.0f);
    glEnd();



}


///ID107
///Taxiways2
void Taxiways2()
{
    glBegin(GL_POLYGON);
    glColor3ub(49,40,45);
    glVertex2f(160.0f, 20.0f);
    glVertex2f(149.0f, 20.0f);
    glVertex2f(152.0f, 23.0f);
    glVertex2f(152.0f, 32.0f);
    glVertex2f(149.0f, 35.0f);
    glVertex2f(160.0f, 35.0f);

    glEnd();

    glLineWidth(4);
    glBegin(GL_LINES);
    glColor3f(1.0f,1.0f,1.0f);
    glVertex2f(156.0f, 25.0f);
    glVertex2f(156.0f, 30.0f);
    glEnd();

    glLineWidth(4);
    glBegin(GL_LINES);
    glColor3f(1.0f,1.0f,1.0f);
    glVertex2f(153.0f, 21.0f);
    glVertex2f(155.0f, 23.0f);
    glEnd();

    glLineWidth(4);
    glBegin(GL_LINES);
    glColor3f(1.0f,1.0f,1.0f);
    glVertex2f(155.0f, 32.0f);
    glVertex2f(153.0f, 34.0f);
    glEnd();


}


///ID108
///Taxiways3
void Taxiways3()
{
    glBegin(GL_POLYGON);
    glColor3ub(49,40,45);
    glVertex2f(90.0f, 20.0f);
    glVertex2f(95.0f, 20.0f);
    glVertex2f(95.0f, 23.0f);
    glVertex2f(92.0f, 23.0f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(49,40,45);
    glVertex2f(92.0f, 32.0f);
    glVertex2f(95.0f, 32.0f);
    glVertex2f(95.0f, 23.0f);
    glVertex2f(92.0f, 23.0f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(49,40,45);
    glVertex2f(90.0f, 35.0f);
    glVertex2f(95.0f, 35.0f);
    glVertex2f(95.0f, 32.0f);
    glVertex2f(92.0f, 32.0f);
    glEnd();




    glBegin(GL_POLYGON);
    glColor3ub(49,40,45);
    glVertex2f(100.0f, 20.0f);
    glVertex2f(98.0f, 23.0f);
    glVertex2f(95.0f, 23.0f);
    glVertex2f(95.0f, 20.0f);
    glEnd();


    glBegin(GL_POLYGON);
    glColor3ub(49,40,45);
    glVertex2f(95.0f, 23.0f);
    glVertex2f(95.0f, 32.0f);
    glVertex2f(98.0f, 32.0f);
    glVertex2f(98.0f, 23.0f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(49,40,45);
    glVertex2f(100.0f, 35.0f);
    glVertex2f(95.0f, 35.0f);
    glVertex2f(95.0f, 32.0f);
    glVertex2f(98.0f, 32.0f);
    glEnd();


    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    for(int i=0; i<4; i++)
    {

        glLineWidth(4);
        glBegin(GL_LINES);
        glColor3f(1.0f,1.0f,1.0f);
        glVertex2f(95.0f, 34.0f);
        glVertex2f(95.0f, 32.0f);
        glEnd();
        glTranslatef(0.0f, -4.0f, 0.0f);

    }

    glPopMatrix();
}


// Aviation1, Aviation2, Parking, Terminal1, Terminal2, Tower, flower


///ID109
///Aviation1
void Aviation1()
{

    //aviation parking background
    glBegin(GL_POLYGON);
    glColor4ub(120,115,107,255);
    glVertex2f(0.0f, 65.0f);
    glVertex2f(30.0f, 65.0f);
    glVertex2f(30.0f, 44.0f);
    glVertex2f(0.0f, 44.0f);
    glEnd();


    glBegin(GL_POLYGON);
    glColor4ub(55,86,115,255);
    glVertex2f(1.0f, 65.0f);
    glVertex2f(1.0f, 75.0f);
    glVertex2f(7.5f, 77.0f);
    glVertex2f(14.0f, 75.0f);
    glVertex2f(14.0f, 65.0f);

    glEnd();

    glLineWidth(4);
    glBegin(GL_LINES);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(0.0f, 75.0f);
    glVertex2f(7.5f, 77.0f);
    glVertex2f(7.5f, 77.0f);
    glVertex2f(15.0f, 75.0f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor4ub(58,138,205,255);
    glVertex2f(3.0f, 72.0f);
    glVertex2f(3.0f, 74.0f);
    glVertex2f(12.0f, 74.0f);
    glVertex2f(12.0f, 72.0f);

    glEnd();

    glBegin(GL_POLYGON);
    glColor4ub(203,211,215,255);
    glVertex2f(0.0f, 65.0f);
    glVertex2f(15.0f, 65.0f);
    glVertex2f(15.0f, 65.7f);
    glVertex2f(0.0f, 65.70f);

    glEnd();

    //Door
    glBegin(GL_POLYGON);
    glColor4ub(122,114,114,255);
    glVertex2f(2.0f, 65.7f);
    glVertex2f(2.0f, 71.0f);
    glVertex2f(13.0f, 71.0f);
    glVertex2f(13.0f, 65.7f);

    glEnd();
    //Door Line
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    for(int i=0; i<4; i++)
    {
        glLineWidth(2);
        glBegin(GL_LINES);
        glColor3f(0.0f,0.0f,0.0f);
        glVertex2f(2.0f, 65.7f);
        glVertex2f(2.0f, 71.0f);
        glEnd();
        glTranslatef(3.725f, 0.0f, 0.0f);
    }
    glPopMatrix();

    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(2.0f, 71.0f);
    glVertex2f(13.0f, 71.0f);
    glEnd();


    glColor3f(1.0f, 1.0f, 0.0f);
    airportRenderTextAviation(5.0f, 72.5f, "Aviation 1");


}

///ID110
///Aviation2
void Aviation2()
{


    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(15.0f, 0.0f, 0.0f);

    // second translate start here
    glBegin(GL_POLYGON);
    glColor4ub(55,86,115,255);
    glVertex2f(1.0f, 65.0f);
    glVertex2f(1.0f, 75.0f);
    glVertex2f(7.5f, 77.0f);
    glVertex2f(14.0f, 75.0f);
    glVertex2f(14.0f, 65.0f);

    glEnd();

    glLineWidth(4);
    glBegin(GL_LINES);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(0.0f, 75.0f);
    glVertex2f(7.5f, 77.0f);
    glVertex2f(7.5f, 77.0f);
    glVertex2f(15.0f, 75.0f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor4ub(58,138,205,255);
    glVertex2f(3.0f, 72.0f);
    glVertex2f(3.0f, 74.0f);
    glVertex2f(12.0f, 74.0f);
    glVertex2f(12.0f, 72.0f);

    glEnd();

    glBegin(GL_POLYGON);
    glColor4ub(203,211,215,255);
    glVertex2f(0.0f, 65.0f);
    glVertex2f(15.0f, 65.0f);
    glVertex2f(15.0f, 65.7f);
    glVertex2f(0.0f, 65.70f);

    glEnd();

    //Door
    glBegin(GL_POLYGON);
    glColor4ub(122,114,114,255);
    glVertex2f(2.0f, 65.7f);
    glVertex2f(2.0f, 71.0f);
    glVertex2f(13.0f, 71.0f);
    glVertex2f(13.0f, 65.7f);

    glEnd();
    //Door Line
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    for(int i=0; i<4; i++)
    {
        glLineWidth(2);
        glBegin(GL_LINES);
        glColor3f(0.0f,0.0f,0.0f);
        glVertex2f(2.0f, 65.7f);
        glVertex2f(2.0f, 71.0f);
        glEnd();
        glTranslatef(3.725f, 0.0f, 0.0f);
    }
    glPopMatrix();


    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(2.0f, 71.0f);
    glVertex2f(13.0f, 71.0f);
    glEnd();

    glPopMatrix();


    glColor3f(1.0f, 1.0f, 0.0f);
    airportRenderTextAviation(20.0f, 72.5f, "Aviation 2");
}


///ID111
///Parking
void Parking()
{
    glBegin(GL_POLYGON);
    glColor4ub(151,149,160,255);
    glVertex2f(30.0f, 44.0f);
    glVertex2f(160.0f, 44.0f);
    glVertex2f(160.0f, 62.0f);
    glVertex2f(30.0f, 62.0f);
    glEnd();

}

///ID112
///Terminal1
void Terminal1()
{

    glBegin(GL_POLYGON);
    glColor4ub(255,218,212,255);
    glVertex2f(37.0f, 80.0f);
    glVertex2f(39.0f, 77.0f);
    glVertex2f(75.0f, 77.0f);
    glVertex2f(75.0f, 80.0f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor4ub(255,218,212,255);
    glVertex2f(75.0f, 63.0f);
    glVertex2f(72.0f, 63.0f);
    glVertex2f(72.0f, 80.0f);
    glVertex2f(75.0f, 80.0f);
    glEnd();


    glBegin(GL_POLYGON);
    glColor4ub(176,202,239,255);
    glVertex2f(72.0f, 63.0f);
    glVertex2f(72.0f, 77.0f);
    glVertex2f(39.0f, 77.0f);
    glVertex2f(39.0f, 63.0f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor4ub(255,218,212,255);
    glVertex2f(30.0f, 72.0f);
    glVertex2f(50.0f, 72.0f);
    glVertex2f(50.0f, 69.0f);
    glVertex2f(32.0f, 69.0f);
    glEnd();


    glBegin(GL_POLYGON);
    glColor4ub(255,218,212,255);
    glVertex2f(47.0f, 63.0f);
    glVertex2f(50.0f, 63.0f);
    glVertex2f(50.0f, 69.0f);
    glVertex2f(47.0f, 69.0f);
    glEnd();


    glBegin(GL_POLYGON);
    glColor4ub(176,202,239,255);
    glVertex2f(32.0f, 69.0f);
    glVertex2f(47.0f, 69.0f);
    glVertex2f(47.0f, 63.0f);
    glVertex2f(32.0f, 63.0f);
    glEnd();

    glLineWidth(2);
    glBegin(GL_LINES);
    glColor4ub(184,179,188,255);
    glVertex2f(50.0f, 67.66f);
    glVertex2f(72.0f, 67.66f);
    glEnd();

    glLineWidth(2);
    glBegin(GL_LINES);
    glColor4ub(184,179,188,255);
    glVertex2f(39.0f, 72.32f);
    glVertex2f(72.0f, 72.32f);
    glEnd();


    glLineWidth(2);
    glBegin(GL_LINES);
    glColor4ub(184,179,188,255);
    glVertex2f(55.5f, 63.0f);
    glVertex2f(55.5f, 77.0f);
    glVertex2f(61.0f, 63.0f);
    glVertex2f(61.0f, 77.0f);
    glVertex2f(66.5f, 63.0f);
    glVertex2f(66.5f, 77.0f);
    glVertex2f(44.5f, 72.0f);
    glVertex2f(44.5f, 77.0f);
    glVertex2f(50.0f, 63.0f);
    glVertex2f(50.0f, 77.0f);

    glVertex2f(37.5f, 63.0f);
    glVertex2f(37.5f, 69.0f);
    glVertex2f(42.0f, 63.0f);
    glVertex2f(42.0f, 69.0f);

    glVertex2f(32.0f, 65.0f);
    glVertex2f(47.0f, 65.0f);

    glVertex2f(32.0f, 67.0f);
    glVertex2f(47.0f, 67.0f);
    glEnd();


    glLineWidth(2);
    glBegin(GL_LINES);
    glColor4ub(110,110,110,255);
    glVertex2f(66.0f, 63.0f);
    glVertex2f(66.0f, 64.0f);
    glVertex2f(66.0f, 64.0f);
    glVertex2f(62.0f, 64.0f);
    glVertex2f(62.0f, 64.0f);
    glVertex2f(62.0f, 63.0f);


    glVertex2f(60.0f, 63.0f);
    glVertex2f(60.0f, 64.0f);
    glVertex2f(60.0f, 64.0f);
    glVertex2f(56.0f, 64.0f);
    glVertex2f(56.0f, 64.0f);
    glVertex2f(56.0f, 63.0f);

    glEnd();

    glLineWidth(3);
    glBegin(GL_LINES);
    glColor4ub(110,110,110,255);
    glVertex2f(37.0f, 63.0f);
    glVertex2f(37.0f, 66.0f);
    glVertex2f(37.0f, 66.0f);
    glVertex2f(42.0f, 66.0f);
    glVertex2f(42.0f, 66.0f);
    glVertex2f(42.0f, 63.0f);
    glVertex2f(38.5f, 63.0f);
    glVertex2f(38.5f, 66.0f);
    glVertex2f(40.0f, 63.0f);
    glVertex2f(40.0f, 66.0f);

    glEnd();

    //text
    glColor3f(1.0f, 0.0f, 0.0f);
    airportRenderTextTerminal(50.0f, 80.5f, "TERMINAL 1");


}

///ID113
///Terminal2

void Terminal2()
{
    //whole Background
    glBegin(GL_POLYGON);
    glColor3ub(4,91,164);
    glVertex2f(81.0f, 63.0f);
    glVertex2f(139.0f, 63.0f);
    glVertex2f(139.0f, 75.0f);
    glVertex2f(81.0f, 75.0f);
    glEnd();
    //left side line
    glLineWidth(1);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    for(int i=0; i<13; i++)
    {
        glBegin(GL_LINES);
        glColor4ub(0,0,0,255);
        glVertex2f(83.0f, 63.0f);
        glVertex2f(83.0f, 75.0f);
        glEnd();
        glTranslatef(4.5f, 0.0f, 0.0f);
    }
    glPopMatrix();
    //left
    glBegin(GL_POLYGON);
    glColor4ub(203,211,215,255);
    glVertex2f(76.0f, 63.0f);
    glVertex2f(102.0f, 63.0f);
    glVertex2f(102.0f, 65.0f);
    glVertex2f(76.0f, 65.0f);
    glEnd();
    //right
    glBegin(GL_POLYGON);
    glVertex2f(118.0f, 63.0f);
    glVertex2f(144.0f, 63.0f);
    glVertex2f(144.0f, 65.0f);
    glVertex2f(118.0f, 65.0f);
    glEnd();

    glLineWidth(8);
    glBegin(GL_LINES);
    glVertex2f(79.0f, 75.0f);
    glVertex2f(98.0f, 75.0f);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(122.0f, 75.0f);
    glVertex2f(141.0f, 75.0f);
    glEnd();
    // curve line
    glLineWidth(10);
    glBegin(GL_LINES);
    glVertex2f(101.5f, 65.0f);
    glVertex2f(97.5f, 75.0f);
    glVertex2f(118.5f, 65.0f);
    glVertex2f(122.5f, 75.0f);
    glEnd();

    // upper curve semi circle
    float centerX = 110.0f, centerY = 70.0f, radius = 13.5;
    glBegin(GL_POLYGON);
    glColor4ub(203,211,215,255);
    for (int i = 18; i <= 162; i++)
    {
        float theta = i * M_PI / 180.0f;
        float x = centerX + radius * cos(theta);
        float y = centerY + radius * sin(theta);
        glVertex2f(x, y);
    }
    glEnd();



    // text
    glColor3f(1.0f, 0.0f, 0.0f);
    airportRenderTextTerminal(104.0f, 78.0f, "TERMINAL 2");


}

///ID114
///TerminalLamp1

void Terminal_Lamp1()
{

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    for(int i=0; i<4; i++)
    {
///Stand lower
        glLineWidth(3.5);
        glBegin(GL_LINES);
        glColor4ub(110,110,110,255);
        glVertex2f(69.25f, 63.0f);
        glVertex2f(69.25f, 64.5f);

        glEnd();
///Stand Upper
        glLineWidth(2);
        glBegin(GL_LINES);
        glColor4ub(110,110,110,255);
        glVertex2f(69.25f, 64.5f);
        glVertex2f(69.25f, 68.5f);

        glEnd();

        if (airportWeather == RAINY_AIRPORT)
        {
            glColor4ub(255, 255, 255, 255); // Light white for rainy weather
        }
        else
        {
            glColor4ub(255, 255, 0, 255);
        }

        //lamp
        glBegin(GL_POLYGON);
        glVertex2f(68.5f, 68.5f);
        glVertex2f(70.0f, 68.5f);
        glVertex2f(70.0f, 69.0f);
        glVertex2f(68.5f, 69.0f);
        glEnd();

        glTranslatef(-8.0f, 0.0f, 0.0f);


    }

    glPopMatrix();
}


///ID115
///TerminalLamp2
void Terminal_Lamp2()
{

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    for(int i=0; i<13; i++)
    {
///Stand lower
        glLineWidth(3.5);
        glBegin(GL_LINES);
        glColor4ub(110,110,110,255);
        glVertex2f(69.25f, 63.0f);
        glVertex2f(69.25f, 64.5f);

        glEnd();
///Stand Upper
        glLineWidth(2);
        glBegin(GL_LINES);
        glColor4ub(110,110,110,255);
        glVertex2f(69.25f, 64.5f);
        glVertex2f(69.25f, 68.5f);

        glEnd();

        if (airportWeather == RAINY_AIRPORT)
        {
            glColor4ub(255, 255, 255, 255); // Light white for rainy weather
        }
        else
        {
            glColor4ub(255, 255, 0, 255);
        }

        //lamp
        glBegin(GL_POLYGON);
        glVertex2f(68.5f, 68.5f);
        glVertex2f(70.0f, 68.5f);
        glVertex2f(70.0f, 69.0f);
        glVertex2f(68.5f, 69.0f);
        glEnd();

        glTranslatef(8.0f, 0.0f, 0.0f);
    }

    glPopMatrix();
}


///ID116
///Tower
void Tower()
{
    // lamp in the tower
    glBegin(GL_POLYGON);
    glColor4ub(255,0,0,255);
    glVertex2f(147.5f, 86.0f);
    glVertex2f(148.5f, 86.0f);
    glVertex2f(148.5f, 87.0f);
    glVertex2f(147.5f, 87.0f);
    glEnd();

    glLineWidth(6);
    glBegin(GL_LINES);
    glColor4ub(110,110,110,255);
    glVertex2f(148.0f, 82.0f);
    glVertex2f(148.0f, 84.0f);
    glEnd();

    glLineWidth(3);
    glBegin(GL_LINES);
    glColor4ub(110,110,110,255);
    glVertex2f(148.0f, 84.0f);
    glVertex2f(148.0f, 86.0f);

    glEnd();

    //
    glBegin(GL_POLYGON);
    glColor3ub(78,106,117);
    glVertex2f(150.0f, 82.0f);
    glVertex2f(152.0f, 82.0f);
    glVertex2f(152.0f, 84.0f);
    glVertex2f(150.0f, 84.0f);
    glEnd();
    // stand
    glBegin(GL_POLYGON);
    glColor3ub(78,106,117);
    glVertex2f(150.0f, 63.0f);
    glVertex2f(155.0f, 63.0f);
    glVertex2f(154.0f, 64.0f);
    glVertex2f(154.0f, 80.0f);
    glVertex2f(150.0f, 80.0f);
    glVertex2f(150.0f, 64.0f);
    glVertex2f(149.0f, 63.0f);
    glEnd();
    // lower rect
    glBegin(GL_POLYGON);
    glColor3ub(170,196,207);
    glVertex2f(148.0f, 75.0f);
    glVertex2f(156.0f, 75.0f);
    glVertex2f(156.0f, 77.0f);
    glVertex2f(148.0f, 77.0f);
    glEnd();
    // upper rect
    glBegin(GL_POLYGON);
    glColor3ub(170,196,207);
    glVertex2f(149.0f, 78.5f);
    glVertex2f(155.0f, 78.5f);
    glVertex2f(158.0f, 82.0f);
    glVertex2f(146.0f, 82.0f);
    glEnd();
    //upper line
    glLineWidth(4);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(146.0f, 82.0f);
    glVertex2f(158.0f, 82.0f);
    glEnd();
    glLineWidth(6);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(153.0f, 82.0f);
    glVertex2f(155.0f, 86.0f);
    glEnd();
    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(154.0f, 84.5f);
    glVertex2f(157.0f, 87.0f);
    glEnd();

    //semi circle antena
    float centerX = 156.0f, centerY = 86.0f, radius = 2.7;
    glBegin(GL_POLYGON);
    glColor4ub(203,211,215,255);
    for (int i = 135; i <= 300 ; i++)
    {
        float theta = i * M_PI / 180.0f;
        float x = centerX + radius * cos(theta);
        float y = centerY + radius * sin(theta);
        glVertex2f(x, y);
    }
    glEnd();



}

///ID117
///Plane in the runway 1
void Plane_1()
{

    glPushMatrix();
    glTranslatef(airport_plane_x_1, airport_plane_y_1, 0.0f);
    ///Body
    glBegin(GL_POLYGON);
    glColor3f(1.0f,1.0f,0.0f);

    glVertex2f(62.0348400722083, 13.5697074741735);
    glVertex2f(63.648263279815, 13.4269259298819);
    glVertex2f(65.496857646712, 13.3734797574);
    glVertex2f(67.290939628641, 13.4575773503029);
    glVertex2f(70.1502577873405, 13.7799514564308);
    glVertex2f(76.7727952222888, 14.7817179029556);
    glVertex2f(81.3221778287197, 15.3853336839869);
    glVertex2f(82.690518228275, 15.6313274636822);
    glVertex2f(83.428499567361, 15.7850735759918);
    glVertex2f(84, 16);
    glVertex2f(84.566220798452, 16.6153025824636);
    glVertex2f(84.5200969647591, 17.0304170856995);
    glVertex2f(84.1010885599861, 17.4858128560801);
    glVertex2f(83.4000074105309, 17.7672806533398);
    glVertex2f(82.4468875316829, 17.9421441742327);
    glVertex2f(81.3060592363014, 17.8280613446946);
    glVertex2f(74.6506227440897, 16.9510646806473);
    glVertex2f(65.4304645607189, 15.6662885403416);
    glVertex2f(63.3899377496449, 15.1977231244653);
    glVertex2f(61.8935514215241, 14.8651928293274);
    glVertex2f(61.5088826196783, 14.5677148277859);
    glVertex2f(61.531000535547, 14.030728907963);

    glEnd();

    ///engine1
    glBegin(GL_POLYGON);
    glColor3f(1.0f,0.0f,0.0f);

    glVertex2f(73.29274673961, 13.5227770298599);
    glVertex2f(76.4123615905668, 13.6243485959955);
    glVertex2f(76.5237545800719, 14.1598777192561);
    glVertex2f(76.5035013330612, 14.6527067298481);
    glVertex2f(76.3410417742373, 15.1363287021806);
    glVertex2f(75.3140364190927, 15.0364809593194);
    glEnd();

    ///engine2
    glBegin(GL_POLYGON);
    glColor3f(1.0f,1.0f,1.0f);

    glVertex2f(75.7646151959418, 13.6215552566992);
    glVertex2f(76.4123615905668, 13.6243485959955);
    glVertex2f(76.5237545800719, 14.1598777192561);
    glVertex2f(76.5035013330612, 14.6527067298481);
    glVertex2f(76.3410417742373, 15.1363287021806);
    glVertex2f(75.6997854738863, 15.0721202876924);
    glVertex2f(75.7484077654279, 14.4805490739354);
    glVertex2f(75.7727189111988, 14.0186373042895);
    glEnd();

    ///Wing1
    glBegin(GL_POLYGON);
    glColor4ub(255,0,0,255);

    glVertex2f(67.9171198628514, 11.43910826639);
    glVertex2f(69.967980315507, 11.5456475539978);
    glVertex2f(70.50371184065, 11.7699072621972);
    glVertex2f(76.1737934162823, 15.6602650090589);
    glVertex2f(71.6326432319957, 14.9916700842561);
    glVertex2f(67.9171198628514, 11.43910826639);
    glEnd();

    ///Wing2
    glBegin(GL_POLYGON);
    glColor4ub(255,0,0,255);

    glVertex2f(72.0094984854808, 16.5500716182045);
    glVertex2f(74.6506227440897, 16.9510646806473);
    glVertex2f(71.1964714398317, 18.1612821870234);
    glVertex2f(70.8014007435091, 18.1838576553847);
    glVertex2f(69.3678585025669, 17.9693907059524);
    glEnd();

    ///tail Wing1
    glBegin(GL_POLYGON);
    glColor3f(1.0f,0.0f,0.0f);

    glVertex2f(61.8631690799238, 14.9094894921613);
    glVertex2f(65.3965716199788, 15.6123188802376);
    glVertex2f(61.86826488695, 18.4472699413502);
    glVertex2f(60.1769106775854, 18.384879582497);
    glEnd();

    ///tail Wing2
    glBegin(GL_POLYGON);
    glColor4ub(255,0,0,255);

    glVertex2f(60.7076406431436, 13.4494339452451);
    glVertex2f(62.0348400722083, 13.5697074741735);
    glVertex2f(62.6739128752754, 13.7795127637117);
    glVertex2f(64.6812742923197, 14.7448850482445);
    glVertex2f(62.5894891235955, 14.6434343604283);
    glVertex2f(61.531000535547, 14.030728907963);
    glEnd();

    ///cocpit glass
    glBegin(GL_POLYGON);
    glColor4ub(0,101,143,255);

    glVertex2f(82.9718520891545, 17.228074888823);
    glVertex2f(83.3521123754167, 17.3151460752753);
    glVertex2f(83.1257139830502, 17.7069352007394);
    glVertex2f(82.9034238361872, 17.6974760455537);
    glEnd();

    ///cocpit glass
    glBegin(GL_POLYGON);
    glColor4ub(0,101,143,255);

    glVertex2f(83.4448135947306, 17.3293966141372);
    glVertex2f(84.1010885599861, 17.4858128560801);
    glVertex2f(83.4000074105309, 17.7672806533398);
    glVertex2f(83.2138953022288, 17.6969808348543);
    glEnd();

    glPushMatrix();
    for(int i=0; i<16; i++)
    {
        airportCircle(0.28,80.3974968821253, 16.9871509543515, 0.0f, 0.45f, 0.45f);
        glTranslatef(-0.87f,-0.12f,0.0f);
    }
    glPopMatrix();

    ///Tyre base
    glBegin(GL_POLYGON);
    glColor4ub(255,255,255,255);

    glVertex2f(82.0253473976836, 15.1962021813241);
    glVertex2f(82.3926527548586, 15.3203089478841);
    glVertex2f(82.3828656205478, 15.5212187475643);
    glVertex2f(81.8739369020709, 15.4362310169115);
    glEnd();

    ///Tyre base line
    glLineWidth(1.5);
    glBegin(GL_LINES);
    glColor4ub(255,255,255,255);

    glVertex2f(82.1875450949274, 15.2451260243895);
    glVertex2f(82.2, 14.6);
    glEnd();

    airportCircle(0.35,82.2800513458849, 14.6266837819616, 0.0f, 0.0f, 0.0f);
    airportCircle(0.1,82.2800513458849, 14.6266837819616, 1.0f, 1.0f, 1.0f);

    glPopMatrix();

}


///ID118
///Plane1 in the Parking
void Plane_2()
{
    glBegin(GL_POLYGON);
    //Body
    //glColor4ub(230,231,233,255);
    glColor4ub(39,82,97,255);
    glVertex2f(37.36f, 58.0f);
    glVertex2f(37.32f, 58.0f);
    glVertex2f(36.81f, 56.91f);
    glVertex2f(36.81f, 51.23f);
    glVertex2f(38.01f, 51.23f);
    glVertex2f(38.01f, 56.91f);

    glEnd();
    //Body
    glBegin(GL_POLYGON);

    //glColor4ub(230,231,233,255);
    glColor4ub(39,82,97,255);
    glVertex2f(36.84f, 51.23f);
    glVertex2f(38.00f, 51.23f);
    glVertex2f(37.81f, 50.38f);
    glVertex2f(37.11f, 50.38f);

    glEnd();

    //Body's Glass
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    for(int i=0; i<10; i++)
    {

        glLineWidth(2);
        glBegin(GL_LINES);
        glColor3ub(63,129,193);
        glVertex2f(37.70f, 56.0f);
        glVertex2f(38.00f, 56.0f);
        glVertex2f(37.0f, 56.0f);
        glVertex2f(37.30f, 56.0f);
        glEnd();
        glTranslatef(0.0f, -0.5f, 0.0f);

    }

    glPopMatrix();


    glLineWidth(1.5);
    glBegin(GL_LINES);
    glColor3ub(63,129,193);
    glVertex2f(37.00f, 56.85f);
    glVertex2f(37.75f, 56.85f);
    glEnd();


    //Wing
    glBegin(GL_POLYGON);
    //glColor4ub(230,231,233,255);
    glColor4ub(255,47,49,255);
    //glColor4ub(39,82,97,255);

    glVertex2f(37.11f, 50.36f);
    glVertex2f(35.84f, 49.32f);
    glVertex2f(35.81f, 48.99f);
    glVertex2f(37.4f, 49.54f);
    glVertex2f(39.0f, 49.0f);

    glVertex2f(39.10f, 49.33f);
    glVertex2f(37.81f, 50.38f);

    glEnd();


    //Wing LIne

    glLineWidth(2.0);
    glBegin(GL_LINES);
    glColor4ub(215,68,60,255);
    glVertex2f(37.11f, 50.36f);
    glVertex2f(35.84f, 49.32f);
    glVertex2f(39.10f, 49.33f);
    glVertex2f(37.81f, 50.38f);

    glVertex2f(37.43f, 48.5f);
    glVertex2f(37.43f, 51.00f);

    glEnd();
    //Left Engine

    glBegin(GL_POLYGON);
    glColor4ub(230,231,233,255);
    glVertex2f(34.52,52.63);
    glVertex2f(34.52,54.5);
    glVertex2f(35.11,54.5);
    glVertex2f(35.11,52.99);
    glEnd();

    glBegin(GL_POLYGON);
    glColor4ub(230,231,233,255);
    glVertex2f(35.62,53.36);
    glVertex2f(35.62,55.4);
    glVertex2f(36.15,55.4);
    glVertex2f(36.15,53.7);
    glEnd();
//Right Engine
    glBegin(GL_POLYGON);
    glColor4ub(230,231,233,255);
    glVertex2f(38.67,54.73);
    glVertex2f(38.67,55.5);
    glVertex2f(39.19,55.5);
    glVertex2f(39.19,54.001);

    glEnd();

    glBegin(GL_POLYGON);
    glColor4ub(230,231,233,255);
    glVertex2f(39.74,54.007);
    glVertex2f(39.74,55.00);
    glVertex2f(40.26,55.00);
    glVertex2f(40.26,54.07);
    glEnd();

    //Engine Line
    glLineWidth(2.0);
    glBegin(GL_LINES);
    glColor4ub(215,68,60,255);
    glVertex2f(38.67,55.5);
    glVertex2f(39.19,55.5);

    glVertex2f(39.74,55.00);
    glVertex2f(40.26,55.00);

    //Left Engine LINe
    glVertex2f(34.52,54.5);
    glVertex2f(35.11,54.5);

    glVertex2f(35.62,55.4);
    glVertex2f(36.15,55.4);

    glEnd();

    //Left and Right Engine White LINe

    glLineWidth(2.0);
    glBegin(GL_LINES);
    glColor4ub(230,231,233,255);
    glVertex2f(34.0,52.5);
    glVertex2f(34.0,51.5);
    glVertex2f(35.2,53.5);
    glVertex2f(35.2,52.0);
    glVertex2f(36.4,53.5);
    glVertex2f(36.4,52.5);


    glVertex2f(38.5,53.15);
    glVertex2f(38.5,52.45);

    glVertex2f(39.7,54.15);
    glVertex2f(39.7,52.15);

    glVertex2f(40.9,53.15);
    glVertex2f(40.9,51.65);
    glEnd();

    //LeftWing

    glBegin(GL_POLYGON);
    glColor4ub(230,231,233,255);
    glVertex2f(36.81f, 55.20f);
    glVertex2f(36.81f, 53.28f);
    glVertex2f(32.95f, 51.58f);
    glVertex2f(33.06f, 52.0f);
    glEnd();

    //RightWing

    glBegin(GL_POLYGON);
    glColor4ub(230,231,233,255);
    glVertex2f(38.01f, 55.20f);
    glVertex2f(38.01f, 53.28f);
    glVertex2f(42.0f, 52.0f);
    glVertex2f(41.77f, 52.58f);
    glEnd();

    //LeftWingLIne

    glLineWidth(2.5);
    glBegin(GL_LINES);
    glColor4ub(215,68,60,255);
    glVertex2f(36.81f, 55.20f);
    glVertex2f(33.06f, 52.0f);
    glVertex2f(33.06f, 52.0f);
    glVertex2f(32.95f, 51.58f);
    glEnd();


    //RightWingLIne

    glLineWidth(2.5);
    glBegin(GL_LINES);
    glColor4ub(215,68,60,255);
    glVertex2f(38.01f, 55.20f);
    glVertex2f(41.77f, 52.58f);
    glVertex2f(41.77f, 52.58f);
    glVertex2f(42.0f, 52.0f);
    glEnd();


}



///ID119
///Plane2 in the Parking
void Plane_3()
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glTranslatef(12.0f, 0.0f, 0.0f);
    Plane_2();

    glPopMatrix();

}

///ID120
///Plane1 in the Runway 2
void Plane_4()
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glTranslatef(airport_plane_4_pos, 0.0, 0.0f);

    glScalef(0.6f, 0.6f, 0.0f);
    glTranslatef(90.0f, 118.0f, 0.0f);
    glRotatef(90, 0.0f, 0.0f, 1.0f);
    glTranslatef(-90.0f, -118.0f, 0.0f);

    Plane_2();
    glPopMatrix();

}
///ID121
///Plane2 in the Runway 2
void Plane_5()
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

        glTranslatef(airport_plane_5_pos, 0.0, 0.0f);


    glTranslatef(120.0f, 2.7f, 0.0f);

    glRotatef(90, 0.0f, 0.0f, 1.0f);

    Plane_2();
    glPopMatrix();
}



///ID122
///PrivateJet1
void Private_Jet1(int a)
{
///Body
    glBegin(GL_POLYGON);
    glColor3f(1.0f,1.0f,1.0f);

    glVertex2f(65.5277947122752,50.1666844885298);
    glVertex2f(65.2870114205349,50.6537000804388);
    glVertex2f(65.2870114205349,52.6392509521775);
    glVertex2f(65.3053015113849,52.883458943759);
    glVertex2f(65.6114436897628,52.88864779424);
    glVertex2f(65.6529544936106,52.6551495225958);
    glVertex2f(65.7466296778818,50.6720848107327);

    glEnd();

///body

    glBegin(GL_POLYGON);
    glColor3f(1.0f,1.0f,1.0f);
    glVertex2f(64.9877238329859,52.8590135945929);
    glVertex2f(65.0545773976909,53.5860461107599);
    glVertex2f(65.8317500873866,53.6361862842886);
    glVertex2f(65.9487438256204,52.9091537681216);
    glEnd();

///Left Wing


    if(a == 1)
    {
        glColor3f(1.0f,1.0f,1.0f);
    }
    else
    {
        glColor3f(1.0f,1.0f,0.0f);
    }

    glBegin(GL_POLYGON);
    glVertex2f(65.2718514829822,51.7809998637246);
    glVertex2f(63.5,53);
    glVertex2f(63.5708036019281,53.2110638681587);
    glVertex2f(65.2870114205349,52.6392509521775);
    glEnd();

///Right Wing

    glBegin(GL_POLYGON);
    glVertex2f(65.6993095044905,51.8456650826279);
    glVertex2f(67.4086336020617,53.106766416836);
    glVertex2f(67.4138224525427,53.3298869875181);
    glVertex2f(65.6529544936106,52.6551495225958);
    glEnd();

/// Wing

    if(a == 1)
    {
        glColor3f(1.0f,1.0f,1.0f);
    }
    else
    {
        glColor3f(1.0f,0.0f,0.0f);
    }

    glBegin(GL_POLYGON);
    // glColor3f(1.0f,1.0f,1.0f);
    glVertex2f(65.5,54);
    glVertex2f(65.4871328614541,54.3992759643215);
    glVertex2f(64.7483129555271,54.73977557314);
    glVertex2f(64.7483129555271,54.495643778138);
    glEnd();

    glBegin(GL_POLYGON);
    //glColor3f(1.0f,1.0f,1.0f);
    glVertex2f(65.5,54);
    glVertex2f(65.4871328614541,54.3992759643215);
    glVertex2f(66.1809811209333,54.7590491359033);
    glVertex2f(66.1588586364902,54.5054209353018);
    glEnd();


    glBegin(GL_LINES);
    glLineWidth(1);
    glColor3f(1.0f,1.0f,1.0f);
    glVertex2f(65.5,54);
    glVertex2f(65.4482501234927,53.4541303981043);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(0.7);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(65.2341707048678,52.0281804411075);
    glVertex2f(65.2133504164015,52.4185608498518);

    glVertex2f(65.7182424117108,52.1114615949729);
    glVertex2f(65.7286525559439,52.4549963546679);

    glVertex2f(65.4274634874626,50.6022085349507);
    glVertex2f(65.6344909547818,50.6114784215471);

    glEnd();

}


///ID123
///PrivateJet2
void Private_Jet2()
{

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glTranslatef(-2.0f, -7.0f, 0.0f);
    glScalef(1.15f, 1.15f, 0.0f);

    Private_Jet1(2);

    glPopMatrix();



}

///ID124
///PrivateJet3
void Private_Jet3()
{

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glTranslatef(16.0f, 00.0f, 0.0f);

    Private_Jet1(1);

    glPopMatrix();



}

///ID125
///RawFighterPlane
void Raw_Fighter_Plane()
{
//Body of the plane
    glBegin(GL_POLYGON);
    glColor4ub(20,22,21,255);
    glVertex2f(6.5163300387062,58.8310308797524);
    glVertex2f(5.6711011524944,54.2828944920415);
    glVertex2f(8.2470368057112,54.2828944920415);
    glVertex2f(7.4018079194994,58.7907818851709);
    glEnd();


    glBegin(GL_POLYGON);
    glColor4ub(255,255,255,255);
    glVertex2f(7.0395669682658,60.0787497117793);
    glVertex2f(6.5163300387062,58.8310308797524);
    glVertex2f(7.4018079194994,58.7907818851709);
    glEnd();
///
    glBegin(GL_POLYGON);
    glColor4ub(20,22,21,255);
    glVertex2f(5.5787617115485,48.766597252134);
    glVertex2f(8.3667679911585,48.7701131976887);
    glVertex2f(8.3278022867518,52.3167170478434);
    glVertex2f(5.6393132660684,52.2682758042275);

    glEnd();


    glBegin(GL_POLYGON);
    glColor4ub(20,22,21,255);
    glVertex2f(5.6711011524944,54.2828944920415);
    glVertex2f(1.5657037051802,51.2239709038466);
    glVertex2f(1.4449567214356,49.8957540826567);
    glVertex2f(5.4296071850053,50.7007339742869);
    glVertex2f(8.4482817786188,50.78123196345);
    glVertex2f(12.47318123677,49.7347581043306);
    glVertex2f(12.47318123677,51.1434729146836);
    glVertex2f(8.2470368057112,54.2828944920415);
    glEnd();

    glBegin(GL_POLYGON);
    glColor4ub(20,22,21,255);
    glVertex2f(5.4296071850053,51.0);
    glVertex2f(5.309392419371,49.9950127602032);
    glVertex2f(3.1472563468104,48.4316220615824);
    glVertex2f(3.546419929437,47.799613055757);
    glVertex2f(5.1763378918288,47.9659312151848);
    glEnd();

    glBegin(GL_POLYGON);
    glColor4ub(20,22,21,255);
    glVertex2f(8.4482817786188,51.0);
    glVertex2f(8.5712435645277,50.0878446705128);
    glVertex2f(8.3667679911585,48.7701131976887);
    glVertex2f(8.6621215971363,47.9522109042117);
    glVertex2f(10.3206456922425,47.7931743471467);
    glVertex2f(10.7977553634374,48.4066010672545);
    glEnd();

    glBegin(GL_POLYGON);
    glColor4ub(20,22,21,255);
    glVertex2f(6.5869452944752,47.20);
    glVertex2f(7.295807205351,47.20);
    glVertex2f(7.4690845613429,51.25);
    glVertex2f(6.1747691614096,51.25);
    glEnd();


    glBegin(GL_POLYGON);
    glColor4ub(255,255,255,255);
    glVertex2f(6.9627023873562,53.7365976797464);
    glVertex2f(6.1379842414336,53.2867514183341);
    glVertex2f(6.0630098645315,50.4127336370884);
    glVertex2f(7.8374034512136,50.3627507191537);
    glVertex2f(7.862394910181,53.2367685003993);


    glEnd();


    glBegin(GL_POLYGON);
    glColor4ub(255,255,255,255);
    glVertex2f(6.9876938463236,56.3357094123512);
    glVertex2f(6.2129586183356,55.4360168895264);
    glVertex2f(5.7869720221429,54.1167006308965);
    glVertex2f(4.7729362503105,53.1623140221131);
    glVertex2f(6.9799552831221,54.5938939352882);
    glVertex2f(9.2227638137631,53.1026648590641);
    glVertex2f(8.0417103853937,54.546174604849);
    glVertex2f(7.8985523940761,55.3931927201443);

    glEnd();
///Engine
    glBegin(GL_POLYGON);
    glColor4ub(255,255,255,255);
    glVertex2f(5.7072599401728,49.7307048628008);
    glVertex2f(6.3372264458267,49.7549343437874);
    glVertex2f(6.2718955563082,48.1485131058359);
    glVertex2f(5.7314894211595,48.1557885986659);

    glEnd();

///Engine
    glBegin(GL_POLYGON);
    glColor4ub(255,255,255,255);
    glVertex2f(7.5951044566097,49.6607518490377);
    glVertex2f(8.2252039329437,49.7395142835794);
    glVertex2f(8.1621939853103,48.1642655927443);
    glVertex2f(7.610856943518,48.1800180796527);

    glEnd();

}


///ID126
///FighterPlane1
void Fighter_plane1()
{

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glScalef(0.6, 0.6f, 0.0f);
    glTranslatef(0.0f, 40.0f, 0.0f);

    Raw_Fighter_Plane();

    glPopMatrix();

}
///ID127
///FighterPlane2
void Fighter_plane2()
{

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    // glScalef(0.6, 0.6f, 0.0f);
    glTranslatef(10.0f, -2.0f, 0.0f);

    Fighter_plane1();

    glPopMatrix();

}

///ID128
///FighterPlane3
void Fighter_plane3()
{

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    // glScalef(0.6, 0.6f, 0.0f);
    glTranslatef(10.0f, 2.0f, 0.0f);

    Fighter_plane2();

    glPopMatrix();

}

///ID129
///Bus

void Bus()
{

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(airport_bus_position, 0, 0);

    glScalef(0.6, 0.6, 1.0);
    glTranslatef(105, 72, 0);
    ///Main Body
    glColor4ub(242,255,0,255);
    glBegin(GL_POLYGON);
    glVertex2f(133.8742995638485, 22.0514744183132);
    glVertex2f(155.0866929085396, 22.0514744183132);
    glVertex2f(159.3555508663921, 22.7798219685151);
    glVertex2f(159.0998193882714, 28.9747813767135);
    glVertex2f(154.1377853572519, 29.0182472755849);
    glVertex2f(153.952898810401, 29.0182472755849);
    glVertex2f(152.391015121074, 29.0182472755849);
    glVertex2f(152.1918545275239, 29.0182472755849);
    glVertex2f(152.1918545275239, 29.0182472755849);
    glVertex2f(143.8250295585076, 28.9747813767135);
    glVertex2f(143.6023299458792, 29.1632542248947);
    glVertex2f(137.1579599054453, 29.1632542248947);
    glVertex2f(136.9213415670276, 28.9747813767135);
    glVertex2f(135.1360094748324, 28.9747813767135);
    glVertex2f(134.3807780416417, 28.3818073535841);
    glVertex2f(133.4785458475064, 22.5265747571625);
    glVertex2f(133.629418693105, 22.2029340768237);
    glEnd();

    ///Front Window
    glColor4ub(28,102,138,255);
    glBegin(GL_POLYGON);
    glVertex2f(134.0639432040195, 24.4205704615218);
    glVertex2f(135.3057035239542, 24.4205704615218);
    glVertex2f(136.5893209333249, 25.3414264291139);
    glVertex2f(136.5893209333249, 28.53851934003);
    glVertex2f(135.1520769065262, 28.53851934003);
    glVertex2f(134.8386392737431, 28.3779781134825);
    glVertex2f(134.6169394847015, 27.9498681760228);
    glEnd();

    ///Main Windows
    glColor4ub(28,102,138,255);
    glBegin(GL_POLYGON);
    glVertex2f(136.9235334894507, 26.1421820514168);
    glVertex2f(158.4091296407599, 26.1421820514168);
    glVertex2f(158.4091296407599, 28.53851934003);
    glVertex2f(136.9235334894507, 28.53851934003);
    glEnd();

///Window lines

    glLineWidth(0.5);
    glColor4ub(41,51,60,255);
    glBegin(GL_LINES);
    glVertex2f(136.9235334894507, 26.1421820514168);
    glVertex2f(158.4091296407599, 26.1421820514168);
    glEnd();

    glColor4ub(41,51,60,255);
    glBegin(GL_LINES);
    glVertex2f(158.4091296407599, 28.53851934003);
    glVertex2f(136.9235334894507, 28.53851934003);
    glEnd();

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    for (int i=0; i<8; i++)
    {
        glColor4ub(41,51,60,255);
        glBegin(GL_LINES);
        glVertex2f(136.9235334894507, 26.1421820514168);
        glVertex2f(136.9235334894507, 28.53851934003);
        glEnd();

        glTranslatef(3.05f, 0.0f, 0.0f);
    }
    glPopMatrix();

    ///Front Black Line
    glLineWidth(1.5);
    glColor4ub(41,51,60,255);
    glBegin(GL_LINES);
    glVertex2f(135.8152288533063, 28.8806527352546);
    glVertex2f(135.1620907686621, 28.8806527352546);
    glVertex2f(134.3807780416417, 28.3818073535841);
    glVertex2f(133.6775408336954, 24.099277561161);
    glEnd();

    ///Body Lines
    glLineWidth(0.3);
    glColor4ub(193,193,195,255);
    glBegin(GL_LINES);
    glVertex2f(134.0639432040195, 24.6326643299349);
    glVertex2f(158.4253793638388, 24.6326643299349);
    glVertex2f(158.4253793638388, 22.6061170478029);
    glVertex2f(158.4253793638388, 26.2009500934061);
    glVertex2f(135.730616650045, 22.0514744183132);
    glVertex2f(135.7459961951742, 24.6326643299349);
    glEnd();

    glPushMatrix();

    for (int i=0; i<7; i++)
    {
        glColor4ub(193,193,195,255);
        glBegin(GL_LINES);
        glVertex2f(137.145534801933, 22.0514744183132);
        glVertex2f(137.1301552568038, 24.6326643299349);
        glEnd();

        glTranslatef(3.05f, 0.0f, 0.0f);
    }
    glPopMatrix();

    ///Back Light
    glColor4ub(230,70,31,255);
    glBegin(GL_POLYGON);
    glVertex2f(158.9290707850402, 23.4733728536112);
    glVertex2f(159.3386913537838, 23.4733728536112);
    glVertex2f(159.3059217082843, 24.5465787437194);
    glVertex2f(158.9290707850402, 24.5465787437194);
    glEnd();

    ///Red Head Lights
    glColor4ub(211,49,39,255);
    glBegin(GL_POLYGON);
    glVertex2f(133.484275065947, 22.7383036793105);
    glVertex2f(133.7519612738629, 22.7383036793105);
    glVertex2f(133.7519612738629, 23.0046544181491);
    glVertex2f(133.4885126841226, 23.0046544181491);
    glEnd();

    ///White Head Lights
    glColor3ub(242, 201, 34 );
    glBegin(GL_POLYGON);
    glVertex2f(133.4885126841226, 23.0046544181491);
    glVertex2f(133.7519612738629, 23.0046544181491);
    glVertex2f(133.7519612738629, 23.4320583213311);
    glVertex2f(133.5097007750009, 23.4320583213311);
    glEnd();

    ///Rear Wheel
    airportCircle(1.2, 138.8870871195253, 22.598998649373, 0.0,0.0,0.0);
    airportCircle(0.97, 138.8870871195253, 22.598998649373, 0.24, 0.24, 0.24);
    airportCircle(0.70, 138.8870871195253, 22.598998649373, 0.576, 0.565, 0.553);

    glPointSize(3.5);
    glBegin(GL_POINTS);
    glColor4ub(58,49,47,255);
    glVertex2f(138.8870871195253, 22.598998649373);
    glEnd();

    ///front wheel
    airportCircle(1.2, 152.3065698453618, 22.633483417416, 0.0,0.0,0.0);
    airportCircle(0.99, 152.3065698453618, 22.633483417416,0.24, 0.24, 0.24);
    airportCircle(0.70, 152.3065698453618, 22.633483417416, 0.576, 0.565, 0.553);

    glPointSize(3.5);
    glBegin(GL_POINTS);
    glColor4ub(58,49,47,255);
    glVertex2f(152.3065698453618, 22.633483417416);
    glEnd();

    glPopMatrix();
    glColor3ub(255,0,0);
    // renderText(140.7050334604724, 25.140169481459, "DESH TRAVELS");

}



///ID130
///Area_between_Runways

void Background_For_between_Runways()
{
    glBegin(GL_POLYGON);
    glColor3f(0.08f,0.33f,0.14);
    glVertex2f(30,20);
    glVertex2f(160,20);
    glVertex2f(160,35);
    glVertex2f(30,35);
    glEnd();
}
///ID131
///Area_Beside_Parking
void Background_Beside_Parking()
{
    glBegin(GL_POLYGON);
    glColor3f(0.08f,0.33f,0.14);
    glVertex2f(30,62);
    glVertex2f(160,62);
    glVertex2f(160,63);
    glVertex2f(30,63);
    glEnd();
}



///ID132
///Plane_Parking_Line
void Plane_Parking_Line()
{

    glBegin(GL_POLYGON);
    glColor3f(1.0f,1.0f,0.0f);
    glVertex2f(30,60.5);
    glVertex2f(90,60.5);
    glVertex2f(90,61);
    glVertex2f(30,61);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(1.0f,1.0f,0.0f);
    glVertex2f(37.4,61);
    glVertex2f(37.4,45);
    glVertex2f(49.4,61);
    glVertex2f(49.4,45);
    glEnd();


    glBegin(GL_POLYGON);
    glColor3f(1.0f,1.0f,0.0f);
    glVertex2f(60,47.5);
    glVertex2f(90,47.5);
    glVertex2f(90,47);
    glVertex2f(60,47);
    glEnd();



    glLineWidth(1);
    glBegin(GL_LINES);
    glColor3f(0.0f,0.0f,1.0f);
    glVertex2f(65.5,47.5);
    glVertex2f(65.5,59);

    glVertex2f(73.35,47.5);
    glVertex2f(73.35,59);
    glVertex2f(81.5,47.5);
    glVertex2f(81.5,59);
    glEnd();



}

float move_Cloud = 0.0f;

void Animated_Cloud(bool a)
{
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    glTranslatef(move_Cloud, 0.0f, 0.0f);
    Cloud(a);
    glPopMatrix();
    //glutSwapBuffers();

}

void update_Cloud_1(int value)
{

    move_Cloud += 0.9;
    if(move_Cloud > 130)
    {
        move_Cloud = -120.0;
    }
    glutPostRedisplay();
    glutTimerFunc(100, update_Cloud_1, 0);
}

void airportCloud(bool rain)
{
    float r = 1.0, g = 1.0, b = 1.0;
    if(rain)
        r = g = b = 0.65;
///ID133
///Cloud1
    // first cloud
    airportCircle(1.5, 81, 87,  r, g, b);
    airportCircle(2.8, 75.0, 87.0, r, g, b);
    airportCircle(2.5, 79.0, 87.0, r, g, b);
    airportCircle(2.2, 72.0, 87,  r, g, b);
    airportCircle(1.2, 69.8, 87,  r, g, b);
///ID134
///Cloud2
    // second cloud
    airportCircle(1.5, 131, 87,  r, g, b);
    airportCircle(2.8, 125.0, 87.0, r, g, b);
    airportCircle(2.5, 121.0, 87.0, r, g, b);
    airportCircle(2.0, 129.0, 87.0,  r, g, b);
    airportCircle(1.5, 119, 87,  r, g, b);
}
///ID136
///Car
void Car()
{

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(airport_car_position, 0.0f, 0.0f);

    glTranslatef(50.0f, 27.0f, 0.0f);
    glScalef(0.7f, 0.7f, 0.0f);

    glTranslatef(-50.0f, -27.0f, 0.0f);

    glBegin(GL_POLYGON);
    glColor4ub(0,51,153,255);
    glVertex2f(112.03f, 57.35f);
    glVertex2f(112.03f, 58.54f);
    glVertex2f(113.26f, 59.02f);
    glVertex2f(114.24f, 59.38f);


    glVertex2f(115.39f, 59.74f);
    glVertex2f(116.66f, 60.06f);
    glVertex2f(118.04f, 60.35f);
    glVertex2f(119.01f, 60.53f);

    glVertex2f(119.92f, 60.43f);
    glVertex2f(121.15f, 60.32f);
    glVertex2f(123.0f, 59.77f);

    glVertex2f(124.59f, 59.23f);
    glVertex2f(125.71f, 58.98f);
    glVertex2f(126.87f, 58.76f);
    glVertex2f(128.28f, 58.11f);
    glVertex2f(128.82f, 57.10f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor4ub(0,51,153,255);
    glVertex2f(112.03f, 57.35f);
    glVertex2f(111.38f, 56.81f);
    glVertex2f(111.96f, 55.29f);
    glVertex2f(128.35f, 55.29f);
    glVertex2f(129.0f, 56.34f);
    glVertex2f(128.82f, 57.10f);
    glEnd();


    glBegin(GL_POLYGON);
    glColor4ub(0,0,0,255);
    glVertex2f(115.11f, 58.69f);
    glVertex2f(115.12f, 59.22f);
    glVertex2f(117.13f, 59.90f);
    glVertex2f(119.85f, 60.137f);
    glVertex2f(122.33f, 59.76f);
    glVertex2f(124.77f, 58.69f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor4ub(153,153,153,255);
    glVertex2f(115.98f, 58.75f);
    glVertex2f(116.29f, 59.51f);
    glVertex2f(118.0f, 59.95f);
    glVertex2f(119.75f, 59.95f);
    glVertex2f(119.92f, 58.73f);

    glEnd();

    glBegin(GL_POLYGON);
    glColor4ub(153,153,153,255);

    glVertex2f(120.5f, 58.725f);
    glVertex2f(120.1f, 59.95f);
    glVertex2f(124.59f, 58.64f);
    glEnd();

    // rotating wheel
    glPushMatrix();
    glTranslatef(114.8, 55.8, 0.f);
    glRotatef(-airport_angle1, 0.0f, 0.0f, 1.0f);
    glTranslatef(-114.8, -55.8, 0.f);
    airportWheel(1.5f, 114.8, 55.8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(125.5, 55.8, 0.f);
    glRotatef(-airport_angle1, 0.0f, 0.0f, 1.0f);
    glTranslatef(-125.5, -55.8, 0.f);
    airportWheel(1.5f, 125.5, 55.8);
    glPopMatrix();




    glPopMatrix();


}
///ID137
void flower()
{
    glPushMatrix();

    for (int i=0; i<3; i++)
    {
        ///Right green leaf
   glBegin(GL_POLYGON);
    glColor4ub(39,188,133,255);
    glVertex2f(15.0846577489773, 35.0337465204212);
    glVertex2f(15.209989386278, 34.914111775725);
    glVertex2f(15.4549557682748, 34.8685366348884);
    glVertex2f(15.8138600023633, 34.8799304200975);
    glVertex2f(16.2012486994746, 34.9425962387479);
    glVertex2f(16.7994224229552, 35.0793216612578);
    glVertex2f(16.4063368332394, 35.4894979287874);
    glEnd();

    glBegin(GL_POLYGON);
    glColor4ub(181,64,55,255);
    glVertex2f(15.7682324238074, 35.2632039117802);
    glVertex2f(16.0193711731199, 35.2835665130758);
    glVertex2f(16.2263909529585, 35.3785919857886);
    glVertex2f(16.4063368332394, 35.4894979287874);
    glVertex2f(16.579342708749, 35.7009998396357);
    glVertex2f(16.2671161555497, 35.7688751772877);
    glEnd();

    glBegin(GL_POLYGON);
    glColor4ub(255,170,177,255);
    glVertex2f(15.0846577489773, 35.0337465204212);
    glVertex2f(15.4899435394341, 35.1206657027109);
    glVertex2f(15.7682324238074, 35.2632039117802);
    glVertex2f(16.0656469211718, 35.5116398244706);
    glVertex2f(16.2671161555497, 35.7688751772877);
    glVertex2f(16.5074950798354, 36.3953361417978);
    glVertex2f(15.7558453386606, 36.1667939907649);
    glVertex2f(15.4308076127471, 35.9534879831342);
    glEnd();

    glBegin(GL_POLYGON);
    glColor4ub(178,66,52,255);
    glVertex2f(15.4308076127471, 35.9534879831342);
    glVertex2f(15.7558453386606, 36.1667939907649);
    glVertex2f(15.7558453386606, 36.6492718651676);
    glVertex2f(15.3749417536058, 36.385178712863);

    glEnd();

    glBegin(GL_POLYGON);
    glColor4ub(255,164,169,255);
    glVertex2f(15.0846577489773, 35.0337465204212);
    glVertex2f(15.313997179997, 35.389750677253);
    glVertex2f(15.4003353259428, 35.6640012584925);
    glVertex2f(15.4308076127471, 35.9534879831342);
    glVertex2f(15.3749417536058, 36.385178712863);
    glVertex2f(15.2600232143552, 36.7359874951038);
    glVertex2f(15.0846577489773, 37.0541226386267);

    glEnd();

    ///Left green leaf
    glBegin(GL_POLYGON);
    glColor4ub(39,188,133,255);
    glVertex2f(15.0846577489773, 35.0337465204212);
    glVertex2f(14.9593261116766, 34.914111775725);
    glVertex2f(14.7143597296798, 34.8685366348884);
    glVertex2f(14.3554554955913, 34.8799304200975);
    glVertex2f(13.96806679848, 34.9425962387479);
    glVertex2f(13.3698930749994, 35.0793216612578);
    glVertex2f(13.7629786647152, 35.4894979287874);
    glEnd();

    glBegin(GL_POLYGON);
    glColor4ub(181,64,55,255);
    glVertex2f(14.4010830741472, 35.2632039117802);
    glVertex2f(14.1499443248347, 35.2835665130758);
    glVertex2f(13.9429245449961, 35.3785919857886);
    glVertex2f(13.7629786647152, 35.4894979287874);
    glVertex2f(13.5899727892056, 35.7009998396357);
    glVertex2f(13.9021993424049, 35.7688751772877);
    glEnd();

    glBegin(GL_POLYGON);
    glColor4ub(255,170,177,255);
    glVertex2f(15.0846577489773, 35.0337465204212);
    glVertex2f(14.6793719585205, 35.1206657027109);
    glVertex2f(14.4010830741472, 35.2632039117802);
    glVertex2f(14.1020735760855, 35.5116398244706);
    glVertex2f(13.9021993424049, 35.7688751772877);
    glVertex2f(13.6618204181192, 36.3953361417978);
    glVertex2f(14.4134701592939, 36.1667939907649);
    glVertex2f(14.7385978852075, 35.9534879831342);
    glEnd();

    glBegin(GL_POLYGON);
    glColor4ub(178,66,52,255);
    glVertex2f(14.7385978852075, 35.9534879831342);
    glVertex2f(14.4134701592939, 36.1667939907649);
    glVertex2f(14.4134701592939, 36.6492718651676);
    glVertex2f(14.7933737443488, 36.385178712863);
    glEnd();

    glBegin(GL_POLYGON);
    glColor4ub(255,164,169,255);
    glVertex2f(15.0846577489773, 35.0337465204212);
    glVertex2f(14.8553183179576, 35.389750677253);
    glVertex2f(14.7689801719118, 35.6640012584925);
    glVertex2f(14.7385978852075, 35.9534879831342);
    glVertex2f(14.7933737443488, 36.385178712863);
    glVertex2f(14.9092922835994, 36.7359874951038);
    glVertex2f(15.0846577489773, 37.0541226386267);
    glEnd();

        glTranslatef(4.02f, 0.6f, 0.0f);
    }
    glPopMatrix();

    glPushMatrix();

    for (int i=0; i<3; i++)
    {
        ///Right green leaf
   glBegin(GL_POLYGON);
    glColor4ub(39,188,133,255);
    glVertex2f(15.0846577489773, 35.0337465204212);
    glVertex2f(15.209989386278, 34.914111775725);
    glVertex2f(15.4549557682748, 34.8685366348884);
    glVertex2f(15.8138600023633, 34.8799304200975);
    glVertex2f(16.2012486994746, 34.9425962387479);
    glVertex2f(16.7994224229552, 35.0793216612578);
    glVertex2f(16.4063368332394, 35.4894979287874);
    glEnd();

    glBegin(GL_POLYGON);
    glColor4ub(181,64,55,255);
    glVertex2f(15.7682324238074, 35.2632039117802);
    glVertex2f(16.0193711731199, 35.2835665130758);
    glVertex2f(16.2263909529585, 35.3785919857886);
    glVertex2f(16.4063368332394, 35.4894979287874);
    glVertex2f(16.579342708749, 35.7009998396357);
    glVertex2f(16.2671161555497, 35.7688751772877);
    glEnd();

    glBegin(GL_POLYGON);
    glColor4ub(255,170,177,255);
    glVertex2f(15.0846577489773, 35.0337465204212);
    glVertex2f(15.4899435394341, 35.1206657027109);
    glVertex2f(15.7682324238074, 35.2632039117802);
    glVertex2f(16.0656469211718, 35.5116398244706);
    glVertex2f(16.2671161555497, 35.7688751772877);
    glVertex2f(16.5074950798354, 36.3953361417978);
    glVertex2f(15.7558453386606, 36.1667939907649);
    glVertex2f(15.4308076127471, 35.9534879831342);
    glEnd();

    glBegin(GL_POLYGON);
    glColor4ub(178,66,52,255);
    glVertex2f(15.4308076127471, 35.9534879831342);
    glVertex2f(15.7558453386606, 36.1667939907649);
    glVertex2f(15.7558453386606, 36.6492718651676);
    glVertex2f(15.3749417536058, 36.385178712863);

    glEnd();

    glBegin(GL_POLYGON);
    glColor4ub(255,164,169,255);
    glVertex2f(15.0846577489773, 35.0337465204212);
    glVertex2f(15.313997179997, 35.389750677253);
    glVertex2f(15.4003353259428, 35.6640012584925);
    glVertex2f(15.4308076127471, 35.9534879831342);
    glVertex2f(15.3749417536058, 36.385178712863);
    glVertex2f(15.2600232143552, 36.7359874951038);
    glVertex2f(15.0846577489773, 37.0541226386267);

    glEnd();

    ///Left green leaf
    glBegin(GL_POLYGON);
    glColor4ub(39,188,133,255);
    glVertex2f(15.0846577489773, 35.0337465204212);
    glVertex2f(14.9593261116766, 34.914111775725);
    glVertex2f(14.7143597296798, 34.8685366348884);
    glVertex2f(14.3554554955913, 34.8799304200975);
    glVertex2f(13.96806679848, 34.9425962387479);
    glVertex2f(13.3698930749994, 35.0793216612578);
    glVertex2f(13.7629786647152, 35.4894979287874);
    glEnd();

    glBegin(GL_POLYGON);
    glColor4ub(181,64,55,255);
    glVertex2f(14.4010830741472, 35.2632039117802);
    glVertex2f(14.1499443248347, 35.2835665130758);
    glVertex2f(13.9429245449961, 35.3785919857886);
    glVertex2f(13.7629786647152, 35.4894979287874);
    glVertex2f(13.5899727892056, 35.7009998396357);
    glVertex2f(13.9021993424049, 35.7688751772877);
    glEnd();

    glBegin(GL_POLYGON);
    glColor4ub(255,170,177,255);
    glVertex2f(15.0846577489773, 35.0337465204212);
    glVertex2f(14.6793719585205, 35.1206657027109);
    glVertex2f(14.4010830741472, 35.2632039117802);
    glVertex2f(14.1020735760855, 35.5116398244706);
    glVertex2f(13.9021993424049, 35.7688751772877);
    glVertex2f(13.6618204181192, 36.3953361417978);
    glVertex2f(14.4134701592939, 36.1667939907649);
    glVertex2f(14.7385978852075, 35.9534879831342);
    glEnd();

    glBegin(GL_POLYGON);
    glColor4ub(178,66,52,255);
    glVertex2f(14.7385978852075, 35.9534879831342);
    glVertex2f(14.4134701592939, 36.1667939907649);
    glVertex2f(14.4134701592939, 36.6492718651676);
    glVertex2f(14.7933737443488, 36.385178712863);
    glEnd();

    glBegin(GL_POLYGON);
    glColor4ub(255,164,169,255);
    glVertex2f(15.0846577489773, 35.0337465204212);
    glVertex2f(14.8553183179576, 35.389750677253);
    glVertex2f(14.7689801719118, 35.6640012584925);
    glVertex2f(14.7385978852075, 35.9534879831342);
    glVertex2f(14.7933737443488, 36.385178712863);
    glVertex2f(14.9092922835994, 36.7359874951038);
    glVertex2f(15.0846577489773, 37.0541226386267);
    glEnd();

        glTranslatef(-6.10f, -3.6f, 0.0f);
    }
    glPopMatrix();

    glPushMatrix();

    for (int i=0; i<3; i++)
    {
        ///Right green leaf
   glBegin(GL_POLYGON);
    glColor4ub(39,188,133,255);
    glVertex2f(15.0846577489773, 35.0337465204212);
    glVertex2f(15.209989386278, 34.914111775725);
    glVertex2f(15.4549557682748, 34.8685366348884);
    glVertex2f(15.8138600023633, 34.8799304200975);
    glVertex2f(16.2012486994746, 34.9425962387479);
    glVertex2f(16.7994224229552, 35.0793216612578);
    glVertex2f(16.4063368332394, 35.4894979287874);
    glEnd();

    glBegin(GL_POLYGON);
    glColor4ub(181,64,55,255);
    glVertex2f(15.7682324238074, 35.2632039117802);
    glVertex2f(16.0193711731199, 35.2835665130758);
    glVertex2f(16.2263909529585, 35.3785919857886);
    glVertex2f(16.4063368332394, 35.4894979287874);
    glVertex2f(16.579342708749, 35.7009998396357);
    glVertex2f(16.2671161555497, 35.7688751772877);
    glEnd();

    glBegin(GL_POLYGON);
    glColor4ub(255,170,177,255);
    glVertex2f(15.0846577489773, 35.0337465204212);
    glVertex2f(15.4899435394341, 35.1206657027109);
    glVertex2f(15.7682324238074, 35.2632039117802);
    glVertex2f(16.0656469211718, 35.5116398244706);
    glVertex2f(16.2671161555497, 35.7688751772877);
    glVertex2f(16.5074950798354, 36.3953361417978);
    glVertex2f(15.7558453386606, 36.1667939907649);
    glVertex2f(15.4308076127471, 35.9534879831342);
    glEnd();

    glBegin(GL_POLYGON);
    glColor4ub(178,66,52,255);
    glVertex2f(15.4308076127471, 35.9534879831342);
    glVertex2f(15.7558453386606, 36.1667939907649);
    glVertex2f(15.7558453386606, 36.6492718651676);
    glVertex2f(15.3749417536058, 36.385178712863);

    glEnd();

    glBegin(GL_POLYGON);
    glColor4ub(255,164,169,255);
    glVertex2f(15.0846577489773, 35.0337465204212);
    glVertex2f(15.313997179997, 35.389750677253);
    glVertex2f(15.4003353259428, 35.6640012584925);
    glVertex2f(15.4308076127471, 35.9534879831342);
    glVertex2f(15.3749417536058, 36.385178712863);
    glVertex2f(15.2600232143552, 36.7359874951038);
    glVertex2f(15.0846577489773, 37.0541226386267);

    glEnd();

    ///Left green leaf
    glBegin(GL_POLYGON);
    glColor4ub(39,188,133,255);
    glVertex2f(15.0846577489773, 35.0337465204212);
    glVertex2f(14.9593261116766, 34.914111775725);
    glVertex2f(14.7143597296798, 34.8685366348884);
    glVertex2f(14.3554554955913, 34.8799304200975);
    glVertex2f(13.96806679848, 34.9425962387479);
    glVertex2f(13.3698930749994, 35.0793216612578);
    glVertex2f(13.7629786647152, 35.4894979287874);
    glEnd();

    glBegin(GL_POLYGON);
    glColor4ub(181,64,55,255);
    glVertex2f(14.4010830741472, 35.2632039117802);
    glVertex2f(14.1499443248347, 35.2835665130758);
    glVertex2f(13.9429245449961, 35.3785919857886);
    glVertex2f(13.7629786647152, 35.4894979287874);
    glVertex2f(13.5899727892056, 35.7009998396357);
    glVertex2f(13.9021993424049, 35.7688751772877);
    glEnd();

    glBegin(GL_POLYGON);
    glColor4ub(255,170,177,255);
    glVertex2f(15.0846577489773, 35.0337465204212);
    glVertex2f(14.6793719585205, 35.1206657027109);
    glVertex2f(14.4010830741472, 35.2632039117802);
    glVertex2f(14.1020735760855, 35.5116398244706);
    glVertex2f(13.9021993424049, 35.7688751772877);
    glVertex2f(13.6618204181192, 36.3953361417978);
    glVertex2f(14.4134701592939, 36.1667939907649);
    glVertex2f(14.7385978852075, 35.9534879831342);
    glEnd();

    glBegin(GL_POLYGON);
    glColor4ub(178,66,52,255);
    glVertex2f(14.7385978852075, 35.9534879831342);
    glVertex2f(14.4134701592939, 36.1667939907649);
    glVertex2f(14.4134701592939, 36.6492718651676);
    glVertex2f(14.7933737443488, 36.385178712863);
    glEnd();

    glBegin(GL_POLYGON);
    glColor4ub(255,164,169,255);
    glVertex2f(15.0846577489773, 35.0337465204212);
    glVertex2f(14.8553183179576, 35.389750677253);
    glVertex2f(14.7689801719118, 35.6640012584925);
    glVertex2f(14.7385978852075, 35.9534879831342);
    glVertex2f(14.7933737443488, 36.385178712863);
    glVertex2f(14.9092922835994, 36.7359874951038);
    glVertex2f(15.0846577489773, 37.0541226386267);
    glEnd();

        glTranslatef(-1.50f, -5.9f, 0.0f);
    }
    glPopMatrix();

    glPushMatrix();

    for (int i=0; i<4; i++)
    {
        ///Right green leaf
   glBegin(GL_POLYGON);
    glColor4ub(39,188,133,255);
    glVertex2f(15.0846577489773, 35.0337465204212);
    glVertex2f(15.209989386278, 34.914111775725);
    glVertex2f(15.4549557682748, 34.8685366348884);
    glVertex2f(15.8138600023633, 34.8799304200975);
    glVertex2f(16.2012486994746, 34.9425962387479);
    glVertex2f(16.7994224229552, 35.0793216612578);
    glVertex2f(16.4063368332394, 35.4894979287874);
    glEnd();

    glBegin(GL_POLYGON);
    glColor4ub(181,64,55,255);
    glVertex2f(15.7682324238074, 35.2632039117802);
    glVertex2f(16.0193711731199, 35.2835665130758);
    glVertex2f(16.2263909529585, 35.3785919857886);
    glVertex2f(16.4063368332394, 35.4894979287874);
    glVertex2f(16.579342708749, 35.7009998396357);
    glVertex2f(16.2671161555497, 35.7688751772877);
    glEnd();

    glBegin(GL_POLYGON);
    glColor4ub(255,170,177,255);
    glVertex2f(15.0846577489773, 35.0337465204212);
    glVertex2f(15.4899435394341, 35.1206657027109);
    glVertex2f(15.7682324238074, 35.2632039117802);
    glVertex2f(16.0656469211718, 35.5116398244706);
    glVertex2f(16.2671161555497, 35.7688751772877);
    glVertex2f(16.5074950798354, 36.3953361417978);
    glVertex2f(15.7558453386606, 36.1667939907649);
    glVertex2f(15.4308076127471, 35.9534879831342);
    glEnd();

    glBegin(GL_POLYGON);
    glColor4ub(178,66,52,255);
    glVertex2f(15.4308076127471, 35.9534879831342);
    glVertex2f(15.7558453386606, 36.1667939907649);
    glVertex2f(15.7558453386606, 36.6492718651676);
    glVertex2f(15.3749417536058, 36.385178712863);

    glEnd();

    glBegin(GL_POLYGON);
    glColor4ub(255,164,169,255);
    glVertex2f(15.0846577489773, 35.0337465204212);
    glVertex2f(15.313997179997, 35.389750677253);
    glVertex2f(15.4003353259428, 35.6640012584925);
    glVertex2f(15.4308076127471, 35.9534879831342);
    glVertex2f(15.3749417536058, 36.385178712863);
    glVertex2f(15.2600232143552, 36.7359874951038);
    glVertex2f(15.0846577489773, 37.0541226386267);

    glEnd();

    ///Left green leaf
    glBegin(GL_POLYGON);
    glColor4ub(39,188,133,255);
    glVertex2f(15.0846577489773, 35.0337465204212);
    glVertex2f(14.9593261116766, 34.914111775725);
    glVertex2f(14.7143597296798, 34.8685366348884);
    glVertex2f(14.3554554955913, 34.8799304200975);
    glVertex2f(13.96806679848, 34.9425962387479);
    glVertex2f(13.3698930749994, 35.0793216612578);
    glVertex2f(13.7629786647152, 35.4894979287874);
    glEnd();

    glBegin(GL_POLYGON);
    glColor4ub(181,64,55,255);
    glVertex2f(14.4010830741472, 35.2632039117802);
    glVertex2f(14.1499443248347, 35.2835665130758);
    glVertex2f(13.9429245449961, 35.3785919857886);
    glVertex2f(13.7629786647152, 35.4894979287874);
    glVertex2f(13.5899727892056, 35.7009998396357);
    glVertex2f(13.9021993424049, 35.7688751772877);
    glEnd();

    glBegin(GL_POLYGON);
    glColor4ub(255,170,177,255);
    glVertex2f(15.0846577489773, 35.0337465204212);
    glVertex2f(14.6793719585205, 35.1206657027109);
    glVertex2f(14.4010830741472, 35.2632039117802);
    glVertex2f(14.1020735760855, 35.5116398244706);
    glVertex2f(13.9021993424049, 35.7688751772877);
    glVertex2f(13.6618204181192, 36.3953361417978);
    glVertex2f(14.4134701592939, 36.1667939907649);
    glVertex2f(14.7385978852075, 35.9534879831342);
    glEnd();

    glBegin(GL_POLYGON);
    glColor4ub(178,66,52,255);
    glVertex2f(14.7385978852075, 35.9534879831342);
    glVertex2f(14.4134701592939, 36.1667939907649);
    glVertex2f(14.4134701592939, 36.6492718651676);
    glVertex2f(14.7933737443488, 36.385178712863);
    glEnd();

    glBegin(GL_POLYGON);
    glColor4ub(255,164,169,255);
    glVertex2f(15.0846577489773, 35.0337465204212);
    glVertex2f(14.8553183179576, 35.389750677253);
    glVertex2f(14.7689801719118, 35.6640012584925);
    glVertex2f(14.7385978852075, 35.9534879831342);
    glVertex2f(14.7933737443488, 36.385178712863);
    glVertex2f(14.9092922835994, 36.7359874951038);
    glVertex2f(15.0846577489773, 37.0541226386267);
    glEnd();

        glTranslatef(-5.50f, 2.0f, 0.0f);
    }
    glPopMatrix();

    glPushMatrix();

    for (int i=0; i<2; i++)
    {
        ///Right green leaf
   glBegin(GL_POLYGON);
    glColor4ub(39,188,133,255);
    glVertex2f(15.0846577489773, 35.0337465204212);
    glVertex2f(15.209989386278, 34.914111775725);
    glVertex2f(15.4549557682748, 34.8685366348884);
    glVertex2f(15.8138600023633, 34.8799304200975);
    glVertex2f(16.2012486994746, 34.9425962387479);
    glVertex2f(16.7994224229552, 35.0793216612578);
    glVertex2f(16.4063368332394, 35.4894979287874);
    glEnd();

    glBegin(GL_POLYGON);
    glColor4ub(181,64,55,255);
    glVertex2f(15.7682324238074, 35.2632039117802);
    glVertex2f(16.0193711731199, 35.2835665130758);
    glVertex2f(16.2263909529585, 35.3785919857886);
    glVertex2f(16.4063368332394, 35.4894979287874);
    glVertex2f(16.579342708749, 35.7009998396357);
    glVertex2f(16.2671161555497, 35.7688751772877);
    glEnd();

    glBegin(GL_POLYGON);
    glColor4ub(255,170,177,255);
    glVertex2f(15.0846577489773, 35.0337465204212);
    glVertex2f(15.4899435394341, 35.1206657027109);
    glVertex2f(15.7682324238074, 35.2632039117802);
    glVertex2f(16.0656469211718, 35.5116398244706);
    glVertex2f(16.2671161555497, 35.7688751772877);
    glVertex2f(16.5074950798354, 36.3953361417978);
    glVertex2f(15.7558453386606, 36.1667939907649);
    glVertex2f(15.4308076127471, 35.9534879831342);
    glEnd();

    glBegin(GL_POLYGON);
    glColor4ub(178,66,52,255);
    glVertex2f(15.4308076127471, 35.9534879831342);
    glVertex2f(15.7558453386606, 36.1667939907649);
    glVertex2f(15.7558453386606, 36.6492718651676);
    glVertex2f(15.3749417536058, 36.385178712863);

    glEnd();

    glBegin(GL_POLYGON);
    glColor4ub(255,164,169,255);
    glVertex2f(15.0846577489773, 35.0337465204212);
    glVertex2f(15.313997179997, 35.389750677253);
    glVertex2f(15.4003353259428, 35.6640012584925);
    glVertex2f(15.4308076127471, 35.9534879831342);
    glVertex2f(15.3749417536058, 36.385178712863);
    glVertex2f(15.2600232143552, 36.7359874951038);
    glVertex2f(15.0846577489773, 37.0541226386267);

    glEnd();

    ///Left green leaf
    glBegin(GL_POLYGON);
    glColor4ub(39,188,133,255);
    glVertex2f(15.0846577489773, 35.0337465204212);
    glVertex2f(14.9593261116766, 34.914111775725);
    glVertex2f(14.7143597296798, 34.8685366348884);
    glVertex2f(14.3554554955913, 34.8799304200975);
    glVertex2f(13.96806679848, 34.9425962387479);
    glVertex2f(13.3698930749994, 35.0793216612578);
    glVertex2f(13.7629786647152, 35.4894979287874);
    glEnd();

    glBegin(GL_POLYGON);
    glColor4ub(181,64,55,255);
    glVertex2f(14.4010830741472, 35.2632039117802);
    glVertex2f(14.1499443248347, 35.2835665130758);
    glVertex2f(13.9429245449961, 35.3785919857886);
    glVertex2f(13.7629786647152, 35.4894979287874);
    glVertex2f(13.5899727892056, 35.7009998396357);
    glVertex2f(13.9021993424049, 35.7688751772877);
    glEnd();

    glBegin(GL_POLYGON);
    glColor4ub(255,170,177,255);
    glVertex2f(15.0846577489773, 35.0337465204212);
    glVertex2f(14.6793719585205, 35.1206657027109);
    glVertex2f(14.4010830741472, 35.2632039117802);
    glVertex2f(14.1020735760855, 35.5116398244706);
    glVertex2f(13.9021993424049, 35.7688751772877);
    glVertex2f(13.6618204181192, 36.3953361417978);
    glVertex2f(14.4134701592939, 36.1667939907649);
    glVertex2f(14.7385978852075, 35.9534879831342);
    glEnd();

    glBegin(GL_POLYGON);
    glColor4ub(178,66,52,255);
    glVertex2f(14.7385978852075, 35.9534879831342);
    glVertex2f(14.4134701592939, 36.1667939907649);
    glVertex2f(14.4134701592939, 36.6492718651676);
    glVertex2f(14.7933737443488, 36.385178712863);
    glEnd();

    glBegin(GL_POLYGON);
    glColor4ub(255,164,169,255);
    glVertex2f(15.0846577489773, 35.0337465204212);
    glVertex2f(14.8553183179576, 35.389750677253);
    glVertex2f(14.7689801719118, 35.6640012584925);
    glVertex2f(14.7385978852075, 35.9534879831342);
    glVertex2f(14.7933737443488, 36.385178712863);
    glVertex2f(14.9092922835994, 36.7359874951038);
    glVertex2f(15.0846577489773, 37.0541226386267);
    glEnd();

        glTranslatef(-12.50f, 0.0f, 0.0f);
    }
    glPopMatrix();




}

void drawAirportScene() {
    // Weather effects: do NOT call glClearColor here in unified mode.
    // If you have a central displayUnified() that sets sky, it can set clear color based on airportWeather.
    // If you want clouds/rain visual here, draw them via airport-specific functions below.

    // Ground strips and separators
    Background_For_between_Runways();
    Background_Beside_Parking();

    // Runways and taxiways
    Runways1();
    Taxiways1();
    Runways2();

    // Lake and buildings
    Lake();
    Aviation1();
    Aviation2();

    // Sun, parking lines, more taxiways
    // Sun uses airport_sun_position internally (renamed in update)
    Sun(3, 40, 85);         // relies on airportWeather via internal branch (updated in key handler)
    Parking();
    Plane_Parking_Line();
    Taxiways2();
    Taxiways3();

    // Foreground greens
    Grass();
    Catkin();

    // Planes and vehicles
    // Plane_1 uses airport_plane_x_1, airport_plane_y_1 via renamed update logic
    Plane_1();
    Plane_2();
    Plane_3();
    Plane_4();              // uses airport_plane_4_pos
    Plane_5();              // uses airport_plane_5_pos

    Fighter_plane1();
    Fighter_plane2();
    Fighter_plane3();

    Private_Jet1(1);
    Private_Jet2();
    Private_Jet3();

    // Car and bus use airport_car_position, airport_bus_position and airport_angle1
    Car();
    Bus();

    // Clouds and rain
    {
        // Clouds
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslatef(airport_move_Cloud, 0.0f, 0.0f);
        // Cloud color depends on rainy or not; we pass false to draw white clouds first,
        // and if rainy we draw a darker pass as in original.
        Cloud(false);
        glPopMatrix();

        if (airportWeather == RAINY_AIRPORT) {
            glMatrixMode(GL_MODELVIEW);
            glPushMatrix();
            glTranslatef(airport_move_Cloud, 0.0f, 0.0f);
            Cloud(true); // darker clouds
            glPopMatrix();

            drawAirportRaindrops();
        }
    }

    // Terminals, tower, lamps, flowers
    Terminal1();
    Terminal2();
    Tower();
    Terminal_Lamp1();
    Terminal_Lamp2();
    flower();
}
void updateAirport(int value) {
    // Bus animation (merged from bus_animation_1)
    if (airport_bus_moving) {
        airport_bus_position -= airport_bus_speed;
        if (airport_bus_position < -50.0f) {
            airport_bus_moving = !airport_bus_moving; // same toggle behavior as original
        }
    }

    // Car animation (merged from car_animation_1)
    if (airport_car_moving) {
        airport_angle1 += 2.0f;
        airport_car_position += airport_car_speed;
        if (airport_car_position > 80.0f)
            airport_car_position = 0.0f;
    }

    // Runway plane animation (merged from Runway_plane_animation_1)
    if (airport_plane_moving) {
        airport_plane_x_1 += 0.1f;
        airport_plane_y_1 += 0.026f;
    }

    // Sun shine (merged from sun_shine_animation)
    if (airport_sun_position < 0.0f)
        airport_sun_position += 0.1f;

    // Grass sway (merged from grass_movement_animation)
    // We emulate the timer-based v increment by using value as the tick count.
    if (value == 0)
        airport_grass_movement = 0.0f;
    else
        airport_grass_movement = 0.1f * sin(value * 0.1f);

    // Moving planes (merged from moving_plane)
    if (airport_plane_5_pos > -20.0f)
        airport_plane_5_pos -= 0.1f;
    if (airport_plane_4_pos > -20.0f)
        airport_plane_4_pos -= 0.1f;

    // Cloud movement (merged from update_Cloud_1)
    airport_move_Cloud += 0.9f;
    if (airport_move_Cloud > 130.0f)
        airport_move_Cloud = -120.0f;

    // Rain update if raining
    if (airportWeather == RAINY_AIRPORT) {
        updateAirportRaindrops(0);
    }

    // Redraw and re-arm single unified timer
    glutPostRedisplay();
}
void handleKeypressAirport(unsigned char key, int x, int y) {
    switch (key) {
        case 's':
            airportWeather = SUNNY_AIRPORT;
            break;
        case 'o':
            airportWeather = OVERCAST_AIRPORT;
            break;
        case 'r':
            airportWeather = RAINY_AIRPORT;
            initializeAirportRaindrops(100);
            break;
        case '+':
            for (auto& drop : airportRaindrops) {
                drop.speed *= 1.2f;
            }
            break;
        case '-':
            for (auto& drop : airportRaindrops) {
                drop.speed *= 0.8f;
            }
            break;
        case 27: // ESC optional
            exit(0);
    }
    glutPostRedisplay();
}
void handleMouseAirport(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        if (button == GLUT_LEFT_BUTTON) {
            airport_bus_speed *= 1.2f;
            airport_car_speed *= 1.2f;

            airport_move_Cloud += 1.0f;
            airport_sun_position += 0.5f;
        } else if (button == GLUT_RIGHT_BUTTON) {
            airport_bus_speed *= 0.8f;
            airport_car_speed *= 0.8f;

            airport_move_Cloud -= 1.0f;
            airport_sun_position -= 0.5f;
        }
        glutPostRedisplay();
    }
}

void initGL()
{
    glClearColor(0.08f, 0.33f, 0.14f, 1.0f); // Black and opaque
    glMatrixMode(GL_PROJECTION);         // Set up the projection matrix
    glLoadIdentity();                    // Reset projection matrix
    gluOrtho2D(0.0, 160.0, 0.0, 90.0);   // Define a 2D orthographic projection
}

void ChageWeather_1( bool a)
{

    Animated_Cloud(a);

    if (airportWeather == RAINY_AIRPORT)
    {

        Animated_Cloud(!a);
        drawAirportRaindrops();
    }
}

void scene1()
{
     glClear(GL_COLOR_BUFFER_BIT);
     glClearColor(0.0, 0.0, 0.5, 1.0);

    ChageWeather_1(airportWeather == RAINY_AIRPORT);
;
    Background_For_between_Runways();
    Background_Beside_Parking();

    Runways1();
    Taxiways1();
    Runways2();

    Lake();
    Aviation1();
    Aviation2();

    Sun(3,40,85);
    Parking();
    Plane_Parking_Line();
    Taxiways2();
    Taxiways3();

    Grass();
    Catkin();

    Plane_1();
    Plane_2();
    Plane_3();
    Plane_4();
    Plane_5();

    Fighter_plane1();
    Fighter_plane2();
    Fighter_plane3();

    Private_Jet1(1);
    Private_Jet2();
    Private_Jet3();

    Car();
    Bus();


    ChageWeather_1( false);

    Terminal1();
    Terminal2();
    Tower();
    Terminal_Lamp1();
    Terminal_Lamp2();
    flower();


    glutSwapBuffers(); // Use this for double buffering
}

void bus_animation_1()
{
    if(airport_bus_moving)
    {
    airport_bus_position -= airport_bus_speed;

        if (airport_bus_position < -50 ) {
            airport_bus_moving = !airport_bus_moving;
        }

    }
}
void car_animation_1()
{
    if(airport_car_moving)
    {
        airport_angle1 += 2.0f;
        airport_car_position += airport_car_speed;
        if(airport_car_position > 80)
            airport_car_position = 0;
    }

}
void Runway_plane_animation_1() {
    if (airport_plane_moving) {
        airport_plane_x_1 += 0.1;
        airport_plane_y_1 += 0.026;
    }
}

void sun_shine_animation(int v)
{
    if(airport_sun_position < 0)
        airport_sun_position += 0.1f;
}

void grass_movement_animation(int v)
{

    if(v == 0)
        airport_grass_movement = 0.0f;
    else
        airport_grass_movement = 0.1f * sin(v * 0.1f);


    glutTimerFunc(10, grass_movement_animation, v+1);

}

void moving_plane(int v)
{
    if(airport_plane_5_pos > -20)
        airport_plane_5_pos -= 0.1f;

    if(airport_plane_4_pos > -20)
        airport_plane_4_pos -= 0.1f;

}

void update_all_vhicle_1(int value)
{

    bus_animation_1();
    car_animation_1();

    Runway_plane_animation_1();

}

// ========================= UTTARA SCENE (Project 3) =========================

// Time of day enum renamed to avoid conflicts
enum TimeOfDayUttara { UTTARA_DAY, UTTARA_NIGHT };
TimeOfDayUttara uttaraTime = UTTARA_DAY;

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
    if (uttaraTime == UTTARA_DAY) {
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
    if (uttaraTime == UTTARA_DAY) {
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

    if (uttaraTime == UTTARA_DAY) {
        drawCircle(7, x + 40, y + 62.5, 255, 255, 255);
    } else {
        drawCircle(7, x + 40, y + 62.5, 255, 243, 0);
    }
}

void drawUttaraScene() {
    // Removed glClear() and glClearColor() — handled by displayUnified()

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 1280, 0, 720);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Original draw order preserved
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
}

void updateUttara(int value) {
    if (enable_animation) {
        if (enable_car_animation) {
            car_x_pos_road1 += car_speed_road1;
            if (car_x_pos_road1 > 1280 + 50) car_x_pos_road1 = -200;

            bus_x_pos_road1 += bus_speed_road1;
            if (bus_x_pos_road1 > 1280 + 50) bus_x_pos_road1 = -200;

            school_bus_x_pos_road1 += school_bus_speed_road1;
            if (school_bus_x_pos_road1 > 1280 + 50) school_bus_x_pos_road1 = -200;
        }

        train_x_pos += train_speed;
        if (train_x_pos > 1280 + 100) train_x_pos = -400;

        boat_x_pos_lake += boat_speed_lake;
        if (boat_x_pos_lake > 1280 + 50) boat_x_pos_lake = -200;

        airplane_x_pos -= airplane_speed;
        airplane_y_pos += airplane_speed * 0.05f;
        if (airplane_x_pos < -200) {
            airplane_x_pos = 1280 + 200;
            airplane_y_pos = 0;
        }

        cloud_x_pos += cloud_speed;
        if (cloud_x_pos > 1280 + 150) cloud_x_pos = -250;
    }

    glutPostRedisplay();
}

void handleKeypressUttara(unsigned char key, int x, int y) {
    if (key == 'n') uttaraTime = UTTARA_NIGHT;
    else if (key == 'd') uttaraTime = UTTARA_DAY;
    glutPostRedisplay();
}
void handleMouseUttara(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        if (button == GLUT_LEFT_BUTTON) {
            // Increase speed
            car_speed_road1      *= 1.2f;
            bus_speed_road1      *= 1.2f;
            school_bus_speed_road1 *= 1.2f;
            train_speed          *= 1.2f;
            boat_speed_lake      *= 1.2f;
            airplane_speed       *= 1.2f;
            cloud_speed          *= 1.2f;
        } else if (button == GLUT_RIGHT_BUTTON) {
            // Decrease speed
            car_speed_road1      *= 0.8f;
            bus_speed_road1      *= 0.8f;
            school_bus_speed_road1 *= 0.8f;
            train_speed          *= 0.8f;
            boat_speed_lake      *= 0.8f;
            airplane_speed       *= 0.8f;
            cloud_speed          *= 0.8f;
        }
    }
}


// ========================= 300ft (Project 3) =========================

enum TimeOfDay300ft { FT_DAY, FT_NIGHT };
TimeOfDay300ft time300ft = FT_NIGHT;

float ft_CAR_FULL_x = 0.0f, ft_CAR_FULL_speed = 0.5f;
float ft_car2_x = 0.0f, ft_car2_speed = 0.4f;
float ft_car3_x = 0.0f, ft_car3_speed = 0.4f;
float ft_Bus_x = 0.0f, ft_Bus_speed = 0.4f;
float ft_Truck_x = 0.0f, ft_Truck_speed = 0.4f;
float ft_Cloud_x = 0.0f, ft_Cloud_speed = 0.2f;

float ft_plane_x = 0, ft_plane_y = 0;

float ft_cloud_moving = false;


void renderText300ft(float x, float y, const char* text) {
    glRasterPos2f(x, y);  // Set the position to start drawing text
    for (const char* c = text; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);  // Render each character
    }
}

//Road 1//
///ID-401//
void Road1()
{

    glBegin(GL_POLYGON);
    glColor3ub(96, 96, 104) ;
    glVertex2f(0, 30);
    glVertex2f(160, 30);
    glVertex2f(160, 20);
    glVertex2f(0, 20);
    glEnd();

//dividing and border Road-1


    glLineWidth(3);
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0) ;
    glVertex2f(0, 30);
    glVertex2f(160, 30);
    glVertex2f(160, 20);
    glVertex2f(0, 20);
    glEnd();

    //Crossing-5


    glBegin(GL_POLYGON);
    glColor3ub(255, 255, 255 ) ;
    glVertex2f(20, 28);
    glVertex2f(30, 28);
    glVertex2f(28, 26);
    glVertex2f(18, 26);
    glEnd();

//Crossing-6


    glBegin(GL_POLYGON);
    glColor3ub(255, 255, 255 ) ;
    glVertex2f(16, 24);
    glVertex2f(26, 24);
    glVertex2f(24, 22);
    glVertex2f(14, 22);
    glEnd();

//Crossing-7


    glBegin(GL_POLYGON);
    glColor3ub(255, 255, 255 ) ;
    glVertex2f(100, 28);
    glVertex2f(110, 28);
    glVertex2f(108, 26);
    glVertex2f(98, 26);
    glEnd();

    //Crossing-8

    glBegin(GL_POLYGON);
    glColor3ub(255, 255, 255 ) ;
    glVertex2f(96, 24);
    glVertex2f(106, 24);
    glVertex2f(104, 22);
    glVertex2f(94, 22);
    glEnd();
}

//Road 2//
///ID-402//
void Road2()
{

    glBegin(GL_POLYGON);
    glColor3ub(96, 96, 104) ;
    glVertex2f(0, 20);
    glVertex2f(160, 20);
    glVertex2f(160, 10);
    glVertex2f(0, 10);
    glEnd();

     //Dividing and border Road-2


    glLineWidth(3);
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0) ;
    glVertex2f(0, 20);
    glVertex2f(160, 20);
    glVertex2f(160, 10);
    glVertex2f(0, 10);
    glEnd();

    // Divider and Road-2 Side Border


    glLineWidth(3);
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0 ) ;
    glVertex2f(0, 10);
    glVertex2f(160, 10);
    glVertex2f(160.0311161208932, 7.9305861998759);
    glVertex2f(0, 8);
    glEnd();


    //Crossing-1


    glBegin(GL_POLYGON);
    glColor3ub(255, 255, 255 ) ;
    glVertex2f(10, 18);
    glVertex2f(20, 18);
    glVertex2f(18, 16);
    glVertex2f(8, 16);
    glEnd();

//Crossing-2

    glBegin(GL_POLYGON);
    glColor3ub(255, 255, 255 ) ;
    glVertex2f(6, 14);
    glVertex2f(16, 14);
    glVertex2f(14, 12);
    glVertex2f(4, 12);
    glEnd();

//Crossing-3


    glBegin(GL_POLYGON);
    glColor3ub(255, 255, 255 ) ;
    glVertex2f(86, 14);
    glVertex2f(96, 14);
    glVertex2f(94, 12);
    glVertex2f(84, 12);
    glEnd();

//Crossing-4


    glBegin(GL_POLYGON);
    glColor3ub(255, 255, 255 ) ;
    glVertex2f(90, 18);
    glVertex2f(100, 18);
    glVertex2f(98, 16);
    glVertex2f(88, 16);
    glEnd();


}

///ID403//

void Footpath()
{

    //Footpath//
    glBegin(GL_POLYGON);
    glColor3ub(143, 249, 106) ;
    glVertex2f(0, 35);
    glVertex2f(160, 35);
    glVertex2f(160, 30);
    glVertex2f(0, 30);
    glEnd();

//Footpath- border//


    glBegin(GL_POLYGON);
    glColor3ub(144, 103, 44) ;
    glVertex2f(5.1004403962092, 34.0052974814963);
    glVertex2f(157.925095329689, 34.047057686253);
    glVertex2f(155.0473573954382, 31.0609122884895);
    glVertex2f(2.8785075862655, 30.9753891043005);
    glEnd();
}

///ID404//
void underlake()
{

    //under-lake
    glBegin(GL_POLYGON);
    glColor3ub(89, 168, 251  ) ;
    glVertex2f(0,10);
    glVertex2f(160, 10);
    glVertex2f(160,5);
    glVertex2f(0,5);
    glEnd();

}

///441
void Garden()
{
///Background area for garden
    glBegin(GL_POLYGON);
    glColor4ub(40,60,4,255);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(160.0f, 0.0f);
    glVertex2f(160.0f, 5.0f);
    glVertex2f(0.0f, 5.0f);
    glEnd();

///Grass
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    for(int i=0; i<11; i++)
    {

        glBegin(GL_POLYGON);
        glColor4ub(163,219,0,255);
        glVertex2f(4.0f, 0.0f);
        glVertex2f(2.0f, 3.0f);
        glVertex2f(6.0f, 0.0f);
        glEnd();

        glBegin(GL_POLYGON);
        glColor4ub(57,181,74,255);
        glVertex2f(4.0f, 0.0f);
        glVertex2f(3.0f, 5.0f);
        glVertex2f(6.0f, 0.0f);
        glEnd();

        glBegin(GL_POLYGON);
        glColor4ub(163,219,0,255);
        glVertex2f(4.0f, 0.0f);
        glVertex2f(6.0f, 5.0f);
        glVertex2f(6.0f, 0.0f);
        glEnd();

        glBegin(GL_POLYGON);
        glColor4ub(57,181,74,255);
        glVertex2f(4.0f, 0.0f);
        glVertex2f(8.0f, 4.0f);
        glVertex2f(6.0f, 0.0f);
        glEnd();

        glTranslatef(15.0f, 0.0f, 0.0f);

    }

    glPopMatrix();
}

void Tree()
{

 glPushMatrix();
    for(int i=0; i<11; i++)
    {
///Tree Root
    glBegin(GL_POLYGON);
    glColor3ub(116, 80, 64  ) ;
    glVertex2f(12, 1);
    glVertex2f(14, 1);
    glVertex2f(14, 5);
    glVertex2f(12, 5);
    glEnd();

///Tree Leaf-1
    glBegin(GL_TRIANGLES);
    glColor3ub(78, 207, 33 ) ;
    glVertex2f(10, 5);
    glVertex2f(16, 5);
    glVertex2f(13, 8);
    glEnd();

///Tree-1 Leaf-2
    glBegin(GL_TRIANGLES);
    glColor3ub(78, 207, 33) ;
    glVertex2f(10.5, 7.5);
    glVertex2f(15.5, 7.5);
    glVertex2f(13, 11);
    glEnd();

    glTranslatef(15.0f, 0.0f, 0.0f);
}
    glPopMatrix();
}

///ID405//
// Road-3
void Road3()
{

    // Road-3
    glBegin(GL_POLYGON);
    glColor3ub(96, 96, 104)  ;
    glVertex2f(0, 44);
    glVertex2f(159.9398454124169, 43.8914401369006);
    glVertex2f(160, 35);
    glVertex2f(0, 35);
    glEnd();

// Road-3 Border

    glLineWidth(3);
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0) ;
    glVertex2f(0, 44);
    glVertex2f(159.9398454124169, 43.8914401369006);
    glVertex2f(160, 35);
    glVertex2f(0, 35);
    glEnd();

//Crossing-9 Road-3


    glBegin(GL_POLYGON);
    glColor3ub(255, 255, 255 ) ;
    glVertex2f(34, 42);
    glVertex2f(42, 42);
    glVertex2f(40,40);
    glVertex2f(32, 40);
    glEnd();

//Crossing-10 Road-3


    glBegin(GL_POLYGON);
    glColor3ub(255, 255, 255 ) ;
    glVertex2f(30,38);
    glVertex2f(38, 38);
    glVertex2f(36, 36);
    glVertex2f(28, 36);
    glEnd();

//Crossing-11 Road-3

    glBegin(GL_POLYGON);
    glColor3ub(255, 255, 255 ) ;
    glVertex2f(114, 42);
    glVertex2f(124, 42);
    glVertex2f(122, 40);
    glVertex2f(112, 40);
    glEnd();

//Crossing-12 Road-3


    glBegin(GL_POLYGON);
    glColor3ub(255, 255, 255 ) ;
    glVertex2f(110, 38);
    glVertex2f(120, 38);
    glVertex2f(118, 36);
    glVertex2f(108, 36);
    glEnd();

// Road-3 Side Footpath


    glBegin(GL_POLYGON);
    glColor3ub(143, 249, 106) ;
    glVertex2f(0, 48);
    glVertex2f(160, 48);
    glVertex2f(160, 44);
    glVertex2f(0, 44);
    glEnd();

//Road-3 Side border


    glLineWidth(3);
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0 ) ;
    glVertex2f(0, 48);
    glVertex2f(160, 48);
    glVertex2f(160, 44);
    glVertex2f(0, 44);
    glEnd();

}



/////////Road-1 Road-2 Road-3 footpath Under lake end here//////

///ID406
void Tree1()
{

     //Tree-1 Root
    glBegin(GL_POLYGON);
    glColor3ub(116, 80, 64  ) ;
    glVertex2f(14, 43);
    glVertex2f(16, 43);
    glVertex2f(16, 32);
    glVertex2f(14, 32);
    glEnd();

//Tree-1 Leaf-1



    glBegin(GL_TRIANGLES);
    glColor3ub(78, 207, 33 ) ;
    glVertex2f(15, 50);
    glVertex2f(19, 43);
    glVertex2f(11, 43);
    glEnd();

//Tree-1 Leaf-2



    glBegin(GL_TRIANGLES);
    glColor3ub(78, 207, 33 ) ;
    glVertex2f(15, 45);
    glVertex2f(18, 40);
    glVertex2f(12, 40);
    glEnd();
}

///ID407
void Tree2()
{

    //Tree-2 Root
    glBegin(GL_POLYGON);
    glColor3ub(116, 80, 64  ) ;
    glVertex2f(44, 43);
    glVertex2f(46, 43);
    glVertex2f(46, 32);
    glVertex2f(44, 32);
    glEnd();

//Tree-2 Leaf-1


    glBegin(GL_TRIANGLES);
    glColor3ub(78, 207, 33 ) ;
    glVertex2f(45, 50);
    glVertex2f(49, 43);
    glVertex2f(41, 43);
    glEnd();

//Tree-2 Leaf-2


    glBegin(GL_TRIANGLES);
    glColor3ub(78, 207, 33 ) ;
    glVertex2f(45, 46);
    glVertex2f(48, 40);
    glVertex2f(42, 40);
    glEnd();
}

///ID408
void Tree4()
{

     //Tree-4 Root
    glBegin(GL_POLYGON);
    glColor3ub(116, 80, 64  ) ;
    glVertex2f(144, 43);
    glVertex2f(146, 43);
    glVertex2f(146, 32);
    glVertex2f(144, 32);
    glEnd();

//Tree-4 Leaf-1


    glBegin(GL_TRIANGLES);
    glColor3ub(78, 207, 33 ) ;
    glVertex2f(145, 50);
    glVertex2f(149, 43);
    glVertex2f(141, 43);
    glEnd();

//Tree-4 Leaf-2



    glBegin(GL_TRIANGLES);
    glColor3ub(78, 207, 33 ) ;
    glVertex2f(145, 45);
    glVertex2f(148, 40);
    glVertex2f(142, 40);
    glEnd();
}

///ID409
void Tree3()
{
    //Tree-3 Root
    glBegin(GL_POLYGON);
    glColor3ub(116, 80, 64  ) ;
    glVertex2f(98, 43);
    glVertex2f(100, 43);
    glVertex2f(100, 32);
    glVertex2f(98, 32);
    glEnd();


//Tree-3 Leaf-1


    glBegin(GL_TRIANGLES);
    glColor3ub(78, 207, 33 ) ;
    glVertex2f(99, 50);
    glVertex2f(103, 43);
    glVertex2f(95, 43);
    glEnd();

//Tree-3 Leaf-2


    glBegin(GL_TRIANGLES);
    glColor3ub(78, 207, 33 ) ;
    glVertex2f(99, 45);
    glVertex2f(96, 40);
    glVertex2f(102, 40);
    glEnd();
}

//Car-1 Wheel front and back
void circle1_300ft_300ft(float radius, float xc, float yc, float r, float g, float b)
{
    glBegin(GL_POLYGON);
    for(int i=0; i<200; i++)
    {
        glColor3f(0,0,0);
        float pi=3.1416;
        float A=(i*2*pi)/200;
        float r=radius;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x+xc,y+yc);
    }
    glEnd();
}

///ID410
void CAR_FULL(double r, double g, double b)
{
    glPushMatrix();
    glTranslatef(ft_car2_x, 0.0f, 0.0f);

    //Car-1 Roof

    glBegin(GL_POLYGON);
    glColor3ub(r, g, b  ) ;
    glVertex2f(36, 18);
    glVertex2f(44, 18);
    glVertex2f(46, 16);
    glVertex2f(34, 16);
    glEnd();

//Car-1 Body

    glBegin(GL_POLYGON);
    glVertex2f(32, 16);
    glVertex2f(48, 16);
    glVertex2f(48, 14);
    glVertex2f(32, 14);
    glEnd();

//Car-1 right door

    glBegin(GL_POLYGON);
    glColor3ub(218, 247, 166  ) ;
    glVertex2f(40, 17.5);
    glVertex2f(44, 17);
    glVertex2f(45, 16);
    glVertex2f(40, 16);
    glEnd();


//Car-1 Left door

    glBegin(GL_POLYGON);
    glColor3ub(218, 247, 166  ) ;
    glVertex2f(36, 17);
    glVertex2f(40, 17.5);
    glVertex2f(40, 16);
    glVertex2f(36, 16);
    glEnd();
//Car-1 left door border

    glLineWidth(2);
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0 ) ;
    glVertex2f(36, 17);
    glVertex2f(40, 17.5);
    glVertex2f(40, 16);
    glVertex2f(36, 16);
    glEnd();

//Car-1 Right Door Border

    glLineWidth(2);
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0  ) ;
    glVertex2f(40, 17.5);
    glVertex2f(44, 17);
    glVertex2f(45, 16);
    glVertex2f(40, 16);
    glEnd();


    circle1_300ft_300ft(1.437,33.556, 14, 1.0, 1.0, 1.0); //Car-1 Wheel back
    circle1_300ft_300ft(1.437,45.323, 14, 1.0, 1.0, 1.0); //Car-1 Wheel Front

    glPopMatrix();

}

///ID411
void Car_2(double r, double g, double b)
 {
     glPushMatrix();
    glTranslatef(ft_car2_x, 0.0f, 0.0f);

     glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(70.0f, 0.0f, 0.0f);

     CAR_FULL(r, g, b);

    glPopMatrix();  // Render now

    glPopMatrix();

 }


// Lamp-post -1 Circle
///ID439
void circle2_300ft(float radius, float xc, float yc, float r, float g, float b)
{
    glBegin(GL_POLYGON);
    for(int i=0; i<200; i++)
    {
     if(time300ft == FT_DAY)
        glColor3ub(255,255,255 );
    else
        glColor3ub(255, 243, 0);

        float pi=3.1416;
        float A=(i*2*pi)/200;
        float r=radius;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x+xc,y+yc);
    }
    glEnd();
}

///ID412
//Lamp-post- 1
void Lamp_post_1()
{


    glBegin(GL_POLYGON);
    glColor3ub(199, 0, 57 ) ;
    glVertex2f(135, 43);
    glVertex2f(136, 43);
    glVertex2f(136, 32);
    glVertex2f(135, 32);
    glEnd();

    //Lamp-post-1 stand


    circle2_300ft(2.00,133, 41.5, 1.0, 1.0, 1.0); //Lamp-post- 1 left light
    circle2_300ft(2.00,138, 41.5, 1.0, 1.0, 1.0);//Lamp-post- 1 right light
    circle2_300ft(2.00,135.5, 44.618, 1.0, 1.0, 1.0);//Lamp-post- 1 top light

}
///ID413
void Lamp_post_2()
 {
     glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(-25.0f, 0.0f, 0.0f);

     Lamp_post_1();///ID414
     glTranslatef(-30.0f, 0.0f, 0.0f);

     Lamp_post_1();///ID415
     glTranslatef(-50.0f, 0.0f, 0.0f);

     Lamp_post_1();///ID16

    glPopMatrix();  // Render now

 }
 //circle of traffic light Red
void circle9(float radius, float xc, float yc, float r, float g, float b)
{
    glBegin(GL_POLYGON);
    for(int i=0; i<200; i++)
    {
        glColor3ub(231, 11, 11);
        float pi=3.1416;
        float A=(i*2*pi)/200;
        float r=radius;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x+xc,y+yc);
    }
    glEnd();
}
 //circle of traffic light yellow
void circle1_300ft_300ft0(float radius, float xc, float yc, float r, float g, float b)
{
    glBegin(GL_POLYGON);
    for(int i=0; i<200; i++)
    {
        glColor3ub(255, 244, 11);
        float pi=3.1416;
        float A=(i*2*pi)/200;
        float r=radius;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x+xc,y+yc);
    }
    glEnd();
}

 //circle of traffic light green
void circle1_300ft_300ft1(float radius, float xc, float yc, float r, float g, float b)
{
    glBegin(GL_POLYGON);
    for(int i=0; i<200; i++)
    {
        glColor3ub(76, 217, 48 );
        float pi=3.1416;
        float A=(i*2*pi)/200;
        float r=radius;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x+xc,y+yc);
    }
    glEnd();
}

///ID417
 void Traffic_light(){

    //light stand
    glBegin(GL_POLYGON);
    glColor3ub(0,0,0 );
    glVertex2f(93, 40);
    glVertex2f(94, 40);
    glVertex2f(94, 32);
    glVertex2f(93, 32);
    glEnd();

    //light box
    glBegin(GL_POLYGON);
    glColor3ub(0,0,0 );
    glVertex2f(91, 40);
    glVertex2f(93, 40);
    glVertex2f(93, 35);
    glVertex2f(91, 35);
    glEnd();

    circle9(0.626,92.4194653871472, 38.9081896855175,1.0,1.0,1.0 );
    circle1_300ft_300ft0(0.626,92.4194653871472, 37.7296355417906,1.0,1.0,1.0 );
    circle1_300ft_300ft1(0.626,92.4194653871472, 36.3183740203471,1.0,1.0,1.0 );




 }

 ///ID418
void sky(){

    if(time300ft == FT_DAY)
        glColor3ub(87, 150, 231);
    else
        glColor4ub(37,20,40,255);

    glBegin(GL_POLYGON);
    glVertex2f(0,90);
    glVertex2f(160, 90);
    glVertex2f(160, 48);
    glVertex2f(0,48);
    glEnd();


 }

 ///ID419
 void building_ausis()
{
    // left piller

    glBegin(GL_POLYGON);
    glColor3ub(131,131,131 ) ;
    glVertex2f(0,70);
    glVertex2f(10, 70);
    glVertex2f(10, 48);
    glVertex2f(0,48);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0, 0, 0) ;
    glVertex2f(0,70);
    glVertex2f(10, 70);
    glVertex2f(10, 48);
    glVertex2f(0,48);
    glEnd();


    // 2nd floor

    glBegin(GL_POLYGON);
    glColor3ub(230, 182, 182) ;
    glVertex2f(10, 68);
    glVertex2f(26, 68);
    glVertex2f(26, 62);
    glVertex2f(10, 62);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0, 0, 0) ;
    glVertex2f(10, 68);
    glVertex2f(26, 68);
    glVertex2f(26, 62);
    glVertex2f(10, 62);
    glEnd();

    // 1st floor
    glBegin(GL_POLYGON);
    glColor3ub(230, 182, 182) ;
    glVertex2f(10, 62);
    glVertex2f(26, 62);
    glVertex2f(26, 56);
    glVertex2f(10, 56);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0, 0, 0) ;
    glVertex2f(10, 62);
    glVertex2f(26, 62);
    glVertex2f(26, 56);
    glVertex2f(10, 56);
    glEnd();

    // 2nd floor glass-1 left
    glBegin(GL_POLYGON);
    glColor3ub(75,89,98) ;
    glVertex2f(12, 66);
    glVertex2f(14, 66);
    glVertex2f(14, 64);
    glVertex2f(12, 64);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0 ) ;
    glVertex2f(12, 66);
    glVertex2f(14, 66);
    glVertex2f(14, 64);
    glVertex2f(12, 64);
    glEnd();

    // 2nd floor glass-2 left
    glBegin(GL_POLYGON);
    glColor3ub(75,89,98 ) ;
    glVertex2f(14, 66);
    glVertex2f(16, 66);
    glVertex2f(16, 64);
    glVertex2f(14, 64);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0 ) ;
    glVertex2f(14, 66);
    glVertex2f(16, 66);
    glVertex2f(16, 64);
    glVertex2f(14, 64);
    glEnd();

    // 2nd floor glass-3 left
    glBegin(GL_POLYGON);
    glColor3ub(75,89,98) ;
    glVertex2f(16, 66);
    glVertex2f(18, 66);
    glVertex2f(18, 64);
    glVertex2f(16, 64);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0 ) ;
    glVertex2f(16, 66);
    glVertex2f(18, 66);
    glVertex2f(18, 64);
    glVertex2f(16, 64);
    glEnd();

    // 2nd floor glass-4 left
    glBegin(GL_POLYGON);
    glColor3ub(75,89,98) ;
    glVertex2f(18, 66);
    glVertex2f(20, 66);
    glVertex2f(20, 64);
    glVertex2f(18, 64);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0 ) ;
    glVertex2f(18, 66);
    glVertex2f(20, 66);
    glVertex2f(20, 64);
    glVertex2f(18, 64);
    glEnd();

    // 2nd floor glass-5 left
    glBegin(GL_POLYGON);
    glColor3ub(75,89,98 ) ;
    glVertex2f(20, 66);
    glVertex2f(22, 66);
    glVertex2f(22, 64);
    glVertex2f(20, 64);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0 ) ;
    glVertex2f(20, 66);
    glVertex2f(22, 66);
    glVertex2f(22, 64);
    glVertex2f(20, 64);
    glEnd();

    // 2nd floor glass-6 left
    glBegin(GL_POLYGON);
    glColor3ub(75,89,98) ;
    glVertex2f(22, 66);
    glVertex2f(24, 66);
    glVertex2f(24, 64);
    glVertex2f(22, 64);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0 ) ;
    glVertex2f(22, 66);
    glVertex2f(24, 66);
    glVertex2f(24, 64);
    glVertex2f(22, 64);
    glEnd();

     // 1st floor glass-1 up
    glBegin(GL_POLYGON);
    glColor3ub(75,89,98) ;
    glVertex2f(11,61);
    glVertex2f(25, 61);
    glVertex2f(25, 59);
    glVertex2f(11, 59);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0 ) ;
    glVertex2f(11,61);
    glVertex2f(25, 61);
    glVertex2f(25, 59);
    glVertex2f(11, 59);
    glEnd();

    // 1st floor glass-2 low
    glBegin(GL_POLYGON);
    glColor3ub(75,89,98) ;
    glVertex2f(11, 58);
    glVertex2f(25, 58);
    glVertex2f(25, 57);
    glVertex2f(11, 57);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0 ) ;
    glVertex2f(11, 58);
    glVertex2f(25, 58);
    glVertex2f(25, 57);
    glVertex2f(11, 57);
    glEnd();

    // background ground
    glBegin(GL_POLYGON);
    glColor3ub(163,137,112) ;
    glVertex2f(10, 56);
    glVertex2f(26, 56);
    glVertex2f(26, 48);
    glVertex2f(10, 48);
    glEnd();



     // Ground Floor piller -1
    glBegin(GL_POLYGON);
    glColor3ub(140, 50, 50) ;
    glVertex2f(12, 56);
    glVertex2f(13, 56);
    glVertex2f(13, 48);
    glVertex2f(12, 48);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0) ;
    glVertex2f(12, 56);
    glVertex2f(13, 56);
    glVertex2f(13, 48);
    glVertex2f(12, 48);
    glEnd();

    //Ground gloor carpet
    glBegin(GL_POLYGON);
    glColor3ub(75,89,98) ;
    glVertex2f(13, 48);
    glVertex2f(16, 50);
    glVertex2f(20,50);
    glVertex2f(23, 48);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0) ;
    glVertex2f(13, 48);
    glVertex2f(16, 50);
    glVertex2f(20,50);
    glVertex2f(23, 48);
    glEnd();

     // Ground Floor piller -2
    glBegin(GL_POLYGON);
    glColor3ub(140, 50, 50) ;
    glVertex2f(16, 56);
    glVertex2f(17, 56);
    glVertex2f(17, 50);
    glVertex2f(16, 50);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0) ;
    glVertex2f(16, 56);
    glVertex2f(17, 56);
    glVertex2f(17, 50);
    glVertex2f(16, 50);
    glEnd();

     // Ground Floor piller -3
    glBegin(GL_POLYGON);
    glColor3ub(140, 50, 50) ;
    glVertex2f(19, 56);
    glVertex2f(20, 56);
    glVertex2f(20, 50);
    glVertex2f(19, 50);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0) ;
    glVertex2f(19, 56);
    glVertex2f(20, 56);
    glVertex2f(20, 50);
    glVertex2f(19, 50);
    glEnd();

    // Ground Floor piller -4
    glBegin(GL_POLYGON);
    glColor3ub(140, 50, 50) ;
    glVertex2f(23, 56);
    glVertex2f(24, 56);
    glVertex2f(24, 48);
    glVertex2f(23,48);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0) ;
    glVertex2f(23, 56);
    glVertex2f(24, 56);
    glVertex2f(24, 48);
    glVertex2f(23,48);
    glEnd();

    // Right piller
    glBegin(GL_POLYGON);
    glColor3ub(131,131,131) ;
    glVertex2f(26, 56);
    glVertex2f(32, 56);
    glVertex2f(32, 48);
    glVertex2f(26, 48);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0) ;
    glVertex2f(26, 56);
    glVertex2f(32, 56);
    glVertex2f(32, 48);
    glVertex2f(26, 48);
    glEnd();

    // Right piller door
    glBegin(GL_POLYGON);
    glColor3ub(75,89,98) ;
    glVertex2f(28, 52);
    glVertex2f(30, 52);
    glVertex2f(30, 48);
    glVertex2f(28, 48);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0) ;
    glVertex2f(28, 52);
    glVertex2f(30, 52);
    glVertex2f(30, 48);
    glVertex2f(28, 48);
    glEnd();

    // Right piller upper
    glBegin(GL_POLYGON);
    glColor3ub(131,131,131) ;
    glVertex2f(26, 70);
    glVertex2f(32, 70);
    glVertex2f(32, 56);
    glVertex2f(26, 56);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0) ;
    glVertex2f(26, 70);
    glVertex2f(32, 70);
    glVertex2f(32, 56);
    glVertex2f(26, 56);
    glEnd();

    glColor3ub(255, 255, 255);
    renderText300ft(2, 65, "AUSIS");


}

///ID420
void building_iccb(){


// front upper
    glBegin(GL_POLYGON);
    glColor3ub(132, 146, 150) ;
    glVertex2f(32, 62);
    glVertex2f(58, 62);
    glVertex2f(54, 60);
    glVertex2f(36, 60);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0) ;
    glVertex2f(32, 62);
    glVertex2f(58, 62);
    glVertex2f(54, 60);
    glVertex2f(36, 60);
    glEnd();

    // Left piller
    glBegin(GL_POLYGON);
    glColor3ub(132, 146, 150) ;
    glVertex2f(32, 62);
    glVertex2f(36, 60);
    glVertex2f(36, 48);
    glVertex2f(32, 48);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0) ;
    glVertex2f(32, 62);
    glVertex2f(36, 60);
    glVertex2f(36, 48);
    glVertex2f(32, 48);
    glEnd();

     // right piller
    glBegin(GL_POLYGON);
    glColor3ub(132, 146, 150) ;
    glVertex2f(54, 60);
    glVertex2f(58, 62);
    glVertex2f(58, 48);
    glVertex2f(54, 48);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0) ;
    glVertex2f(54, 60);
    glVertex2f(58, 62);
    glVertex2f(58, 48);
    glVertex2f(54, 48);
    glEnd();

    // ground background
    glBegin(GL_POLYGON);
    glColor3ub(218, 247, 166) ;
    glVertex2f(36, 60);
    glVertex2f(54, 60);
    glVertex2f(54, 48);
    glVertex2f(36, 48);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0) ;
    glVertex2f(36, 60);
    glVertex2f(54, 60);
    glVertex2f(54, 48);
    glVertex2f(36, 48);
    glEnd();

    // ground line -1
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0) ;
    glVertex2f(36, 58);
    glVertex2f(54, 58);
    glEnd();

    // ground line-2
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0) ;
    glVertex2f(36, 56);
    glVertex2f(54, 56);
    glEnd();

    // ground line-3
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0) ;
    glVertex2f(36, 54);
    glVertex2f(54, 54);
    glEnd();

    // ground line-4
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0) ;
    glVertex2f(36, 52);
    glVertex2f(54, 52);
    glEnd();

    // ground line-5
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0) ;
    glVertex2f(36, 50);
    glVertex2f(54, 50);
    glEnd();

     // ground Door
    glBegin(GL_POLYGON);
    glColor3ub(132, 146, 150) ;
    glVertex2f(40, 52);
    glVertex2f(50, 52);
    glVertex2f(50, 48);
    glVertex2f(40, 48);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0) ;
    glVertex2f(40, 52);
    glVertex2f(50, 52);
    glVertex2f(50, 48);
    glVertex2f(40, 48);
    glEnd();

    // ground line-1 horizontal
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0) ;
    glVertex2f(38, 60);
    glVertex2f(38, 48);
    glEnd();

    // ground line-2 horizontal
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0) ;
    glVertex2f(42, 60);
    glVertex2f(42, 52);
    glEnd();

    // ground line-3 horizontal
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0) ;
    glVertex2f(46, 60);
    glVertex2f(46, 52);
    glEnd();

    // ground line-4 horizontal
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0) ;
    glVertex2f(50, 60);
    glVertex2f(50, 52);
    glEnd();

    // ground line-5 horizontal
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0) ;
    glVertex2f(52, 60);
    glVertex2f(52, 48);
    glEnd();


    glColor3ub(255, 255, 255);
    renderText300ft(43, 60.2, "ICCB");



}

///ID421
void building_Eye_hospital(){

    // ground floor
    glBegin(GL_POLYGON);
    glColor3ub(132, 146, 150) ;
    glVertex2f(58, 64);
    glVertex2f(78, 64);
    glVertex2f(78, 48);
    glVertex2f(58, 48);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0) ;
    glVertex2f(58, 64);
    glVertex2f(78, 64);
    glVertex2f(78, 48);
    glVertex2f(58, 48);
    glEnd();

    // ground floor left side
    glBegin(GL_POLYGON);
    glColor3ub(232, 215, 35 ) ;
    glVertex2f(58, 60);
    glVertex2f(74, 60);
    glVertex2f(74, 48);
    glVertex2f(58, 48);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0) ;
    glVertex2f(58, 60);
    glVertex2f(74, 60);
    glVertex2f(74, 48);
    glVertex2f(58, 48);
    glEnd();

    // ground line-1 horizontal
     glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0) ;
    glVertex2f(58, 56);
    glVertex2f(74, 56);
    glEnd();

    // ground line-2 horizontal
     glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0) ;
    glVertex2f(58, 52);
    glVertex2f(74, 52);
    glEnd();

    // ground line-3 vartical
     glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0) ;
    glVertex2f(62, 60);
    glVertex2f(62, 48);
    glEnd();

    // ground line-4 vartical
     glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0) ;
    glVertex2f(66, 60);
    glVertex2f(66, 48);
    glEnd();


    // ground line-5 vartical
     glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0) ;
    glVertex2f(70, 60);
    glVertex2f(70, 48);
    glEnd();

    // ground floor Door
    glBegin(GL_POLYGON);
    glColor3ub(232, 215, 135 ) ;
    glVertex2f(62, 52);
    glVertex2f(70, 52);
    glVertex2f(70, 48);
    glVertex2f(62, 48);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0 ) ;
    glVertex2f(62, 52);
    glVertex2f(70, 52);
    glVertex2f(70, 48);
    glVertex2f(62, 48);
    glEnd();

    // top floor
    glBegin(GL_POLYGON);
    glColor3ub(199, 0, 57 ) ;
    glVertex2f(62, 80);
    glVertex2f(78, 80);
    glVertex2f(78, 64);
    glVertex2f(62, 64);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0 ) ;
    glVertex2f(62, 80);
    glVertex2f(78, 80);
    glVertex2f(78, 64);
    glVertex2f(62, 64);
    glEnd();

    // top floor window background
    glBegin(GL_POLYGON);
    glColor3ub(232, 215, 135 ) ;
    glVertex2f(64, 78);
    glVertex2f(76, 78);
    glVertex2f(76, 66);
    glVertex2f(64, 66);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0) ;
    glVertex2f(64, 78);
    glVertex2f(76, 78);
    glVertex2f(76, 66);
    glVertex2f(64, 66);
    glEnd();

     // top floor window line-1 horizontal
     glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0) ;
    glVertex2f(68, 78);
    glVertex2f(68, 66);
    glEnd();

    // top floor window line-2 horizontal
     glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0) ;
    glVertex2f(72, 78);
    glVertex2f(72, 66);
    glEnd();

    // top floor window line-3 horizontal
     glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0) ;
    glVertex2f(76, 78);
    glVertex2f(76, 66);
    glEnd();

    //window-1
    glBegin(GL_POLYGON);
    glColor3ub(240, 99, 46 ) ;
    glVertex2f(64, 76);
    glVertex2f(70, 76);
    glVertex2f(70, 72);
    glVertex2f(64, 72);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0) ;
    glVertex2f(64, 76);
    glVertex2f(70, 76);
    glVertex2f(70, 72);
    glVertex2f(64, 72);
    glEnd();

    //window-2
    glBegin(GL_POLYGON);
    glColor3ub(240, 99, 46 ) ;
    glVertex2f(70, 72);
    glVertex2f(76, 72);
    glVertex2f(76, 68);
    glVertex2f(70, 68);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0 ) ;
    glVertex2f(70, 72);
    glVertex2f(76, 72);
    glVertex2f(76, 68);
    glVertex2f(70, 68);
    glEnd();

    // top floor window line-1 vartical
     glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0) ;
    glVertex2f(64, 74);
    glVertex2f(76, 74);
    glEnd();

    // top floor window line-2 vartical
     glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0) ;
    glVertex2f(64, 70);
    glVertex2f(76, 70);
    glEnd();

     glColor3ub(255,255,0);
    renderText300ft(62, 61, " Eye Hospital");


}

///ID422
void bank(){

    // bank roof
    glBegin(GL_TRIANGLES);
    glColor3ub(199, 0, 57 ) ;
    glVertex2f(78, 64);
    glVertex2f(92, 70);
    glVertex2f(106, 64);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0 ) ;
    glVertex2f(78, 64);
    glVertex2f(92, 70);
    glVertex2f(106, 64);
    glEnd();

    //top cealing
    glBegin(GL_POLYGON);
    glColor3ub(225, 141, 165 ) ;
    glVertex2f(78, 64);
    glVertex2f(106, 64);
    glVertex2f(104, 62);
    glVertex2f(80, 62);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0 ) ;
    glVertex2f(78, 64);
    glVertex2f(106, 64);
    glVertex2f(104, 62);
    glVertex2f(80, 62);
    glEnd();

    //left cealing
    glBegin(GL_POLYGON);
    glColor3ub(225, 141, 165 ) ;
    glVertex2f(78, 64);
    glVertex2f(80, 62);
    glVertex2f(80, 48);
    glVertex2f(78, 48);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0 ) ;
    glVertex2f(78, 64);
    glVertex2f(80, 62);
    glVertex2f(80, 48);
    glVertex2f(78, 48);
    glEnd();

    //right cealing
    glBegin(GL_POLYGON);
    glColor3ub(225, 141, 165 ) ;
    glVertex2f(104, 62);
    glVertex2f(106, 64);
    glVertex2f(106, 48);
    glVertex2f(104, 48);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0) ;
    glVertex2f(104, 62);
    glVertex2f(106, 64);
    glVertex2f(106, 48);
    glVertex2f(104, 48);
    glEnd();

    //ground background
    glBegin(GL_POLYGON);
    glColor3ub(252, 186, 3) ;
    glVertex2f(80, 62);
    glVertex2f(104, 62);
    glVertex2f(104, 48);
    glVertex2f(80, 48);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0) ;
    glVertex2f(80, 62);
    glVertex2f(104, 62);
    glVertex2f(104, 48);
    glVertex2f(80, 48);
    glEnd();

     //ground piller-1 up
    glBegin(GL_POLYGON);
    glColor3ub(121, 109, 127) ;
    glVertex2f(86, 62);
    glVertex2f(90, 62);
    glVertex2f(90, 60);
    glVertex2f(86, 60);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0) ;
    glVertex2f(86, 62);
    glVertex2f(90, 62);
    glVertex2f(90, 60);
    glVertex2f(86, 60);
    glEnd();

    //ground piller-1 down
    glBegin(GL_POLYGON);
    glColor3ub(121, 109, 127) ;
    glVertex2f(86, 50);
    glVertex2f(90, 50);
    glVertex2f(90, 48);
    glVertex2f(86, 48);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0) ;
    glVertex2f(86, 50);
    glVertex2f(90, 50);
    glVertex2f(90, 48);
    glVertex2f(86, 48);
    glEnd();

    // piller -1
    glBegin(GL_POLYGON);
    glColor3ub(121, 109, 127) ;
    glVertex2f(87, 60);
    glVertex2f(89, 60);
    glVertex2f(89, 50);
    glVertex2f(87, 50);
    glEnd();
     glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0) ;
    glVertex2f(87, 60);
    glVertex2f(89, 60);
    glVertex2f(89, 50);
    glVertex2f(87, 50);
    glEnd();

        //ground piller-2 up
    glBegin(GL_POLYGON);
    glColor3ub(121, 109, 127) ;
    glVertex2f(94, 62);
    glVertex2f(98, 62);
    glVertex2f(98, 60);
    glVertex2f(94, 60);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0) ;
    glVertex2f(94, 62);
    glVertex2f(98, 62);
    glVertex2f(98, 60);
    glVertex2f(94, 60);
    glEnd();

      //ground piller-2 down
    glBegin(GL_POLYGON);
    glColor3ub(121, 109, 127) ;
    glVertex2f(94, 50);
    glVertex2f(98, 50);
    glVertex2f(98, 48);
    glVertex2f(94, 48);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0) ;
    glVertex2f(94, 50);
    glVertex2f(98, 50);
    glVertex2f(98, 48);
    glVertex2f(94, 48);
    glEnd();

     //ground piller-2
    glBegin(GL_POLYGON);
    glColor3ub(121, 109, 127) ;
    glVertex2f(95, 60);
    glVertex2f(97, 60);
    glVertex2f(97, 50);
    glVertex2f(95, 50);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0) ;
    glVertex2f(95, 60);
    glVertex2f(97, 60);
    glVertex2f(97, 50);
    glVertex2f(95, 50);
    glEnd();

    //ground door
    glBegin(GL_POLYGON);
    glColor3ub(121, 109, 127) ;
    glVertex2f(91, 55);
    glVertex2f(93, 55);
    glVertex2f(93, 48);
    glVertex2f(91, 48);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0) ;
    glVertex2f(91, 55);
    glVertex2f(93, 55);
    glVertex2f(93, 48);
    glVertex2f(91, 48);
    glEnd();

     //window-1
    glBegin(GL_POLYGON);
    glColor3ub(121, 109, 127) ;
    glVertex2f(81, 60);
    glVertex2f(85, 60);
    glVertex2f(85, 56);
    glVertex2f(81, 56);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0) ;
    glVertex2f(81, 60);
    glVertex2f(85, 60);
    glVertex2f(85, 56);
    glVertex2f(81, 56);
    glEnd();

    //window-2
    glBegin(GL_POLYGON);
    glColor3ub(121, 109, 127) ;
    glVertex2f(81, 54);
    glVertex2f(85, 54);
    glVertex2f(85, 50);
    glVertex2f(81, 50);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0) ;
    glVertex2f(81, 54);
    glVertex2f(85, 54);
    glVertex2f(85, 50);
    glVertex2f(81, 50);
    glEnd();

    //window-3
    glBegin(GL_POLYGON);
    glColor3ub(121, 109, 127) ;
    glVertex2f(99, 60);
    glVertex2f(103, 60);
    glVertex2f(103, 56);
    glVertex2f(99, 56);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0) ;
    glVertex2f(99, 60);
    glVertex2f(103, 60);
    glVertex2f(103, 56);
    glVertex2f(99, 56);
    glEnd();

    //window-4
    glBegin(GL_POLYGON);
    glColor3ub(121, 109, 127) ;
    glVertex2f(99, 54);
    glVertex2f(103, 54);
    glVertex2f(103, 50);
    glVertex2f(99, 50);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0) ;
    glVertex2f(99, 54);
    glVertex2f(103, 54);
    glVertex2f(103, 50);
    glVertex2f(99, 50);
    glEnd();

     glColor3ub(255,255,255);
    renderText300ft(82, 62.5, "BASUNDHARA BANK");

}

///ID423
void commercial_building(){

    //side building
    glBegin(GL_POLYGON);
    glColor3ub(89, 112, 167 ) ;
    glVertex2f(106, 68);
    glVertex2f(116, 68);
    glVertex2f(116, 48);
    glVertex2f(106, 48);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0) ;
    glVertex2f(106, 68);
    glVertex2f(116, 68);
    glVertex2f(116, 48);
    glVertex2f(106, 48);
    glEnd();

    //side building roof
    glBegin(GL_POLYGON);
    glColor3ub(89, 112, 167 ) ;
    glVertex2f(106, 68);
    glVertex2f(104, 68);
    glVertex2f(104, 70);
    glVertex2f(118, 70);
    glVertex2f(118, 68);
    glVertex2f(116, 68);
    glEnd();
     glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0) ;
    glVertex2f(106, 68);
    glVertex2f(104, 68);
    glVertex2f(104, 70);
    glVertex2f(118, 70);
    glVertex2f(118, 68);
    glVertex2f(116, 68);
    glEnd();

     //side building glass
    glBegin(GL_POLYGON);
    glColor3ub(152, 172, 221  ) ;
    glVertex2f(108, 66);
    glVertex2f(114, 66);
    glVertex2f(114, 50);
    glVertex2f(108, 50);
    glEnd();
     glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0 ) ;
    glVertex2f(108, 66);
    glVertex2f(114, 66);
    glVertex2f(114, 50);
    glVertex2f(108, 50);
    glEnd();

    //glass line-1
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0 ) ;
    glVertex2f(108, 62);
    glVertex2f(114, 62);
    glEnd();

    //glass line-2
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0 ) ;
    glVertex2f(108, 58);
    glVertex2f(114, 58);
    glEnd();

    //glass line-3
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0 ) ;
    glVertex2f(108, 54);
    glVertex2f(114, 54);
    glEnd();

    //glass line-4 horizontal
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0 ) ;
    glVertex2f(111, 66);
    glVertex2f(111, 50);
    glEnd();

    //main building
    glBegin(GL_POLYGON);
    glColor3ub(31, 62, 140 ) ;
    glVertex2f(116, 66);
    glVertex2f(132, 66);
    glVertex2f(132, 48);
    glVertex2f(116, 48);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0 ) ;
    glVertex2f(116, 66);
    glVertex2f(132, 66);
    glVertex2f(132, 48);
    glVertex2f(116, 48);
    glEnd();

    //main building glass-1
    glBegin(GL_POLYGON);
    glColor3ub(152, 172, 221 ) ;
    glVertex2f(118, 64);
    glVertex2f(130, 64);
    glVertex2f(130, 60);
    glVertex2f(118, 60);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0) ;
    glVertex2f(118, 64);
    glVertex2f(130, 64);
    glVertex2f(130, 60);
    glVertex2f(118, 60);
    glEnd();

    //main building glass-2
    glBegin(GL_POLYGON);
    glColor3ub(152, 172, 221 ) ;
    glVertex2f(118, 58);
    glVertex2f(130, 58);
    glVertex2f(130, 54);
    glVertex2f(118, 54);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0 ) ;
    glVertex2f(118, 58);
    glVertex2f(130, 58);
    glVertex2f(130, 54);
    glVertex2f(118, 54);
    glEnd();

     //glass line-1 upper
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0 ) ;
    glVertex2f(118, 62);
    glVertex2f(130, 62);
    glEnd();

     //glass line-2 upper
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0 ) ;
    glVertex2f(118, 56);
    glVertex2f(130, 56);
    glEnd();

    // door
    glBegin(GL_POLYGON);
    glColor3ub(152, 172, 221 ) ;
    glVertex2f(122, 52);
    glVertex2f(126, 52);
    glVertex2f(126, 48);
    glVertex2f(122, 48);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0 ) ;
    glVertex2f(122, 52);
    glVertex2f(126, 52);
    glVertex2f(126, 48);
    glVertex2f(122, 48);
    glEnd();

    glColor3ub(255,255,255);
    renderText300ft(140, 73, "RUPAYAN ");

}

///ID424
void office(){

    //office background
    glBegin(GL_POLYGON);
    glColor3ub(152, 172, 221 ) ;
    glVertex2f(132, 76);
    glVertex2f(160, 76);
    glVertex2f(160, 48);
    glVertex2f(132, 48);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0 ) ;
    glVertex2f(132, 76);
    glVertex2f(160, 76);
    glVertex2f(160, 48);
    glVertex2f(132, 48);
    glEnd();

     //window-1
    glBegin(GL_POLYGON);
    glColor3ub(152, 172, 21 ) ;
    glVertex2f(134, 72);
    glVertex2f(140, 72);
    glVertex2f(140, 66);
    glVertex2f(134, 66);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0 ) ;
    glVertex2f(134, 72);
    glVertex2f(140, 72);
    glVertex2f(140, 66);
    glVertex2f(134, 66);
    glEnd();

     //window-2
    glBegin(GL_POLYGON);
    glColor3ub(152, 172, 21 ) ;
    glVertex2f(142, 72);
    glVertex2f(148, 72);
    glVertex2f(148, 66);
    glVertex2f(142, 66);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0 ) ;
    glVertex2f(142, 72);
    glVertex2f(148, 72);
    glVertex2f(148, 66);
    glVertex2f(142, 66);
    glEnd();

      //window-3
    glBegin(GL_POLYGON);
    glColor3ub(152, 172, 21 ) ;
    glVertex2f(150, 72);
    glVertex2f(156, 72);
    glVertex2f(156, 66);
    glVertex2f(150, 66);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0) ;
    glVertex2f(150, 72);
    glVertex2f(156, 72);
    glVertex2f(156, 66);
    glVertex2f(150, 66);
    glEnd();

     //glass line-1 upper
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0 ) ;
    glVertex2f(134, 69);
    glVertex2f(140, 69);
    glEnd();

      //glass line-2 upper
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0 ) ;
    glVertex2f(142, 69);
    glVertex2f(148, 69);
    glEnd();

     //glass line-3 upper
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0 ) ;
    glVertex2f(150, 69);
    glVertex2f(156, 69);
    glEnd();

      //varanda
    glBegin(GL_POLYGON);
    glColor3ub(152, 172, 21 ) ;
    glVertex2f(134, 62);
    glVertex2f(156, 62);
    glVertex2f(156, 54);
    glVertex2f(134, 54);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0) ;
    glVertex2f(134, 62);
    glVertex2f(156, 62);
    glVertex2f(156, 54);
    glVertex2f(134, 54);
    glEnd();

    //glass line-1 lower
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0 ) ;
    glVertex2f(140, 62);
    glVertex2f(140, 54);
    glEnd();

    //glass line-2 lower
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0 ) ;
    glVertex2f(148, 62);
    glVertex2f(148, 54);
    glEnd();

    //Door
    glBegin(GL_POLYGON);
    glColor3ub(152, 172, 21 ) ;
    glVertex2f(140, 48);
    glVertex2f(140, 52);
    glVertex2f(148, 52);
    glVertex2f(148, 48);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0 ) ;
    glVertex2f(140, 48);
    glVertex2f(140, 52);
    glVertex2f(148, 52);
    glVertex2f(148, 48);
    glEnd();


}

// cloud Circle
void circle3(float radius, float xc, float yc, float r, float g, float b)
{
    glBegin(GL_POLYGON);
    for(int i=0; i<200; i++)
    {
        glColor3f(194, 68, 205 );
        float pi=3.1416;
        float A=(i*2*pi)/200;
        float r=radius;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x+xc,y+yc);
    }
    glEnd();
}

///ID425
void cloud(){

    glPushMatrix();
    glTranslatef(ft_Cloud_x, 0.0f, 0.0f);

    circle3(5.86,10.313, 82.598, 1.0, 1.0, 1.0); // cloud-1
    circle3(5.62,25.288, 82.645, 1.0, 1.0, 1.0); //cloud-2
    circle3(5.50,18,84, 1.0, 1.0, 1.0); // cloud-3
    circle3(5.65,17.229, 77.829, 1.0, 1.0, 1.0); // cloud-4
    circle3(5.60,92.512, 80.995, 1.0, 1.0, 1.0); // cloud-5
    circle3(5.68,108.50, 80.467, 1.0, 1.0, 1.0); // cloud-6
    circle3(5.59,99.377, 84.233, 1.0, 1.0, 1.0); // cloud-7
    circle3(5.63,99.266, 77.450, 1.0, 1.0, 1.0); // cloud-8

    glPopMatrix();

}
// sun Circle
void circle4(float radius, float xc, float yc, float r, float g, float b)
{
    glBegin(GL_POLYGON);
    for(int i=0; i<200; i++)
    {
        if(time300ft == FT_DAY)
        glColor3ub(255, 243, 0 );
    else
        glColor4ub(255,255,255,255);

        float pi=3.1416;
        float A=(i*2*pi)/200;
        float r=radius;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x+xc,y+yc);
    }
    glEnd();
}

///ID426
void Sun(){



    circle4(7.061,47.181, 77.676, 1.0, 1.0, 0.0);



}

// bus wheel
void circle5(float radius, float xc, float yc, float r, float g, float b)
{
    glBegin(GL_POLYGON);
    for(int i=0; i<200; i++)
    {
        glColor3f( 0,0,0);
        float pi=3.1416;
        float A=(i*2*pi)/200;
        float r=radius;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x+xc,y+yc);
    }
    glEnd();
}

///ID427
void Bus_300ft(){

   glPushMatrix();
    glTranslatef(ft_Bus_x, 0.0f, 0.0f);

  //bus body
    glBegin(GL_POLYGON);
    glColor3ub(249, 27, 4  ) ;
    glVertex2f(54, 38);
    glVertex2f(54, 42);
    glVertex2f(56, 43);
    glVertex2f(75, 43);
    glVertex2f(76, 42);
    glVertex2f(76, 38);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0 ) ;
    glVertex2f(54, 38);
    glVertex2f(54, 42);
    glVertex2f(56, 43);
    glVertex2f(75, 43);
    glVertex2f(76, 42);
    glVertex2f(76, 38);
    glEnd();

    //bus glass side
     glBegin(GL_POLYGON);
    glColor3ub(0,0,0 ) ;
    glVertex2f(54.5, 40);
    glVertex2f(56, 42.5);
    glVertex2f(74.5, 42.5);
    glVertex2f(75.5, 41);
    glVertex2f(75.5, 40);
    glEnd();

    //glass line-1
    glBegin(GL_LINE_LOOP);
    glColor3ub(214, 197, 195) ;
    glVertex2f(58, 42.5);
    glVertex2f(58, 40);
    glEnd();

    //glass line-2
    glBegin(GL_LINE_LOOP);
    glColor3ub(214, 197, 195) ;
    glVertex2f(60, 42.5);
    glVertex2f(60, 40);
    glEnd();

    //glass line-3
    glBegin(GL_LINE_LOOP);
    glColor3ub(214, 197, 195) ;
    glVertex2f(62, 42.5);
    glVertex2f(62, 40);
    glEnd();

    //glass line-4
    glBegin(GL_LINE_LOOP);
    glColor3ub(214, 197, 195) ;
    glVertex2f(64, 42.5);
    glVertex2f(64, 40);
    glEnd();

    //glass line-5
    glBegin(GL_LINE_LOOP);
    glColor3ub(214, 197, 195) ;
    glVertex2f(66, 42.5);
    glVertex2f(66, 40);
    glEnd();

     //glass line-6
    glBegin(GL_LINE_LOOP);
    glColor3ub(214, 197, 195) ;
    glVertex2f(68, 42.5);
    glVertex2f(68, 40);
    glEnd();

    //glass line-7
    glBegin(GL_LINE_LOOP);
    glColor3ub(214, 197, 195) ;
    glVertex2f(70, 42.5);
    glVertex2f(70, 40);
    glEnd();

    //glass line-8
    glBegin(GL_LINE_LOOP);
    glColor3ub(214, 197, 195) ;
    glVertex2f(72, 42.5);
    glVertex2f(72, 40);
    glEnd();

    //glass line-9
    glBegin(GL_LINE_LOOP);
    glColor3ub(214, 197, 195) ;
    glVertex2f(72, 41);
    glVertex2f(75.5, 41);
    glEnd();

     //box for product
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0) ;
    glVertex2f(62, 38);
    glVertex2f(62, 39);
    glVertex2f(64, 39);
    glVertex2f(64, 38);
    glEnd();

    //box for product
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0) ;
    glVertex2f(64, 38);
    glVertex2f(64, 39);
    glVertex2f(67, 39);
    glVertex2f(67, 38);
    glEnd();

     circle5(1.40,58.57, 38.001, 1.0, 1.0, 1.0); // back wheel
     circle5(1.40,71,38, 1.0, 1.0, 1.0); // front wheel

     glPopMatrix();


}
// plane window circle
void circle6(float radius, float xc, float yc, float r, float g, float b)
{
    glBegin(GL_POLYGON);
    for(int i=0; i<200; i++)
    {
        glColor3f( 0,0,0);
        float pi=3.1416;
        float A=(i*2*pi)/200;
        float r=radius;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x+xc,y+yc);
    }
    glEnd();
}
///ID428
void Plane(){

glPushMatrix();
    glTranslatef(ft_plane_x, 0.0f, 0.0f);

  //plane body
    glBegin(GL_POLYGON);
    glColor3ub(246, 239, 230 ) ;
    glVertex2f(121, 83);
    glVertex2f(125, 85);
    glVertex2f(146, 85);
    glVertex2f(151, 84);
    glVertex2f(155, 83);
    glVertex2f(151, 81);
    glVertex2f(146, 80);
    glVertex2f(125, 80);
    glVertex2f(121, 81);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0 ) ;
    glVertex2f(121, 83);
    glVertex2f(125, 85);
    glVertex2f(146, 85);
    glVertex2f(151, 84);
    glVertex2f(155, 83);
    glVertex2f(151, 81);
    glVertex2f(146, 80);
    glVertex2f(125, 80);
    glVertex2f(121, 81);
    glEnd();

    //plane back
    glBegin(GL_POLYGON);
    glColor3ub(249, 27, 4  ) ;
    glVertex2f(146, 85);
    glVertex2f(148, 88);
    glVertex2f(149, 89);
    glVertex2f(153, 89);
    glVertex2f(151, 84);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0 ) ;
    glVertex2f(146, 85);
    glVertex2f(148, 88);
    glVertex2f(149, 89);
    glVertex2f(153, 89);
    glVertex2f(151, 84);
    glEnd();

    //plane pilot window
    glBegin(GL_POLYGON);
    glColor3ub(249, 27, 4  ) ;
    glVertex2f(121, 82);
    glVertex2f(124, 84);
    glVertex2f(128, 84);
    glVertex2f(128, 82);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0  ) ;
    glVertex2f(121, 82);
    glVertex2f(124, 84);
    glVertex2f(128, 84);
    glVertex2f(128, 82);
    glEnd();

    //plane wing
    glBegin(GL_POLYGON);
    glColor3ub(249, 27, 4  ) ;
    glVertex2f(134, 78);
    glVertex2f(128, 81);
    glVertex2f(135, 81);
    glVertex2f(138, 78);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0  ) ;
    glVertex2f(134, 78);
    glVertex2f(128, 81);
    glVertex2f(135, 81);
    glVertex2f(138, 78);
    glEnd();

        circle6(1.09,133.63, 83.24, 1.0, 1.0, 1.0); // glass-1
        circle6(1.09,137.6803018211402, 83.24, 1.0, 1.0, 1.0); // glass-2
        circle6(1.09,141.6682422717561, 83.24, 1.0, 1.0, 1.0); // glass-3
        circle6(1.09,145.7602159515186, 83.24, 1.0, 1.0, 1.0); // glass-4
        circle6(1.09,129.82, 83.24, 1.0, 1.0, 1.0); // glass-5

        glPopMatrix();


}
// truck wheel circle
void circle7(float radius, float xc, float yc, float r, float g, float b)
{
    glBegin(GL_POLYGON);
    for(int i=0; i<200; i++)
    {
        glColor3f( 0,0,0);
        float pi=3.1416;
        float A=(i*2*pi)/200;
        float r=radius;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x+xc,y+yc);
    }
    glEnd();
}
///ID429
void Truck(){

    glPushMatrix();
    glTranslatef(ft_Truck_x, 0.0f, 0.0f);

 //truck body
    glBegin(GL_POLYGON);
    glColor3ub(249, 27, 4  ) ;
    glVertex2f(46, 28);
    glVertex2f(52, 28);
    glVertex2f(52, 22);
    glVertex2f(44, 22);
    glVertex2f(44, 24);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0 ) ;
    glVertex2f(46, 28);
    glVertex2f(52, 28);
    glVertex2f(52, 22);
    glVertex2f(44, 22);
    glVertex2f(44, 24);
    glEnd();

    //truck back carrier
    glBegin(GL_POLYGON);
    glColor3ub(25, 104, 217 ) ;
    glVertex2f(53, 28);
    glVertex2f(64, 28);
    glVertex2f(64, 22);
    glVertex2f(53, 22);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0 ) ;
    glVertex2f(53, 28);
    glVertex2f(64, 28);
    glVertex2f(64, 22);
    glVertex2f(53, 22);
    glEnd();

    glLineWidth(2);
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0 ) ;
    glVertex2f(52, 22);
    glVertex2f(53, 22);
    glEnd();

    //front glass
    glBegin(GL_POLYGON);
    glColor3ub(25, 104, 217 ) ;
    glVertex2f(45, 25);
    glVertex2f(47, 28);
    glVertex2f(51, 28);
    glVertex2f(51, 25);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0 ) ;
    glVertex2f(45, 25);
    glVertex2f(47, 28);
    glVertex2f(51, 28);
    glVertex2f(51, 25);
    glEnd();

    circle7(1.40,48, 22, 1.0, 1.0, 1.0); // front wheel
    circle7(1.40,59.6797157488301, 22, 1.0, 1.0, 1.0); // front wheel

    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0 ) ;
    glVertex2f(53, 28);
    glVertex2f(53, 22);
    glEnd();

    glPopMatrix();

}
// car_3 wheel circle
void circle8(float radius, float xc, float yc, float r, float g, float b)
{
    glBegin(GL_POLYGON);
    for(int i=0; i<200; i++)
    {
        glColor3f( 0,0,0);
        float pi=3.1416;
        float A=(i*2*pi)/200;
        float r=radius;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x+xc,y+yc);
    }
    glEnd();

}

///ID430
void car_3(){

      glPushMatrix();
    glTranslatef(ft_car3_x, 0.0f, 0.0f);

    //car body
    glBegin(GL_POLYGON);
    glColor3ub(25, 104, 217 ) ;
    glVertex2f(120, 22);
    glVertex2f(120,24);
    glVertex2f(121,26);
    glVertex2f(124, 26);
    glVertex2f(126, 28);
    glVertex2f(136, 28);
    glVertex2f(138, 26);
    glVertex2f(140, 26);
    glVertex2f(140, 22);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0 ) ;
    glVertex2f(120, 22);
    glVertex2f(120,24);
    glVertex2f(121,26);
    glVertex2f(124, 26);
    glVertex2f(126, 28);
    glVertex2f(136, 28);
    glVertex2f(138, 26);
    glVertex2f(140, 26);
    glVertex2f(140, 22);
    glEnd();

    //car door
    glBegin(GL_POLYGON);
    glColor3ub(25, 104, 88 ) ;
    glVertex2f(125, 26);
    glVertex2f(126.6, 27.8);
    glVertex2f(131, 27.8);
    glVertex2f(131, 26);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0 ) ;
    glVertex2f(125, 26);
    glVertex2f(126.6, 27.8);
    glVertex2f(131, 27.8);
    glVertex2f(131, 26);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(25, 104, 88 ) ;
    glVertex2f(131, 27.8);
    glVertex2f(135.6, 27.8);
    glVertex2f(137.5, 26);
    glVertex2f(131, 26);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0 ) ;
    glVertex2f(131, 27.8);
    glVertex2f(135.6, 27.8);
    glVertex2f(137.5, 26);
    glVertex2f(131, 26);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0 ) ;
    glVertex2f(125, 26);
    glVertex2f(137.5, 26);
    glVertex2f(137.5, 23);
    glVertex2f(125, 23);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0 ) ;
    glVertex2f(131, 26);
    glVertex2f(131, 23);
    glEnd();

     circle7(1.60,123.4992587968514, 23.0475727516139, 1.0, 1.0, 1.0);//front wheel
     circle7(1.60,136.6266017237032, 23.0031471449257, 1.0, 1.0, 1.0);// back wheel

    glPopMatrix();

}

///ID431
/*void Boat(){

     glPushMatrix();
    glTranslatef(Boat_x, 0.0f, 0.0f);
    //boat body
    glBegin(GL_POLYGON);
    glColor3ub(199, 154, 57  ) ;
    glVertex2f(56, 4);
    glVertex2f(70, 4);
    glVertex2f(74, 6);
    glVertex2f(70, 2);
    glVertex2f(56, 2);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0) ;
    glVertex2f(56, 4);
    glVertex2f(70, 4);
    glVertex2f(74, 6);
    glVertex2f(70, 2);
    glVertex2f(56, 2);
    glEnd();

    // boat upper part
    glBegin(GL_POLYGON);
    glColor3ub(217, 48, 225 ) ;
    glVertex2f(64, 4);
    glVertex2f(67, 7);
    glVertex2f(70,7);
    glVertex2f(70, 4);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0 ) ;
    glVertex2f(64, 4);
    glVertex2f(67, 7);
    glVertex2f(70,7);
    glVertex2f(70, 4);
    glEnd();

    //boat window
    glBegin(GL_POLYGON);
    glColor3ub(48, 212, 225 ) ;
    glVertex2f(66, 6);
    glVertex2f(68, 6);
    glVertex2f(68, 4);
    glVertex2f(65, 4);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub( 0,0,0) ;
    glVertex2f(66, 6);
    glVertex2f(68, 6);
    glVertex2f(68, 4);
    glVertex2f(65, 4);
    glEnd();

    glPopMatrix();



}
*/

void draw300ftScene()
{



    Garden();

    Road1();

    Road2();


    Road3();

    Footpath();


    underlake();
   // Boat();
    Tree();

    CAR_FULL(155, 20, 50);//left car road-2

    Car_2(55, 20, 250);// right car road-2
    Bus();

    Lamp_post_1();//right side lamp post-1
    Lamp_post_2();// right side lamp post-2

    sky();

    cloud();

    building_ausis();

    building_iccb();

    building_Eye_hospital();

    bank();

    office();
    commercial_building();

    Sun();

    Tree1();
    Tree2();
    Tree3();
    Tree4();
    Traffic_light();

    Plane();

    car_3();

    Truck();






    glFlush();


}

void update300ft(int value)
{


    // update300ft300ft the car full and car -2 position
    ///ID431

    ft_CAR_FULL_x += ft_CAR_FULL_speed;

    if (ft_CAR_FULL_x >  200.0f) {
        ft_CAR_FULL_x = -20;
    }

     ///ID432
    ft_car2_x += ft_car2_speed;

    if (ft_car2_x > 150.0f) {
        ft_car2_x = -70;
    }
    ///ID433
    // update300ft300ft the car-3 position and speed
    ft_car3_x -= ft_car3_speed;

    if (ft_car3_x < -150.0f) {
        ft_car3_x = 10;
    }

    // update300ft300ft the Bus position and speed
    ///ID434
    ft_Bus_x += ft_Bus_speed;

    if (ft_Bus_x > 150.0f) {
        ft_Bus_x = -70;
    }
    ///ID435
    ft_Truck_x -= ft_Truck_speed;

    if (ft_Truck_x < -160.0f) {
        ft_Truck_x = 120;
    }
    ///ID440
    /*Boat_x += Boat_speed;

    if (Boat_x > 150.0f) {
        Boat_x = -100;
    }
/*
    Cloud_x += Cloud_speed;

    if (Cloud_x >  180.0f) {
        Cloud_x = -10;
    }
*/
    ///ID436
    ft_plane_x-=0.2;

// update300ft300ft cloud position if it's moving
    ///ID437
    if (ft_cloud_moving) {
        ft_Cloud_x += ft_Cloud_speed;
        if (ft_Cloud_x > 170.0f) {
            ft_Cloud_x = -10.0f; // Reset to the left side
        }
    }

    glutPostRedisplay();       // Trigger display function
    }

void handleKeypress300ft(unsigned char key, int x, int y) {
    if (key == 'n') time300ft = FT_NIGHT;
    else if (key == 'd') time300ft = FT_DAY;
    glutPostRedisplay();
}

void handleMouse300ft(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        if (button == GLUT_LEFT_BUTTON) {
            ft_CAR_FULL_speed *= 1.2f;
            ft_Bus_speed *= 1.2f;
            ft_Truck_speed *= 1.2f;
            ft_Cloud_speed *= 1.2f;
        } else if (button == GLUT_RIGHT_BUTTON) {
            ft_CAR_FULL_speed *= 0.8f;
            ft_Bus_speed *= 0.8f;
            ft_Truck_speed *= 0.8f;
            ft_Cloud_speed *= 0.8f;
        }
    }
}



// ========================= main() =========================

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Merged: Airport + Uttara (OpenGL/GLUT)");

    initUnified();

    glutDisplayFunc(displayUnified);
    glutKeyboardFunc(handleKeypressUnified);
    glutMouseFunc(handleMouseUnified);
    glutTimerFunc(0, updateUnified, 0);

    glutMainLoop();
    return 0;
}
