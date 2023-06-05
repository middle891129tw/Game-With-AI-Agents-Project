/*
* camera.hpp
*/

#pragma once

#include <vector>

class Camera
{
public:
	Camera();
	~Camera();

	std::vector<double> getEye();
	std::vector<double> getCenter();
	std::vector<double> getUp();

	void reset();
	void translate(std::vector<double>);
	void setPos(std::vector<double>);

private:
	std::vector<double> _eye;
	std::vector<double> _front;
	std::vector<double> _center;
	std::vector<double> _up;
	
};