from class_boid import Boid
from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *

width, height = 1600, 900
QNT_BOIDS = 150
boids = []


def init():
    global boids
    boids = [Boid(width, height) for _ in range(QNT_BOIDS)]


def show_boids():
    global boids
    for b in boids:
        glColor3f(b.red, b.green, b.blue)
        glLineWidth(8.0)
        glBegin(GL_LINES)
        glVertex3f(b.x, b.y, 0)
        off_x = b.vel_x * 2
        off_y = b.vel_y * 2
        glVertex3f(b.x + off_x, b.y + off_y, 0)
        glEnd()


def boid_interaction():
    for boid in boids:
        close_boids = boid.get_close_boids(boids)
        boid.move_closer(close_boids)
        boid.move_with(close_boids)
        boid.move_away(close_boids)
        boid.move(width, height)


def draw_scene():
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glClearColor(0/255, 153/255, 255/255, 1)
    # glEnable(GL_LINE_SMOOTH)  # anti-aliasing
    glDisable(GL_LINE_SMOOTH)  # no anti-aliasing
    glMatrixMode(GL_MODELVIEW)
    show_boids()
    boid_interaction()
    glutSwapBuffers()


def reshape(w, h):
    glViewport(0, 0, w, h)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    glOrtho(0.0, width, 0.0, height, 0.0, 1.0)
    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()


def keyboard(key, x, y):
    key = ord(key)
    if key == ord(' '):
        boids.clear()
    elif key == ord('m'):
        for _ in range(10):
            boids.append(Boid(width, height))
    elif key == ord('n'):
        try:
            for _ in range(10):
                boids.pop()
        except IndexError:
            pass
    elif key == ord('s'):
        glutDestroyWindow(glutGetWindow())


def mouse(button, state, x, y):
    if button == GLUT_LEFT_BUTTON:
        if state == GLUT_DOWN:
            boids.append(Boid.from_pos(x, height - y))

    elif button == GLUT_RIGHT_BUTTON:
        if state == GLUT_DOWN:
            try:
                boids.pop()
            except IndexError:
                pass


glutInit()
glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE)
glutInitWindowSize(width, height)
glutCreateWindow("TC4 - Paulo Albuquerque")
init()
glutDisplayFunc(draw_scene)
glutReshapeFunc(reshape)
glutIdleFunc(draw_scene)
glutKeyboardFunc(keyboard)
glutMouseFunc(mouse)
glutMainLoop()
