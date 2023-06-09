class Texture
{
private:
    
public:
    Texture(const char* path, int format, int wrapMode, int filterMode);
    ~Texture();

    unsigned int ID;
    int width, height, channels;


    void bind();
};