#ifndef CREATURE_H
#define CREATURE_H

#include <Ogre.h>
#include <string>
using namespace std;

class Creature
{
	public:
		Creature();
		Creature(string nClassName, string nMeshName, Ogre::Vector3 nScale);
		friend ostream& operator<<(ostream& os, Creature *c);
		friend istream& operator>>(istream& is, Creature *c);
		void createMesh();
		void destroyMesh();

		// Class properties
		string className;
		string meshName;
		Ogre::Vector3 scale;

		// Individual properties
		string name;
		string meshID, nodeID;
		Ogre::Vector3 position;
		int color;
		int hp, mana;
};

#endif
