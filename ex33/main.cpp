/*
 * Exercise 33:
 * - Да се състави клас масив от точки (обекти от клас точка) с методи:
 *   - конструктор за създаване на празен масив,
 *   - добавяне на нова точка към масива,
 *   - предефинирана операция << за извеждане на съдържанието на масива на екрана,
 *   - за изчисляване на разстоянието между две точки,
 *   - предефинирана операция [],
 *   - член-функция за модифициране на масива чрез замяна на точките в него с
 *     огледалните им копия (спрямо началото на координатната система).
 * - Да се състави главна функция, която тества класа като създава обект от
 *   клас масив от точки, добавя известен брой точки към него, визуализира
 *   масива и модифицирания масив.
 * - Данните да се съхраняват във файл.
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <sstream>

using namespace std;

class Point
{
private:
    int x_;
    int y_;

public:
    Point(int x = 0, int y = 0) : x_(x), y_(y) {}

    ~Point()
    {
        cout << "Point with coordinates x = " << x_ << " and y = " << y_ << " is destroying " << endl;
        x_ = 0;
        y_ = 0;
    }

    int getX() const { return x_; }
    int getY() const { return y_; }

    void setX(int x) { x_ = x; }
    void setY(int y) { y_ = y; }

    void mirrorPoint()
    {
        x_ = -x_;
        y_ = -y_;
    }

    string printPoint(int index) const
    {
        stringstream ss;

        ss << "Point [" << index << "] = x = " << x_
           << ", y = " << y_;

        return ss.str();
    }
};

class PointsArray
{
private:
    vector<Point> points;

public:
    PointsArray() {}

    void insertPoint(const Point &point)
    {
        points.push_back(point);
    }

    double getDistanceBetween(const Point &point1, const Point &point2)
    {
        return sqrt(pow(point2.getX() - point1.getX(), 2) + pow(point2.getY() - point1.getY(), 2));
    }

    Point &operator[](int index)
    {
        return points[index];
    }

    void mirrorPoints()
    {
        for (Point &point : points)
        {
            point.mirrorPoint();
        }
    }

    friend ostream &operator<<(ostream &out, const PointsArray &pointsArray)
    {
        out << "PointArray with " << pointsArray.points.size() << " points:\n";

        for (int index = 0; index < pointsArray.points.size(); index++)
        {
            out << pointsArray.points[index].printPoint(index) << endl;
        }

        return out;
    }

    ~PointsArray()
    {
        cout << "Destroying points array" << endl;
        points.clear();
    }
};

int main()
{
    PointsArray pointsArray;

    pointsArray.insertPoint(Point(1, 2));
    pointsArray.insertPoint(Point(3, -4));
    pointsArray.insertPoint(Point(-2, 5));
    pointsArray.insertPoint(Point(0, 3));

    cout << "Original array:\n"
         << pointsArray << endl;

    cout << "Distance between points 0 and 2: "
         << pointsArray.getDistanceBetween(pointsArray[0], pointsArray[2]) << endl
         << endl;

    pointsArray.mirrorPoints();
    cout << "After mirroring all points:\n"
         << pointsArray << endl;
    return 0;
}
