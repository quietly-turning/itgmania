#ifndef NetworkSyncManager_H
#define NetworkSyncManager_H
   
/*
-----------------------------------------------------------------------------
 Class: NetworkSyncManager  (And netholder)

 Desc: Uses ezsockets for primitive song syncing and score reporting.

 Copyright (c) 2003-2004 by the person(s) listed below.  All rights reserved.
	Charles Lohr
	Joshua Allen
-----------------------------------------------------------------------------
*/

#include "PlayerNumber.h"
 
class EzSockets;

class NetworkSyncManager 
{
public:
	NetworkSyncManager(int argc, char **argv);
	~NetworkSyncManager();

    //If "useSMserver" then send score to server
	void ReportScore(int playerID, int step, int score, int combo);	
	void ReportSongOver();	//Report to server that song is over
	void StartRequest();	//Request a start.  Block until granted.
	bool Connect(const CString& addy, unsigned short port); // Connect to SM Server

	int m_playerLife[NUM_PLAYERS];	//Life

private:
	int m_playerID;  //these are currently unused, but need to stay
	int m_step;
	int m_score;
	int m_combo;
    
	bool FlashXMLStyle;	//Append 4 0s at end of packet.
							//For FLASH client.

	bool useSMserver;

    EzSockets *NetPlayerClient;

	int m_ServerVersion; //ServerVersion

	bool Listen(unsigned short port);

    
    struct netHolder		//Data structure used for sending data to server
    {
        int m_playerID;	//PID (also used for Commands)
        int m_step;		//SID (StepID, 0-6 for Miss to Marv, 7,8 for boo and ok)
        int m_score;	//Player's Score
        int m_combo;	//Player's Current Combo
		int m_life;		//Player's Life
    };

	struct netHolderFlash
	{
		char data[73];
	};
    
};

extern NetworkSyncManager *NSMAN;
 
#endif
 
