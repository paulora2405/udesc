from ctypes import ArgumentError
import math
from random import randint, uniform, choice


class Boid:
    max_velocity = 10
    min_distance = 20
    close_distance = 150
    border = 25

    def __init__(self, *args):
        self.x = 0
        self.y = 0
        if len(args) == 2:
            width, height = args[0], args[1]
            if width % 2 != 0:
                width += 1
            if height % 2 != 0:
                height += 1
            self.x = randint(0, width/2) + width/4
            self.y = randint(0, height/2) + height/4
        elif args:
            raise ArgumentError

        self.vel_x = randint(4, 8) * choice([-1, 1])
        self.vel_y = randint(4, 8) * choice([-1, 1])
        # custom color
        self.rgb = (uniform(0.3, 1.0), uniform(0.3, 1.0), uniform(0.12, 0.4))

    @classmethod
    def from_pos(cls, x, y):
        self = cls()
        self.x = x
        self.y = y
        return self

    def separation(self, boids):
        if len(boids) < 1:
            return

        dis_x = 0
        dis_y = 0
        num_close = 0

        for boid in boids:
            if boid is self:
                continue

            distance = self.distance_to(boid)
            if distance < Boid.min_distance:
                num_close += 1
                x_diff = self.x - boid.x
                y_diff = self.y - boid.y

                if x_diff >= 0:
                    x_diff = math.sqrt(Boid.min_distance) - x_diff
                else:
                    x_diff = -math.sqrt(Boid.min_distance) - x_diff

                if y_diff >= 0:
                    y_diff = math.sqrt(Boid.min_distance) - y_diff
                else:
                    y_diff = -math.sqrt(Boid.min_distance) - y_diff

                dis_x += x_diff
                dis_y += y_diff

        if num_close == 0:
            return

        self.vel_x -= dis_x/5
        self.vel_y -= dis_y/5

    def cohesion(self, boids):
        if len(boids) < 1:
            return

        avg_x = 0
        avg_y = 0

        for boid in boids:
            if boid is self:
                continue

            avg_x += self.x - boid.x
            avg_y += self.y - boid.y

        avg_x /= len(boids)
        avg_y /= len(boids)

        self.vel_x -= avg_x / 100
        self.vel_y -= avg_y / 100

    def alignment(self, boids):
        if len(boids) < 1:
            return

        avg_x = 0
        avg_y = 0

        for boid in boids:
            if boid is self:
                continue
            avg_x += boid.vel_x
            avg_y += boid.vel_y

        avg_x /= len(boids)
        avg_y /= len(boids)

        self.vel_x += avg_x / 40
        self.vel_y += avg_y / 40

    def move(self, width, height):
        if self.x < Boid.border and self.vel_x < 0:
            self.vel_x *= - randint(1, 10) / 5.0
            self.vel_y *= 1 + randint(1, 10) / 5.0

        if self.x > width - Boid.border and self.vel_x > 0:
            self.vel_x *= - randint(1, 10) / 5.0
            self.vel_y *= 1 + randint(1, 10) / 5.0

        if self.y < Boid.border and self.vel_y < 0:
            self.vel_y *= - randint(1, 10) / 5.0
            self.vel_x *= 1 + randint(1, 10) / 5.0

        if self.y > height - Boid.border and self.vel_y > 0:
            self.vel_y *= - randint(1, 10) / 5.0
            self.vel_x *= 1 + randint(1, 10) / 5.0

        if abs(self.vel_x) > Boid.max_velocity or abs(self.vel_y) > Boid.max_velocity:
            scale_factor = Boid.max_velocity / \
                max(abs(self.vel_x), abs(self.vel_y))
            self.vel_x *= scale_factor
            self.vel_y *= scale_factor

        self.x += self.vel_x
        self.y += self.vel_y

    def get_close_boids(self, boids):
        close_boids = []
        for other in boids:
            if other is self:
                continue
            distance = self.distance_to(other)
            if distance < Boid.close_distance:
                close_boids.append(other)
        return close_boids

    def distance_to(self, boid):
        dist_x = self.x - boid.x
        dist_y = self.y - boid.y
        return math.sqrt(dist_x**2 + dist_y**2)
