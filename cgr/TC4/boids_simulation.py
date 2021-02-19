from class_boid import Boid
from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *

# --MUDE A RESOLUÇÃO AQUI--
width, height = 1600, 900
# --------------^^^^--^^^--
bg_rgba = (0/255, 153/255, 255/255, 1)
QNT_BOIDS = 150
boids = []


def init():
    global boids
    boids = [Boid(width, height) for _ in range(QNT_BOIDS)]


def show_boids():
    global boids
    for b in boids:
        glColor3f(*b.rgb)
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
        # separation: steer to avoid crowding local flockmates
        # alignment: steer towards the average heading of local flockmates
        # cohesion: steer to move towards the average position (center of mass) of local flockmates
        boid.cohesion(close_boids)
        boid.alignment(close_boids)
        boid.separation(close_boids)
        boid.move(width, height)


def draw_scene():
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glClearColor(*bg_rgba)
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


def idle():
    glutPostRedisplay()


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


def update_info(_):
    s = f"Boids = {len(boids)}"
    print(s, " \t\r", end='')
    glutTimerFunc(100, update_info, 0)


if __name__ == "__main__":
    glutInit()
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE)
    glutInitWindowSize(width, height)
    glutCreateWindow("TC4 - Paulo Albuquerque")
    init()
    glutDisplayFunc(draw_scene)
    glutReshapeFunc(reshape)
    glutIdleFunc(idle)
    glutKeyboardFunc(keyboard)
    glutMouseFunc(mouse)

    update_info(0)
    glutMainLoop()
