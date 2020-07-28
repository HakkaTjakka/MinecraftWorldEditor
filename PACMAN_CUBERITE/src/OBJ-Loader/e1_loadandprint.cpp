// Example 1: Load and Print
//
// Load the data from the .obj then print it into a file
//	called e1Out.txt

// Iostream - STD I/O Library
#include <iostream>

// fStream - STD File I/O Library
#include <fstream>

// OBJ_Loader - .obj Loader
#include "OBJ_Loader.h"

// Main function
int main3d(int argc, char* argv[]);

extern int shut_up;

int do3d() {
    char *m_argv[2];
    char arg1[20]="ik";
    char arg2[]="model.3.obj";
    m_argv[0]=arg1;
    m_argv[1]=arg2;
    int old_shut_up=shut_up;
    shut_up=1;
    int ret=main3d(2,m_argv);
    shut_up=old_shut_up;
    return ret;
}

extern kiki();
extern int monitor_off;

int main3d(int argc, char* argv[])
{
	// Initialize Loader
	objl_pacman::Loader Loader;

	// Load .obj File
	bool loadout = Loader.LoadFile(argv[1]);

	// Check to see if it loaded

	// If so continue
//    printf("here 1\n");
	if (loadout)
	{
		// Create/Open e1Out.txt
		std::ofstream file("e1Out.txt");

		// Go through each loaded mesh and out its contents
//        printf("Size=%d\n",Loader.LoadedMeshes.size());
        file << "LoadedMeshes=" << Loader.LoadedMeshes.size() << "\n";
		for (int i = 0; i < Loader.LoadedMeshes.size(); i++)
		{
			// Copy one of the loaded meshes to be our current mesh
			objl_pacman::Mesh curMesh = Loader.LoadedMeshes[i];

			// Print Mesh Name
			file << "Mesh " << i << ": Name=" << curMesh.MeshName << "\n";

			// Print Vertices
			file << "Vertices=" <<  curMesh.Vertices.size() << "\n";

			// Go through each vertex and print its number,
			//  position, normal, and texture coordinate
			for (int j = 0; j < curMesh.Vertices.size(); j++)
			{
				file << "V" << j << ": " <<
					"P(" << curMesh.Vertices[j].Position.X << ", " << curMesh.Vertices[j].Position.Y << ", " << curMesh.Vertices[j].Position.Z << ") " <<
					"N(" << curMesh.Vertices[j].Normal.X << ", " << curMesh.Vertices[j].Normal.Y << ", " << curMesh.Vertices[j].Normal.Z << ") " <<
					"TC(" << curMesh.Vertices[j].TextureCoordinate.X << ", " << curMesh.Vertices[j].TextureCoordinate.Y << ")\n";
			}

			// Print Indices
			file << "Indices=" << curMesh.Indices.size() << "\n";

			// Go through every 3rd index and print the
			//	triangle that these indices represent
			for (int j = 0; j < curMesh.Indices.size(); j += 3)
			{
				file << "T" << j / 3 << ": " << curMesh.Indices[j] << ", " << curMesh.Indices[j + 1] << ", " << curMesh.Indices[j + 2] << "\n";
			}

			// Print Material
			file << "Material: " << curMesh.MeshMaterial.name << "\n";
			file << "Ambient Color: " << curMesh.MeshMaterial.Ka.X << ", " << curMesh.MeshMaterial.Ka.Y << ", " << curMesh.MeshMaterial.Ka.Z << "\n";
			file << "Diffuse Color: " << curMesh.MeshMaterial.Kd.X << ", " << curMesh.MeshMaterial.Kd.Y << ", " << curMesh.MeshMaterial.Kd.Z << "\n";
			file << "Specular Color: " << curMesh.MeshMaterial.Ks.X << ", " << curMesh.MeshMaterial.Ks.Y << ", " << curMesh.MeshMaterial.Ks.Z << "\n";
			file << "Specular Exponent: " << curMesh.MeshMaterial.Ns << "\n";
			file << "Optical Density: " << curMesh.MeshMaterial.Ni << "\n";
			file << "Dissolve: " << curMesh.MeshMaterial.d << "\n";
			file << "Illumination: " << curMesh.MeshMaterial.illum << "\n";
			file << "Ambient Texture Map: " << curMesh.MeshMaterial.map_Ka << "\n";
			file << "Diffuse Texture Map: " << curMesh.MeshMaterial.map_Kd << "\n";
			file << "Specular Texture Map: " << curMesh.MeshMaterial.map_Ks << "\n";
			file << "Alpha Texture Map: " << curMesh.MeshMaterial.map_d << "\n";
			file << "Bump Map: " << curMesh.MeshMaterial.map_bump << "\n";
			std::cout << "Mesh " << i << ": " << curMesh.MeshName << "\n";

			// Leave a space to separate from the next mesh
			file << "\n";
            kiki();
            monitor_off=1;
		}

		// Close File
		file.close();
	}
	// If not output an error
	else
	{
		// Create/Open e1Out.txt
		std::ofstream file("e1Out.txt");

		// Output Error
		file << "Failed to Load File. May have failed to find it or it was not an .obj file.\n";

		// Close File
		file.close();
	}

	// Exit the program
	return 0;
}
