//  ========================================================================
//  COSC363: Computer Graphics (2019);  University of Canterbury.
//
//  FILE NAME: Shadow.cpp
//  See Lab03.pdf for details.
//  ========================================================================
 
#include <iostream>
#include <cmath>
#include <climits>
#include <GL/glut.h>
#include "loadTGA.h"
using namespace std;

//-- Globals---------------------------------------------------------------------------------------------
float angle = 0.0, lookAngle = 0, verticleLookAngle = 0, look_x = 0.0, look_y = 30.0, look_z = 50.0, eye_x = 0.0, eye_y = 30.0, eye_z = 150.0;  // Camera 1 parameters
float lightAngle = 0.0; // Main Light Source angle from the origin
float lightXPosition = 60.0, lightZPosition = 0.0;
bool camera2 = false;

// Ship color
int shipColorCounter = 0;
float shipRedAmount = 0.99;
bool shipRedRising = false;
float shipGreenAmount = 0.5;
bool shipGreenRising = true;
float shipBlueAmount = 0.01;
bool shipBlueRising = true;

// Cannon
float *x, *y, *z;  //vertex coordinate arrays
int *t1, *t2, *t3; //triangles
int nvrt, ntri;    //total number of vertices and triangles

// Tower Roof Shell
const int roofN = 17;
float roofVx[roofN] = {0, 12, 11.2, 10.4, 9.6, 8.8, 8, 7.2, 6.4, 5.6, 4.8, 4, 3.2, 2.4, 1.6, 0.8, 0};
float roofVy[roofN] = {0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
float roofVz[roofN] = {0};

// Gate
float gateAngle = 0.0;

// Tower Shell
const int towerN = 40;  // Total number of vertices on the base curve
float towerVx[towerN] = {0, 12, 12, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 9, 8, 7, 6, 5.5, 5, 4.5, 4, 3.5, 3, 2.5, 2, 1.5, 1, 0.5, 0.25, 0};
float towerVy[towerN] = {0, 0, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31, 33, 35, 37, 39, 41, 43, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45};
float towerVz[towerN] = {0};

// Space Ship Shell
const int shipN = 101;  // Total number of vertices on the base curve
float shipVx[shipN] = {0,0.197999999999999,0.391999999999999,0.581999999999999,0.768,0.949999999999998,1.128,1.302,1.472,1.638,1.8,1.958,2.112,2.262,2.408,2.55,2.688,2.822,2.952,3.078,3.2,3.318,3.432,3.542,3.648,3.75,3.848,3.942,4.032,4.118,4.2,4.278,4.352,4.422,4.488,4.55,4.608,4.662,4.712,4.758,4.8,4.838,4.872,4.902,4.928,4.95,4.968,4.982,4.992,4.998,5,4.998,4.992,4.982,4.968,4.95,4.928,4.902,4.872,4.838,4.8,4.758,4.712,4.662,4.608,4.55,4.488,4.422,4.352,4.278,4.2,4.118,4.032,3.942,3.848,3.75,3.648,3.542,3.432,3.318,3.2,3.078,2.952,2.822,2.688,2.55,2.408,2.262,2.112,1.958,1.8,1.638,1.472,1.302,1.128,0.949999999999998,0.768,0.582000000000001,0.391999999999998,0.197999999999999,0};
float shipVy[shipN] = {0.0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4, 2.6, 2.8, 3.0, 3.2, 3.4, 3.6, 3.8, 4.0, 4.2, 4.4, 4.6, 4.8, 5.0, 5.2, 5.4, 5.6, 5.8, 6.0, 6.2, 6.4, 6.6, 6.8, 7.0, 7.2, 7.4, 7.6, 7.8, 8.0, 8.2, 8.4, 8.6, 8.8, 9.0, 9.2, 9.4, 9.6, 9.8, 10.0, 10.2, 10.4, 10.6, 10.8, 11.0, 11.2, 11.4, 11.6, 11.8, 12.0, 12.2, 12.4, 12.6, 12.8, 13.0, 13.2, 13.4, 13.6, 13.8, 14.0, 14.2, 14.4, 14.6, 14.8, 15.0, 15.2, 15.4, 15.6, 15.8, 16.0, 16.2, 16.4, 16.6, 16.8, 17.0, 17.2, 17.4, 17.6, 17.8, 18.0, 18.2, 18.4, 18.6, 18.8, 19.0, 19.2, 19.4, 19.6, 19.8, 20.0};
float shipVz[shipN] = {0.0};

// Space Ship Related Globals
float shipAltitude = 0.0;
float shipRotationAngle = 0.0;
float orbitersAngle = 0.0;
bool takeoff = false;
float lidAngle = 0.0;
bool lidOpen = false;

// Robot Related Globals
float robotArmsAngle = 0.0;
float robotHandsAngle = 45;
float robotXposition = 0.0;
float robotYposition = 0.0;
float robotAngle = 0;
int robotCounter = 0;
float robotCircleAngle = 0.0;

// Cannon Ball Variables
float cannonBallYTranslation = 9.0;
float cannonBallZTranslation = 0.0;
bool cannonBallFiring = false;
int cannonCounter = 0;

// Textures
GLuint texId[5];
GLuint skyboxTexId[6];

//-------------------------------------------------------------------------

//-- Loads mesh data in OFF format    -------------------------------------
void loadMeshFile(const char* fname)
{
    ifstream fp_in;
    int num, ne;

    fp_in.open(fname, ios::in);
    if(!fp_in.is_open())
    {
        cout << "Error opening mesh file" << endl;
        exit(1);
    }

    fp_in.ignore(INT_MAX, '\n');				//ignore first line
    fp_in >> nvrt >> ntri >> ne;			    // read number of vertices, polygons, edges

    x = new float[nvrt];                        //create arrays
    y = new float[nvrt];
    z = new float[nvrt];

    t1 = new int[ntri];
    t2 = new int[ntri];
    t3 = new int[ntri];

    for(int i=0; i < nvrt; i++)                         //read vertex list
        fp_in >> x[i] >> y[i] >> z[i];

    for(int i=0; i < ntri; i++)                         //read polygon list
    {
        fp_in >> num >> t1[i] >> t2[i] >> t3[i];
        if(num != 3)
        {
            cout << "ERROR: Polygon with index " << i  << " is not a triangle." << endl;  //not a triangle!!
            exit(1);
        }
    }

    fp_in.close();
    cout << " File successfully read." << endl;
}

//--Function to compute the normal vector of a triangle with index tindx --
void cannonNormal(int tindx)
{
    float x1 = x[t1[tindx]], x2 = x[t2[tindx]], x3 = x[t3[tindx]];
    float y1 = y[t1[tindx]], y2 = y[t2[tindx]], y3 = y[t3[tindx]];
    float z1 = z[t1[tindx]], z2 = z[t2[tindx]], z3 = z[t3[tindx]];
    float nx, ny, nz;
    nx = y1*(z2-z3) + y2*(z3-z1) + y3*(z1-z2);
    ny = z1*(x2-x3) + z2*(x3-x1) + z3*(x1-x2);
    nz = x1*(y2-y3) + x2*(y3-y1) + x3*(y1-y2);
    glNormal3f(nx, ny, nz);
}

//--------draws the mesh model of the cannon-------------------------------
void drawCannon()
{
    //Construct the object model here using triangles read from OFF file
    glBegin(GL_TRIANGLES);
        for(int tindx = 0; tindx < ntri; tindx++)
        {
           cannonNormal(tindx);
           glVertex3d(x[t1[tindx]], y[t1[tindx]], z[t1[tindx]]);
           glVertex3d(x[t2[tindx]], y[t2[tindx]], z[t2[tindx]]);
           glVertex3d(x[t3[tindx]], y[t3[tindx]], z[t3[tindx]]);
        }
    glEnd();
}

//-- Rotates the light around the scene -----------------------------------
void lightRotation(int value) {
    lightAngle += 0.01;
    orbitersAngle += 0.5;
    if (lightAngle > 360) {
        lightAngle = 0;
    }
    if (orbitersAngle > 359) {
        orbitersAngle = 0;
    }
    lightXPosition = 60 * cos(lightAngle);
    lightZPosition = 60 * sin(lightAngle);
    glutPostRedisplay();
    glutTimerFunc(30, lightRotation, 0);
}

//-- Ship Color Warping ---------------------------------------------------
void shipColorWarp(int value) {
    if (shipRedRising) {
        shipRedAmount += 0.01;
    } else {
        shipRedAmount -= 0.01;
    }
    if (shipRedAmount > 0.99 || shipRedAmount < 0.01) {
        shipRedRising = !shipRedRising;
    }
    if (shipColorCounter % 2 == 0) {
        if (shipGreenRising) {
            shipGreenAmount += 0.01;
        } else {
            shipGreenAmount -= 0.01;
        }
        if (shipGreenAmount > 0.99 || shipGreenAmount < 0.01) {
            shipGreenRising = !shipGreenRising;
        }
    }
    if (shipColorCounter % 3 == 0) {
        if (shipBlueRising) {
            shipBlueAmount += 0.01;
        } else {
            shipBlueAmount -= 0.01;
        }
        if (shipBlueAmount > 0.99 || shipBlueAmount < 0.01) {
            shipBlueRising = !shipBlueRising;
        }
    }
    glutPostRedisplay();
    glutTimerFunc(30, shipColorWarp, 0);
}

//-- Cannon ---------------------------------------------------------------
void cannon(bool shadow)
{
    glPushMatrix();
    // Face towards the front
        glScalef(0.2, 0.2, 0.2);
        glRotatef(-90, 0, 1, 0);

        // Cannon
        glPushMatrix();
            glTranslatef(-20.0, 30.0, 0.0);
            glRotatef(40, 0.0, 0.0, 1.0);
            glTranslatef(20.0, -30.0, 0.0);
            if (shadow) {
                glColor4f(0.2, 0.2, 0.2, 1.0);
            } else {
                glColor3f(0.41, 0.41, 0.41);
            }
            drawCannon();
        glPopMatrix();

        // Base
        glPushMatrix();
        glTranslatef(-10.0, 5.0, 17.0);
        glScalef(80.0, 10.0, 6.0);
        if (shadow) {
            glColor4f(0.2, 0.2, 0.2, 1.0);
        } else {
            glColor3f(0.545, 0.271, 0.075);
        }
        glutSolidCube(1.0);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-20.0, 25.0, 17.0);
        glScalef(40.0, 30.0, 6.0);
        glutSolidCube(1.0);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-10.0, 5.0, -17.0);
        glScalef(80.0, 10.0, 6.0);
        glutSolidCube(1.0);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-20.0, 25.0, -17.0);
        glScalef(40.0, 30.0, 6.0);
        glutSolidCube(1.0);
        glPopMatrix();
    glPopMatrix();
}

//-- Camera control function ----------------------------------------------
void special(int key, int x, int y)
{
    if (!camera2)
    {
        if (key == GLUT_KEY_LEFT)   // Change direction by 5 degrees (in radians)
        {
            lookAngle -= 0.0872665;
        }
        else if (key == GLUT_KEY_RIGHT)
        {
            lookAngle += 0.0872665;
        }
        else if(key == GLUT_KEY_DOWN)
        {  // Move backward
            eye_x -= 1.0 * sin(lookAngle);
            if (eye_x < -199.9 || eye_x > 199.9) {
                eye_x += 1.0 * sin(lookAngle);
            } else if (abs(eye_x) < 62.1 && abs(eye_x) > 37.9 && abs(eye_z) < 62.1 && abs(eye_z) > 37.9 && eye_y < 60.1) {
                eye_x += 1.0 * sin(lookAngle);
            } else if ((abs(eye_x) < 57.1 && abs(eye_x) > 42.9 && abs(eye_z) < 50.1 || eye_z > -57.1 && eye_z < -42.9 &&  abs(eye_x) < 50.1) && eye_y < 35.1) {
                eye_x += 1.0 * sin(lookAngle);
            } else if (gateAngle < 90.0 && ((eye_z < 58.1 && eye_z > 42.9 && abs(eye_x) < 50.1 && abs(eye_x) > 9.9 && eye_y < 35.1) ||
                                            (eye_z < 58.1 && eye_z > 42.9 && eye_y > 24.9 && eye_y < 35.1) ||
                                            (eye_z < 58.1 && eye_z > 56.9 && eye_y < 25))) {
                eye_x += 1.0 * sin(lookAngle);
            } else if (gateAngle > 89.9 && ((eye_z < 58.1 && eye_z > 42.9 && abs(eye_x) < 50.1 && abs(eye_x) > 9.9 && eye_y < 35.1) ||
                                            (eye_z < 58.1 && eye_z > 42.9 && eye_y > 24.9 && eye_y < 35.1))) {
                eye_x += 1.0 * sin(lookAngle);
            } else if(abs(eye_x) < 16.6 && abs(eye_z) < 16.6 && eye_y < 40.1) {
                eye_x += 1.0 * sin(lookAngle);
            }

            eye_y -= 1.0 * tan(verticleLookAngle);
            if (eye_y < 0.1 || eye_y > 199.9) {
                eye_y += 1.0 * tan(verticleLookAngle);
            } else if (abs(eye_x) < 62.1 && abs(eye_x) > 37.9 && abs(eye_z) < 62.1 && abs(eye_z) > 37.9 && eye_y < 60.1) {
                eye_y += 1.0 * tan(verticleLookAngle);
            } else if ((abs(eye_x) < 57.1 && abs(eye_x) > 42.9 && abs(eye_z) < 50.1 || eye_z > -57.1 && eye_z < -42.9 &&  abs(eye_x) < 50.1) && eye_y < 35.1) {
                eye_y += 1.0 * tan(verticleLookAngle);
            } else if (gateAngle < 90.0 && ((eye_z < 58.1 && eye_z > 42.9 && abs(eye_x) < 50.1 && abs(eye_x) > 9.9 && eye_y < 35.1) ||
                                            (eye_z < 58.1 && eye_z > 42.9 && eye_y > 24.9 && eye_y < 35.1) ||
                                            (eye_z < 58.1 && eye_z > 56.9 && eye_y < 25))) {
                eye_y += 1.0 * tan(verticleLookAngle);
            } else if (gateAngle > 89.9 && ((eye_z < 58.1 && eye_z > 42.9 && abs(eye_x) < 50.1 && abs(eye_x) > 9.9 && eye_y < 35.1) ||
                                            (eye_z < 58.1 && eye_z > 42.9 && eye_y > 24.9 && eye_y < 35.1))) {
                eye_y += 1.0 * tan(verticleLookAngle);
            } else if(abs(eye_x) < 16.6 && abs(eye_z) < 16.6 && eye_y < 40.1) {
                eye_y += 1.0 * tan(verticleLookAngle);
            }

            eye_z += 1.0 * cos(lookAngle);
            if (eye_z < -199.9 || eye_z > 199.9) {
                eye_z -= 1.0 * cos(lookAngle);
            } else if (abs(eye_x) < 62.1 && abs(eye_x) > 37.9 && abs(eye_z) < 62.1 && abs(eye_z) > 37.9 && eye_y < 60.1) {
                eye_z -= 1.0 * cos(lookAngle);
            } else if ((abs(eye_x) < 57.1 && abs(eye_x) > 42.9 && abs(eye_z) < 50.1 || eye_z > -57.1 && eye_z < -42.9 &&  abs(eye_x) < 50.1) && eye_y < 35.1) {
                eye_z -= 1.0 * cos(lookAngle);
            } else if (gateAngle < 90.0 && ((eye_z < 58.1 && eye_z > 42.9 && abs(eye_x) < 50.1 && abs(eye_x) > 9.9 && eye_y < 35.1) ||
                                            (eye_z < 58.1 && eye_z > 42.9 && eye_y > 24.9 && eye_y < 35.1) ||
                                            (eye_z < 58.1 && eye_z > 56.9 && eye_y < 25))) {
                eye_z -= 1.0 * cos(lookAngle);
            } else if (gateAngle > 89.9 && ((eye_z < 58.1 && eye_z > 42.9 && abs(eye_x) < 50.1 && abs(eye_x) > 9.9 && eye_y < 35.1) ||
                                            (eye_z < 58.1 && eye_z > 42.9 && eye_y > 24.9 && eye_y < 35.1))) {
                eye_z -= 1.0 * cos(lookAngle);
            } else if(abs(eye_x) < 16.6 && abs(eye_z) < 16.6 && eye_y < 40.1) {
                eye_z -= 1.0 * cos(lookAngle);
            }
        }
        else if(key == GLUT_KEY_UP)
        { // Move forward
            eye_x += 1.0 * sin(lookAngle);
            if (eye_x < -199.9 || eye_x > 199.9) {
                eye_x -= 1.0 * sin(lookAngle);
            } else if (abs(eye_x) < 62.1 && abs(eye_x) > 37.9 && abs(eye_z) < 62.1 && abs(eye_z) > 37.9 && eye_y < 60.1) {
                eye_x -= 1.0 * sin(lookAngle);
            } else if ((abs(eye_x) < 57.1 && abs(eye_x) > 42.9 && abs(eye_z) < 50.1 || eye_z > -57.1 && eye_z < -42.9 &&  abs(eye_x) < 50.1) && eye_y < 35.1) {
                eye_x -= 1.0 * sin(lookAngle);
            } else if (gateAngle < 90.0 && ((eye_z < 58.1 && eye_z > 42.9 && abs(eye_x) < 50.1 && abs(eye_x) > 9.9 && eye_y < 35.1) ||
                                            (eye_z < 58.1 && eye_z > 42.9 && eye_y > 24.9 && eye_y < 35.1) ||
                                            (eye_z < 58.1 && eye_z > 56.9 && eye_y < 25))) {
                eye_x -= 1.0 * sin(lookAngle);
            } else if (gateAngle > 89.9 && ((eye_z < 58.1 && eye_z > 42.9 && abs(eye_x) < 50.1 && abs(eye_x) > 9.9 && eye_y < 35.1) ||
                                            (eye_z < 58.1 && eye_z > 42.9 && eye_y > 24.9 && eye_y < 35.1))) {
                eye_x -= 1.0 * sin(lookAngle);
            } else if(abs(eye_x) < 16.6 && abs(eye_z) < 16.6 && eye_y < 40.1) {
                eye_x -= 1.0 * sin(lookAngle);
            }

            eye_y += 1.0 * tan(verticleLookAngle);
            if (eye_y < 0.1 || eye_y > 199.9) {
                eye_y -= 1.0 * tan(verticleLookAngle);
            } else if (abs(eye_x) < 62.1 && abs(eye_x) > 37.9 && abs(eye_z) < 62.1 && abs(eye_z) > 37.9 && eye_y < 60.1) {
                eye_y -= 1.0 * tan(verticleLookAngle);
            } else if ((abs(eye_x) < 57.1 && abs(eye_x) > 42.9 && abs(eye_z) < 50.1 || eye_z > -57.1 && eye_z < -42.9 &&  abs(eye_x) < 50.1) && eye_y < 35.1) {
                eye_y -= 1.0 * tan(verticleLookAngle);
            } else if (gateAngle < 90.0 && ((eye_z < 58.1 && eye_z > 42.9 && abs(eye_x) < 50.1 && abs(eye_x) > 9.9 && eye_y < 35.1) ||
                                            (eye_z < 58.1 && eye_z > 42.9 && eye_y > 24.9 && eye_y < 35.1) ||
                                            (eye_z < 58.1 && eye_z > 56.9 && eye_y < 25))) {
                eye_y -= 1.0 * tan(verticleLookAngle);
            } else if (gateAngle > 89.9 && ((eye_z < 58.1 && eye_z > 42.9 && abs(eye_x) < 50.1 && abs(eye_x) > 9.9 && eye_y < 35.1) ||
                                            (eye_z < 58.1 && eye_z > 42.9 && eye_y > 24.9 && eye_y < 35.1))) {
                eye_y -= 1.0 * tan(verticleLookAngle);
            } else if(abs(eye_x) < 16.6 && abs(eye_z) < 16.6 && eye_y < 40.1) {
                eye_y -= 1.0 * tan(verticleLookAngle);
            }

            eye_z -= 1.0 * cos(lookAngle);
            if (eye_z < -199.9 || eye_z > 199.9) {
                eye_z += 1.0 * cos(lookAngle);
            } else if (abs(eye_x) < 62.1 && abs(eye_x) > 37.9 && abs(eye_z) < 62.1 && abs(eye_z) > 37.9 && eye_y < 60.1) {
                eye_z += 1.0 * cos(lookAngle);
            } else if ((abs(eye_x) < 57.1 && abs(eye_x) > 42.9 && abs(eye_z) < 50.1 || eye_z > -57.1 && eye_z < -42.9 &&  abs(eye_x) < 50.1) && eye_y < 35.1) {
                eye_z += 1.0 * cos(lookAngle);
            } else if (gateAngle < 90.0 && ((eye_z < 58.1 && eye_z > 42.9 && abs(eye_x) < 50.1 && abs(eye_x) > 9.9 && eye_y < 35.1) ||
                                            (eye_z < 58.1 && eye_z > 42.9 && eye_y > 24.9 && eye_y < 35.1) ||
                                            (eye_z < 58.1 && eye_z > 56.9 && eye_y < 25))) {
                eye_z += 1.0 * cos(lookAngle);
            } else if (gateAngle > 89.9 && ((eye_z < 58.1 && eye_z > 42.9 && abs(eye_x) < 50.1 && abs(eye_x) > 9.9 && eye_y < 35.1) ||
                                            (eye_z < 58.1 && eye_z > 42.9 && eye_y > 24.9 && eye_y < 35.1))) {
                eye_z += 1.0 * cos(lookAngle);
            } else if(abs(eye_x) < 16.6 && abs(eye_z) < 16.6 && eye_y < 40.1) {
                eye_z += 1.0 * cos(lookAngle);
            }
        }
        else if (key == GLUT_KEY_PAGE_DOWN) {
            verticleLookAngle -= 0.0872665;
            if (verticleLookAngle < -1.570796327) {
                verticleLookAngle += 0.0872665;
            }
        } else if (key == GLUT_KEY_PAGE_UP) {
            verticleLookAngle += 0.0872665;
            if (verticleLookAngle > 1.570796327) {
                verticleLookAngle -= 0.0872665;
            }
        }

        look_x = eye_x + 100 * sin(lookAngle);
        look_y = eye_y + 100 * tan(verticleLookAngle);
        look_z = eye_z - 100 * cos(lookAngle);
    }
    if (key == GLUT_KEY_HOME) {
        camera2 = !camera2;
    }
    glutPostRedisplay();

}

//-- Robot movement -------------------------------------------------------
void moveRobots(int value) {
    if (robotCounter > 45 && robotCounter < 90) {
        robotAngle -= 2;
    } else if (robotCounter > 90 && robotCounter < 135) {
        robotArmsAngle -= 2;
    } else if (robotCounter > 135 && robotCounter < 195) {
        robotXposition--;
    } else if (robotCounter > 195 && robotCounter < 240) {
        robotArmsAngle += 2;
    } else if (robotCounter > 240 && robotCounter < 285) {
        robotAngle += 2;
    } else if (robotCounter > 330 && robotCounter < 375) {
        robotAngle += 2;
    } else if (robotCounter > 375 && robotCounter < 420) {
        robotArmsAngle -= 2;
    } else if (robotCounter > 420 && robotCounter < 480) {
        robotXposition++;
    } else if (robotCounter > 480 && robotCounter < 525) {
        robotArmsAngle += 2;
    } else if (robotCounter > 525 && robotCounter < 570) {
        robotAngle -= 2;
    } else if (robotCounter > 570) {
        robotCounter = 0;
    }

    robotCounter++;

    // Hand rotation
    robotHandsAngle += 15;
    if (robotHandsAngle > 359) {
        robotHandsAngle = 0;
    }
    glutPostRedisplay();
    glutTimerFunc(30, moveRobots, 0);
}

//-- Robot Circle ---------------------------------------------------------
void robotCircle(int value)
{
    robotCircleAngle++;
    if (robotCircleAngle > 359.0) {
        robotCircleAngle = 0;
    }
    glutPostRedisplay();
    glutTimerFunc(30, robotCircle, 0);
}

//-- Ship takeoff function ------------------------------------------------
void blastOff(int value)
{
    if (lidAngle > 89 && takeoff && shipAltitude < 300) {
        shipAltitude++;
        shipRotationAngle += 5;
        if (shipRotationAngle > 359) {
            shipRotationAngle = 0;
        }
        glutPostRedisplay();
        glutTimerFunc(30, blastOff, 0);
    } else if (!takeoff && shipAltitude > 0) {
        shipAltitude--;
        shipRotationAngle += 5;
        if (shipRotationAngle > 359) {
            shipRotationAngle = 0;
        }
        glutPostRedisplay();
        glutTimerFunc(30, blastOff, 0);
    } else if (takeoff && lidAngle < 90) {
        lidAngle++;
        glutPostRedisplay();
        glutTimerFunc(30, blastOff, 0);
    } else if (shipAltitude < 0.1 && lidAngle > 0.0) {
        lidAngle--;
        glutPostRedisplay();
        glutTimerFunc(30, blastOff, 0);
    } else if (shipAltitude > 0.0) {
        shipRotationAngle += 5;
        if (shipRotationAngle > 359) {
            shipRotationAngle = 0;
        }
        glutPostRedisplay();
        glutTimerFunc(30, blastOff, 0);
    }
}

//-- Load the skybox texture ----------------------------------------------
void loadSkyboxTextures()
{
    glGenTextures(6, skyboxTexId); 		// Create texture id

    glBindTexture(GL_TEXTURE_2D, skyboxTexId[0]);
    loadTGA("left.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_2D, skyboxTexId[1]);
    loadTGA("front.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_2D, skyboxTexId[2]);
    loadTGA("right.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_2D, skyboxTexId[3]);
    loadTGA("back.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_2D, skyboxTexId[4]);
    loadTGA("up.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_2D, skyboxTexId[5]);
    loadTGA("down.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

//-- Cannon ball trajection calculator ------------------------------------
void calculateBallFlight(int value)
{
    if (cannonBallFiring && cannonCounter < 150) {
        cannonCounter++;
        cannonBallZTranslation += 2;
        cannonBallYTranslation = 30 * abs(sin(cannonBallZTranslation/20 + 6.5)) * exp(-0.19 * cannonBallZTranslation/20);

        glutPostRedisplay();
        glutTimerFunc(10, calculateBallFlight, 0);
    } else {
        cannonBallFiring = false;
    }
}

//-- Function to fire the cannon ------------------------------------------
void fireCannon()
{
    if (!cannonBallFiring) {
        cannonBallFiring = true;
        cannonBallYTranslation = 9.0;
        cannonBallZTranslation = 0.0;
        cannonCounter = 0;
        glutTimerFunc( 10, calculateBallFlight, 1 );
    } else {
        cannonBallYTranslation = 9.0;
        cannonBallZTranslation = 0.0;
        cannonCounter = 0;
    }
}

//-- Key press function for handling events -------------------------------
void keyboard(unsigned char key, int x, int y)
{
    if (key == 'c' || key == 'C')
    {
        fireCannon();
    }
    else if (key == 's' || key == 'S')
    {
        takeoff = !takeoff;
        if (lidAngle < 0.1) {
            glutTimerFunc(30, blastOff, 0);
        }
    }
    else if (key == 'o' || key == 'O') {
        if (gateAngle > 0) {
            gateAngle -= 1;
        }
    }
    else if (key == 'l' || key == 'L') {
        if (gateAngle < 90) {
            gateAngle += 1;
        }
    }
    glutPostRedisplay();
}

//-------------------Load glass texture------------------------------------
void loadTextures()
{
    glGenTextures(5, texId);

    // Floor Texture
    glBindTexture(GL_TEXTURE_2D, texId[0]);
    loadTGA("ground-texture.tga");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    // Castle Texture
    glBindTexture(GL_TEXTURE_2D, texId[1]);
    loadTGA("castle-texture.tga");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    // Roof Texture
    glBindTexture(GL_TEXTURE_2D, texId[2]);
    loadTGA("roof-texture.tga");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    // Gate Texture
    glBindTexture(GL_TEXTURE_2D, texId[3]);
    loadTGA("gate-texture.tga");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    // Tile Texture
    glBindTexture(GL_TEXTURE_2D, texId[4]);
    loadTGA("tile-texture.tga");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

//-------------------------------------------------------------------------
void normal(float x1, float y1, float z1,
            float x2, float y2, float z2,
              float x3, float y3, float z3 )
{
      float nx, ny, nz;
      nx = y1 * ( z2 - z3 ) + y2 * ( z3 - z1 ) + y3 * ( z1 - z2 );
      ny = z1 * ( x2 - x3 ) + z2 * ( x3 - x1 ) + z3 * ( x1 - x2 );
      nz = x1 * ( y2 - y3 ) + x2 * ( y3 - y1 ) + x3 * ( y1 - y2 );

      glNormal3f( -nx, -ny, -nz );
}

//-------------------Initialization----------------------------------------
void initialise()
{
    float greySpot[4] = {0.6, 0.6, 0.6, 1.0};
    float greyMain[4] = {0.2, 0.2, 0.2, 1.0};
    float white[4]  = {1.0, 1.0, 1.0, 1.0};

    // Load the cannon file
    loadMeshFile("Cannon.off");				//Specify mesh file name here
    loadSkyboxTextures();
    loadTextures();

    glClearColor (0.0, 0.0, 0.0, 0.0);

    glEnable(GL_LIGHTING);

    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, greyMain);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);

    // Robot Spotlight 1
    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_AMBIENT, greySpot);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT1, GL_SPECULAR, white);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 15.0);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 0.01);

    // Robot Spotlight 2
    glLightfv(GL_LIGHT2, GL_AMBIENT, greySpot);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT2, GL_SPECULAR, white);
    glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 15.0);
    glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 0.01);

    // Robot Spotlight 3
    glEnable(GL_LIGHT3);
    glLightfv(GL_LIGHT3, GL_AMBIENT, greySpot);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT3, GL_SPECULAR, white);
    glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 15.0);
    glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 0.01);

    // Robot Spotlight 4
    glEnable(GL_LIGHT4);
    glLightfv(GL_LIGHT4, GL_AMBIENT, greySpot);
    glLightfv(GL_LIGHT4, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT4, GL_SPECULAR, white);
    glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, 15.0);
    glLightf(GL_LIGHT4, GL_SPOT_EXPONENT, 0.01);

    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);

	glMatrixMode(GL_PROJECTION);						
    glLoadIdentity();
    gluPerspective(80.0, 1.78, 0.1, 4000.0);
}

//-- Castle Floor Plane ---------------------------------------------------------
void castleFloor()
{
    float floor_height = -0.1;

    glColor4f(1.0, 1.0, 1.0, 0.3);   //The fourth component is the transparency term for reflection
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, texId[4]);

    glNormal3f(0.0, 1.0, 0.0);

    //The floor is made up of several tiny squares on a 114x114 grid. Each square has a unit size.
    glBegin(GL_QUADS);
    for(int i = -57; i < 57; i++)
    {
        for(int j = -57;  j < 57; j++)
        {
            glTexCoord2f((i + 57) * 0.00877, (j + 57) * 0.00877);   glVertex3f(i,   floor_height, j  );
            glTexCoord2f((i + 57) * 0.00877, (j + 57) * 0.00877);   glVertex3f(i,   floor_height, j+1);
            glTexCoord2f((i + 57) * 0.00877, (j + 57) * 0.00877);   glVertex3f(i+1, floor_height, j+1);
            glTexCoord2f((i + 57) * 0.00877, (j + 57) * 0.00877);   glVertex3f(i+1, floor_height, j  );
        }
    }
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

//-- Roof of a tower
void roof(bool shadow)
{
    float wx[roofN], wy[roofN], wz[roofN];
    float angStep = 1.0 * 3.1415926 / 180.0;  //Rotate in 10 deg steps (converted to radians)

    if (shadow) {
        glColor4f(0.2, 0.2, 0.2, 1.0);
    } else {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texId[2]);
    }

    //  Include code for drawing the surface of revolution here.
    for (int j = 0; j < 360; j++) {
        for (int i = 0; i < roofN; i++) {
            wx[i] = roofVx[i] * cos(angStep) + roofVz[i] * sin(angStep);
            wy[i] = roofVy[i];
            wz[i] = -roofVx[i] * sin(angStep) + roofVz[i] * cos(angStep);
        }
        glBegin(GL_TRIANGLE_STRIP);
            for (int i = 0; i < roofN; i++) {
                if (i > 0) normal( wx[i - 1], wy[i - 1], wz[i - 1],
                                   roofVx[i - 1], roofVy[i - 1], roofVz[i - 1],
                                   roofVx[i], roofVy[i], roofVz[i] );
                glTexCoord2f((j/360.0), (i/float(roofN)));                                   glVertex3f(roofVx[i], roofVy[i], roofVz[i]);
                if (i > 0) normal( wx[i - 1], wy[i - 1], wz[i - 1],
                                   roofVx[i], roofVy[i], roofVz[i],
                                   wx[i], wy[i], wz[i] );
                glTexCoord2f(((j + 1)/360.0), ((i)/float(roofN)));                   glVertex3f(wx[i], wy[i], wz[i]);
            }
        glEnd();
        for (int i = 0; i < roofN; i++) {
            roofVx[i] = wx[i];
            roofVy[i] = wy[i];
            roofVz[i] = wz[i];
        }
    }
}

//-- Tower ---------------------------------------------------------------
void tower(bool shadow)
{
    float wx[towerN], wy[towerN], wz[towerN];
    float angStep = 1.0 * 3.1415926 / 180.0;  //Rotate in 10 deg steps (converted to radians)

    if (shadow) {
        glColor4f(0.2, 0.2, 0.2, 1.0);
    } else {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texId[1]);
        glColor4f (1.0, 0.75, 0.5, 1.0);
    }

    //  Include code for drawing the surface of revolution here.
    for (int j = 0; j < 360; j++) {
        for (int i = 0; i < towerN; i++) {
            wx[i] = towerVx[i] * cos(angStep) + towerVz[i] * sin(angStep);
            wy[i] = towerVy[i];
            wz[i] = -towerVx[i] * sin(angStep) + towerVz[i] * cos(angStep);
        }
        glBegin(GL_TRIANGLE_STRIP);
            for (int i = 0; i < towerN; i++) {
                if (i > 0) normal( wx[i - 1], wy[i - 1], wz[i - 1],
                                   towerVx[i - 1], towerVy[i - 1], towerVz[i - 1],
                                   towerVx[i], towerVy[i], towerVz[i] );
                glTexCoord2f((j/360.0), (i/float(towerN)));                                   glVertex3f(towerVx[i], towerVy[i], towerVz[i]);
                if (i > 0) normal( wx[i - 1], wy[i - 1], wz[i - 1],
                                   towerVx[i], towerVy[i], towerVz[i],
                                   wx[i], wy[i], wz[i] );
                glTexCoord2f(((j + 1)/360.0), ((i)/float(towerN)));                   glVertex3f(wx[i], wy[i], wz[i]);
            }
        glEnd();
        for (int i = 0; i < towerN; i++) {
            towerVx[i] = wx[i];
            towerVy[i] = wy[i];
            towerVz[i] = wz[i];
        }
    }

    // Roof
    glPushMatrix();
        glTranslatef(0, 45, 0);
        roof(shadow);
    glPopMatrix();

    // Reset the values for the arrays
    float roofx[roofN] = {0, 12, 11.2, 10.4, 9.6, 8.8, 8, 7.2, 6.4, 5.6, 4.8, 4, 3.2, 2.4, 1.6, 0.8, 0};
    float roofy[roofN] = {0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    float roofz[roofN] = {0};
    float towerx[towerN] = {0, 12, 12, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 9, 8, 7, 6, 5.5, 5, 4.5, 4, 3.5, 3, 2.5, 2, 1.5, 1, 0.5, 0.25, 0};
    float towery[towerN] = {0, 0, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31, 33, 35, 37, 39, 41, 43, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45};
    float towerz[towerN] = {0};
    for (int i = 0; i < roofN; i++) {
        roofVx[i] = roofx[i];
        roofVy[i] = roofy[i];
        roofVz[i] = roofz[i];
    }
    for (int i = 0; i < towerN; i++) {
        towerVx[i] = towerx[i];
        towerVy[i] = towery[i];
        towerVz[i] = towerz[i];
    }
}

//-- Parapet -------------------------------------------------------------
void battlement()
{
    glBegin(GL_QUADS);
      glNormal3f(0.0, 0.0, 1.0);   //Facing +z (Front side)
      glTexCoord2f(0.0, 0.0);       glVertex3f(-2.5, 0.0, 1.5);
      glTexCoord2f(0.0625, 0.0);       glVertex3f(2.5, 0.0, 1.5);
      glTexCoord2f(0.0625, 0.0625);       glVertex3f(2.5, 5.0, 1.5);
      glTexCoord2f(0.0, 0.0625);       glVertex3f(-2.5, 5.0, 1.5);

      glNormal3f(0.0, 0.0, -1.0);   //Facing -z (Back side)
      glTexCoord2f(0.0, 0.0);       glVertex3f(2.5, 0.0, -1.5);
      glTexCoord2f(0.0625, 0.0);       glVertex3f(-2.5, 0.0,-1.5);
      glTexCoord2f(0.0625, 0.0625);       glVertex3f(-2.5, 5.0,-1.5);
      glTexCoord2f(0.0, 0.0625);       glVertex3f(2.5, 5.0, -1.5);

      glNormal3f(0.0, 1.0, 0.0);   //Facing +y (Top side)
      glTexCoord2f(0.0, 0.0625);    glVertex3f(-2.5, 5.0, 1.5);
      glTexCoord2f(0.0625, 0.0625);    glVertex3f(2.5, 5.0,  1.5);
      glTexCoord2f(0.0625, 0.125);    glVertex3f(2.5, 5.0, -1.5);
      glTexCoord2f(0.0, 0.125);    glVertex3f(-2.5, 5.0, -1.5);

      glNormal3f(1.0, 0.0, 0.0);   //Facing -x (Left side)
      glTexCoord2f(0.0625, 0.0625);    glVertex3f(-2.5, 0.0, -1.5);
      glTexCoord2f(0.125, 0.0625);    glVertex3f(-2.5, 0.0,  1.5);
      glTexCoord2f(0.125, 0.125);    glVertex3f(-2.5, 5.0, 1.5);
      glTexCoord2f(0.0625, 0.125);    glVertex3f(-2.5, 5.0, -1.5);

      glNormal3f(-1.0, 0.0, 0.0);   //Facing +x (Right side)
      glTexCoord2f(0.0625, 0.0625);    glVertex3f(2.5, 0.0, 1.5);
      glTexCoord2f(0.125, 0.0625);    glVertex3f(2.5, 0.0,  -1.5);
      glTexCoord2f(0.125, 0.125);    glVertex3f(2.5, 5.0, -1.5);
      glTexCoord2f(0.0625, 0.125);    glVertex3f(2.5, 5.0, 1.5);


    glEnd();
}

//-- Wall ----------------------------------------------------------------
void wall(bool shadow)
{
    if (shadow) {
        glColor4f(0.2, 0.2, 0.2, 1.0);
    } else {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texId[1]);
    }

    glBegin(GL_QUADS);
      glNormal3f(0.0, 0.0, 1.0);   //Facing +z (Front side)
      glTexCoord2f(0.0, 0.0);       glVertex3f(-50.0, 0.0, 7.0);
      glTexCoord2f(1.0, 0.0);       glVertex3f(50.0, 0.0, 7.0);
      glTexCoord2f(1.0, 0.66666);       glVertex3f(50.0, 30.0, 7.0);
      glTexCoord2f(0.0, 0.66666);       glVertex3f(-50.0, 30.0, 7.0);

      glNormal3f(0.0, 0.0, -1.0);   //Facing -z (Back side)
      glTexCoord2f(0.0, 0.0);       glVertex3f(50.0, 0.0, -7.0);
      glTexCoord2f(1.0, 0.0);       glVertex3f(-50.0, 0.0,-7.0);
      glTexCoord2f(1.0, 0.66666);       glVertex3f(-50.0, 30.0,-7.0);
      glTexCoord2f(0.0, 0.66666);       glVertex3f(50.0, 30.0, -7.0);

      glNormal3f(0.0, 1.0, 0.0);   //Facing +y (Top side)
      for(int i = -50; i < 50; i++)
      {
          for(int j = -7;  j < 7; j++)
          {
              glTexCoord2f((i + 50) * 0.01, 0.4492 + (j + 7) * 0.027064286);   glVertex3f(i,   30.0, j  );
              glTexCoord2f((i + 50) * 0.01, 0.4492 + (j + 8) * 0.027064286);   glVertex3f(i,   30.0, j+1);
              glTexCoord2f((i + 51) * 0.01, 0.4492 + (j + 8) * 0.027064286);   glVertex3f(i+1, 30.0, j+1);
              glTexCoord2f((i + 51) * 0.01, 0.4492 + (j + 7) * 0.027064286);   glVertex3f(i+1, 30.0, j  );
          }
      }
    glEnd();

    for (int i = -5; i < 5; i++) {
        glPushMatrix();
            glTranslatef(i * 10, 30, 5.5);
            battlement();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(i * 10, 30, -5.5);
            battlement();
        glPopMatrix();
    }
}

//-- Gate Wall -----------------------------------------------------------
void gate_wall(bool shadow)
{
    // Set Castle Texture
    if (shadow) {
        glColor4f(0.2, 0.2, 0.2, 1.0);
    } else {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texId[1]);
    }

    // Build the walls
    glBegin(GL_QUADS);

        //-- Left of the gate ---------------------------------------
        glNormal3f(0.0, 0.0, 1.0);      //Facing +z (Front Left side)
        glTexCoord2f(0.0, 0.0);         glVertex3f(-50.0, 0.0, 7.0);
        glTexCoord2f(0.4, 0.0);         glVertex3f(-10.0, 0.0, 7.0);
        glTexCoord2f(0.4, 0.66666);     glVertex3f(-10.0, 30.0, 7.0);
        glTexCoord2f(0.0, 0.66666);     glVertex3f(-50.0, 30.0, 7.0);

        glNormal3f(1.0, 0.0, 0.0);      //Facing +x (Middle Left side)
        glTexCoord2f(0.54, 0.0);         glVertex3f(-10.0, 0.0,  -7.0);
        glTexCoord2f(0.4, 0.0);        glVertex3f(-10.0, 0.0,   7.0);
        glTexCoord2f(0.4, 0.66666);     glVertex3f(-10.0, 30.0,  7.0);
        glTexCoord2f(0.54, 0.66666);     glVertex3f(-10.0, 30.0, -7.0);

        glNormal3f(0.0, 0.0, -1.0);     //Facing -z (Back Left side)
        glTexCoord2f(0.54, 0.0);         glVertex3f(-50.0, 0.0, -7.0);
        glTexCoord2f(0.94, 0.0);         glVertex3f(-10.0, 0.0,-7.0);
        glTexCoord2f(0.94, 0.66666);     glVertex3f(-10.0, 30.0,-7.0);
        glTexCoord2f(0.54, 0.66666);     glVertex3f(-50.0, 30.0, -7.0);
        //-----------------------------------------------------------

        //-- Gate section -------------------------------------
        glNormal3f(0.0, 0.0, 1.0);      //Facing +z (Front side)
        glTexCoord2f(0.4, 0.55555);     glVertex3f(-10.0, 25.0, 7.0);
        glTexCoord2f(0.6, 0.55555);     glVertex3f(10.0, 25.0, 7.0);
        glTexCoord2f(0.6, 0.66666);     glVertex3f(10.0, 30.0, 7.0);
        glTexCoord2f(0.4, 0.66666);     glVertex3f(-10.0, 30.0, 7.0);

        glNormal3f(0.0, 0.0, -1.0);     //Facing -z (Back side)
        glTexCoord2f(0.46, 0.55555);     glVertex3f(10.0, 25.0, -7.0);
        glTexCoord2f(0.66, 0.55555);     glVertex3f(-10.0, 25.0,-7.0);
        glTexCoord2f(0.66, 0.66666);     glVertex3f(-10.0, 30.0,-7.0);
        glTexCoord2f(0.46, 0.66666);     glVertex3f(10.0, 30.0, -7.0);

        glNormal3f(0.0, -1.0, 0.0);     //Facing -y (Under side)
        glTexCoord2f(0.0, 0.4492);      glVertex3f(-10.0, 25.0, 7.0);
        glTexCoord2f(1.0, 0.4492);      glVertex3f(10.0, 25.0,  7.0);
        glTexCoord2f(1.0, 0.8281);      glVertex3f(10.0, 25.0, -7.0);
        glTexCoord2f(0.0, 0.8281);      glVertex3f(-10.0, 25.0, -7.0);
        //-----------------------------------------------------------

        //-- Right of the gate --------------------------------------
        glNormal3f(0.0, 0.0, 1.0);      //Facing +z (Front Right side)
        glTexCoord2f(0.6, 0.0);         glVertex3f(10.0, 0.0, 7.0);
        glTexCoord2f(1.0, 0.0);         glVertex3f(50.0, 0.0, 7.0);
        glTexCoord2f(1.0, 0.66666);     glVertex3f(50.0, 30.0, 7.0);
        glTexCoord2f(0.6, 0.66666);     glVertex3f(10.0, 30.0, 7.0);

        glNormal3f(-1.0, 0.0, 0.0);     //Facing -x (Middle Right side)
        glTexCoord2f(0.6, 0.0);         glVertex3f(10.0, 0.0,   7.0);
        glTexCoord2f(0.46, 0.0);         glVertex3f(10.0, 0.0,  -7.0);
        glTexCoord2f(0.46, 0.66666);     glVertex3f(10.0, 30.0, -7.0);
        glTexCoord2f(0.6, 0.66666);     glVertex3f(10.0, 30.0,  7.0);

        glNormal3f(0.0, 0.0, -1.0);     //Facing -z (Back Right side)
        glTexCoord2f(0.46, 0.0);         glVertex3f(10.0, 0.0, -7.0);
        glTexCoord2f(0.06, 0.0);         glVertex3f(50.0, 0.0,-7.0);
        glTexCoord2f(0.06, 0.66666);     glVertex3f(50.0, 30.0,-7.0);
        glTexCoord2f(0.46, 0.66666);     glVertex3f(10.0, 30.0, -7.0);
        //-----------------------------------------------------------

        //-- Top of the wall ----------------------------------------
        glNormal3f(0.0, 1.0, 0.0);      //Facing +y (Top side)
        for(int i = -50; i < 50; i++)
        {
            for(int j = -7;  j < 7; j++)
            {
                glTexCoord2f((i + 50) * 0.01, 0.4492 + (j + 7) * 0.027064286);   glVertex3f(i,   30.0, j  );
                glTexCoord2f((i + 50) * 0.01, 0.4492 + (j + 8) * 0.027064286);   glVertex3f(i,   30.0, j+1);
                glTexCoord2f((i + 51) * 0.01, 0.4492 + (j + 8) * 0.027064286);   glVertex3f(i+1, 30.0, j+1);
                glTexCoord2f((i + 51) * 0.01, 0.4492 + (j + 7) * 0.027064286);   glVertex3f(i+1, 30.0, j  );
            }
        }
    glEnd();

    // Build the parapets
    for (int i = -5; i < 5; i++) {
        glPushMatrix();
            glTranslatef(i * 10, 30, 5.5);
            battlement();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(i * 10, 30, -5.5);
            battlement();
        glPopMatrix();
    }
}

//-- Gate ----------------------------------------------------------------
void gate(bool shadow)
{
    //-- Gate -------------------------------------------------------
    if (shadow) {
        glColor4f(0.2, 0.2, 0.2, 1.0);
    } else {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texId[3]);
    }
    glBegin(GL_QUADS);

        glNormal3f(0.0, 0.0, 1.0);      //Facing +z (Front side)
        glTexCoord2f(0.0, 0.0);     glVertex3f(-11.0, 0.0, 8.0);
        glTexCoord2f(1.0, 0.0);     glVertex3f(11.0, 0.0, 8.0);
        glTexCoord2f(1.0, 1.0);     glVertex3f(11.0, 26.0, 8.0);
        glTexCoord2f(0.0, 1.0);     glVertex3f(-11.0, 26.0, 8.0);

        glNormal3f(0.0, 0.0, -1.0);     //Facing -z (Back side)
        glTexCoord2f(1.0, 1.0);     glVertex3f(11.0, 0.0,  7.0);
        glTexCoord2f(0.0, 1.0);     glVertex3f(-11.0, 0.0, 7.0);
        glTexCoord2f(0.0, 0.0);     glVertex3f(-11.0, 26.0, 7.0);
        glTexCoord2f(1.0, 0.0);     glVertex3f(11.0, 26.0,  7.0);

        glNormal3f(0.0, 1.0, 0.0);     //Facing +y (Top side)
        glTexCoord2f(0.0, 0.0);      glVertex3f(-11.0, 26.0, 8.0);
        glTexCoord2f(0.1, 0.0);      glVertex3f(11.0, 26.0,  8.0);
        glTexCoord2f(0.0, 0.1);      glVertex3f(11.0, 26.0,  7.0);
        glTexCoord2f(0.1, 0.1);      glVertex3f(-11.0, 26.0, 7.0);

        glNormal3f(0.0, -1.0, 0.0);     //Facing -y (Under side)
        glTexCoord2f(0.0, 0.0);      glVertex3f(11.0, 0.0, 7.0);
        glTexCoord2f(0.1, 0.0);      glVertex3f(-11.0, 0.0,  7.0);
        glTexCoord2f(0.1, 0.1);      glVertex3f(-11.0, 0.0,  8.0);
        glTexCoord2f(0.0, 0.1);      glVertex3f(11.0, 0.0, 8.0);

        glNormal3f(-1.0, 0.0, 0.0);     //Facing -x (Left side)
        glTexCoord2f(0.0, 0.4492);      glVertex3f(-11.0, 0.0, 7.0);
        glTexCoord2f(1.0, 0.4492);      glVertex3f(-11.0, 0.0,  8.0);
        glTexCoord2f(1.0, 0.8281);      glVertex3f(-11.0, 26.0, 8.0);
        glTexCoord2f(0.0, 0.8281);      glVertex3f(-11.0, 26.0, 7.0);

        glNormal3f(1.0, 0.0, 0.0);     //Facing +x (Right side)
        glTexCoord2f(0.0, 0.4492);      glVertex3f(11.0, 0.0, 8.0);
        glTexCoord2f(1.0, 0.4492);      glVertex3f(11.0, 0.0,  7.0);
        glTexCoord2f(1.0, 0.8281);      glVertex3f(11.0, 26.0, 7.0);
        glTexCoord2f(0.0, 0.8281);      glVertex3f(11.0, 26.0, 8.0);

    glEnd();
}

//-- Castle --------------------------------------------------------------
void castle(bool shadow)
{
    if (shadow) {
        glColor4f(0.2, 0.2, 0.2, 1.0);
    } else {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texId[1]);
    }

    //-- Towers ------------------------------------
    glPushMatrix();
        glTranslatef(-50, 0, -50);
        tower(shadow);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-50, 0, 50);
        tower(shadow);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(50, 0, -50);
        tower(shadow);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(50, 0, 50);
        tower(shadow);
    glPopMatrix();
    //----------------------------------------------

    //-- Walls -------------------------------------
    glPushMatrix();
        glTranslatef(0, 0, -50);
        wall(shadow);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0, 0, 50);
        gate_wall(shadow);
        glPushMatrix();
            glTranslatef(0, 0, 8);
            glRotatef(gateAngle, 1, 0, 0);
            glTranslatef(0, 0, -8);
            gate(shadow);
        glPopMatrix();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-50, 0, 0);
        glRotatef(90, 0, 1, 0);
        wall(shadow);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(50, 0, 0);
        glRotatef(90, 0, 1, 0);
        wall(shadow);
    glPopMatrix();
    //----------------------------------------------
    glDisable(GL_TEXTURE_2D);
}

//-- Fin for the space ship ----------------------------------------------
void fin()
{
    glBegin(GL_TRIANGLES);
    // Front
        normal(-7, 0, 0.5,
               -2, 5, 0.5,
               -5.5, 6, 0.5);
        glVertex3f(-7.0, 0.0, 0.5);
        glVertex3f(-2.0, 5.0, 0.5);
        glVertex3f(-5.5, 6.0, 0.5);

        normal(-2, 5, 0.5,
               -3, 7.5, 0.5,
               -5.5, 6, 0.5);
        glVertex3f(-2.0, 5.0, 0.5);
        glVertex3f(-3.0, 7.5, 0.5);
        glVertex3f(-5.5, 6.0, 0.5);

    // Back
        normal(-7, 0, -0.5,
               -5.5, 6, -0.5,
               -2, 5, -0.5);
        glVertex3f(-7.0, 0.0, -0.5);
        glVertex3f(-5.5, 6.0, -0.5);
        glVertex3f(-2.0, 5.0, -0.5);

        normal(-2, 5, -0.5,
               -5.5, 6, -0.5,
               -3, 7.5, -0.5);
        glVertex3f(-2.0, 5.0, -0.5);
        glVertex3f(-5.5, 6.0, -0.5);
        glVertex3f(-3.0, 7.5, -0.5);

    // Top
        normal(-5.5, 6, 0.5,
               -3.0, 7.5, 0.5,
               -3.0, 7.5, -0.5);
        glVertex3f(-5.5, 6.0, 0.5);
        glVertex3f(-3.0, 7.5, 0.5);
        glVertex3f(-3.0, 7.5, -0.5);

        normal(-5.5, 6.0, 0.5,
               -3.0, 7.5, -0.5,
               -5.5, 6.0, -0.5);
        glVertex3f(-5.5, 6.0, 0.5);
        glVertex3f(-3.0, 7.5, -0.5);
        glVertex3f(-5.5, 6.0, -0.5);

        normal(-7.0, 0.0, 0.5,
               -5.5, 6.0, 0.5,
               -5.5, 6.0, -0.5);
        glVertex3f(-7.0, 0.0, 0.5);
        glVertex3f(-5.5, 6.0, 0.5);
        glVertex3f(-5.5, 6.0, -0.5);

        normal(-7.0, 0.0, 0.5,
               -5.5, 6.0, -0.5,
               -7.0, 0.0, -0.5);
        glVertex3f(-7.0, 0.0, 0.5);
        glVertex3f(-5.5, 6.0, -0.5);
        glVertex3f(-7.0, 0.0, -0.5);

    //Bottom
        normal(-7.0, 0.0, 0.5,
               -7.0, 0.0, -0.5,
               -5.5, 6.0, -0.5);
        glVertex3f(-7.0, 0.0, 0.5);
        glVertex3f(-7.0, 0.0, -0.5);
        glVertex3f(-5.5, 6.0, -0.5);

        normal(-7.0, 0.0, 0.5,
               -5.5, 6.0, -0.5,
               -5.5, 6.0, 0.5);
        glVertex3f(-7.0, 0.0, 0.5);
        glVertex3f(-5.5, 6.0, -0.5);
        glVertex3f(-5.5, 6.0, 0.5);
    glEnd();
}

//-- Space Ship ----------------------------------------------------------
void spaceShip(bool shadow)
{
    float wx[shipN], wy[shipN], wz[shipN];
    float angStep = 1.0 * 3.1415926 / 180.0;  //Rotate in 10 deg steps (converted to radians)

    // Balls Orbiting Spaceship
    if (shadow) {
        glColor4f(0.2, 0.2, 0.2, 1.0);
    } else {
        glColor4f(1 - shipRedAmount, 1 - shipGreenAmount, 1 - shipBlueAmount, 1.0);
    }

    for (int g = -1; g < 2; g += 2) {
        for (int h = -1; h < 2; h += 2) {
            for (float x = -1.0; x < 2.0; x++)
            {
                for (float y = -1.0; y < 2.0; y++)
                {
                    for (float z = -1.0; z < 2.0; z++)
                    {
                        if (abs(x) < 0.1 || abs(z) < 0.1 && abs(y) > 0.1) {
                            glPushMatrix();
                                glTranslatef(0, shipAltitude, 0);
                                glPushMatrix();
                                    glTranslatef(0, 10, 0);
                                    glRotatef(orbitersAngle * 10, x, y, z);
                                    glTranslatef(0, -10, 0);
                                    glPushMatrix();
                                        glTranslatef(10 * g, 10, 10 * h);
                                        glutSolidSphere(0.5, 20, 20);
                                    glPopMatrix();
                                glPopMatrix();
                            glPopMatrix();
                        }
                    }
                }
            }
        }
    }

    // Translation for take off
    glPushMatrix();
        glTranslatef(0, shipAltitude, 0);
        glRotatef(shipRotationAngle, 0, 1, 0);

        if (shadow) {
            glColor4f(0.2, 0.2, 0.2, 1.0);
        } else {
            glColor4f(shipRedAmount, shipGreenAmount, shipBlueAmount, 1.0);
        }

        //  Include code for drawing the surface of revolution here.
        for (int j = 0; j < 360; j++) {
            for (int i = 0; i < shipN; i++) {
                wx[i] = shipVx[i] * cos(angStep) + shipVz[i] * sin(angStep);
                wy[i] = shipVy[i];
                wz[i] = -shipVx[i] * sin(angStep) + shipVz[i] * cos(angStep);
            }
            glBegin(GL_TRIANGLE_STRIP);
                for (int i = 0; i < shipN; i++) {
                    if (i > 0) normal( wx[i - 1], wy[i - 1], wz[i - 1],
                                       shipVx[i - 1], shipVy[i - 1], shipVz[i - 1],
                                       shipVx[i], shipVy[i], shipVz[i] );
                    glTexCoord2f((j/360.0), (i/float(shipN)));                                   glVertex3f(shipVx[i], shipVy[i], shipVz[i]);
                    if (i > 0) normal( wx[i - 1], wy[i - 1], wz[i - 1],
                                       shipVx[i], shipVy[i], shipVz[i],
                                       wx[i], wy[i], wz[i] );
                    glTexCoord2f(((j + 1)/360.0), ((i)/float(shipN)));                   glVertex3f(wx[i], wy[i], wz[i]);
                }
            glEnd();
            for (int i = 0; i < shipN; i++) {
                shipVx[i] = wx[i];
                shipVy[i] = wy[i];
                shipVz[i] = wz[i];
            }
        }


        // Engines
        if (shadow) {
            glColor4f(0.2, 0.2, 0.2, 1.0);
        } else {
            glColor4f(1, 0, 0, 1);
        }

        glPushMatrix();
            glTranslatef(-2, 2, -2);
            glRotatef(90,-1, 0, 0);
            glutSolidCylinder(1, 10, 20, 10);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-2, 2, 2);
            glRotatef(90,-1, 0, 0);
            glutSolidCylinder(1, 10, 20, 10);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(2, 2, 2);
            glRotatef(90,-1, 0, 0);
            glutSolidCylinder(1, 10, 20, 10);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(2, 2, -2);
            glRotatef(90,-1, 0, 0);
            glutSolidCylinder(1, 10, 20, 10);
        glPopMatrix();

        if (shadow) {
            glColor4f(0.2, 0.2, 0.2, 1.0);
        } else {
            glColor4f(0, 0, 1, 1);
        }

        // Fins
        fin();

        glPushMatrix();
            glRotatef(90, 0, 1, 0);
            fin();
        glPopMatrix();

        glPushMatrix();
            glRotatef(-90, 0, 1, 0);
            fin();
        glPopMatrix();

        glPushMatrix();
            glRotatef(180, 0, 1, 0);
            fin();
        glPopMatrix();
    glPopMatrix();

    // Reset the ship array to its default
    float shipx[shipN] = {0,0.197999999999999,0.391999999999999,0.581999999999999,0.768,0.949999999999998,1.128,1.302,1.472,1.638,1.8,1.958,2.112,2.262,2.408,2.55,2.688,2.822,2.952,3.078,3.2,3.318,3.432,3.542,3.648,3.75,3.848,3.942,4.032,4.118,4.2,4.278,4.352,4.422,4.488,4.55,4.608,4.662,4.712,4.758,4.8,4.838,4.872,4.902,4.928,4.95,4.968,4.982,4.992,4.998,5,4.998,4.992,4.982,4.968,4.95,4.928,4.902,4.872,4.838,4.8,4.758,4.712,4.662,4.608,4.55,4.488,4.422,4.352,4.278,4.2,4.118,4.032,3.942,3.848,3.75,3.648,3.542,3.432,3.318,3.2,3.078,2.952,2.822,2.688,2.55,2.408,2.262,2.112,1.958,1.8,1.638,1.472,1.302,1.128,0.949999999999998,0.768,0.582000000000001,0.391999999999998,0.197999999999999,0};
    float shipy[shipN] = {0.0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4, 2.6, 2.8, 3.0, 3.2, 3.4, 3.6, 3.8, 4.0, 4.2, 4.4, 4.6, 4.8, 5.0, 5.2, 5.4, 5.6, 5.8, 6.0, 6.2, 6.4, 6.6, 6.8, 7.0, 7.2, 7.4, 7.6, 7.8, 8.0, 8.2, 8.4, 8.6, 8.8, 9.0, 9.2, 9.4, 9.6, 9.8, 10.0, 10.2, 10.4, 10.6, 10.8, 11.0, 11.2, 11.4, 11.6, 11.8, 12.0, 12.2, 12.4, 12.6, 12.8, 13.0, 13.2, 13.4, 13.6, 13.8, 14.0, 14.2, 14.4, 14.6, 14.8, 15.0, 15.2, 15.4, 15.6, 15.8, 16.0, 16.2, 16.4, 16.6, 16.8, 17.0, 17.2, 17.4, 17.6, 17.8, 18.0, 18.2, 18.4, 18.6, 18.8, 19.0, 19.2, 19.4, 19.6, 19.8, 20.0};
    float shipz[shipN] = {0.0};

    for (int i = 0; i < shipN; i++) {
        shipVx[i] = shipx[i];
        shipVy[i] = shipy[i];
        shipVz[i] = shipz[i];
    }
}

//-- Robot ---------------------------------------------------------------
void robot(bool wallRobot, bool shadow)
{
    if (shadow) {
        glColor4f(0.2, 0.2, 0.2, 1.0);
    } else {
        glColor4f(0, 0, 0, 1);  // Black
    }

    // Wheels
    glPushMatrix();
        glTranslatef(-2, 0.5, 0);
        glRotatef(90, 0, 1, 0);
        glutSolidCylinder(1, 0.2, 20, 2);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(2, 0.5, 0);
        glRotatef(-90, 0, 1, 0);
        glutSolidCylinder(1, 0.2, 20, 2);
    glPopMatrix();

    if (shadow) {
        glColor4f(0.2, 0.2, 0.2, 1.0);
    } else {
        glColor4f(0, 0, 0.54, 1);  // Dark Blue
    }

    // Base
    glPushMatrix();
        glTranslatef(0, 0.5, 0);
        glScalef(3.9, 0.5, 1);
        glutSolidCube(1);
    glPopMatrix();

    if (shadow) {
        glColor4f(0.2, 0.2, 0.2, 1.0);
    } else {
        glColor4f(0, 0.54, 0, 1);  // Dark Green
    }

    // Legs
    glPushMatrix();
        glTranslatef(-0.75, 0.75, 0);
        glRotatef(-90, 1, 0, 0);
        glutSolidCylinder(0.5, 4, 20, 5);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.75, 0.75, 0);
        glRotatef(-90, 1, 0, 0);
        glutSolidCylinder(0.5, 4, 20, 5);
    glPopMatrix();

    if (shadow) {
        glColor4f(0.2, 0.2, 0.2, 1.0);
    } else {
        glColor4f(0.54, 0, 0, 1);  // Dark Red
    }

    // Torso
    glPushMatrix();
        glTranslatef(0, 6.25, 0);
        glScalef(4, 3, 1);
        glutSolidCube(1);
    glPopMatrix();

    if (shadow) {
        glColor4f(0.2, 0.2, 0.2, 1.0);
    } else {
        glColor4f(0, 0, 0.54, 1);  // Dark Blue
    }

    //Arms
    glPushMatrix();
        glTranslatef(2.25, 7.25, 0);
        glutSolidSphere(0.5, 20, 20);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-2.25, 7.25, 0);
        glutSolidSphere(0.5, 20, 20);
    glPopMatrix();

    // Left Arm
    if (shadow) {
        glColor4f(0.2, 0.2, 0.2, 1.0);
    } else {
        glColor4f(0, 0.54, 0, 1);  // Dark Green
    }
    glPushMatrix();
        if (wallRobot) {
            glTranslatef(2.25, 7.25, 0);
            glRotatef(robotArmsAngle, 1, 0, 0);
            glTranslatef(-2.25, -7.25, 0);
        } else {
            glTranslatef(2.25, 7.25, 0);
            glRotatef(-90, 1, 0, 0);
            glTranslatef(-2.25, -7.25, 0);
        }

        glPushMatrix();
            glTranslatef(2.25, 7.25, 0);
            glRotatef(90, 1, 0, 0);
            glutSolidCylinder(0.25, 3, 20, 20);
        glPopMatrix();

        // Left Hand
        if (shadow) {
            glColor4f(0.2, 0.2, 0.2, 1.0);
        } else {
            glColor4f(0, 0, 0.54, 1);  // Dark Blue
        }

        glPushMatrix();
            glTranslatef(2.25, 3.85, 0);
            glRotatef(-robotHandsAngle, 0, 1, 0);
            glutSolidTorus(0.3, 0.5, 20, 20);
        glPopMatrix();
    glPopMatrix();

    // Right Arm
    if (shadow) {
        glColor4f(0.2, 0.2, 0.2, 1.0);
    } else {
        glColor4f(0, 0.54, 0, 1);  // Dark Green
    }
    glPushMatrix();
        if (wallRobot) {
            glTranslatef(-2.25, 7.25, 0);
            glRotatef(robotArmsAngle, 1, 0, 0);
            glTranslatef(2.25, -7.25, 0);
        } else {
            glTranslatef(-2.25, 7.25, 0);
            glRotatef(-90, 1, 0, 0);
            glTranslatef(2.25, -7.25, 0);
        }

        glPushMatrix();
            glTranslatef(-2.25, 7.25, 0);
            glRotatef(90, 1, 0, 0);
            glutSolidCylinder(0.25, 3, 20, 20);
        glPopMatrix();

        // Right Hand
        if (shadow) {
            glColor4f(0.2, 0.2, 0.2, 1.0);
        } else {
            glColor4f(0, 0, 0.54, 1);  // Dark Blue
        }

        glPushMatrix();
            glTranslatef(-2.25, 3.85, 0);
            glRotatef(robotHandsAngle, 0, 1, 0);
            glutSolidTorus(0.3, 0.5, 20, 20);
        glPopMatrix();
    glPopMatrix();

    // Neck
    if (shadow) {
        glColor4f(0.2, 0.2, 0.2, 1.0);
    } else {
        glColor4f(0, 0, 0.54, 1);  // Dark Blue
    }

    glPushMatrix();
        glTranslatef(0, 8.0, 0);
        glRotatef(90, 1, 0, 0);
        glutSolidCylinder(0.5, 0.25, 20, 20);
    glPopMatrix();

    // Head
    if (shadow) {
        glColor4f(0.2, 0.2, 0.2, 1.0);
    } else {
        glColor4f(0, 0.54, 0, 1);  // Dark Green
    }

    glPushMatrix();
        glTranslatef(0, 8.8, 0);
        glutSolidSphere(1, 20, 20);
    glPopMatrix();

    // Antennae
    if (shadow) {
        glColor4f(0.2, 0.2, 0.2, 1.0);
    } else {
        glColor4f(0, 0, 0.54, 1);  // Dark Blue
    }

    glPushMatrix();
        glTranslatef(0, 8.8, 0);
        glRotatef(-30, 0, 0, 1);
        glPushMatrix();
            glRotatef(-90, 1, 0, 0);
            glutSolidCylinder(0.1, 2, 5, 10);
        glPopMatrix();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0, 8.8, 0);
        glRotatef(30, 0, 0, 1);
        glPushMatrix();
            glRotatef(-90, 1, 0, 0);
            glutSolidCylinder(0.1, 2, 5, 10);
        glPopMatrix();
    glPopMatrix();

    // HeadLight
    glPushMatrix();
        glTranslatef(0, 9.5, 0.4);
        glutSolidCylinder(0.25, 0.6, 20, 5);
    glPopMatrix();

    // Eye Lense
    if (shadow) {
        glColor4f(0.2, 0.2, 0.2, 1.0);
    } else {
        glColor4f(0.545, 0, 0, 1); // Dark Red
    }

    glPushMatrix();
        glTranslatef(0, 8.9, 0.8);
        glScalef(1.5, 0.4, 0.5);
        glutSolidCube(1);
    glPopMatrix();
}

//-- Cannon Balls --------------------------------------------------------
void cannonBall(bool shadow)
{
    if (shadow) {
        glColor4f(0.2, 0.2, 0.2, 1.0);
    } else {
        glColor3f(0.85, 0.85, 0.85);
    }

    glPushMatrix();
        glTranslatef(0, cannonBallYTranslation, cannonBallZTranslation);
        glutSolidSphere(1.0, 20, 20);
    glPopMatrix();
}

//-- Hanger --------------------------------------------------------------
void hangar(bool shadow)
{
    glDisable(GL_TEXTURE_2D);
// Front Wall
    glPushMatrix();
        glTranslatef(0, 0, 8.6);
        glScalef(1.5, 1.5, 1);
        gate(shadow);
    glPopMatrix();

// Left Wall
    glPushMatrix();
        glRotatef(-90, 0, 1, 0);
        glPushMatrix();
            glTranslatef(0, 0, 8.6);
            glScalef(1.5, 1.5, 1);
            gate(shadow);
        glPopMatrix();
    glPopMatrix();

// Right Wall
    glPushMatrix();
        glRotatef(90, 0, 1, 0);
        glPushMatrix();
            glTranslatef(0, 0, 8.6);
            glScalef(1.5, 1.5, 1);
            gate(shadow);
        glPopMatrix();
    glPopMatrix();

// Back Wall
    glPushMatrix();
        glRotatef(180, 0, 1, 0);
        glPushMatrix();
            glTranslatef(0, 0, 8.6);
            glScalef(1.5, 1.5, 1);
            gate(shadow);
        glPopMatrix();
    glPopMatrix();

// Left Lid
    glPushMatrix();
        glTranslatef(-16, 40, 0);
        glRotatef(lidAngle, 0, 0, 1);
        glTranslatef(16, -40, 0);
        glPushMatrix();
            glRotatef(90, 0, 1, 0);
            glTranslatef(0, 32, 0);
            glRotatef(-90, 1, 0, 0);
            glScalef(1.5, 0.63, 1);
            gate(shadow);
        glPopMatrix();
    glPopMatrix();

// Right Lid
    glPushMatrix();
        glTranslatef(16, 40, 0);
        glRotatef(-lidAngle, 0, 0, 1);
        glTranslatef(-16, -40, 0);
        glPushMatrix();
            glRotatef(-90, 0, 1, 0);
            glTranslatef(0, 32, 0);
            glRotatef(-90, 1, 0, 0);
            glScalef(1.5, 0.63, 1);
            gate(shadow);
        glPopMatrix();
    glPopMatrix();
}

//-- Sky Box -------------------------------------------------------------
void skybox(float light[])
{
    float floor_height = -0.1;
    float baseDimension = 2400;
    float roof_height = 1200;

    glEnable(GL_TEXTURE_2D);
    glColor4f(0.7, 0.7, 0.7, 1.0);

    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);

    //--------------------- LEFT WALL ---------------------//
    glBindTexture(GL_TEXTURE_2D, skyboxTexId[0]);
    glNormal3f(1.0, 0.0, 0.0);
    glBegin(GL_QUADS);
        glTexCoord2f(1.0,  0.0);  glVertex3f(-baseDimension, floor_height,  baseDimension);
        glTexCoord2f(0.0, 0.0);  glVertex3f(-baseDimension, floor_height, -baseDimension);
        glTexCoord2f(0.0, 1.0);  glVertex3f(-baseDimension,  roof_height, -baseDimension);
        glTexCoord2f(1.0,  1.0);  glVertex3f(-baseDimension,  roof_height,  baseDimension);
    glEnd();

    //-------------------- FRONT WALL ---------------------//
    glBindTexture(GL_TEXTURE_2D, skyboxTexId[1]);
    glNormal3f(0.0, 0.0, 1.0);
    glBegin(GL_QUADS);
        glTexCoord2f(1.0, 0.0);  glVertex3f(-baseDimension, floor_height, -baseDimension);
        glTexCoord2f(0.0,  0.0);  glVertex3f( baseDimension, floor_height, -baseDimension);
        glTexCoord2f(0.0,  1.0);  glVertex3f( baseDimension,  roof_height, -baseDimension);
        glTexCoord2f(1.0, 1.0);  glVertex3f(-baseDimension,  roof_height, -baseDimension);
    glEnd();

    //--------------------- RIGHT WALL ---------------------//
    glBindTexture(GL_TEXTURE_2D, skyboxTexId[2]);
    glNormal3f(-1.0, 0.0, 0.0);
    glBegin(GL_QUADS);
        glTexCoord2f(1.0,  0.0);  glVertex3f(baseDimension, floor_height, -baseDimension);
        glTexCoord2f(0.0, 0.0);  glVertex3f(baseDimension, floor_height,  baseDimension);
        glTexCoord2f(0.0, 1.0);  glVertex3f(baseDimension,  roof_height,  baseDimension);
        glTexCoord2f(1.0,  1.0);  glVertex3f(baseDimension,  roof_height, -baseDimension);
    glEnd();


    //-------------------- REAR WALL ----------------------//
    glBindTexture(GL_TEXTURE_2D, skyboxTexId[3]);
    glNormal3f(0.0, 0.0, -1.0);
    glBegin(GL_QUADS);
        glTexCoord2f(1.0, 0.0);  glVertex3f( baseDimension, floor_height, baseDimension);
        glTexCoord2f(0.0,  0.0);  glVertex3f(-baseDimension, floor_height, baseDimension);
        glTexCoord2f(0.0,  1.0);  glVertex3f(-baseDimension,  roof_height, baseDimension);
        glTexCoord2f(1.0, 1.0);  glVertex3f( baseDimension,  roof_height, baseDimension);
    glEnd();

    //----------------------- TOP -------------------------//
    glBindTexture(GL_TEXTURE_2D, skyboxTexId[4]);
    glNormal3f(0.0, 1.0, 0.0);
    glBegin(GL_QUADS);
        glTexCoord2f(1.0, 1.0);  glVertex3f(-baseDimension, roof_height, -baseDimension);
        glTexCoord2f(1.0,  0.0);  glVertex3f( baseDimension, roof_height, -baseDimension);
        glTexCoord2f(0.0,  0.0);      glVertex3f( baseDimension, roof_height,  baseDimension);
        glTexCoord2f(0.0, 1.0);      glVertex3f(-baseDimension, roof_height,  baseDimension);
    glEnd();

    // Top Reflection
    light[1] = -light[1]; //Invert light
    glLightfv(GL_LIGHT0, GL_POSITION, light);
    glPushMatrix();
      glScalef(1, -1, 1);
      glBegin(GL_QUADS);
          glTexCoord2f(1.0, 1.0);   glVertex3f(-baseDimension, roof_height, -baseDimension);
          glTexCoord2f(1.0,  0.0);  glVertex3f( baseDimension, roof_height, -baseDimension);
          glTexCoord2f(0.0,  0.0);  glVertex3f( baseDimension, roof_height,  baseDimension);
          glTexCoord2f(0.0, 1.0);   glVertex3f(-baseDimension, roof_height,  baseDimension);
      glEnd();
    glPopMatrix();
    light[1] = -light[1]; //Invert light again
    glLightfv(GL_LIGHT0, GL_POSITION, light);

    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);

    //---------------------- FLOOR ------------------------//
    glBindTexture(GL_TEXTURE_2D, skyboxTexId[5]);
    glNormal3f(0.0, 1.0, 0.0);

    // Outskirts
    glBegin(GL_QUADS);
    for (int i = -12; i < 12; i++) {
        for (int j = -12; j < 12; j++) {
            if (j > 1 || j < -2 || i > 1 || i < -2) {
                glTexCoord2f(0.416666668 + (i + 4) * 0.041666667, 0.416666668 + (j + 4) * 0.041666667);         glVertex3f((i + 1) * 200, floor_height, (j + 1) * 200);
                glTexCoord2f(0.416666668 + (i + 4) * 0.041666667, 0.416666668 + (j + 3) * 0.041666667);         glVertex3f((i + 1) * 200, floor_height, j * 200  );
                glTexCoord2f(0.416666668 + (i + 3) * 0.041666667, 0.416666668 + (j + 3) * 0.041666667);         glVertex3f(i * 200,   floor_height, j * 200  );
                glTexCoord2f(0.416666668 + (i + 3) * 0.041666667, 0.416666668 + (j + 4) * 0.041666667);         glVertex3f(i * 200,   floor_height, (j + 1) * 200);
            }
        }
    }
    glEnd();

    // Nearer the fortress
    glBegin(GL_QUADS);
    for(int i = -400; i < 400; i++)
    {
        for(int j = -400;  j < 400; j++)
        {
            if (abs(j) > 57 || abs(i) > 57) {
                glTexCoord2f((i + baseDimension + 1) * 0.000208333, (j + baseDimension + 1) * 0.000208333);   glVertex3f(i+1, floor_height, j+1);
                glTexCoord2f((i + baseDimension + 1) * 0.000208333, (j + baseDimension) * 0.000208333);       glVertex3f(i+1, floor_height, j  );
                glTexCoord2f((i + baseDimension) * 0.000208333, (j + baseDimension) * 0.000208333);           glVertex3f(i,   floor_height, j  );
                glTexCoord2f((i + baseDimension) * 0.000208333, (j + baseDimension + 1) * 0.000208333);       glVertex3f(i,   floor_height, j+1);
            }
        }
    }
    glEnd();

}

//----------------Display Callback----------------------------------------
void display() 
{
    float light[] = {lightXPosition, 100, lightZPosition, 1};
    float shadowMat[16] = { light[1],0,0,0, -light[0],0,-light[2],
                            -1,0,0,light[1],0,  0,0,0,light[1] };
    float robot_lgt_pos[] = {0.0f, 9.5f, 0.5f, 1.0f};  // Robot light position (the headlight of the robot)
    float spot_pos[] = {0, -1, 1};

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if (camera2) {
        gluLookAt(0, shipAltitude, 0, 0, -90, 0,  1, 0, 0);
    } else {
        gluLookAt(eye_x, eye_y, eye_z, look_x, look_y, look_z,  0, 1, 0);
    }
    glLightfv(GL_LIGHT0, GL_POSITION, light);   //light position

// Draw the hangar
    hangar(false);

// Hangar Shadow
    glDisable(GL_LIGHTING);
    glPushMatrix();
        glMultMatrixf(shadowMat);
        hangar(true);
    glPopMatrix();
    glEnable(GL_LIGHTING);

// Hangar Reflection
    light[1] = -light[1]; //Invert light
    glLightfv(GL_LIGHT0, GL_POSITION, light);
    glPushMatrix();
        glScalef(1, -1, 1);
        hangar(false);
    glPopMatrix();
    light[1] = -light[1]; //Invert light again
    glLightfv(GL_LIGHT0, GL_POSITION, light);

// Draw the castle
    castle(false);

// Castle Reflection
    light[1] = -light[1]; //Invert light
    glLightfv(GL_LIGHT0, GL_POSITION, light);
    glPushMatrix();
        glScalef(1, -1, 1);
        castle(false);
    glPopMatrix();
    light[1] = -light[1]; //Invert light again
    glLightfv(GL_LIGHT0, GL_POSITION, light);

// Castle Shadow
    glDisable(GL_LIGHTING);
    glPushMatrix();
        glMultMatrixf(shadowMat);
        castle(true);
    glPopMatrix();
    glEnable(GL_LIGHTING);

// Draw Cannon
    glPushMatrix();
        glTranslatef(0, 0, 100);
        cannon(false);
        cannonBall(false);
    glPopMatrix();

// Cannon Shadow
    glDisable(GL_LIGHTING);
    glPushMatrix();
        glMultMatrixf(shadowMat);
        glTranslatef(0, 0, 100);
        cannon(true);
        cannonBall(true);
    glPopMatrix();
    glEnable(GL_LIGHTING);

// Draw Space Ship
    spaceShip(false);

// Space Ship Reflection
    light[1] = -light[1]; //Invert light
    glLightfv(GL_LIGHT0, GL_POSITION, light);
    glPushMatrix();
        glScalef(1, -1, 1);
        glTranslatef(0, shipAltitude, 0);
        glRotatef(shipRotationAngle, 0, 1, 0);
        spaceShip(false);
    glPopMatrix();
    light[1] = -light[1]; //Invert light again
    glLightfv(GL_LIGHT0, GL_POSITION, light);

// Space Ship Shadow
    glDisable(GL_LIGHTING);
    glPushMatrix();
        glMultMatrixf(shadowMat);
        glTranslatef(0, shipAltitude, 0);
        glRotatef(shipRotationAngle, 0, 1, 0);
        spaceShip(true);
    glPopMatrix();
    glEnable(GL_LIGHTING);

// Wall Robots
    // Front Wall Robot
    glPushMatrix();
        glTranslatef(30, 30.5, 50);
        glPushMatrix();
            glTranslatef(robotXposition, 0, robotYposition);
            glRotatef(robotAngle, 0, 1, 0);
            glLightfv(GL_LIGHT1, GL_POSITION, robot_lgt_pos);   //robot headlight position
            glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_pos);   //robot headlight direction
            robot(true, false);
        glPopMatrix();

        glDisable(GL_LIGHTING);
        glPushMatrix(); // Shadow on top of wall
            glMultMatrixf(shadowMat);
            glTranslatef(robotXposition, 0, robotYposition);
            glRotatef(robotAngle, 0, 1, 0);
            robot(true, true);
        glPopMatrix();
        glEnable(GL_LIGHTING);
    glPopMatrix();

// Reflection inside castle
    light[1] = -light[1]; //Invert light
    glLightfv(GL_LIGHT0, GL_POSITION, light);
    glPushMatrix();
        glScalef(1, -1, 1);
        glPushMatrix();
            glTranslatef(30, 30.5, 50);
            glPushMatrix();
                glTranslatef(robotXposition, 0, robotYposition);
                glRotatef(robotAngle, 0, 1, 0);
                robot(true, false);
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
    light[1] = -light[1]; //Invert light again
    glLightfv(GL_LIGHT0, GL_POSITION, light);

    glPushMatrix(); // Shadow on ground
        glMultMatrixf(shadowMat);
        glTranslatef(30, 30.5, 50);
        glDisable(GL_LIGHTING);
        glPushMatrix();
            glTranslatef(robotXposition, 0, robotYposition);
            glRotatef(robotAngle, 0, 1, 0);
            robot(true, true);
        glPopMatrix();
        glEnable(GL_LIGHTING);
    glPopMatrix();

    // Back Wall Robot
    glPushMatrix();
        glTranslatef(-30, 30.5, -50);
        glRotatef(180, 0, 1, 0);
        glPushMatrix();
            glTranslatef(robotXposition, 0, robotYposition);
            glRotatef(robotAngle, 0, 1, 0);
            glLightfv(GL_LIGHT2, GL_POSITION, robot_lgt_pos);   //robot headlight position
            glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_pos);   //robot headlight direction
            robot(true, false);
        glPopMatrix();

        glDisable(GL_LIGHTING);
        glPushMatrix(); // Shadow on top of wall
            glMultMatrixf(shadowMat);
            glTranslatef(robotXposition, 0, robotYposition);
            glRotatef(robotAngle, 0, 1, 0);
            robot(true, true);
        glPopMatrix();
        glEnable(GL_LIGHTING);
    glPopMatrix();

    // Reflection inside castle
        light[1] = -light[1]; //Invert light
        glLightfv(GL_LIGHT0, GL_POSITION, light);
        glPushMatrix();
            glScalef(1, -1, 1);
            glPushMatrix();
            glTranslatef(-30, 30.5, -50);
            glRotatef(180, 0, 1, 0);
                glPushMatrix();
                    glTranslatef(robotXposition, 0, robotYposition);
                    glRotatef(robotAngle, 0, 1, 0);
                    robot(true, false);
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();
        light[1] = -light[1]; //Invert light again
        glLightfv(GL_LIGHT0, GL_POSITION, light);

    glPushMatrix(); // Shadow on ground
        glMultMatrixf(shadowMat);
        glTranslatef(-30, 30.5, -50);
        glRotatef(180, 0, 1, 0);
        glDisable(GL_LIGHTING);
        glPushMatrix();
            glTranslatef(robotXposition, 0, robotYposition);
            glRotatef(robotAngle, 0, 1, 0);
            robot(true, true);
        glPopMatrix();
        glEnable(GL_LIGHTING);
    glPopMatrix();

    // Right Wall Robot
    glPushMatrix();
        glTranslatef(50, 30.5, -30);
        glRotatef(90, 0, 1, 0);
        glPushMatrix();
            glTranslatef(robotXposition, 0, robotYposition);
            glRotatef(robotAngle, 0, 1, 0);
            glLightfv(GL_LIGHT3, GL_POSITION, robot_lgt_pos);   //robot headlight position
            glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, spot_pos);   //robot headlight direction
            robot(true, false);
        glPopMatrix();

        glDisable(GL_LIGHTING);
        glPushMatrix(); // Shadow on top of wall
            glMultMatrixf(shadowMat);
            glTranslatef(robotXposition, 0, robotYposition);
            glRotatef(robotAngle, 0, 1, 0);
            robot(true, true);
        glPopMatrix();
        glEnable(GL_LIGHTING);
    glPopMatrix();

    // Reflection inside castle
        light[1] = -light[1]; //Invert light
        glLightfv(GL_LIGHT0, GL_POSITION, light);
        glPushMatrix();
            glScalef(1, -1, 1);
            glPushMatrix();
            glTranslatef(50, 30.5, -30);
            glRotatef(90, 0, 1, 0);
                glPushMatrix();
                    glTranslatef(robotXposition, 0, robotYposition);
                    glRotatef(robotAngle, 0, 1, 0);
                    robot(true, false);
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();
        light[1] = -light[1]; //Invert light again
        glLightfv(GL_LIGHT0, GL_POSITION, light);

    glPushMatrix(); // Shadow on ground
        glMultMatrixf(shadowMat);
        glTranslatef(50, 30.5, -30);
        glRotatef(90, 0, 1, 0);
        glDisable(GL_LIGHTING);
        glPushMatrix();
            glTranslatef(robotXposition, 0, robotYposition);
            glRotatef(robotAngle, 0, 1, 0);
            robot(true, true);
        glPopMatrix();
        glEnable(GL_LIGHTING);
    glPopMatrix();

    // Left Wall Robot
    glPushMatrix();
        glTranslatef(-50, 30.5, 30);
        glRotatef(-90, 0, 1, 0);
        glPushMatrix();
            glTranslatef(robotXposition, 0, robotYposition);
            glRotatef(robotAngle, 0, 1, 0);
            glLightfv(GL_LIGHT4, GL_POSITION, robot_lgt_pos);   //robot headlight position
            glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, spot_pos);   //robot headlight direction
            robot(true, false);
        glPopMatrix();

        glDisable(GL_LIGHTING);
        glPushMatrix(); // Shadow on top of wall
            glMultMatrixf(shadowMat);
            glTranslatef(robotXposition, 0, robotYposition);
            glRotatef(robotAngle, 0, 1, 0);
            robot(true, true);
        glPopMatrix();
        glEnable(GL_LIGHTING);
    glPopMatrix();

    // Reflection inside castle
        light[1] = -light[1]; //Invert light
        glLightfv(GL_LIGHT0, GL_POSITION, light);
        glPushMatrix();
            glScalef(1, -1, 1);
            glPushMatrix();
            glTranslatef(-50, 30.5, 30);
            glRotatef(-90, 0, 1, 0);
                glPushMatrix();
                    glTranslatef(robotXposition, 0, robotYposition);
                    glRotatef(robotAngle, 0, 1, 0);
                    robot(true, false);
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();
        light[1] = -light[1]; //Invert light again
        glLightfv(GL_LIGHT0, GL_POSITION, light);

    glPushMatrix(); // Shadow on ground
        glMultMatrixf(shadowMat);
        glTranslatef(-50, 30.5, 30);
        glRotatef(-90, 0, 1, 0);
        glDisable(GL_LIGHTING);
        glPushMatrix();
            glTranslatef(robotXposition, 0, robotYposition);
            glRotatef(robotAngle, 0, 1, 0);
            robot(true, true);
        glPopMatrix();
        glEnable(GL_LIGHTING);
    glPopMatrix();

    // Patrolling outside robots
    glPushMatrix();
        glRotatef(robotCircleAngle, 0, 1, 0);
        glPushMatrix();
            glTranslatef(110, 0, 0);
            glRotatef(180, 0, 1, 0);
            robot(false, false);
        glPopMatrix();

        // Shadow
        glDisable(GL_LIGHTING);
        glPushMatrix();
            glMultMatrixf(shadowMat);
            glTranslatef(110, 0, 0);
            glRotatef(180, 0, 1, 0);
            robot(false, true);
        glPopMatrix();
        glEnable(GL_LIGHTING);
    glPopMatrix();

    glPushMatrix();
        glRotatef(robotCircleAngle + 180, 0, 1, 0);
        glPushMatrix();
            glTranslatef(110, 0, 0);
            glRotatef(180, 0, 1, 0);
            robot(false, false);
        glPopMatrix();

        // Shadow
        glDisable(GL_LIGHTING);
        glPushMatrix();
            glMultMatrixf(shadowMat);
            glTranslatef(110, 0, 0);
            glRotatef(180, 0, 1, 0);
            robot(false, true);
        glPopMatrix();
        glEnable(GL_LIGHTING);
    glPopMatrix();

    glPushMatrix();
        glRotatef(-robotCircleAngle - 90, 0, 1, 0);
        glPushMatrix();
            glTranslatef(120, 0, 0);
            robot(false, false);
        glPopMatrix();

        // Shadow
        glDisable(GL_LIGHTING);
        glPushMatrix();
            glMultMatrixf(shadowMat);
            glTranslatef(120, 0, 0);
            robot(false, true);
        glPopMatrix();
        glEnable(GL_LIGHTING);
    glPopMatrix();

    glPushMatrix();
        glRotatef(-robotCircleAngle + 90, 0, 1, 0);
        glPushMatrix();
            glTranslatef(120, 0.5, 0);
            robot(false, false);
        glPopMatrix();

        // Shadow
        glDisable(GL_LIGHTING);
        glPushMatrix();
            glMultMatrixf(shadowMat);
            glTranslatef(120, 0, 0);
            robot(false, true);
        glPopMatrix();
        glEnable(GL_LIGHTING);
    glPopMatrix();

//  Draw floors
//    floor();
    castleFloor();

    skybox(light);

    glutSwapBuffers();

    glFlush();
}

//--------------------------Main------------------------------------------
int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH);
   glutInitWindowSize (1920, 1080);
   glutInitWindowPosition (50, 50);
   glutCreateWindow ("Alien Occupation");
   initialise();

   glutTimerFunc(30, robotCircle, 0);
   glutTimerFunc(30, shipColorWarp, 0);
   glutTimerFunc(30, moveRobots, 0);
   glutTimerFunc(30, lightRotation, 0);
   glutSpecialFunc(special);
   glutKeyboardFunc(keyboard);
   glutDisplayFunc(display);
   glutMainLoop();
   return 0;
}
