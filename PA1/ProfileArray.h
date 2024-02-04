#include "header.h"
#include "Profile.h"

// manages profile array
class ProfileArray 
{
private:
    static const int MAX_PROFILES = 100;
    Profile profiles[MAX_PROFILES];
    int numProfiles;

public:
    // constructor
    ProfileArray() : numProfiles(0) {}

    // getters
    int getNumProfiles() const 
    {
        return numProfiles;
    }
    Profile getProfile(int index)
    {
        if (index >= 0 && index < numProfiles) 
        {
            return profiles[index];
        } else
        {
            return Profile();
        }
    }

    // setters
    void setProfile(int index, const Profile& newProfile)
    {
        if (index >= 0 && index < MAX_PROFILES) 
        {
            profiles[index] = newProfile;
            if (index >= numProfiles) 
            {
                numProfiles = index + 1; 
            }
        }
    }

    //  insert or update a player profile
    void insertOrUpdateProfile(const string& playerName, int playerPoints) 
    {
        for (int i = 0; i < numProfiles; i++) 
        {
            if (profiles[i].getName() == playerName) 
            {
                // update existing profile
                profiles[i].setPoints(playerPoints);
                return;
            }
        }

        // add new profile
        if (numProfiles < MAX_PROFILES) {
            profiles[numProfiles++] = Profile(playerName, playerPoints);
        }
    }

    // search for a player profile
    int searchProfile(const string& playerName) 
    {
        for (int i = 0; i < numProfiles; i++) 
        {
            if (profiles[i].getName() == playerName) 
            {
                // returns the index of the profile
                return i; 
            }
        }
        // if profile is not found
        return -1; 
    }

    // displays all player profiles
    void displayAllProfiles() 
    {
        for (int i = 0; i < numProfiles; i++) 
        {
            cout << "Name: " << profiles[i].getName() << "\nPoints: " << profiles[i].getPoints() << "\n\n";
        }
    }
};