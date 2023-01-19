#include <iostream>
#include <optional>
#include <tuple>
#include <vector>
#include <fstream>
#include <sstream>
#include <exception>
#include <iomanip>
#include <algorithm>
#include <gtest/gtest.h>

struct Person
{
	std::string					last_name;
	std::string					first_name;
	std::optional<std::string>	patronymic;
};

std::ostream	&operator<<(std::ostream &os, const Person &Pers)
{
	return (os << std::setw(15) << std::left << Pers.last_name << 
			std::setw(15)  << std::left << Pers.first_name <<
			std::setw(15) << std::left << Pers.patronymic.value_or("") );
}

bool			operator==(const Person &Pers1, const Person &Pers2)
{
	if (Pers1.patronymic.has_value() && Pers2.patronymic.has_value())
	{
		return (std::tie(Pers1.last_name, Pers1.first_name, Pers1.patronymic.value()) == 
				std::tie(Pers2.last_name, Pers2.first_name, Pers2.patronymic.value()));
	}
	return (std::tie(Pers1.last_name, Pers1.first_name) == 
				std::tie(Pers2.last_name, Pers2.first_name));
}

bool			operator<(const Person &Pers1, const Person &Pers2)
{
	if (Pers1.patronymic.has_value() && Pers2.patronymic.has_value())
	{
		return (std::tie(Pers1.last_name, Pers1.first_name, Pers1.patronymic.value()) < 
				std::tie(Pers2.last_name, Pers2.first_name, Pers2.patronymic.value()));
	}
	return (std::tie(Pers1.last_name, Pers1.first_name) < 
			std::tie(Pers2.last_name, Pers2.first_name));
}

bool			operator>(const Person &Pers1, const Person &Pers2)
{
	return (!(Pers1 < Pers2));
}

struct PhoneNumber
{
	std::string					country_number="";
	std::string					city_number="";
	std::string					main_number="";
	std::optional<std::string>	additional_number;
};

std::ostream	&operator<<(std::ostream &os, const PhoneNumber &Num)
{
	if (Num.additional_number.has_value())
	{
		return (os << std::setw(1) << std::left << "+" <<
				Num.country_number << "(" << Num.city_number <<
				")" << Num.main_number << " " << 
				std::setw(1) << std::left << Num.additional_number.value());
	}
	return (os << std::setw(1) << std::left << "+" << Num.country_number << "(" << Num.city_number <<
				")" << Num.main_number);
}

bool			operator==(const PhoneNumber &Num1, const PhoneNumber &Num2)
{
	if (Num1.additional_number.has_value() && Num2.additional_number.has_value())
	{
		return (std::tie(Num1.country_number, Num1.city_number, Num1.main_number, Num1.additional_number.value()) ==
				std::tie(Num2.country_number, Num2.city_number, Num2.main_number, Num2.additional_number.value()));
	}
	return (std::tie(Num1.country_number, Num1.city_number, Num1.main_number) == 
			std::tie(Num2.country_number, Num2.city_number, Num2.main_number));
}

bool			operator<(const PhoneNumber &Num1, const PhoneNumber &Num2)
{
	if (Num1.additional_number.has_value() && Num2.additional_number.has_value())
	{
		return (std::tie(Num1.country_number, Num1.city_number, Num1.main_number, Num1.additional_number.value()) < \
				std::tie(Num2.country_number, Num2.city_number, Num2.main_number, Num2.additional_number.value()));
	}
	return (std::tie(Num1.country_number, Num1.city_number, Num1.main_number) < \
			std::tie(Num2.country_number, Num2.city_number, Num2.main_number));
}

bool			operator>(const PhoneNumber &Num1, const PhoneNumber &Num2)
{
	return (!(Num1 < Num2));
}

class PhoneBook
{
private:
	std::vector<std::pair<Person, PhoneNumber>>	book;
public:
	PhoneBook(std::ifstream &_file);
	~PhoneBook() { book.clear(); };

	friend std::ostream						&operator<<(std::ostream &os, const PhoneBook &local_book);
	void									SortByName(void);
	void									SortByPhone(void);
	std::tuple<std::string, std::string>	GetPhoneNumber(std::string _last_name);
	void									ChangePhoneNumber(Person _pers, PhoneNumber _phone);
};

PhoneBook::PhoneBook(std::ifstream &_file)
{
	try
	{
		if (_file.is_open())
		{
			while (_file)
			{
				Person							pers;
				PhoneNumber						phone_number;
				std::pair<Person, PhoneNumber>	pair_for_book;
				uint32_t						i;
				std::string						temp_str;
				std::istringstream				line;

				i = 0;
				std::getline(_file, temp_str);
				line = static_cast<std::istringstream>(temp_str);
				for (std::string data; std::getline(line, data, ' '); ++i)
				{
					if (i == 0)
					{
						pers.last_name = data;
						// std::cout << "last_name: " << pers.last_name << std::endl;
					}
					else if (i == 1)
					{
						pers.first_name = data;
						// std::cout << "first_name: " << pers.first_name << std::endl;
					}
					else if (i == 2)
					{
						if (data[0] != '+')
						{
							pers.patronymic = data;
						}
						else
						{
							++i;
						}
						// std::cout << "patronic_name: " << pers.patronymic.value() << std::endl;
					}
					if (i == 3)
					{
						for (uint32_t j = 1; j < data.length(); ++j)
						{
							while (data[j] != '(')
							{
								phone_number.country_number.push_back(data[j++]);
							}
							// std::cout << "country_number: " << phone_number.country_number << std::endl;
							++j;
							while (data[j] != ')')
							{
								phone_number.city_number.push_back(data[j++]);
							}
							// std::cout << "city_number: " << phone_number.city_number << std::endl;
							++j;
							while (data[j])
							{
								phone_number.main_number.push_back(data[j++]);
							}
							// std::cout << "main_number: " << phone_number.main_number << std::endl;
						}
					}
					if (i == 4)
					{
						uint32_t	j = 0;
						std::string	temp;

						while (data[j])
						{
							temp.push_back(data[j++]);				
						}
						phone_number.additional_number.emplace(temp);
						// std::cout << "add_number: " << phone_number.additional_number.value() << std::endl;
					}
				}
				pair_for_book.first = pers;
				pair_for_book.second = phone_number;
				book.push_back(pair_for_book);
			}
		}
		else throw std::overflow_error("File wasn't open!");
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
}

std::ostream									&operator<<(std::ostream &os, const PhoneBook &local_book)
{
	auto	it = local_book.book.begin();

	for (; it < local_book.book.end(); ++it)
	{
		os << (*(it)).first << "\t\t" << (*(it)).second << std::endl;
	}
	return (os << std::endl);
}

void											PhoneBook::SortByName(void)
{
	std::sort(book.begin(), book.end());
}

void											PhoneBook::SortByPhone(void)
{
	auto compare = [](std::pair<Person, PhoneNumber> number_1, std::pair<Person, PhoneNumber> number_2)
					{
						try
						{
							uint32_t	int_num_1 = std::stoi(number_1.second.country_number);
							uint32_t	int_num_2 = std::stoi(number_2.second.country_number);

							if (int_num_1 == int_num_2)
							{
								int_num_1 = std::stoi(number_1.second.city_number);
								int_num_2 = std::stoi(number_2.second.city_number);
								
								if (int_num_1 == int_num_2)
								{
									int_num_1 = std::stoi(number_1.second.main_number);
									int_num_2 = std::stoi(number_2.second.main_number);								
								}
							}
							return (int_num_1 < int_num_2);
						}
						catch(const std::invalid_argument& e)
						{
							return (false);
						}
					};
	std::sort(book.begin(), book.end(), compare);
}

std::tuple<std::string, std::string>			PhoneBook::GetPhoneNumber(std::string _last_name)
{
	const std::string						not_found = "not found";
	const std::string						more_than_one = "found more than 1";
	auto									it = book.begin();
	std::tuple<std::string, std::string>	result;
	std::string								result_number;
	uint32_t								value_of_numbers;
	
	value_of_numbers = 0;
	std::get<0>(result) = _last_name;
	for (; it < book.end(); ++it)
	{
		if ((*it).first.last_name == _last_name)
		{
			result_number.clear();

			//Create number
			result_number.push_back('+');
			result_number.append((*it).second.country_number);
			result_number.push_back('(');
			result_number.append((*it).second.city_number);
			result_number.push_back(')');
			result_number.append((*it).second.main_number);
			
			if ((*it).second.additional_number.has_value())
			{
				result_number.push_back(' ');
				result_number.append((*it).second.additional_number.value());
			}
			std::get<1>(result) = result_number;
			++value_of_numbers;
		}
		if (value_of_numbers > 1)
		{
			break ;
		}
	}
	if (value_of_numbers == 0)
	{
		std::get<1>(result) = not_found;
	}
	else if (value_of_numbers > 1)
	{
		std::get<1>(result) = more_than_one;
	}
	return (result);
}

void											PhoneBook::ChangePhoneNumber(Person _pers, PhoneNumber _phone)
{
	auto	it = book.begin();

	// std::cout << _pers.last_name << " " << _pers.first_name << " " << _pers.patronymic.value() << std::endl;
	for(; it < book.end(); ++it)
	{
		// std::cout << (*it).first.last_name << " " << (*it).first.first_name << std::endl;
		if ((*it).first.last_name == _pers.last_name && 
			(*it).first.first_name == _pers.first_name)
		{
			if ((*it).first.patronymic.has_value() && _pers.patronymic.has_value())
			{
				if ((*it).first.patronymic.value() == _pers.patronymic.value())
				{
					(*it).second.country_number = _phone.country_number;
					(*it).second.city_number = _phone.city_number;
					(*it).second.main_number = _phone.main_number;
					if (_phone.additional_number.has_value())
					{
						(*it).second.additional_number = _phone.additional_number.value();
					}
				}
			}
			else
			{
				(*it).second.country_number = _phone.country_number;
				(*it).second.city_number = _phone.city_number;
				(*it).second.main_number = _phone.main_number;
				if (_phone.additional_number.has_value())
				{
					(*it).second.additional_number = _phone.additional_number.value();
				}
			}
		}
	}
}

TEST(open_file, Existing_of_file)
{
	std::ifstream	file("../../PhoneBook.txt");
	PhoneBook		*new_book = new PhoneBook(file);

	ASSERT_EQ(file.is_open(), true);

	file.close();
	delete new_book;
}

TEST(getphone, Get_phone_number)
{
	std::ifstream	file("../../PhoneBook.txt");
	PhoneBook		*new_book = new PhoneBook(file);

	EXPECT_EQ(file.is_open(), true);

	auto res_phone = new_book->GetPhoneNumber("Chernyshev");
	EXPECT_NE(std::get<0>(res_phone), "not_found");
	res_phone = new_book->GetPhoneNumber("Qfghjjkjhtd");
	EXPECT_NE(std::get<0>(res_phone) , "not_found");
	res_phone = new_book->GetPhoneNumber("Nazarova");
	EXPECT_NE(std::get<0>(res_phone) , "not_found");

	file.close();
	delete new_book;
}

int		main(void)
{
	testing::InitGoogleTest();

	return (RUN_ALL_TESTS());
}