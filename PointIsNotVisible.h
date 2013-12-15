#ifndef POINTISNOTVISIBLE_H
#define POINTISNOTVISIBLE_H

#include <CustomException.h>

class PointIsNotVisible: public CustomException
{
public:
    PointIsNotVisible(string message) : CustomException(message)
    {

    }
};

#endif // POINTISNOTVISIBLE_H
