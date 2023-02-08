#include "../include/DynamicObject.h"

/*------------------Task 1--------------------*/

void	LogVisitor::log(Plane* _plane)
{
	ModifyLogging::GetInstance("Speed: " + std::to_string(_plane->GetSpeed()));
}

void	LogVisitor::log(Bomb* _bomb)
{
	std::string	_direction;

	_direction.append(std::to_string(_bomb->GetDirection()[0]));
	_direction.append(" ");
	_direction.append(std::to_string(_bomb->GetDirection()[1]));
	ModifyLogging::GetInstance("Direction: " + _direction);
}

/*-----------------Task 2----------------------*/

bool    Bomb::HandleInsideCheck(DestroyableGroundObject* _dest_obj)
{
    const double	size = this->GetWidth();
    const double	size_2 = size / 2;
    const double	x1 = this->GetX() - size_2;
	const double	x2 = x1 + size;
    
	if (_dest_obj->isInside(x1, x2))
    {
        return (true);
    }
	return (false);
}

DestroyableGroundObject*    Bomb::AddObserver(std::vector<DestroyableGroundObject*> _vecDestoyableObjects)
{
    for (auto elem : vecDestoyableObjects)
	{
		if (HandleInsideCheck(elem))
		{
			return (elem);
		}
	}
	return (nullptr);
}

/*--------------------------------------------*/

void Bomb::Draw() const
{
    MyTools::SetColor(MyTools::CC_LightMagenta);
    MyTools::GotoXY(x, y);
    std::cout << "*";
}

void Plane::Draw() const
{
    MyTools::SetColor(MyTools::CC_LightBlue);
    MyTools::GotoXY(x, y);
    std::cout << "=========>";
    MyTools::GotoXY(x - 2, y - 1);
    std::cout << "===";
    MyTools::GotoXY(x + 3, y - 1);
    std::cout << "\\\\\\\\";
    MyTools::GotoXY(x + 3, y + 1);
    std::cout << "////";
}