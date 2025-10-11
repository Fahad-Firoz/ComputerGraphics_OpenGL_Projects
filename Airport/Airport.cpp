#include <GL/glut.h>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <vector>
#define PI 3.1416

using namespace std;

// Global variable to track the current scene (0 to 3)
int currentScene = 0;

// Function prototypes for the scenes
void initializeRaindrops(int count);

bool plane_moving = true;


float bus_position = 0.0f, car_position = 0.0f;
float bus_speed = 0.1f, car_speed = 0.1f;

float plane_4_pos = 0.0f, plane_5_pos = 0.0f;

bool bus_moving = true;
bool car_moving = true;

float _angle1 = 0.0f;

float sun_position = -18.0f;

float grass_movement = 0.0f;

// Enum for weather states
enum WeatherState { SUNNY, OVERCAST, RAINY };
WeatherState currentWeather = SUNNY;

float plane_x_1 = 0.0f, plane_y_1 = 0.0f;

struct Raindrop
{
    float x, y; // Position
    float speed; // Speed of falling
};

std::vector<Raindrop> raindrops;

// Initialize raindrops
void initializeRaindrops(int count)
{
    raindrops.clear();
    for (int i = 0; i < count; i++)
    {
        Raindrop drop;
        drop.x = static_cast<float>(rand() % 160);
        drop.y = static_cast<float>(rand() % 90 + 90);
        drop.speed = static_cast<float>((rand() % 10 + 12) * 0.1);
        raindrops.push_back(drop);
    }
}

// Draw raindrops
void drawRaindrops()
{
    glColor3f(1.0f, 1.0f, 1.0f); // White color for raindrops
    glLineWidth(1.5);

    glBegin(GL_LINES);
    for (std::vector<Raindrop>::const_iterator it = raindrops.begin(); it != raindrops.end(); ++it)
    {
        glVertex2f(it->x, it->y);
        glVertex2f(it->x, it->y - 2.0f);
    }
    glEnd();
}

// Update raindrops' positions
void updateRaindrops(int value)
{
    for (std::vector<Raindrop>::iterator it = raindrops.begin(); it != raindrops.end(); ++it)
    {
        it->y -= it->speed;
        if (it->y < 0)
        {
            it->y = static_cast<float>(rand() % 45 + 90); // Reset position
            it->x = static_cast<float>(rand() % 160);
        }
    }

    glutPostRedisplay(); // Trigger a redraw
    glutTimerFunc(30, updateRaindrops, 0); // Continue the animation
}


void Circle(float radius, float xc, float yc, float r, float g, float b)
{
    glLineWidth(7.5);
    glBegin(GL_POLYGON);
    for(int i=0; i<200; i++)
    {
        glColor3f(r,g,b);
        float pi=3.1416;
        float A=(i*2*pi)/200;
        float r=radius;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x+xc,y+yc );
    }
    glEnd();
}


void renderTextForTerminal(float x, float y, const char* text)
{
    glRasterPos2f(x, y);  // Set the position to start drawing text
    for (const char* c = text; *c != '\0'; c++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);   // Render each character
    }
}


void renderTextForAviation(float x, float y, const char* text)
{
    glRasterPos2f(x, y);  // Set the position to start drawing text
    for (const char* c = text; *c != '\0'; c++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);   // Render each character
    }
}


void Wheel(float radius, float xc, float yc)
{

    glBegin(GL_POLYGON);
    for(int i=0; i<200; i++)
    {
        glColor3ub(0, 0, 0);
        float pi=3.1416;
        float A=(i*2*pi)/200;
        float r=radius;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x+xc,y+yc );
    }
    glEnd();

    glBegin(GL_POLYGON);
    for(int i=0; i<200; i++)
    {
        glColor3ub(255, 255, 255);
        float pi=3.1416;
        float A=(i*2*pi)/200;
        float r=radius-0.6;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x+xc,y+yc );
    }
    glEnd();
    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(xc-radius+0.6, yc);
    glVertex2f(xc+radius-0.6, yc);
    glEnd();

    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(xc, yc+radius-0.6);
    glVertex2f(xc, yc-radius+0.6);
    glEnd();

}




///ID101
///Grass
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
    glTranslatef(grass_movement, 0.0, 0.0);
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
    renderTextForAviation(5.0f, 72.5f, "Aviation 1");


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
    renderTextForAviation(20.0f, 72.5f, "Aviation 2");
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
    renderTextForTerminal(50.0f, 80.5f, "TERMINAL 1");


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
    renderTextForTerminal(104.0f, 78.0f, "TERMINAL 2");


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

        if (currentWeather == RAINY)
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

        if (currentWeather == RAINY)
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
    glTranslatef(plane_x_1, plane_y_1, 0.0f);
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
        Circle(0.28,80.3974968821253, 16.9871509543515, 0.0f, 0.45f, 0.45f);
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

    Circle(0.35,82.2800513458849, 14.6266837819616, 0.0f, 0.0f, 0.0f);
    Circle(0.1,82.2800513458849, 14.6266837819616, 1.0f, 1.0f, 1.0f);

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

    glTranslatef(plane_4_pos, 0.0, 0.0f);

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

        glTranslatef(plane_5_pos, 0.0, 0.0f);


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
    glTranslatef(bus_position, 0, 0);

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
    Circle(1.2, 138.8870871195253, 22.598998649373, 0.0,0.0,0.0);
    Circle(0.97, 138.8870871195253, 22.598998649373, 0.24, 0.24, 0.24);
    Circle(0.70, 138.8870871195253, 22.598998649373, 0.576, 0.565, 0.553);

    glPointSize(3.5);
    glBegin(GL_POINTS);
    glColor4ub(58,49,47,255);
    glVertex2f(138.8870871195253, 22.598998649373);
    glEnd();

    ///front wheel
    Circle(1.2, 152.3065698453618, 22.633483417416, 0.0,0.0,0.0);
    Circle(0.99, 152.3065698453618, 22.633483417416,0.24, 0.24, 0.24);
    Circle(0.70, 152.3065698453618, 22.633483417416, 0.576, 0.565, 0.553);

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

void Cloud(bool a);

// Modified renderWeather function

void renderWeather1()
{
    if (currentWeather == SUNNY)
    {
        glClearColor(0.5, 0.8, 1.0, 1.0); // Blue sky
    }
    else if (currentWeather == OVERCAST)
    {
        glClearColor(0.7, 0.7, 0.7, 1.0); // Gray sky
    }
    else if (currentWeather == RAINY)
    {
        glClearColor(0.4, 0.4, 0.5, 1.0); // Darker gray sky

          drawRaindrops();

    }

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

void Cloud(bool rain)
{
    float r = 1.0, g = 1.0, b = 1.0;
    if(rain)
        r = g = b = 0.65;
///ID133
///Cloud1
    // first cloud
    Circle(1.5, 81, 87,  r, g, b);
    Circle(2.8, 75.0, 87.0, r, g, b);
    Circle(2.5, 79.0, 87.0, r, g, b);
    Circle(2.2, 72.0, 87,  r, g, b);
    Circle(1.2, 69.8, 87,  r, g, b);
///ID134
///Cloud2
    // second cloud
    Circle(1.5, 131, 87,  r, g, b);
    Circle(2.8, 125.0, 87.0, r, g, b);
    Circle(2.5, 121.0, 87.0, r, g, b);
    Circle(2.0, 129.0, 87.0,  r, g, b);
    Circle(1.5, 119, 87,  r, g, b);
}


///ID135
///Sun
/// Draws the sun with a color based on the weather state
void Sun(float radius, float xc, float yc)
{
    glPushMatrix();
    glTranslatef(0.0f, sun_position, 0.0f);

    glBegin(GL_POLYGON);

    if (currentWeather == RAINY)
    {
        glColor3f(0.4,0.4,0.4); // Light white for rainy weather
    }
    else
    {
        glColor4ub(253, 255, 50, 255); // Default yellow sun
    }

    for (int i = 0; i < 200; i++)
    {
        float pi = 3.1416;
        float angle = (i * 2 * pi) / 200;
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex2f(x + xc, y + yc);
    }
    glEnd();

    glPopMatrix();
}


///ID136
///Car
void Car()
{

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(car_position, 0.0f, 0.0f);

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
    glRotatef(-_angle1, 0.0f, 0.0f, 1.0f);
    glTranslatef(-114.8, -55.8, 0.f);
    Wheel(1.5f, 114.8, 55.8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(125.5, 55.8, 0.f);
    glRotatef(-_angle1, 0.0f, 0.0f, 1.0f);
    glTranslatef(-125.5, -55.8, 0.f);
    Wheel(1.5f, 125.5, 55.8);
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

    if (currentWeather == RAINY)
    {

        Animated_Cloud(!a);
        drawRaindrops();
    }
}

void scene1()
{
     glClear(GL_COLOR_BUFFER_BIT);
     glClearColor(0.0, 0.0, 0.5, 1.0);

    renderWeather1();
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
    if(bus_moving)
    {
    bus_position -= bus_speed;

        if (bus_position < -50 ) {
            bus_moving = !bus_moving;
        }

    }
}
void car_animation_1()
{
    if(car_moving)
    {
        _angle1 += 2.0f;
        car_position += car_speed;
        if(car_position > 80)
            car_position = 0;
    }

}
void Runway_plane_animation_1() {
    if (plane_moving) {
        plane_x_1 += 0.1;
        plane_y_1 += 0.026;
    }
}

void sun_shine_animation(int v)
{
    if(sun_position < 0)
        sun_position += 0.1f;

    glutTimerFunc(16, sun_shine_animation, 0);
}

void grass_movement_animation(int v)
{

    if(v == 0)
        grass_movement = 0.0f;
    else
        grass_movement = 0.1f * sin(v * 0.1f);


    glutTimerFunc(10, grass_movement_animation, v+1);

}

void moving_plane(int v)
{
    if(plane_5_pos > -20)
        plane_5_pos -= 0.1f;

    if(plane_4_pos > -20)
        plane_4_pos -= 0.1f;

    glutTimerFunc(16, moving_plane, 0);

}

void update_all_vhicle_1(int value)
{

    bus_animation_1();
    car_animation_1();

    Runway_plane_animation_1();

    glutTimerFunc(16, update_all_vhicle_1, 0);
}


void handleKeypress(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 's':
            currentWeather = SUNNY;
            break;
        case 'o':
            currentWeather = OVERCAST;
            break;
        case 'r':
            currentWeather = RAINY;
            initializeRaindrops(100); // Start rain
            glutTimerFunc(0, updateRaindrops, 0);
            break;
        case '+':
            for (auto& drop : raindrops) {
                drop.speed *= 1.2f;
            }
            break;
        case '-':
            for (auto& drop : raindrops) {
                drop.speed *= 0.8f;
            }
            break;
        case 27:
            exit(0);
    }
    glutPostRedisplay();
}

void handleMouse(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        if (button == GLUT_LEFT_BUTTON) {

            bus_speed *= 1.2f;
            car_speed *= 1.2f;

            move_Cloud += 1.0f;
            sun_position += 0.5f;
        } else if (button == GLUT_RIGHT_BUTTON) {

            bus_speed *= 0.8f;
            car_speed *= 0.8f;

            move_Cloud -= 1.0f;
            sun_position -= 0.5f;
        }
        glutPostRedisplay();
    }
}





int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("GLUT Project");

    initGL();
    glutMouseFunc(handleMouse);


    glutDisplayFunc(scene1);
    glutKeyboardFunc(handleKeypress);
    glutTimerFunc(0, update_all_vhicle_1, 0);
    glutTimerFunc(0, update_Cloud_1, 0);
    glutTimerFunc(0, sun_shine_animation, 0);
    glutTimerFunc(0, grass_movement_animation, 0);
    glutTimerFunc(0, moving_plane, 0);

    glutMainLoop();
    return 0;
}
