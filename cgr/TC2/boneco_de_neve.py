from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *
from constants import *

horizontal_angle = 300.0
turn_direction = 1
spinning = True
quality = 100


def draw():
    global spinning, angle_v, horizontal_angle

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)  # remove tudo da tela

    # argumentos rgb + alpha
    glClearColor(*dark_gray, 1.0)
    glLoadIdentity()
    gluLookAt(4.2, 1.4, 0.0, 0.0, 0.4, 0.0, 0.0, 1.0, 0.0)

    # rotação da camera
    if spinning:
        horizontal_angle += turn_direction
    horizontal_angle = horizontal_angle % 360

    glRotatef(horizontal_angle, 0, 1, 0)

    # começa a renderizar as formas
    glPushMatrix()
    glTranslatef(0.0, 0.15, 0.0)

    # chao
    glPushMatrix()
    glTranslatef(0.0, -0.3, 0.0)
    glRotatef(90, 1, 0, 0)
    glColor3f(*white)
    glutSolidCylinder(5.0, 0.002, 100, 1)
    glPopMatrix()

    glColor3f(*white)

    # parte de baixo do boneco
    glTranslatef(0.0, 0.0, 0.0)
    glutSolidSphere(0.45, quality, quality*2)

    # peito do boneco
    glTranslatef(0.0, 0.45, 0.0)
    glutSolidSphere(0.3, quality, quality*2)

    # cabeça do boneco
    glTranslatef(0.0, 0.35, 0.0)
    glutSolidSphere(0.25, quality, quality*2)

    # olho esquerdo
    glPushMatrix()
    glRotatef(-26.0, 0, 1, 0)
    glTranslatef(0.21, 0.08, 0.0)
    glColor3f(0.1, 0.1, 0.1)
    glutSolidSphere(0.04, 8, 8)
    glPopMatrix()

    # olho direito
    glPushMatrix()
    glRotatef(26.0, 0, 1, 0)
    glTranslatef(0.21, 0.08, 0.0)
    glutSolidSphere(0.04, 8, 8)
    glPopMatrix()

    # cenoura do nariz
    glPushMatrix()
    glTranslatef(0.22, -0.01, 0.0)
    glRotatef(90, 0, 1, 0)
    glColor3f(*orange)
    glutSolidCone(0.03, 0.18, 8, 6)
    glPopMatrix()

    glDisable(GL_BLEND)
    glPopMatrix()
    # termina de renderizar tudo
    glFlush()
    glutSwapBuffers()


def keyboard(key, x, y):
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


size_w = 800
size_h = 800
ratio = size_w/size_h
glutInit()
glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH)
glutInitWindowSize(size_w, size_h)
glutCreateWindow("Boneco de neve - Paulo Albuquerque")
glutDisplayFunc(draw)
glutIdleFunc(draw)
glutKeyboardFunc(keyboard)

glMatrixMode(GL_PROJECTION)
glViewport(0, 0, size_w, size_h)
glMatrixMode(GL_PROJECTION)
glLoadIdentity()
gluPerspective(45, ratio, 0.01, 100.0)
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
