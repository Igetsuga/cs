// Сиразетдинов Рустем КМБО-01-21 Вариант- 24
// Circle{double radius,  tuple<double, double> centerCoords(X,Y)}
#include <iostream>
#include <tuple>
#include <cmath>
//#include<utility>

using namespace std;

class circle // Circle{double radius,  tuple<double, double> centerCoords(X,Y)}
{
private: // include radius and coordinates of circle center

	// pair<double, double> centerCoords;

	tuple<double, double> centerCoords; // coordinates of circle, @param limits: no @param X @param Y
	double radius; // radius of circle, @param limits: ( >= 0 )
public:
	// default constructor --> center(0,0) & radius = 0 <--> point
	circle() { centerCoords = make_tuple(0, 0); radius = 0; }

	// center(0,0) & user_radius constructor
	circle(double user_radius)
	{
		if (user_radius >= 0) {
			centerCoords = make_tuple(0, 0);
			radius = user_radius;
		}
		else { cout << "invalid value of radius, try again" << '\n'; }
	}

	// other way to set user_radius to object from class circle 
	circle operator=(double user_radius)
	{
		radius = user_radius;
		return *this;
	}

	// radius = 1 & user_centerCoords consructor
	circle(double user_X, double user_Y)
	{
		radius = 1;
		centerCoords = make_tuple(user_X, user_Y);
	}

	// full constructor
	circle(double user_X, double user_Y, double user_radius)
	{
		if (user_radius >= 0) {
			centerCoords = make_tuple(user_X, user_Y);
			radius = user_radius;
		}
		else { cout << " invalid value of radius, try again" << '\n'; }
	}


	//deconstructor
	~circle() { cout << "circle_N has been deleted" << '\n'; }

	// get & set
	tuple<double, double> get_centerCoords() { return centerCoords; }
	double get_centerCoords_X() { return get<0>(centerCoords); }
	double get_centerCoords_Y() { return get<1>(centerCoords); }
	double get_radius() { return radius; }

	void set_centerCoords(double user_X, double user_Y) { get<0>(centerCoords) = user_X; get<1>(centerCoords) = user_Y; }
	void set_centerCoords_X(double user_X) { get<0>(centerCoords) = user_X; }
	void set_centerCoords_Y(double user_Y) { get<1>(centerCoords) = user_Y; }
	void set_radius(double user_radius) { radius = user_radius; }

	// output
	void print()
	{
		cout << "---->> circle coordinates of center = " << "(" << get<0>(centerCoords) << " : " << get<1>(centerCoords) << ")" << "\n" << "       radius = " << radius << '\n';
	}

	// lenght of the circle 
	double operator~()
	{
		return (2 * radius * 3.14);
	}

	// coordinates center -to- circle center distance
	double distance()
	{
		return sqrt(pow(get<0>(centerCoords), 2) + pow(get<1>(centerCoords), 2));
	}

	// compare circle1 with circle2 
	bool operator<(circle circle2)
	{
		return (distance() < circle2.distance());
	}
	bool operator>(circle circle2)
	{
		return (distance() > circle2.distance());
	}

	// compare circle1 with point
	bool operator<(double s)
	{
		circle c(s);
		return (*this < c);
	}
	bool operator>(double s)
	{
		circle c(s);
		return (*this > c);
	}

	friend double operator!(circle c);
	friend double operator>(double s, circle circle2);
	friend double operator<(double s, circle circle2);

};


// square of the circle
double operator!(circle c)
{
	return (3.14 * pow((c.radius), 2));
}

double operator>(double s, circle circle2)
{
	return (circle2 < s);
}
double operator<(double s, circle circle2)
{
	return (circle2 > s);
}

int main()
{
	circle c(-4, 21, -9); c.print();

	circle c1; c1.print();

	circle c2(9); c2.print();

	circle c3(1, 2); c3.print();

	circle c4(1, 6, 4); c4.print();

	std::tuple<double, double> temp_tuple;
	temp_tuple = c1.get_centerCoords();


	// output
	cout << "---->> " << c2.get_centerCoords_X() << " : " << c2.get_centerCoords_Y() << '\n';

	cout << "---->> " << c3.get_radius() << '\n';

	c4.set_centerCoords(-130, 17); c4.set_radius(8); c4.print();

	cout << "---->> is the circle c4" << "(" << c4.distance() << ")" << "further from the coordinate center than circle c3" << "(" << c3.distance() << "): " << " c4  < c3-->" << " " << (c4 < c3) << '\n';
	cout << "---->> is the circle c4" << "(" << c4.distance() << ")" << "further from the coordinate center than circle c3" << "(" << c3.distance() << "): " << " c4  > c3 -->" << " " << (c4 > c3) << '\n';

	cout << "---->> the lenght of c4 = " << ~c4 << '\n';

	// if (typeid(c5).name() == typeid(circle).name())
	circle c5; c5 = 21; // <=> circle c5(21); 
	cout << "---->> is the circle c4" << "(" << c4.distance() << ")" << "further from the coordinate center than point c5" << "(" << c5.distance() << "): " << " c4  < c5 -->" << " " << (c4 < c5) << '\n';
	cout << "---->> is the circle c4" << "(" << c4.distance() << ")" << "further from the coordinate center than point c5" << "(" << c5.distance() << "): " << " c4  > c5 -->" << " " << (c4 > c5) << '\n';

	// if (typeid(c6).name() == typeid(double).name()) 
	double c6 = 46; // don't know how to use method .distance with point 
	cout << "---->> is the circle c4 further from the coordinate center than point c6:" << " c4  < c6 -->" << " " << (c4 < c6) << '\n';
	cout << "---->> is the circle c4 further from the coordinate center than point c6:" << " c6 < c4 -->" << " " << (c6 < c4) << '\n';

	cout << "---->> the square of c4 = " << !c4 << '\n';

	//if (typeid(circle).name() == typeid(c4).name()) { cout << "MMM" << '\n'; }
	//cout << typeid(double).name() << '\n';
	return 0;
}
