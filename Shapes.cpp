/*
    Author: Linden Kwok
    Date: October 17, 2020
*/

#include <iostream>
#include <tuple>
#include <vector>
#include <assert.h>

class Shape
{
protected:
    double width, height, xCenter, yCenter;
    unsigned int numVertices;
    std::vector<std::tuple<double, double>> vertexList; //<x,y>
    std::vector<std::tuple<std::tuple<double, double>, std::tuple<double, double>>> edgeList; //<pt1(x,y), pt2(x,y)>

public:
    Shape(double x, double y, double h, double w, unsigned int v) : width(w), height(h), xCenter(x), yCenter(y), numVertices(v) {}
    Shape(int v) : width(0), height(0), xCenter(0), yCenter(0), numVertices(v) {};

    virtual ~Shape() {}

    Shape(const Shape &shapeToCopy)
    {
        width = shapeToCopy.width;
        height = shapeToCopy.height;
        xCenter = shapeToCopy.xCenter;
        yCenter = shapeToCopy.yCenter;
        numVertices = shapeToCopy.numVertices;
        vertexList = shapeToCopy.vertexList;
        edgeList = shapeToCopy.edgeList;
    }

    Shape &operator=(const Shape &shapeToCopy)
    {
        if (this != &shapeToCopy)
        {
            width = shapeToCopy.width;
            height = shapeToCopy.height;
            xCenter = shapeToCopy.xCenter;
            yCenter = shapeToCopy.yCenter;
            numVertices = shapeToCopy.numVertices;
            vertexList = shapeToCopy.vertexList;
            edgeList = shapeToCopy.edgeList;
        }
        return *this;
    }

    friend bool operator==(const Shape &lfSide, const Shape &rtSide)
    {
        return (lfSide.xCenter == rtSide.xCenter && lfSide.yCenter == rtSide.yCenter && lfSide.height == rtSide.height && lfSide.width == rtSide.width && rtSide.numVertices == lfSide.numVertices);
    }

    virtual bool checkPointInObject(double x, double y)
    {
        for (size_t i = 0; i < edgeList.size(); ++i)
        {
            std::tuple<double, double> v1 = std::get<1>(edgeList[i]);
            std::tuple<double, double> v2 = std::get<0>(edgeList[i]);

            double test = (std::get<0>(v2) - std::get<0>(v1)) * (y - std::get<1>(v1)) - (x - std::get<0>(v1)) * (std::get<1>(v2) - std::get<1>(v1));
            if (test < 0)
            {
                return false;
            }
        }
        return true;
    };

    double getX() {return xCenter;}
    double getY() {return yCenter;}
    double getHeight() {return height;} 
    double getWidth() {return width;} 
};

class Rectangle : public Shape
{
public:
    Rectangle(double x, double y, double h, double w) : Shape(x, y, h, w, 4)
    {
        vertexList.push_back(std::make_tuple(x - width / 2, y - height / 2));
        vertexList.push_back(std::make_tuple(x - width / 2, y + height / 2));
        vertexList.push_back(std::make_tuple(x + width / 2, y + height / 2));
        vertexList.push_back(std::make_tuple(x + width / 2, y - height / 2));
        edgeList.push_back(std::make_tuple(vertexList[0], vertexList[1]));
        edgeList.push_back(std::make_tuple(vertexList[1], vertexList[2]));
        edgeList.push_back(std::make_tuple(vertexList[2], vertexList[3]));
        edgeList.push_back(std::make_tuple(vertexList[3], vertexList[0]));
    }
    Rectangle() : Shape(4) {}
};

int main()
{
    //constructor test
    Rectangle r1(5,0,10,8);
    assert(r1.getX() == 5);
    assert(r1.getY() == 0);
    assert(r1.getHeight() == 10);
    assert(r1.getWidth() == 8);
 
    //copy constructor test
    Rectangle r2 = r1;
    assert(r2.getX() == 5);
    assert(r2.getY() == 0);
    assert(r2.getHeight() == 10);
    assert(r2.getWidth() == 8);

    //overloaded equality operator test
    assert(r1 == r2);
    Rectangle r3;
    assert((r1 == r3) == false);

    //overloaded assignment operator test
    r3 = r1;
    assert(r3 == r1);

    //point in object tests
    Rectangle r4(0,0,10,10); //rectangle at (0,0) W:10, H:10
    //point inside object
    assert(r4.checkPointInObject(1,1) == true);
    //point far outside object
    assert(r4.checkPointInObject(100,100) == false);
    //point close to object edge
    assert(r4.checkPointInObject(6,0) == false); 
    //point on object line/edge
    assert(r4.checkPointInObject(5,0) == true);
    //point on object center
    assert(r4.checkPointInObject(0,0) == true);
    //point on vertex
    assert(r4.checkPointInObject(5,5) == true);

    std::cout<<"All Tests Passed..."<<std::endl;
    return 0;
}