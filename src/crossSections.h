#ifndef CROSSSECTIONS_H
#define CROSSSECTIONS_H

#include <map>
#include <vector>
#include <string>

// Declare the map to store cross-sections
extern std::map<std::string, std::vector<double>> crossSections;

// Function to initialize the cross-sections
void initCrossSections();

#endif // CROSSSECTIONS_H
