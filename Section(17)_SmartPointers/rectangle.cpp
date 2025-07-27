#include <iostream>

class Shape
{
public:
	// Parameterized Constructor.
    Shape(int h, int w) : h_{h}, w_{w}
    {
        std::cout << "in paramterized height " << h_ << " width " << w_ << std::endl;
    }

	// Default Constructor -> Delegate to -> Parameterized Constructor.
    Shape() : Shape(0, 0)
    {
        std::cout << "in default height " << h_ << " width " << w_ << std::endl;
    }

	// Operator overloading.
    Shape operator=(Shape& shape)
    {
        return *this;
    }

   Shape operator+(Shape shape)
    {
        Shape temp;
        temp.h_  = this->h_ + shape.h_;
        temp.w_ = this->w_ + shape.w_;
        return temp;
    }

    int getHeight()
    {
       return h_;
    }
    int getWidth()
    {
       return w_;
    }
	
private:
    int h_;
    int w_;
};

int main()
{
    Shape shape;
    Shape rect(2,4);
    shape = rect; // assignment operator

    Shape square =  rect + shape;   //rect.operator+(shape); 
    std::cout << "square height " << square.getHeight() << " wdith " << square.getWidth() << "\n";
    return 0;

}