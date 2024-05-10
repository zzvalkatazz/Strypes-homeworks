#include<iostream>

//Function to set a bit at a given position
void setBit(uint64_t& attendance, int pos)
{
	attendance |= (1ULL << pos);
}
//Function to clear a bit at a given position
void clearBit(uint64_t& attendance, int pos)
{
	attendance &= ~(1ULL << pos);
}
//Function to flip(change) bit of a given position
void flipBit(uint64_t& attendance, int pos)
{
	attendance ^= (1ULL << pos);
}

//Function to read value of bit of a given position
bool readBit(uint64_t& attendance, int pos)
{
	return attendance & (1ULL << pos);
}
int main()
{
	uint64_t attendance = 0;
	int option;
	while (true)
	{
		std::cout << "1.Set attendance" << std::endl;
		std::cout << "2.Clear attendance" << std::endl;
		std::cout << "3.Attendance info" << std::endl;
		std::cout << "4.Change attendance" << std::endl;
		std::cout << "5.Exit" << std::endl;
		std::cout << "Enter option:";
		std::cin >> option;
		switch (option)
		{
		case 1: {
			int studentNumber;
			std::cout << "Enter student number to mark present(0-63):";
			std::cin >> studentNumber;
			if (studentNumber >= 0 && studentNumber <= 63)
			{
				setBit(attendance, studentNumber);
				std::cout << "Attendance set for student:" << studentNumber << std::endl;
			}
			else
			{
				std::cout << "Invalid student number!Please enter a number between 0 and 63" << std::endl;
			}
			break;
		}
		case 2:
		{
			int studentNumber;
			std::cout << "Enter student number to mark present(0-63):";
			std::cin >> studentNumber;
			if (studentNumber >= 0 && studentNumber <= 63)
			{
				clearBit(attendance, studentNumber);
				std::cout << "Attendance cleared for student:" << studentNumber << std::endl;
			}
			else
			{
				std::cout << "Invalid student number!Please enter a number between 0 and 63" << std::endl;
			}
			break;
		}
		case 3:
		{
			int presentCount = 0;
			int absentCount = 0;
			for (int i = 0; i < 64; i++)
			{
				if (readBit(attendance, i))
				{
					++presentCount;
				}
				else {
					absentCount++;
				}
			}
			std::cout << "Present students:" << presentCount << std::endl;
			std::cout << "Absent students:" << absentCount << std::endl;
			break;
		}
		case 4:
		{
			int studentNumber;
			std::cout << "Enter student number to mark present(0-63):";
			std::cin >> studentNumber;
			if (studentNumber >= 0 && studentNumber <= 63)
			{
				flipBit(attendance, studentNumber);
				std::cout << "Attendance changed for student:" << studentNumber << std::endl;
			}
			else
			{
				std::cout << "Invalid student number!Please enter a number between 0 and 63" << std::endl;
			}
			break;
		}
		case 5:
			return 0;
		default:
			std::cout << "Invalid option!Please select a valid option." << std::endl;
		}
	}
	return 0;
}