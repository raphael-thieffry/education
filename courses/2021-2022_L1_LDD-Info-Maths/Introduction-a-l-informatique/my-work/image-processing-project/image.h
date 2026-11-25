/** @file
 * Structures de données pour représenter des images
 **/
#ifndef _IMAGE_H
#define _IMAGE_H

using namespace std;
#include <vector>
#include <string>

typedef std::vector<std::vector<int>> ImageNB;
typedef std::vector<std::vector<double>> ImageGris;

struct Couleur{
    double r;
    double g;
    double b;
};

typedef std::vector<std::vector<Couleur>> Image;


#endif