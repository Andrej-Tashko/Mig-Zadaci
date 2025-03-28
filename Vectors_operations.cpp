#include <iostream>
#include <cmath>
using namespace std;

struct Point {
    double e[4] = {0};
    Point(double x = 0, double y = 0, double z = 0, double w = 1) {
        e[0] = x; e[1] = y; e[2] = z; e[3] = w;
    }
};

struct Matrix {
    double m[4][4] = {0};
    
    Matrix() { for (int i = 0; i < 4; i++) m[i][i] = 1; }
    
    Matrix operator*(const Matrix &second) {
        Matrix result;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                result.m[i][j] = 0;
                for (int k = 0; k < 4; k++) {
                    result.m[i][j] += m[i][k] * second.m[k][j];
                }
            }
        }
        return result;
    }
    
    Point operator*(const Point &p) {
        Point result;
        for (int i = 0; i < 4; i++) {
            result.e[i] = 0;
            for (int j = 0; j < 4; j++) {
                result.e[i] += m[i][j] * p.e[j];
            }
        }
        return result;
    }
};

Matrix translation(double tx, double ty, double tz) {
    Matrix t;
    t.m[0][3] = tx;
    t.m[1][3] = ty;
    t.m[2][3] = tz;
    return t;
}

Matrix scale(double sx, double sy, double sz) {
    Matrix s;
    s.m[0][0] = sx;
    s.m[1][1] = sy;
    s.m[2][2] = sz;
    return s;
}

Matrix rotateX(double angle) {
    Matrix r;
    double c = cos(angle), s = sin(angle);
    r.m[1][1] = c;  r.m[1][2] = -s;
    r.m[2][1] = s;  r.m[2][2] = c;
    return r;
    /*
    Rx(angle) = [ { 1,      0,           0     },
                  { 0, cos(angle), -sin(angle) },
                  { 0, sin(angle),  cos(angle) } ]
    */
}

Matrix rotateY(double angle) {
    Matrix r;
    double c = cos(angle), s = sin(angle);
    r.m[0][0] = c;  r.m[0][2] = s;
    r.m[2][0] = -s; r.m[2][2] = c;
    return r;
    /*
    Ry(angle) = [ { cos(angle),  0, sin(angle) },
                  {       0,     1,      0     },
                  { -sin(angle), 0, cos(angle) } ]
    */
}

Matrix rotateZ(double angle) {
    Matrix r;
    double c = cos(angle), s = sin(angle);
    r.m[0][0] = c;  r.m[0][1] = -s;
    r.m[1][0] = s;  r.m[1][1] = c;
    return r;
    /*
    Rx(angle) = [ { cos(angle), -sin(angle), 0 },
                  { sin(angle),  cos(angle), 0 },
                  {      0,           0,     1 } ]
    */
}

ostream &operator<<(ostream &os, const Point &p) {
    os << "[ " << p.e[0] << ' ' << p.e[1] << ' ' << p.e[2] << ' ' << p.e[3] << " ]\n";
    return os;
}

int main() {
    Point p1(1, 2, 3);          // Point (1,2,3)
    
    Matrix t = translation(5, -3, 2);   // Translate by (5, -3, 2)
    Matrix s = scale(2, 2, 2);          // Scale by 2 in all axes
    Matrix rx = rotateX(M_PI / 2);      // Rotate 90 degrees around X-axis
    Matrix ry = rotateY(M_PI / 4);      // Rotate 45 degrees around Y-axis
    Matrix rz = rotateZ(M_PI / 1);      // Rotate 180 degrees around Z-axis
    
    Point p2 = t * p1;
    Point p3 = s * p1;
    Point p4 = rx * p1;
    Point p5 = ry * p1;
    Point p6 = rz * p1;
    
    cout << "Translated: " << p2;
    cout << "Scaled: " << p3;
    cout << "Rotated X: " << p4;
    cout << "Rotated Y: " << p5;
    cout << "Rotated Z: " << p6;
    
    return 0;
}
