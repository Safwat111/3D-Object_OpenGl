#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>

// Define the cube vertices
GLfloat vertices[][3] = {
    {-1.0, -1.0, -1.0},
    {-1.0, 1.0, -1.0},
    {1.0, 1.0, -1.0},
    {1.0, -1.0, -1.0},
    {-1.0, -1.0, 1.0},
    {-1.0, 1.0, 1.0},
    {1.0, 1.0, 1.0},
    {1.0, -1.0, 1.0}
};

// Define the cube faces
GLubyte indices[][4] = {
    {0, 1, 2, 3},
    {3, 2, 6, 7},
    {7, 6, 5, 4},
    {4, 5, 1, 0},
    {1, 5, 6, 2},
    {4, 0, 3, 7}
};

// Define the cube colors
GLfloat colors[][3] = {
    {0.8, 0.0, 0.0}, // red
    {0.0, 0.8, 0.0}, // green
    {0.0, 0.0, 0.8}, // blue
    {0.8, 0.8, 0.0}, // yellow
    {0.8, 0.0, 0.8}, // magenta
    {0.0, 0.8, 0.8} // cyan
};

// Define the initial position, scale, and rotation of the cube
GLfloat position[] = { 0.0, 0.0, -5.0 };
GLfloat scale[] = { 0.8, 0.8, 0.8 };
GLfloat rotation[] = { 0.0, 0.0, 0.0 };

// Define the mouse dragging variables
int mouse_x, mouse_y;
bool mouse_left_pressed = false;

// Define the display function
void display()
{
    // Set color of background 
    glClearColor(0.8, 0.9, 0.9, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Push the current matrix onto the stack
    glPushMatrix();

    // Apply the translation, scaling, and rotationtransformationsto the matrix
    glTranslatef(position[0], position[1], position[2]);
    glScalef(scale[0], scale[1], scale[2]);
    glRotatef(rotation[0], 1.0, 0.0, 0.0);
    glRotatef(rotation[1], 0.0, 1.0, 0.0);
    glRotatef(rotation[2], 0.0, 0.0, 1.0);

    // Set the color of the vertices for each face of the cube
    glBegin(GL_QUADS);
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 4; j++) {
            glColor3fv(colors[i]); // set the color for each vertex in the face
            glVertex3fv(vertices[indices[i][j]]);
        }
    }
    glEnd();

    //Pop the matrix from the stack
    glPopMatrix();

    // Flush the OpenGL commands and swap the buffers
    glutSwapBuffers();
}

// Define the reshape function
void reshape(int width, int height)
{
    // Set the viewport to cover the entire window
    glViewport(0, 0, width, height);

    // Set the projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)width / (GLfloat)height, 0.1, 100.0);

    // Set the matrix mode to modelview
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Define the keyboard function to handle key events
void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 'q':
    case 'Q':
    case 27: // Escape key
        exit(0);
        break;
    }
}

// Define the special keyboard function to handle arrow key events
void specialKeyboard(int key, int x, int y)
{
    switch (key) {
    case GLUT_KEY_LEFT:
        if (glutGetModifiers() == GLUT_ACTIVE_CTRL) { //Scale down using ctrl + left arrow
            scale[0] -= 0.1;
            scale[1] -= 0.1;
            scale[2] -= 0.1;
        }
        else {
            position[0] -= 0.1; //move left
        }
        break;
    case GLUT_KEY_RIGHT:
        if (glutGetModifiers() == GLUT_ACTIVE_CTRL) { //Scale up using ctrl + right arrow
            scale[0] += 0.1;
            scale[1] += 0.1;
            scale[2] += 0.1;
        }
        else {
            position[0] += 0.1; //move right
        }
        break;
    case GLUT_KEY_UP:
        if (glutGetModifiers() == GLUT_ACTIVE_CTRL) { //Scale up using ctrl + up arrow
            scale[0] += 0.1;
            scale[1] += 0.1;
            scale[2] += 0.1;
        }
        else {
            position[1] += 0.1; //move up
        }
        break;
    case GLUT_KEY_DOWN:
        if (glutGetModifiers() == GLUT_ACTIVE_CTRL) { //Scale down using ctrl + down arrow
            scale[0] -= 0.1;
            scale[1] -= 0.1;
            scale[2] -= 0.1;
        }
        else {
            position[1] -= 0.1; //move down
        }
        break;
    }
}

// Define the mouse function to handle mouse events
void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            mouse_x = x;
            mouse_y = y;
            mouse_left_pressed = true;
        }
        else if (state == GLUT_UP) {
            mouse_left_pressed = false;
        }
    }
}

// Define the motion function to handlemouse motion events
void motion(int x, int y)
{
    if (mouse_left_pressed) {
        int dx = x - mouse_x;
        int dy = y - mouse_y;
        rotation[1] += dx;
        rotation[0] += dy;
        mouse_x = x;
        mouse_y = y;
    }
}

// Define the idle function to continuously update the display
void idle()
{
    glutPostRedisplay();
}

// Define the main function
int main(int argc, char** argv)
{
    // Initialize GLUT and create the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(640, 480);
    glutCreateWindow("CS402 Project");

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);

    // Register the callback functions
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutIdleFunc(idle);

    // Enter the main event loop
    glutMainLoop();

    return 0;
}