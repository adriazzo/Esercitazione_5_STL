#ifndef _UTILS_H_
#define _UTILS_H_



#include <iostream>
#include "PolygonalMesh.hpp"

using namespace std;

namespace PolygonalLibrary {

// return the result of the reading, true if is success, false otherwise
bool Tests(const string &filepath,
                PolygonalMesh& mesh);

/// Import the Cell0D properties from Cell0Ds.csv file
/// mesh: a TriangularMesh struct
/// return the result of the reading, true if is success, false otherwise
bool ImportCell0Ds(const string &filename,
                   PolygonalMesh& mesh);

/// Import the Cell1D properties from Cell1Ds.csv file
/// mesh: a TriangularMesh struct
/// return the result of the reading, true if is success, false otherwise
bool ImportCell1Ds(const string &filename,
                   PolygonalMesh& mesh);

/// Import the Cell2D properties from Cell2Ds.csv file
/// mesh: a TriangularMesh struct
/// return the result of the reading, true if is success, false otherwise
bool ImportCell2Ds(const string &filename,
                   PolygonalMesh& mesh);

}

#endif
