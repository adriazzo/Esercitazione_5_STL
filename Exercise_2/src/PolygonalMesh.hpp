#ifndef _POLYGONAL_H_
#define _POLYGONAL_H_



#include <iostream>
#include "Eigen/Eigen"

using namespace std;
using namespace Eigen;


namespace PolygonalLibrary {

struct PolygonalMesh
{
    unsigned int NumberCell0D = 0;                                  //Positive integer, stores the number of Cell0D
    vector<unsigned int> Cell0DId = {};                             //Vector of positive int, stores the id of the Cell0D. Size 1xNumberCell0D
    vector<Vector2d> Cell0DCoordinates = {};                        //Vector 2xNumberCell0D of couples of doubles. Stores the coordinates of the cell
    map<unsigned int, list<unsigned int>> Cell0DMarkers = {};       //Has the marker as key and a list of cells with that marker as value

    unsigned int NumberCell1D = 0;                                  //Positive integer, stores the number of Cell1D
    vector<unsigned int> Cell1DId = {};                             //Vector of positive int, stores the id of the Cell1D. Size 1xNumberCell1D
    vector<Vector2i> Cell1DVertices = {};                           //Vector 2xNumberCell1d, stores the indices of the origin and end of the vertices
    map<unsigned int, list<unsigned int>> Cell1DMarkers = {};       //Has marker as key and the cells with that marker as value in a list

    unsigned int NumberCell2D = 0;                                  //Positive integer, stores the number of Cell2D
    vector<unsigned int> Cell2DId = {};                             //Vector of positive int, stores the id of the Cell2D. Size 1xNumberCell2D
    vector<vector<unsigned int>> Cell2DVertices = {};               //Vector of arrays containing the indices of the Vertices, size 1xNumberCell2D
    vector<vector<unsigned int>> Cell2DEdges = {};                   //Vector of arrays containing the indices of the Edges, size 1xNumberCell2D

};

}

#endif
