import math
from random import randint


class Boid:
    max_velocity = 12
    min_distance = 20
    close_distance = 150
    border = 25

    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.vel_x = randint(1, 10) / 10.0
        self.vel_y = randint(1, 10) / 10.0

    def move_away(self, boids):
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

    def move_closer(self, boids):
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

        # distance = math.sqrt(avg_x**2 + avg_y**2) * -1.0

        self.vel_x -= avg_x / 100
        self.vel_y -= avg_y / 100

    def move_with(self, boids):
        if len(boids) < 1:
            return

        avg_x = 0
        avg_y = 0

        for boid in boids:
            avg_x += boid.vel_x
            avg_y += boid.vel_y

        avg_x /= len(boids)
        avg_y /= len(boids)

        self.vel_x += avg_x / 40
        self.vel_y += avg_y / 40

    def move(self):
        if abs(self.vel_x) > Boid.max_velocity or abs(self.vel_y) > Boid.max_velocity:
            scale_factor = Boid.max_velocity / \
                max(abs(self.vel_x), abs(self.vel_y))
            self.vel_x *= scale_factor
            self.vel_y *= scale_factor

        self.x += self.vel_x
        self.y += self.vel_y

    def distance_to(self, boid):
        dist_x = self.x - boid.x
        dist_y = self.y - boid.y
        return math.sqrt(dist_x**2 + dist_y**2)
