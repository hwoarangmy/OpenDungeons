/*
-----------------------------------------------------------------------------
This source file is part of OGRE
    (Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org/

Copyright (c) 2000-2006 Torus Knot Software Ltd
Also see acknowledgements in Readme.html

You may use this sample code for anything you like, it is not covered by the
LGPL like the rest of the engine.
-----------------------------------------------------------------------------
*/
/*
-----------------------------------------------------------------------------
Filename:    ExampleFrameListener.h
Description: Defines an example frame listener which responds to frame events.
This frame listener just moves a specified camera around based on
keyboard and mouse movements.
-----------------------------------------------------------------------------
*/

#ifndef __ExampleFrameListener_H__
#define __ExampleFrameListener_H__

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "Ogre.h"
#include "OgreStringConverter.h"
#include "OgreException.h"

#include <deque>
#include <CEGUI/CEGUI.h>
#include <OIS/OIS.h>
#include <OgreCEGUIRenderer.h>

//Use this define to signify OIS will be used as a DLL
//(so that dll import/export macros are in effect)
#define OIS_DYNAMIC_LIB
#include <OIS/OIS.h>

using namespace Ogre;

#include "TextRenderer.h"
#include "Socket.h"
#include "Tile.h"

class ExampleFrameListener: public FrameListener, public WindowEventListener, public OIS::MouseListener, public OIS::KeyListener
{
protected:
	void updateStats(void);

public:
	// Constructor takes a RenderWindow because it uses that to determine input context
	ExampleFrameListener(RenderWindow* win, Camera* cam, SceneManager *sceneManager, CEGUI::Renderer *renderer, bool bufferedKeys, bool bufferedMouse, bool bufferedJoy);

	//Adjust mouse clipping area
	virtual void windowResized(RenderWindow* rw);

	//Unattach OIS before window shutdown (very important under Linux)
	virtual void windowClosed(RenderWindow* rw);
	virtual ~ExampleFrameListener();

	virtual bool processUnbufferedKeyInput(const FrameEvent& evt);
	bool processUnbufferedMouseInput(const FrameEvent& evt);
	void moveCamera(double frameTime);
	void showDebugOverlay(bool show);

	// Override frameStarted event to process that (don't care about frameEnded)
	bool frameStarted(const FrameEvent& evt);
	bool frameEnded(const FrameEvent& evt);

	//CEGUI Functions
	bool quit(const CEGUI::EventArgs &e);
	bool mouseMoved(const OIS::MouseEvent &arg);
	bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
	bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
	bool keyPressed(const OIS::KeyEvent &arg);
	bool keyReleased(const OIS::KeyEvent &arg);

	// Console functions
	void printText(string text);
	void executePromptCommand();
	string getHelpText(string arg);
	
	// Console variables
	string command, arguments, commandOutput, prompt;
	deque< pair<time_t, string> > chatMessages;
	string consoleBuffer, promptCommand, chatString;


protected:
	Camera* mCamera;
	SceneNode *mCamNode;

	Ogre::Vector3 mTranslateVector;
	double zChange;
	Ogre::Vector3 mRotateLocalVector;
	Ogre::Vector3 mRotateWorldVector;
	RenderWindow* mWindow;
	bool mStatsOn;

	std::string mDebugText;

	unsigned int mNumScreenShots;
	float mMoveScale;
	float mZoomSpeed;
	Degree mRotScale;
	// just to stop toggles flipping too fast
	Real mTimeUntilNextToggle ;
	Radian mRotX, mRotY, mRotZ;
	TextureFilterOptions mFiltering;
	int mAniso;
	Tile::TileType mCurrentTileType;
	int mCurrentFullness;

	int mSceneDetailIndex ;
	Real mMoveSpeed;
	Degree mRotateSpeed;
	Overlay* mDebugOverlay;

	//OIS Input devices
	OIS::InputManager* mInputManager;
	OIS::Mouse*    mMouse;
	OIS::Keyboard* mKeyboard;
	OIS::JoyStick* mJoy;

	// Mouse query stuff
	RaySceneQuery *mRaySceneQuery;     // The ray scene query pointer
	bool mLMouseDown, mRMouseDown;     // True if the mouse buttons are down
	int mLStartDragX, mLStartDragY;    // The start tile coordinates for a left drag
	int mRStartDragX, mRStartDragY;    // The start tile coordinates for a left drag
	int mCount;                        // The number of robots on the screen
	SceneManager *mSceneMgr;           // A pointer to the scene manager
	SceneNode *mCurrentObject;         // The newly created object
	CEGUI::Renderer *mGUIRenderer;     // CEGUI renderer
	int xPos, yPos;

	enum DragType {creature, tileSelection, nullDragType};

private:
	void handleAcceleration(double accelFactor, double accelLimit, double &accel, bool &positive, bool driven, bool sameDir);
	bool mContinue;
	bool terminalActive;
	int terminalWordWrap;

	DragType mDragType;
	string mDraggedCreature;

	// Multiplayer stuff
	Socket clientSocket, serverSocket;
	pthread_t clientThread;
};

#endif