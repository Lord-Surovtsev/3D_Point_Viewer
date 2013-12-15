#ifndef TRANSFORMATIONPARAMETERS_H
#define TRANSFORMATIONPARAMETERS_H

struct TransformationParameters
{
public:
    double angleX;
    double angleY;
    double angleZ;

    double dX;
    double dY;
    double dZ;

    double focus;

    TransformationParameters(double aX, double aY, double aZ
                             , double x, double y, double z
                             , double f)
    {
        angleX = aX;
        angleY = aY;
        angleZ = aZ;

        dX = x;
        dY = y;
        dZ = z;
        focus = f;
    }

    TransformationParameters()
    {
        angleX = 0;
        angleY = 0;
        angleZ = 0;

        dX = 0;
        dY = 0;
        dZ = 0;
        focus = 0;
    }
};

#endif // TRANSFORMATIONPARAMETERS_H
