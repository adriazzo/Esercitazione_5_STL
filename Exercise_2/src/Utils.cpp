#include "Utils.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

namespace PolygonalLibrary {


bool Tests(const string& filepath,
                PolygonalMesh& mesh)
{

    if(!ImportCell0Ds(filepath + "/Cell0Ds.csv",
                       mesh))
    {
        return false;
    }
    else
    {return true;}

    if(!ImportCell1Ds(filepath + "/Cell1Ds.csv",
                       mesh))
    {
        return false;
    }
    else{return true;}


    if(!ImportCell2Ds(filepath + "/Cell2Ds.csv",
                       mesh))
    {
        return false;
    }
    else{
        vector<vector<double>> sides; //vector of arrays containing the length of the sides of the triangles
        for (unsigned int c = 0; c < mesh.NumberCell2D; c++)
        {
            if (mesh.Cell2DVertices[c].size() == 3)
            {
                vector<unsigned int> edges = mesh.Cell2DEdges[c];
                for (unsigned int e = 0; e < 3; e++)
                {
                    const double origin = mesh.Cell1DVertices[edges[e]][0];
                    const double end = mesh.Cell1DVertices[edges[e]][1];
                    sides[c][e] = (mesh.Cell0DCoordinates[end] - mesh.Cell0DCoordinates[origin]).norm();
                    if(!sides[c][e])
                    {
                        cerr << "Lenght zero!" << endl;
                        return 2;
                    }
                }
                double semiperimeter = (sides[c][0] + sides[c][1] + sides[c][2])/2;
                double area = sqrt(semiperimeter * (semiperimeter - sides[c][0])*(semiperimeter - sides[c][1])*(semiperimeter - sides[c][2]));
                if (!area){
                    cerr << "Zero area!" << endl;
                    return 3;
                }
            }
        }
    }
}

bool ImportCell0Ds(const string &filename,
                   PolygonalMesh& mesh)
{

    ifstream file; //initialize an ifstream object named file and opens it
    file.open(filename);

    if(file.fail())
        return false;

    list<string> listLines; //creates a list of strings that will contain the rows of the csv
    string line;
    while (getline(file, line))
    {
        istringstream lineStream(line);
        string cell;
        string row;
        while (getline(lineStream, cell, ';')) {
            row = row + cell + " ";
        }
        listLines.push_back(row); //line by line in the csv appends at the end of the list the line
    }
    file.close();

    listLines.pop_front(); //removes the header

    mesh.NumberCell0D = listLines.size(); //sets the number of cells as the number of rows in the csv

    if (mesh.NumberCell0D == 0)
    {
        cerr << "There is no cell 0D" << endl;
        return false;
    }

    mesh.Cell0DId.reserve(mesh.NumberCell0D); //allocates the memory for the vector Cell0D
    mesh.Cell0DCoordinates.reserve(mesh.NumberCell0D);

    for (const string& line : listLines) //iterates in the list of lines
    {
        istringstream converter(line); //initializes an istringstream object containing the line

        unsigned int id;
        unsigned int marker;
        Vector2d coord;

        converter >>  id >> marker >> coord(0) >> coord(1); //assigns the values to id, marker, coord

        mesh.Cell0DId.push_back(id); //adds id to the vector of indices
        mesh.Cell0DCoordinates.push_back(coord); //adds coord to the vector of coordinates

        if( marker != 0)
        {
            auto ret = mesh.Cell0DMarkers.insert({marker, {id}}); /*returns and object std::pair that has an iterator pointing at map element for the key which is being inserted as first and a bool that is true if the key is being inserted for the
            first time as second  */
            if(!ret.second) //if the marker is already a key in the map
                (ret.first)->second.push_back(id); //appends to the list (ret.first)->second the value id. ret.first has both the marker (ret.first)->first and id (ret.first)->second
        }

    }
    file.close();
    return true;
}



bool ImportCell1Ds(const string &filename,
                   PolygonalMesh& mesh)
{

    ifstream file;
    file.open(filename);

    if(file.fail())
        return false;

    list<string> listLines;
    string line;
    while (getline(file, line))
    {
        istringstream lineStream(line);
        string cell;
        string row;
        while (getline(lineStream, cell, ';')) {
            row = row + cell + " ";
        }
        listLines.push_back(row);
    }
    listLines.pop_front();

    mesh.NumberCell1D = listLines.size();

    if (mesh.NumberCell1D == 0)
    {
        cerr << "There is no cell 1D" << endl;
        return false;
    }

    mesh.Cell1DId.reserve(mesh.NumberCell1D);
    mesh.Cell1DVertices.reserve(mesh.NumberCell1D);

    for (const string& line : listLines)
    {
        istringstream converter(line);

        unsigned int id;
        unsigned int marker;
        Vector2i vertices;

        converter >>  id >> marker >> vertices(0) >> vertices(1);

        mesh.Cell1DId.push_back(id);
        mesh.Cell1DVertices.push_back(vertices);

        if( marker != 0)
        {
            auto ret = mesh.Cell1DMarkers.insert({marker, {id}});
            if(!ret.second)
                (ret.first)->second.push_back(id);
        }
    }

    file.close();

    return true;
}



bool ImportCell2Ds(const string &filename,
                   PolygonalMesh& mesh)
{

    ifstream file;
    file.open(filename);

    if(file.fail())
        return false;

    list<string> listLines;
    string line;
    while (getline(file, line))
    {
        istringstream lineStream(line);
        string cell;
        string row;
        while (getline(lineStream, cell, ';')) {
            row = row + cell + " ";
        }
        listLines.push_back(row);
    }

    listLines.pop_front();

    mesh.NumberCell2D = listLines.size();

    if (mesh.NumberCell2D == 0)
    {
        cerr << "There is no cell 2D" << endl;
        return false;
    }

    mesh.Cell2DId.reserve(mesh.NumberCell2D);
    mesh.Cell2DVertices.reserve(mesh.NumberCell2D);
    mesh.Cell2DEdges.reserve(mesh.NumberCell2D);

    for (const string& line : listLines)
    {
        istringstream converter(line);

        unsigned int id;
        unsigned int numvertices;
        unsigned int numedges;
        unsigned int marker;

        converter >>  id;
        converter >> marker;
        converter >> numvertices;
        vector<unsigned int> vertices(numvertices);
        for(unsigned int i = 0; i < numvertices; i++)
            converter >> vertices[i];
        converter >> numedges;
        vector<unsigned int> edges(numedges);


        for(unsigned int i = 0; i < numedges; i++)
            converter >> edges[i];

        mesh.Cell2DId.push_back(id);
        mesh.Cell2DVertices.push_back(vertices);
        mesh.Cell2DEdges.push_back(edges);
    }
    file.close();
    return true;
}

}
