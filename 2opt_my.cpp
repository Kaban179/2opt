#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <time.h>
#include <fstream>

#include <filesystem>
namespace fs = std::filesystem;



using namespace std;

class Point {
private:
    double x, y;
    int number;

public:
    Point() : x(0), y(0),  number(0){}

    Point(double x, double y, int num) : x(x), y(y) , number(num){}

    double distanceTo(const Point& other) const {
        double dx = x - other.x;
        double dy = y - other.y;
        return sqrt(dx * dx + dy * dy);
    }



    void setX(double x) { this->x = x; }
    void setY(double y) { this->y = y; }


    double getX() const { return x; }
    double getY() const { return y; }
    int get_number() const {return number; }
};


double dist(Point& p1, Point& p2){
    double dx = p1.getX() - p2.getX();
    double dy = p1.getY() - p2.getY();
    return sqrt(dx * dx + dy * dy);
}



double dist_path(std::vector<Point>& points){
    int i;
    double ans;
    for (i = 1; i < points.size(); i++){
        ans += dist(points[i], points[i - 1]);
    }
    return ans;
}

int main() {
    std::string line;
    std::string path = "data/data";
    for (const auto & entry : fs::directory_iterator(path)){
        std::ifstream in(entry.path()); // окрываем файл для чтения
        std::vector<Point> points;
        int n;
        in >> n;

        points.resize(n);


        for (int i = 0; i < n; ++i) {
            double x, y;
            in >> x >> y;
            points[i] = Point(x, y, i);
        }

        in.close();

        clock_t start = clock();

        for (int i = 0; i < n; ++i) {

            //std::cout << points[i].getX() << " " << points[i].getY() << "\n";
        }

        for (int i = 0; i < n - 1; i++){
            for (int j = i + 2; j < n; j++){
                float delta_dist = - dist(points[i], points[i+1]) - dist(points[j], points[j+1]) + dist(points[i+1], points[j+1]) + dist(points[i], points[j]);
                if (delta_dist < 0){
                    i++;
                    while (i < j){
                        Point temp = points[i];
                        points[i] = points[j];
                        points[j] = temp;
                        i++;
                        j--;
                    }
                }
            }
        }
        for (int i = 0; i < n; i++){
            //std::cout << points[i].get_number();
        }
        clock_t end = clock();
        double time = (double)(end - start) / CLOCKS_PER_SEC;
        std::cout << "\n " << entry.path() << "  " << dist_path(points) << "  " << time;
    }




    return 0;
}
