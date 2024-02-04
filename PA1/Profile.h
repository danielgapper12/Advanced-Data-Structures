#include "header.h"

class Profile
{
    public:
        Profile()
        {
            name = "";
            points = 0;
        }

        // constructor with parameters
        Profile(string playerName, int playerPoints)
        {
            name = playerName;
            points = playerPoints;
        }

        // display profile name and points
        void display() const {
            cout << "Name: " << name << "\nPoints: " << points << "\n\n";
        }

        string getName()
        {
            return name;
        }

        int getPoints()
        {
            return points;
        }

        void setName(string Name)
        {
            name = Name;
        }
        void setPoints(int Points)
        {
            points = Points;
        }

    private:
        string name;
        int points;   
};
