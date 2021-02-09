from OpenGL.GL import *
from OpenGL.GLUT import *
from OpenGL.GLU import *
from constants import *
from formas_complexas import SolidPrismaTriangular

horizontal_angle = 300.0
spinning = True
turn_direction = 1
quality = 100
scale = 8.0


def keyboard(key, x, y):
    # funcao keyboard padrao, para controlar o giro do modelo
    global spinning, horizontal_angle, angle_v, quality, turn_direction, turn_v

    key = ord(key)

    if key == ord('b'):  # B para para de girar ou resumir
        spinning = not spinning
    elif key == ord('g'):  # G para girar para a esquerda
        turn_direction = -1
    elif key == ord('h'):  # H para girar para a direita
        turn_direction = 1
    else:
        horizontal_angle = 300.0
        turn_direction = 1


def draw():
    global spinning, horizontal_angle, angle_v

    glMatrixMode(GL_MODELVIEW)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)  # remove tudo da tela

    # argumentos: rgb + alpha
    glClearColor(*light_blue, 1.0)
    glLoadIdentity()
    gluLookAt(20.0, 3.0, 20.0, 0.0,  2.0,  0.0, 0.0,  1.0,  0.0)

    # Controle de camera
    if spinning:
        horizontal_angle += turn_direction*0.5
    horizontal_angle %= 360
    glRotatef(horizontal_angle, 0, 1, 0)

    # chao externo
    glPushMatrix()
    glColor3f(*light_gray)
    glBegin(GL_QUADS)
    glNormal3f(0.0, 1.0,   0.0)
    glVertex3f(-30.0, 0.0, -30.0)
    glVertex3f(-30.0, 0.0,  30.0)
    glVertex3f(30.0, 0.0,  30.0)
    glVertex3f(30.0, 0.0, -30.0)
    glEnd()

    # chao do forte
    glColor3f(*orange_dark)
    glBegin(GL_QUADS)
    glNormal3f(0.0,  1.0,  0.0)
    glVertex3f(-scale, 0.01, -scale)
    glVertex3f(-scale, 0.01,  scale)
    glVertex3f(scale, 0.01,  scale)
    glVertex3f(scale, 0.01, -scale)
    glEnd()

    # torre grande
    glPushMatrix()
    glColor3f(*amber)
    glTranslatef(0.0, 3.25, 0.0)
    glPushMatrix()
    glScaled(3.7, 10, 3.7)
    glutSolidCube(1.0)
    glPopMatrix()
    glColor3f(*orange)
    glTranslatef(0.0, 6.5, 0.0)
    SolidPrismaTriangular(4, 3, 4)
    glPopMatrix()

    # portao do forte
    glPushMatrix()
    glColor3f(*amber)
    glTranslatef(8, 0, -2)
    glPushMatrix()
    glScaled(2.1, 8.5, 2.4)
    glutSolidCube(1.0)
    glPopMatrix()
    glColor3f(*orange_dark)
    glTranslatef(0.0, 5.1, 0.0)
    SolidPrismaTriangular(3, 2, 4.5)
    glPopMatrix()
    glPushMatrix()
    glColor3f(*amber)
    glTranslatef(8, 0, 2)
    glPushMatrix()
    glScaled(2.1, 8.5, 2.4)
    glutSolidCube(1.0)
    glPopMatrix()
    glColor3f(*orange_dark)
    glTranslatef(0.0, 5.1, 0.0)
    SolidPrismaTriangular(3, 2, 4.5)
    glPopMatrix()

    # torre simples 1
    torreSimples(amber, orange_dark, scale, scale)

    # torre simples 2
    torreSimples(amber, orange_dark, scale, -scale)

    # torre simples 3
    torreSimples(amber, orange_dark, -scale, -scale)

    # torre simples 4
    torreSimples(amber, orange_dark, -scale, scale)

    # muro entre 1-2
    muroEntreTorre(amber, scale, scale/2, 1, scale-2)
    muroEntreTorre(amber, scale, -scale/2, 1, scale-2)

    # muro entre 2-3
    muroEntreTorre(amber, 0, -scale, 2*scale, 1)

    # muro entre 3-4
    muroEntreTorre(amber, -scale, 0, 1, 2*scale)

    # muro entre 1-4
    muroEntreTorre(amber, 0, scale, 2*scale, 1)

    glEnable(GL_BLEND)
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)
    glDisable(GL_BLEND)
    glPopMatrix()

    glFlush()
    glutSwapBuffers()


def torreSimples(tower_color, roof_color, x, y):
    glPushMatrix()
    glTranslatef(x, 0.0, y)
    glRotated(-90.0, 1, 0, 0)
    glColor3f(*tower_color)
    glutSolidCylinder(1.4, 6.0, 12, 1)
    glRotated(90.0, 1, 0, 0)

    glColor3f(*roof_color)
    glTranslatef(0.0,  6.0, 0.0)
    glRotated(-90.0, 1, 0, 0)
    glutSolidCone(1.9, 2.1, 12, 12)
    glPopMatrix()


def muroEntreTorre(wall_color, x, y, u, v):
    glPushMatrix()
    glColor3f(*wall_color)
    glTranslatef(x, 1.8, y)
    glScaled(u, 3.6, v)
    glutSolidCube(1.0)
    glPopMatrix()


size_w = 800
size_h = 600
ratio = size_w/size_h
glutInit()
glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH)
glutInitWindowSize(size_w, size_h)
glutCreateWindow("Forte - Paulo Albuquerque")
glutDisplayFunc(draw)
glutIdleFunc(draw)
glutKeyboardFunc(keyboard)

glViewport(0, 0, size_w, size_h)
glLoadIdentity()
glMatrixMode(GL_PROJECTION)
gluPerspective(45, ratio, .01, 100.0)
glMatrixMode(GL_MODELVIEW)
glShadeModel(GL_SMOOTH)
glClearDepth(1.0)
glEnable(GL_DEPTH_TEST)
glDepthFunc(GL_LEQUAL)
glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST)
glClearColor(0.0, 0.0, 0.0, 1.0)

# configurações de textura e luz, não sei exatamente oq cada uma faz
glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular)
glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess)
glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient)
glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse)
glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular)
glLightfv(GL_LIGHT0, GL_POSITION, light_position)
glEnable(GL_LIGHTING)
glEnable(GL_LIGHT0)
glEnable(GL_COLOR_MATERIAL)
glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE)

glutMainLoop()
