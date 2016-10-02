#include <creek/DynLibrary.hpp>

//CREEK_FUNC_HEADER(my_print);

#include <iostream>

void my_print(std::string output)
{
    std::cout << "my_print: " << output << "\n";
}

//CREEK_FUNC_IMPL(my_print);

CREEK_FUNC(my_print);
