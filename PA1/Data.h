#include "header.h"

class Data 
{
    public:
        // constructor
        Data(string Command, string Description, int Points) 
        {
            command = Command;
            description = Description;
            points = Points;
        }

        // display command, description and points
        void display() const 
        {
            cout << "Command: " << command << "\nDescription: " << description << "\nPoints: " << points << "\n\n";
        }

        // getters
        string getCommand()
        {
            return command;
        }
        string getDescription()
        {
            return description;
        }
        int getPoints()
        {
            return points;
        }

        // setters
        void setCommand(string Command)
        {
            command = Command;
        }
        void setDescription(string Description)
        {
            description = Description;
        }
        void setPoints(int Points)
        {
            points = Points;
        }

    private:
        string command;
        string description;
        int points;

};