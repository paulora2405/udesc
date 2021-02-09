from random import randint
from OpenGL.GL import *
from OpenGL.GLUT import *
from OpenGL.GLU import *


QNT_DROPS = 1000
Drops = []
GRAVITY = -0.01
VIEW_OFFSET = 20


class Drop:
    def __init__(self):
        global VIEW_OFFSET
        self.x = randint(-20, 20)
        self.y = randint(10, 60)
        self.z = randint(-20, 20) - VIEW_OFFSET
        self.vel = -randint(1, 10)/5


def init():
    global Drops
    Drops = [Drop() for i in range(QNT_DROPS)]


def showDrops():
    global Drops, GRAVITY
    for d in Drops:
        glLineWidth(2.0)
        glBegin(GL_LINES)
        glVertex3f(d.x, d.y, d.z)
        glVertex3f(d.x, d.y + 0.5, d.z)
        glEnd()

        d.y += d.vel
        d.vel += GRAVITY
        if d.vel < -1:  # velocidade terminal
            d.vel = -1

        if(d.y < -randint(20, 40)):
            d.__init__()  # recria a gota para variar as outras coordenadas tambem


def drawScene():
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glClearColor(93/255, 138/255, 168/255, 1)  # 93,138,168
    glMatrixMode(GL_MODELVIEW)
    glColor3f(160.0/255.0, 32.0/255, 240.0/255)  # cor da gota

    showDrops()

    glutSwapBuffers()


def reshape(w, h):
    glViewport(0, 0, w, h)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    gluPerspective(55, w / h, .1, 200)
    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()


def idle():
    glutPostRedisplay()


glutInit()
glutInitDisplayMode(GLUT_DEPTH | GLUT_RGB | GLUT_DOUBLE)
glutInitWindowSize(640, 600)
glutCreateWindow("PURPLE RAIN\t\t\tTC3 - Paulo Albuquerque")
init()
glutDisplayFunc(drawScene)
glutReshapeFunc(reshape)
glutIdleFunc(idle)
glutMainLoop()
