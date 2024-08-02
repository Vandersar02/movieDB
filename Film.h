#pragma once
#include <afxstr.h>

// Classe repr�sentant un film
class Film {
public:
    CString original_title;
    CString overview;
    CString poster_path;
    double vote_average;

    Film() {}

    // Constructeur prenant des cha�nes de caract�res
    Film(const CString& n, const CString& desc, const CString& img, double r)
        : original_title(n), overview(desc), poster_path(img), vote_average(r) {}

    // Constructeur prenant des pointeurs de caract�res
    Film(const char* n, const char* desc, const char* img, double r)
        : original_title(n), overview(desc), poster_path(img), vote_average(r) {}
};
