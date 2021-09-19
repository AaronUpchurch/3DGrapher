#include <SFML/Graphics.hpp>
#include <vector>
#include "Line.h"
#include <iostream>
#include <windows.h>
#include "Side.h"
using namespace std;
using namespace sf;
vector<float> multiply(vector<float> xyz, vector<vector<float>> matrix) {
    float x = xyz.at(0) * matrix.at(0).at(0) + xyz.at(1) * matrix.at(0).at(1) + xyz.at(2) * matrix.at(0).at(2);
    float y = xyz.at(0) * matrix.at(1).at(0) + xyz.at(1) * matrix.at(1).at(1) + xyz.at(2) * matrix.at(1).at(2);
    float z = xyz.at(0) * matrix.at(2).at(0) + xyz.at(1) * matrix.at(2).at(1) + xyz.at(2) * matrix.at(2).at(2);
   
    vector<float> temp;
    temp.push_back(x);
    temp.push_back(y);
    temp.push_back(z);
    return temp;
}
void zoom(vector<Line>& cube, float amount) {   //// PLUS TO SHIFT!!!!//
    for (int i = 0; i < cube.size(); ++i) {
        cube.at(i).x0 *= amount;
        cube.at(i).x1 *= amount;
        cube.at(i).y0 *= amount;
        cube.at(i).y1 *= amount;
        cube.at(i).z0 *= amount;
        cube.at(i).z1 *= amount;
    }
}
void shiftX(vector<Line>& cube, float amount) {   //// PLUS TO SHIFT!!!!//
    for (int i = 0; i < cube.size(); ++i) {
        cube.at(i).x0 += amount;
        cube.at(i).x1 += amount;
        
    }
}
void shiftY(vector<Line>& cube, float amount) {   //// PLUS TO SHIFT!!!!//
    for (int i = 0; i < cube.size(); ++i) {
        cube.at(i).y0 += amount;
        cube.at(i).y1 += amount;

    }
}
void shiftZ(vector<Line>& cube, float amount) {   //// PLUS TO SHIFT!!!!//
    for (int i = 0; i < cube.size(); ++i) {
        cube.at(i).z0 += amount;
        cube.at(i).z1 += amount;

    }
}
void updateSide2(ConvexShape& side, vector<Line>& cube) {
    side.setPoint(0, cube.at(0).lines[1].position);
    side.setPoint(1, cube.at(1).lines[1].position);
    side.setPoint(3, cube.at(4).lines[1].position);
    side.setPoint(2, cube.at(5).lines[1].position);
}
void genRotate(vector<Line>& cube, vector<vector<float>>& matrix) {
    
    for (int i = 0; i < cube.size(); ++i) { //rotates points seperately, then remakes line//
        vector<float> start;
        start.push_back(cube.at(i).x0);
        start.push_back(cube.at(i).y0);
        start.push_back(cube.at(i).z0);
        start = multiply(start, matrix);
        vector<float> end;
        end.push_back(cube.at(i).x1);
        end.push_back(cube.at(i).y1);
        end.push_back(cube.at(i).z1);
        end = multiply(end, matrix);
        cube.at(i).x0 = start.at(0);
        cube.at(i).y0 = start.at(1);
        cube.at(i).z0 = start.at(2);
        cube.at(i).x1 = end.at(0);
        cube.at(i).y1 = end.at(1);
        cube.at(i).z1 = end.at(2);
    }
    
}
int getClosestPoint(vector<Line>& cube) { // returns number for closest of 8 vertices to point (0,1,0)//
    float one = cube.at(0).y0;
    float two = cube.at(0).y1;
    float three = cube.at(1).y0;
    float four = cube.at(1).y1;
    float five = cube.at(4).y0;
    float six = cube.at(4).y1;
    float seven = cube.at(5).y0;
    float eight = cube.at(5).y1;
    
    vector<float> values;
    values.push_back(one);
    values.push_back(two);
    values.push_back(three);
    values.push_back(four);
    values.push_back(five);
    values.push_back(six);
    values.push_back(seven);
    values.push_back(eight);
    float max = values.at(0);
    int maxIndex = 0;
    for (int i = 0; i < 8; ++i) {
       
        if (values.at(i) > max) {
            maxIndex = i;
            max = values.at(i);
        }
    }
    return 1 + maxIndex;

    

}
int main()
{
    RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");
    
    RectangleShape border({ 900,900 });
    Color Grey({ 100,100,100 });
    border.setOutlineColor(Grey);
    border.setFillColor(Color::Transparent);
    border.setOutlineThickness(2);
    border.setPosition({ 50,50 });

    RectangleShape upBorder({ 1, 900 });
    upBorder.setFillColor(Grey);
    upBorder.setPosition({ 500,50 });

    RectangleShape horBorder({ 900, 1 });
    horBorder.setFillColor(Grey);
    horBorder.setPosition({ 50,500 });

    vector<Line> cube;
    int length = 250;
    
    cube.push_back(Line(-length, length, -length, length,length, -length, Color::Blue));   //bottom//
    cube.push_back(Line(-length, -length, -length, length, -length, -length, Color::Blue));
    cube.push_back(Line(-length, -length, -length, -length, length, -length, Color::Blue));
    cube.push_back(Line(length, -length, -length, length, length, -length, Color::Blue));
    
    
    cube.push_back(Line(-length, length, length, length, length, length, Color::Red));  //top//
    cube.push_back(Line(-length, -length, length, length, -length, length, Color::Red));
    cube.push_back(Line(-length, -length, length, -length, length, length, Color::Red));
    cube.push_back(Line(length, -length, length, length, length, length, Color::Red));

    cube.push_back(Line(-length, -length, -length, -length, -length, length, Color::White)); //sides//
    cube.push_back(Line(-length, length, -length, -length, length, length, Color::White));
    cube.push_back(Line(length, -length, -length, length, -length, length, Color::White));
    cube.push_back(Line(length, length, -length, length, length, length, Color::White));
    

    float amount = .005;  //keep same, else errors with measuring 360* rotatio //
    float xDeg = amount;
    float yDeg = amount;
    float zDeg = amount;

    vector<vector<float>> XRotMatrix;
    vector<float> Xa;
    Xa.push_back(1);
    Xa.push_back(0);
    Xa.push_back(0);
    vector<float> Xb;
    Xb.push_back(0);
    Xb.push_back(cos(amount));
    Xb.push_back(-sin(amount));
    vector<float> Xc;
    Xc.push_back(0);
    Xc.push_back(sin(amount));
    Xc.push_back(cos(amount));
    XRotMatrix.push_back(Xa);
    XRotMatrix.push_back(Xb);
    XRotMatrix.push_back(Xc);

    vector<vector<float>> negXRotMatrix;
    vector<float> negXa;
    negXa.push_back(1);
    negXa.push_back(0);
    negXa.push_back(0);
    vector<float> negXb;
    negXb.push_back(0);
    negXb.push_back(cos(-amount));
    negXb.push_back(-sin(-amount));
    vector<float> negXc;
    negXc.push_back(0);
    negXc.push_back(sin(-amount));
    negXc.push_back(cos(-amount));
    negXRotMatrix.push_back(negXa);
    negXRotMatrix.push_back(negXb);
    negXRotMatrix.push_back(negXc);

    vector<vector<float>> YRotMatrix;
    vector<float> Ya;
    Ya.push_back(cos(amount));
    Ya.push_back(0);
    Ya.push_back(sin(amount));
    vector<float> Yb;
    Yb.push_back(0);
    Yb.push_back(1);
    Yb.push_back(0);
    vector<float> Yc;
    Yc.push_back(-sin(amount));
    Yc.push_back(0);
    Yc.push_back(cos(amount));
    YRotMatrix.push_back(Ya);
    YRotMatrix.push_back(Yb);
    YRotMatrix.push_back(Yc);

    vector<vector<float>> negYRotMatrix;
    vector<float> negYa;
    negYa.push_back(cos(-amount));
    negYa.push_back(0);
    negYa.push_back(sin(-amount));
    vector<float> negYb;
    negYb.push_back(0);
    negYb.push_back(1);
    negYb.push_back(0);
    vector<float> negYc;
    negYc.push_back(-sin(-amount));
    negYc.push_back(0);
    negYc.push_back(cos(-amount));
    negYRotMatrix.push_back(negYa);
    negYRotMatrix.push_back(negYb);
    negYRotMatrix.push_back(negYc);
    
    vector<vector<float>> ZRotMatrix;
    vector<float> Za;
    Za.push_back(cos(amount));
    Za.push_back(-sin(amount));
    Za.push_back(0);
    vector<float> Zb;
    Zb.push_back(sin(amount));
    Zb.push_back(cos(amount));
    Zb.push_back(0);
    vector<float> Zc;
    Zc.push_back(0);
    Zc.push_back(0);
    Zc.push_back(1);
    ZRotMatrix.push_back(Za);
    ZRotMatrix.push_back(Zb);
    ZRotMatrix.push_back(Zc);

    vector<vector<float>> negZRotMatrix;
    vector<float> negZa;
    negZa.push_back(cos(-amount));
    negZa.push_back(-sin(-amount));
    negZa.push_back(0);
    vector<float> negZb;
    negZb.push_back(sin(-amount));
    negZb.push_back(cos(-amount));
    negZb.push_back(0);
    vector<float> negZc;
    negZc.push_back(0);
    negZc.push_back(0);
    negZc.push_back(1);
    negZRotMatrix.push_back(negZa);
    negZRotMatrix.push_back(negZb);
    negZRotMatrix.push_back(negZc);

    bool aut = false;
    
    Side front;
    int f[8] = {4,1,4,0,0,0,0,1 };
    Side bs;
    int b[8] = { 4,1,4,0,6,0,7,0 };
    bs.shape.setFillColor(Color::Green);
    Side cs;
    int c[8] = {4,1,11,0,10,0,7,0};
    cs.shape.setFillColor(Color::Yellow);
    Side ds;
    int d[8] = { 8,0,9,0,11,0,10,0 };
    ds.shape.setFillColor(Color::Red);
    Side as;
    int a[8] = { 8,0,3,0,7,0,5,0 };
    as.shape.setFillColor(Color::Magenta);
    Side zs;
    int z[8] = { 8,0,0,0,4,0,6,0 };
    zs.shape.setFillColor(Color::Cyan);
    

    float xCheck = 0;
    float yCheck = 0;
    float zCheck = 0;

    bool thisSideA = false;
    bool thisSideB = false;
    bool thisSideC = false;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        
        window.draw(border);
        window.draw(upBorder);
        window.draw(horBorder);
        
        
        
       
        
        if (aut) {
            genRotate(cube, XRotMatrix);
            genRotate(cube, YRotMatrix);
            genRotate(cube, ZRotMatrix);
          
        }
        else {
            if (GetAsyncKeyState(0x57)) {
                zoom(cube, 1.0001);
                genRotate(cube, XRotMatrix);
                
            }
            
            if (GetAsyncKeyState(VK_TAB)) {
                zoom(cube,1.001);
            }
            if (GetAsyncKeyState(VK_SPACE)) {
                zoom(cube, .999);
            }
            if (GetAsyncKeyState(VK_UP)) {
                genRotate(cube, negXRotMatrix);
                xCheck -= amount;
            }
            if (GetAsyncKeyState(VK_LEFT)) {
                genRotate(cube, negYRotMatrix);
                yCheck -= amount;
            }
            if (GetAsyncKeyState(VK_DOWN)) {
                genRotate(cube, XRotMatrix);
                xCheck += amount;
            }
            if (GetAsyncKeyState(VK_RIGHT)) {
                genRotate(cube, YRotMatrix);
                yCheck += amount;
            }
            if (GetAsyncKeyState(VK_SHIFT)) {
                genRotate(cube, ZRotMatrix);
                zCheck += amount;
            }
            if (GetAsyncKeyState(VK_CONTROL)) {
                genRotate(cube, negZRotMatrix);
                zCheck -= amount;
            }
        }


        for (int i = 0; i < cube.size(); ++i) {
            window.draw(cube.at(i).getDrawAble());
        }
        front.update(cube, f);
        bs.update(cube,b);
        cs.update(cube, c);
        ds.update(cube, d);
        as.update(cube, a);
        zs.update(cube, z);
        
        cout << getClosestPoint(cube) << endl;
        /*if (front.cross()) {
            thisSideA = !thisSideA;
        }
        if (thisSideA) {
            window.draw(zs.shape);
        }
        else {
            window.draw(cs.shape);
        }
        
        /*if () {
            window.draw(zs.shape);
        }
        else {
            window.draw(cs.shape);
        }
        if ((int)(zCheck / PI / 2) % 2 == 0) {
            window.draw(ds.shape);
        }
        else {
            window.draw(bs.shape);
        }
        */
        
        window.display();
    }

    return 0;
}