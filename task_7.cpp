#include <iostream>
#include <memory>

class Date
{
private:
	uint32_t	day;
	uint32_t	month;
	uint32_t	year;
public:
	explicit			Date(uint32_t d, uint32_t m, uint32_t y) : day(d), month(m), year(y) {};
	uint32_t			getDay(void) const { return (day); }
	uint32_t			getMonth(void) const { return (month); }
	uint32_t			getYear(void) const { return (year); }
	friend std::ostream	&operator<<(std::ostream &os, const std::shared_ptr<Date> &d);
	friend void			flipDate(std::shared_ptr<Date> &ptr1, std::shared_ptr<Date> &ptr2);
	~Date() {};
};

std::ostream	&operator<<(std::ostream &os, const std::shared_ptr<Date> &d)
{
	return (os << d->day << "." << d->month << "." << d->year << std::endl);
}

void	task_1(void)
{
	std::shared_ptr<Date>	today(new Date(9, 12, 2022));
	std::shared_ptr<Date>	date(new Date(0, 0, 0));

	std::cout << "Task 1: \n";
	std::cout << "Day: " << today->getDay() << std::endl;
	std::cout << "Month: " << today->getMonth() << std::endl;
	std::cout << "Year: " << today->getYear() << std::endl;
	std::cout << today;

	date = today;
	if (today == nullptr || date == nullptr)
	{
		std::cout << "One of pointers is a Null's pointer!" << std::endl;
	}
	else
	{
		std::cout << "Pointers is not a Null's pointers!" << std::endl;
	}
}

template<typename T>
std::shared_ptr<T>	comparePtrs(const std::shared_ptr<T> &ptr1, const std::shared_ptr<T> &ptr2)
{
	if (ptr1->getYear() > ptr2->getYear())
	{
		return (ptr1);
	}
	else if (ptr1->getYear() < ptr2->getYear())
	{
		return (ptr2);
	}
	else if (ptr1->getMonth() < ptr2->getMonth())
	{
		return (ptr1);
	}
	else if (ptr1->getMonth() > ptr2->getMonth())
	{
		return (ptr2);
	}
	else if (ptr1->getDay() < ptr2->getDay())
	{
		return (ptr1);
	}
	else if (ptr1->getDay() > ptr2->getDay())
	{
		return (ptr2);
	}
	else
	{
		return (ptr2);
	}
}

void			flipDate(std::shared_ptr<Date> &ptr1, std::shared_ptr<Date> &ptr2)
{
	uint32_t	temp = ptr1->day;
	ptr1->day = ptr2->day;
	ptr2->day = temp;

	temp = ptr1->month;
	ptr1->month = ptr2->month;
	ptr2->month = temp;

	temp = ptr1->year;
	ptr1->year = ptr2->year;
	ptr2->year = temp;
}

void	task_2(void)
{
	std::shared_ptr<Date>	date1(new Date(9, 12, 2022));
	std::shared_ptr<Date>	date2(new Date(7, 11, 2022));

	std::cout << "Task 2: \nOldest date is ";
	std::cout << comparePtrs<Date>(date1, date2);


	std::cout << "Date 1: " << date1;
	std::cout << "Date 2: " << date2;
	flipDate(date1, date2);
	std::cout << "After flip:" << std::endl;
	std::cout << "Date 1: " << date1;
	std::cout << "Date 2: " << date2;
}

int		main(void)
{
	task_1();
	task_2();

	return (0);
}