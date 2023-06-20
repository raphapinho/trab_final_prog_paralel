#include "pbPlots.h"
#include "supportLib.h"

int main()
{

    double x[] = {-1, 0, 1, 2, 3, 4, 5, 6};
    double y[] = {-5, -4, -3, -2, 1, 0, 1, 2};

    RGBABitmapImageReference *imageRef = CreateRGBABitmapImageReference();

    DrawScatterPlot(imageRef, 600, 400, x, 8, y, 8);

    size_t length;
    double *pngData = ConvertToPNG(&length, imageRef->image);
    WriteToFile(pngData, length, "plot.png");

    return 0;

    /*
    para executar
        gcc -c plot.c -std=c99 -O3 -march=native
        gcc plot.o  pbPlots.o supportLib.o -lm -o example1
        strip example1
    */
}