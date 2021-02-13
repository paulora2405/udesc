from class_boid import Boid
from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *
from random import randint

width, height = 1600, 900
QNT_BOIDS = 150
boids = []


def init():
    global boids
    boids = [Boid(randint(0, width), randint(0, height))
             for _ in range(QNT_BOIDS)]


def show_boids():
    global boids
    for b in boids:
        glLineWidth(3.0)
        glBegin(GL_LINES)
        glVertex3f(b.x, b.y, 0)
        off_x = b.vel_x
        off_y = b.vel_y
        glVertex3f(b.x + off_x, b.y + off_y, 0)
        glEnd()


def boid_interaction():
    for boid in boids:
        close_boids = []
        for other in boids:
            if other is boid:
                continue
            distance = boid.distance_to(other)
            if distance < Boid.close_distance:
                close_boids.append(other)

        boid.move_closer(close_boids)
        boid.move_with(close_boids)
        boid.move_away(close_boids)

        if boid.x < Boid.border and boid.vel_x < 0:
            boid.vel_x *= - randint(1, 10) / 5.0
            boid.vel_y *= 1 + randint(1, 10) / 5.0

        if boid.x > width - Boid.border and boid.vel_x > 0:
            boid.vel_x *= - randint(1, 10) / 5.0
            boid.vel_y *= 1 + randint(1, 10) / 5.0

        if boid.y < Boid.border and boid.vel_y < 0:
            boid.vel_y *= - randint(1, 10) / 5.0
            boid.vel_x *= 1 + randint(1, 10) / 5.0

        if boid.y > height - Boid.border and boid.vel_y > 0:
            boid.vel_y *= - randint(1, 10) / 5.0
            boid.vel_x *= 1 + randint(1, 10) / 5.0

        boid.move()


def draw_scene():
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glClearColor(0/255, 153/255, 255/255, 1)
    glEnable(GL_LINE_SMOOTH)  # anti-aliasing
    # glClearColor(0, 0, 0, 1)
    glMatrixMode(GL_MODELVIEW)
    glColor3f(255/255, 20/255, 0/255)
    # glColor3f(1, 1, 1)
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


glutInit()
glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE)
glutInitWindowSize(width, height)
glutCreateWindow("TC4 - Paulo Albuquerque")
init()
glutDisplayFunc(draw_scene)
glutReshapeFunc(reshape)
glutIdleFunc(draw_scene)
glutMainLoop()
