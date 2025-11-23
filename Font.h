#ifndef FONT_H_
#define FONT_H_


class Font
{
    public:
        Font();
        const int* getDefaultFont() const;

    private:
        int defaultFont[80];
};

#endif