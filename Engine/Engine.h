#include "Graphics.h"
namespace en{
    struct Color
    {
        float r = 0.0f;
        float g = 0.0f;
        float b = 0.0f;
        float a = 1.0f;
    };

    struct fvec3{
        float x;
        float y;
        float z;
    };

    class Engine
    {
    private:
        Graphics graphics;
    public:
        void run();
        Engine(/* args */);
        ~Engine();
    };
}
