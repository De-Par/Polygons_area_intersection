from math import fabs
import matplotlib.pyplot as plt

EPS = 1e-9


class Point:
    def __init__(self, pnt_x: float, pnt_y: float) -> None:
        self.x = pnt_x
        self.y = pnt_y

    def __str__(self) -> str:
        return f'({self.x}, {self.y})'

    def __hash__(self) -> int:
        return hash((self.x, self.y))


class LineSegment:
    def __init__(self, pnt_1: Point, pnt_2: Point) -> None:
        self.p1 = pnt_1
        self.p2 = pnt_2

    def __str__(self) -> str:
        return f'({self.p1}, {self.p2})'

    def length(self) -> float:
        return ((self.p1.x - self.p2.x) ** 2 + (self.p1.y - self.p2.y) ** 2) ** 0.5


class Polygon:
    def __init__(self, vec_p: list[Point]) -> None:
        self.points = vec_p

    def __str__(self) -> str:
        return ', '.join([p.__str__() for p in self.points])

    def line_segments(self) -> list[LineSegment]:
        return ([LineSegment(p_1, p_2) for p_1, p_2 in zip(self.points, self.points[1:])] +
                [LineSegment(self.points[-1], self.points[0])])

    def area(self) -> float:
        square = 0.0
        pv = self.points + [self.points[0]]
        for fr, to in zip(pv, pv[1:]):
            square += fr.x * to.y - to.x * fr.y
        return fabs(square) / 2


def denominator(seg_1: LineSegment, seg_2: LineSegment) -> float:
    return ((seg_2.p2.y - seg_2.p1.y) * (seg_1.p2.x - seg_1.p1.x) -
            (seg_2.p2.x - seg_2.p1.x) * (seg_1.p2.y - seg_1.p1.y))


def line_segments_intersection(seg_1: LineSegment, seg_2: LineSegment) -> Point | None:
    if ((seg_1.p1.x == seg_1.p2.x and seg_1.p1.y == seg_1.p2.y) or
            (seg_2.p1.x == seg_2.p2.x and seg_2.p1.y == seg_2.p2.y)):
        return None
    dnm = denominator(seg_1, seg_2)
    if fabs(dnm) < EPS:
        return None
    u1 = ((seg_2.p2.x - seg_2.p1.x) * (seg_1.p1.y - seg_2.p1.y) -
          (seg_2.p2.y - seg_2.p1.y) * (seg_1.p1.x - seg_2.p1.x)) / dnm
    u2 = ((seg_1.p2.x - seg_1.p1.x) * (seg_1.p1.y - seg_2.p1.y) -
          (seg_1.p2.y - seg_1.p1.y) * (seg_1.p1.x - seg_2.p1.x)) / dnm
    if u1 < 0 or u1 > 1 or u2 < 0 or u2 > 1:
        return None
    return Point(seg_1.p1.x + u1 * (seg_1.p2.x - seg_1.p1.x), seg_1.p1.y + u1 * (seg_1.p2.y - seg_1.p1.y))


def inside(pnt: Point, pol: Polygon) -> bool:
    is_inside = False
    j = len(pol.points) - 1
    for ind in range(len(pol.points)):
        xi, yi = pol.points[ind].x, pol.points[ind].y
        xj, yj = pol.points[j].x, pol.points[j].y
        intersect = ((yi > pnt.y) != (yj > pnt.y)) and (pnt.x < (xj - xi) * (pnt.y - yi) / (yj - yi) + xi)
        if intersect:
            is_inside = not is_inside
        j = ind
    return is_inside


def min_y_point(pnt_v: list[Point]) -> Point:
    cp = pnt_v[0]
    for p in pnt_v[1:]:
        if p.y < cp.y or (fabs(p.y - cp.y) < EPS and p.x < cp.x):
            cp = p
    return cp


def orientation(prev: Point, cand: Point, curr: Point) -> float:
    return (cand.y - prev.y) * (curr.x - cand.x) - (cand.x - prev.x) * (curr.y - cand.y)


def dist(pnt_1: Point, pnt_2: Point) -> float:
    return ((pnt_2.x - pnt_1.x) ** 2 + (pnt_2.y - pnt_1.y) ** 2) ** 0.5


def convex_hull(pnt_v: list[Point]) -> list[Point]:
    src_p = min_y_point(pnt_v)
    hull = [src_p]
    prev_p = src_p

    while True:
        cand_p = None
        for curr_p in pnt_v:
            if curr_p == prev_p:
                continue
            if cand_p is None:
                cand_p = curr_p
                continue
            area_sign = orientation(prev_p, cand_p, curr_p)
            if area_sign < 0 or (area_sign < EPS and dist(prev_p, cand_p) < dist(prev_p, curr_p)):
                cand_p = curr_p
        if cand_p == src_p:
            break
        hull.append(cand_p)
        prev_p = cand_p
    return hull


if __name__ == '__main__':
    f = open('test.txt')
    num_polygons = int(f.readline())
    polygons = []
    for i in range(num_polygons):
        num_points = int(f.readline())
        points = []
        for _ in range(num_points):
            x, y = list(map(float, f.readline().split()))
            points.append(Point(x, y))
        if len(set(points)) >= 3:
            ch = convex_hull(points)
            xs, ys = [p.x for p in ch] + [ch[0].x], [p.y for p in ch] + [ch[0].y]
            plt.plot(xs, ys)
            polygons.append(Polygon(ch))
        del points, ch

    flag = True
    while len(polygons) > 1:
        pol1, pol2 = polygons.pop(), polygons.pop()
        st = set()
        for p1 in pol1.points:
            if inside(p1, pol2):
                st.add(p1)
        for p2 in pol2.points:
            if inside(p2, pol1):
                st.add(p2)
        for line1 in pol1.line_segments():
            for line2 in pol2.line_segments():
                point = line_segments_intersection(line1, line2)
                if point is not None:
                    st.add(point)
        if len(st) == 0:
            flag = False
            break
        points = convex_hull(list(st))
        polygons.append(Polygon(points))
        del points, st

    if flag and len(polygons) == 1:
        coord = polygons[0].points + [polygons[0].points[0]]
        xs, ys = [p.x for p in coord], [p.y for p in coord]
        plt.plot(xs, ys)
        plt.fill(xs, ys, color='#82ffa5')

    plt.show()
    area = 0.0 if len(polygons) != 1 or not flag else polygons[0].area()
    print(f'Area of intersection is {area}')
    if flag:
        print('Vertexes:', polygons.pop())
    del polygons
