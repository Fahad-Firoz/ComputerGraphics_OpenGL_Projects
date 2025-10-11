#include<GL/glut.h>
#include<math.h>


// Enum to represent day and night
enum TimeOfDay { DAY, NIGHT };
TimeOfDay current_time = NIGHT;


float CAR_FULL_x = 0.0f, CAR_FULL_speed = 0.5f;
float car2_x = 0.0f, car2_speed = 0.4f;
float car3_x = 0.0f, car3_speed = 0.4f;
float Bus_x = 0.0f, Bus_speed = 0.4f;
float Truck_x = 0.0f, Truck_speed = 0.4f;
float Cloud_x = 0.0f, Cloud_speed = 0.2f;
//float Boat_x = 0.0f, Boat_speed = 0.4f;


float plane_x=0;
float plane_y=0;

float cloud_moving=false;

void renderText(float x, float y, const char* text) {
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
void circle1(float radius, float xc, float yc, float r, float g, float b)
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
    glTranslatef(car2_x, 0.0f, 0.0f);

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


    circle1(1.437,33.556, 14, 1.0, 1.0, 1.0); //Car-1 Wheel back
    circle1(1.437,45.323, 14, 1.0, 1.0, 1.0); //Car-1 Wheel Front

    glPopMatrix();

}

///ID411
void Car_2(double r, double g, double b)
 {
     glPushMatrix();
    glTranslatef(car2_x, 0.0f, 0.0f);

     glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(70.0f, 0.0f, 0.0f);

     CAR_FULL(r, g, b);

    glPopMatrix();  // Render now

    glPopMatrix();

 }


// Lamp-post -1 Circle
///ID439
void circle2(float radius, float xc, float yc, float r, float g, float b)
{
    glBegin(GL_POLYGON);
    for(int i=0; i<200; i++)
    {
     if(current_time == DAY)
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


    circle2(2.00,133, 41.5, 1.0, 1.0, 1.0); //Lamp-post- 1 left light
    circle2(2.00,138, 41.5, 1.0, 1.0, 1.0);//Lamp-post- 1 right light
    circle2(2.00,135.5, 44.618, 1.0, 1.0, 1.0);//Lamp-post- 1 top light

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
void circle10(float radius, float xc, float yc, float r, float g, float b)
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
void circle11(float radius, float xc, float yc, float r, float g, float b)
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
    circle10(0.626,92.4194653871472, 37.7296355417906,1.0,1.0,1.0 );
    circle11(0.626,92.4194653871472, 36.3183740203471,1.0,1.0,1.0 );




 }

 ///ID418
void sky(){

    if(current_time == DAY)
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
    renderText(2, 65, "AUSIS");


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
    renderText(43, 60.2, "ICCB");



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
    renderText(62, 61, " Eye Hospital");


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
    renderText(82, 62.5, "BASUNDHARA BANK");

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
    renderText(140, 73, "RUPAYAN ");

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
    glTranslatef(Cloud_x, 0.0f, 0.0f);

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
        if(current_time == DAY)
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
void Bus(){

   glPushMatrix();
    glTranslatef(Bus_x, 0.0f, 0.0f);

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
    glTranslatef(plane_x, 0.0f, 0.0f);

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
    glTranslatef(Truck_x, 0.0f, 0.0f);

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
    glTranslatef(car3_x, 0.0f, 0.0f);

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

void display()
{



    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

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

void update_all_vhicle(int value)
{


    // Update the car full and car -2 position
    ///ID431

    CAR_FULL_x += CAR_FULL_speed;

    if (CAR_FULL_x >  200.0f) {
        CAR_FULL_x = -20;
    }

     ///ID432
    car2_x += car2_speed;

    if (car2_x > 150.0f) {
        car2_x = -70;
    }
    ///ID433
    // Update the car-3 position and speed
    car3_x -= car3_speed;

    if (car3_x < -150.0f) {
        car3_x = 10;
    }

    // Update the Bus position and speed
    ///ID434
    Bus_x += Bus_speed;

    if (Bus_x > 150.0f) {
        Bus_x = -70;
    }
    ///ID435
    Truck_x -= Truck_speed;

    if (Truck_x < -160.0f) {
        Truck_x = 120;
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
    plane_x-=0.2;

// Update cloud position if it's moving
    ///ID437
    if (cloud_moving) {
        Cloud_x += Cloud_speed;
        if (Cloud_x > 170.0f) {
            Cloud_x = -10.0f; // Reset to the left side
        }
    }

    glutPostRedisplay();       // Trigger display function
    glutTimerFunc(16, update_all_vhicle, 0); // Call update again after 16ms (~60 FPS)
}

///ID438
void handleKeyboard(unsigned char key, int x, int y) {

    if (key == 'd' || key == 'D') {
        current_time = DAY; // Set time to day
    } else if (key == 'n' || key == 'N') {
        current_time = NIGHT; // Set time to night
    }else if (key == 's' || key == 'S') {

    }

    glutPostRedisplay(); // Request a redraw
}

///ID437
void handleMouse(int button, int state, int x, int y) {
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        cloud_moving = !cloud_moving; // Toggle train movement on right click

    }
}

/* Main function: GLUT runs as a console application starting at main() */

int main(int argc, char** argv)
{

    glutInit(&argc, argv); // Initialize GLUT

    glutCreateWindow("Open GL Setup"); // Create window with the given title

    glutInitWindowSize(620, 620); // Set the window's initial width & height


    gluOrtho2D(0,160,0,90);
    glutDisplayFunc(display); // Register callback handler for window re-paint event
    glutTimerFunc(16,update_all_vhicle,0);
    glutKeyboardFunc(handleKeyboard);
    glutMouseFunc(handleMouse);



    glutMainLoop(); // Enter the event-processing loop

    return 0;

}
