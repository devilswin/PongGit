#include <include\Book\Application.hpp>

#include <stdexcept>
#include <iostream>
#include <cmath>
#include <cstdio>
#include <ctime>

int main()
{
        srand(time(NULL));
	try
	{
		Application app;
		app.run();
	}
	catch (std::exception& e)
	{
		std::cout << "\nEXCEPTION: " << e.what() << std::endl;
	}
	

}
