# FirtsRep
#include <stdlib.h>


#include <iostream>
#include <string>
#include <unistd.h>


int main()
{
/*    std::string path;
    path.resize(1024);

    auto ret = readlink("/proc/self/exe", &path[0], path.size()); // &path[0] - не const char*

    path.resize(ret);

    if (path.at(0) == 0)
    {
        std::cout << "Error" << std::endl;
        return -2;
    } */
    system("xdg-open chessviz.html &");
   // std::cout << path << std::endl;
    return 0;
}




//	system("xdg-open /home/students/2020/ip015s29/chessviz-Vitaly-02/chessviz.html &");
//	return 0;
