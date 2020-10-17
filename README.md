## Adding a future Circle Class:
1. Radius member variable required
2. CheckPointInObject() would need to be redfined/overriden in the derived Circle Class: if the distance from the point to the center is >radius then the point is outside, else inside. 

## Assumptions:
1. The x, y location of a shape is assumed to be in the center of the shape.
2. Shapes dervied from the Shape parent class are assumed to be convex shapes (ie. squares, rectangles, circles, triangles, etc).
3. Height and Width are measured from end to end of the shape, not from the center.
4. Height and Width are non-negative values.
5. checkPointInObject() is a universal check for all convex shapes (triangles, squares, rectangles, pentagons, hexagons, etc).
6. Coordinate plane has (0,0) at the top left corner of the plane with X increasing to the right, and Y increasing downwards.