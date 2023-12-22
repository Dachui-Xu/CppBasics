#include <iostream>
using namespace std;

//this is a pointer
#define PI 3.141592653589793
class Circle{
    public:
    static int count;
    Circle(double radius){
        count++;
        this->radius = radius;
    }
    ~Circle(){
        count--;
    }
    double area(){
        return PI*radius*radius;
    }
    void print_object(){
        cout << "Object address: " << this << endl;
        cout << "radius: " << radius << endl;  
    }
    // 指针object->set_radius_point(radius)->print_radius_point();
    Circle *set_radius_point(double radius){
        cout <<"set point" << endl;
        this->radius = radius;
        return this;
    }
    Circle *get_radius_point(){
        cout <<"get point" << endl;
        return this;
    }
    // 引用object.set_radius_ref(radius).print_radius_ref();
    //*this中*是“解引用”标识符！
    Circle &set_radius_ref(double radius){
        cout <<"set ref" << endl;
        this->radius = radius;
        return *this;
    }
    Circle &get_radius_ref(){
        cout <<"get ref" << endl;
        return *this;
    }
    private:
    double radius{0};
};
// Initialize the static member outside the class
int Circle::count = 0;
int main(){
    //heap create
    cout << "heap create" << endl;
    auto *c1 = new Circle(1);
    c1->print_object();
    c1->get_radius_point()->set_radius_point(2)->get_radius_point();
    cout << "pointer to reference" << endl;
    c1->get_radius_ref().set_radius_ref(3).get_radius_ref();
    //stack create
    cout << "stack create" << endl;
    Circle c2(4);
    c2.print_object();
    c2.get_radius_ref().set_radius_ref(5).get_radius_ref();
    cout << "reference to pointer" << endl;
    c2.get_radius_point()->set_radius_point(6)->get_radius_point();
    //delete
    delete c1;
    c1 = nullptr;
    return 0;
}