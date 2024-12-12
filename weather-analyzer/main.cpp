#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>


int main()
{
	std::filesystem::path rootPath = std::filesystem::current_path();
	std::filesystem::path filePath = rootPath / "data" / "utc_timestamp,AT_temperature,BE_tem.txt";

    try {
        if (!std::filesystem::exists(filePath)) 
        {
            throw std::runtime_error("Error: Path does not exist: " + filePath.string());
        }
    }
    catch (const std::exception& e) 
    {
        std::cerr << e.what() << std::endl;
    }

	return 0;
}