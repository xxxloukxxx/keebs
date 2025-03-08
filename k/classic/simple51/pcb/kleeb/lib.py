from KicadModTree import *
import math, os

LAYERS_BACK = Pad.LAYERS_CONNECT_BACK
LAYERS_FRONT = Pad.LAYERS_CONNECT_FRONT
LAYERS_THT = Pad.LAYERS_THT
LAYERS_FTHT = ['*.Cu', 'F.Mask']
LAYERS_BTHT = ['*.Cu', 'B.Mask']
LAYERS_SMT_BOTH = ['*.Cu', '*.Mask', '*.Paste']

def footprint(dir: str, name: str, smd: bool, entities: list):
    fp = Footprint(name)
    if smd:
        fp.setAttribute("smd")
    fp.extend(entities)
    KicadFileHandler(fp).writeFile(os.path.normpath(os.path.dirname(__file__) + f"/{dir}.pretty/{name}.kicad_mod"))

def vecadd(a, b):
    return (a[0] + b[0], a[1] + b[1])

def rounded_rect(x: float, y: float, w: float, h: float, r: float, layer: str):
    # start from top right
    centers = [
        (x + w/2 - r, y - h/2 + r),
        (x + w/2 - r, y + h/2 - r),
        (x - w/2 + r, y + h/2 - r),
        (x - w/2 + r, y - h/2 + r),
    ]
    points = [
        vecadd(centers[0], (0, -r)),
        vecadd(centers[0], (r, 0)),
        vecadd(centers[1], (r, 0)),
        vecadd(centers[1], (0, r)),
        vecadd(centers[2], (0, r)),
        vecadd(centers[2], (-r, 0)),
        vecadd(centers[3], (-r, 0)),
        vecadd(centers[3], (0, -r)),
    ]
    entities = []
    for i in range(4):
        entities += [
            Arc(start=points[i*2], end=points[i*2+1], center=centers[i], layer=layer),
            Line(start=points[i*2-1], end=points[i*2], layer=layer),
        ]
    return entities

def cap_outline(outline, shrink=0):
    return rounded_rect(*outline[:2], outline[2] - shrink, outline[3] - shrink, 1, 'Dwgs.User')

def npth(x, y, r):
    return Pad(type=Pad.TYPE_NPTH, shape=Pad.SHAPE_CIRCLE, at=(x, y), size=(r, r), drill=r, layers=Pad.LAYERS_NPTH)

def pth(n, x, y, p, r, layers):
    return Pad(number=n, type=Pad.TYPE_THT, shape=Pad.SHAPE_CIRCLE, at=(x, y), size=(p, p), drill=r, layers=layers)

def x_mir(p):
    return (-p[0], p[1])

def lines(pts: list[tuple[float, float]], width: float | None = None, layer=None) -> list:
    layer = {"layer": layer} if layer != None else {}
    width = {"width": width} if width != None else {}
    return [Line(start=pts[i], end=pts[i + 1], **width, **layer) for i in range(len(pts) - 1)]

def line_pad(n, pts: list[tuple[float, float]], pos: tuple[float, float], layers, width):
    return Pad(number=n, type=Pad.TYPE_SMT, shape=Pad.SHAPE_CUSTOM, at=pos, size=(width, width),
               primitives=lines(pts, width=width), layers=layers)
