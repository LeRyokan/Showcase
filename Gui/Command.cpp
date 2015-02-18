/***************************************************************************
 *   Copyright (c) YEAR YOUR NAME         <Your e-mail address>            *
 *                                                                         *
 *   This file is part of the FreeCAD CAx development system.              *
 *                                                                         *
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU Library General Public           *
 *   License as published by the Free Software Foundation; either          *
 *   version 2 of the License, or (at your option) any later version.      *
 *                                                                         *
 *   This library  is distributed in the hope that it will be useful,      *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Library General Public License for more details.                  *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this library; see the file COPYING.LIB. If not,    *
 *   write to the Free Software Foundation, Inc., 59 Temple Place,         *
 *   Suite 330, Boston, MA  02111-1307, USA                                *
 *                                                                         *
 ***************************************************************************/


#include "PreCompiled.h"
#ifndef _PreComp_
#endif

#include <Base/Console.h>
#include <App/Document.h>
#include <App/DocumentObject.h>
#include <App/GeoFeature.h>
#include <Gui/Application.h>
#include <Gui/Command.h>

#include <Gui/MainWindow.h>
#include <Gui/FileDialog.h>

#include <windows.h>
#include "Actions.h"


float stopOpenRightDoorAction();
float stopCloseRightDoorAction();
float stopOpenLeftDoorAction();
float stopCloseLeftDoorAction();
float stopCloseTrunkAction();
float stopOpenTrunkAction();

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//===========================================================================
// CmdShowcaseModTest THIS IS JUST A TEST COMMAND
//===========================================================================
DEF_STD_CMD(CmdShowcaseModTest);

CmdShowcaseModTest::CmdShowcaseModTest()
  :Command("ShowcaseMod_Test")
{
    sAppModule    = "ShowcaseMod";
    sGroup        = QT_TR_NOOP("ShowcaseMod");
    sMenuText     = QT_TR_NOOP("Hello");
    sToolTipText  = QT_TR_NOOP("ShowcaseMod Test function");
    sWhatsThis    = QT_TR_NOOP("ShowcaseMod Test function");
    sStatusTip    = QT_TR_NOOP("ShowcaseMod Test function");
    sPixmap       = "Test1";
    sAccel        = "CTRL+H";
}

void CmdShowcaseModTest::activated(int iMsg)
{
   Base::Console().Message("Hello, World!\n");
}

//===========================================================================
// CmdShowcaseImportCar
//===========================================================================
DEF_STD_CMD(CmdShowcaseImportCar);


CmdShowcaseImportCar::CmdShowcaseImportCar()
  : Command("Import_Car")
{
    sAppModule      = "ShowcaseMod";
    sGroup          = QT_TR_NOOP("ShowcaseMod");
    sMenuText       = QT_TR_NOOP("Import car to animate");
    sToolTipText    = QT_TR_NOOP("Import a new car in the active scene");
    sWhatsThis      = "Import_Car";
    sStatusTip      = sToolTipText;
    sPixmap         = "Test2";
}

void CmdShowcaseImportCar::activated(int iMsg)
{
	// FileOpen //
	App::Application &app = App::GetApplication();
	
	QString docName = Gui::FileDialog::getOpenFileName();

	if(docName != NULL) {
		App::Document * myDoc = app.openDocument(docName.toAscii() );
	}
}

//===========================================================================
// CmdShowcaseOpenRightDoor
//===========================================================================
DEF_STD_CMD(CmdShowcaseOpenRightDoor);

PlacementAction * openRightDoorAction = NULL;

CmdShowcaseOpenRightDoor::CmdShowcaseOpenRightDoor()
  : Command("Open_Right_Door")
{
    sAppModule      = "ShowcaseMod";
    sGroup          = QT_TR_NOOP("ShowcaseMod");
    sMenuText       = QT_TR_NOOP("Open the right door");
    sToolTipText    = QT_TR_NOOP("Animation of the right door when it's openning");
    sWhatsThis      = "Open_Right_Door";
    sStatusTip      = sToolTipText;
    sPixmap         = "Test3";
}

void CmdShowcaseOpenRightDoor::activated(int iMsg)
{
	App::Document* myDoc = App::GetApplication().getActiveDocument();
	PlacementAction * action = new PlacementAction();
	if(openRightDoorAction != NULL)
	{
		openRightDoorAction->stop();
		delete openRightDoorAction;
		openRightDoorAction = NULL;
	}

	float evolution = stopCloseRightDoorAction();

	openRightDoorAction = action;
	Base::Placement porteDroitePlacementOrig(Base::Vector3d(0,0,0),Base::Rotation(Base::Vector3d(0,1,0),(0)));
	Base::Placement porteDroitePlacementDest(Base::Vector3d(100*8,0,100*4),Base::Rotation(Base::Vector3d(0,1,0),(-101*0.8)));
	App::DocumentObject * obj = myDoc->getObject("Peugeot_207001");
	App::GeoFeature * geo = (App::GeoFeature*) obj;
	geo->Placement.setValue(porteDroitePlacementOrig);
	action->setDuration(1);
	action->setTargetAndEndValueAndInitialEvolution(obj,porteDroitePlacementDest,evolution);
	action->update();
}

float stopOpenRightDoorAction() {
	float evolution = 0;
	if(openRightDoorAction != NULL)
	{
		evolution = openRightDoorAction->getOppositeEvolution();
		openRightDoorAction->stop();
		delete openRightDoorAction;
		openRightDoorAction = NULL;
	}
	return evolution;
}

//===========================================================================
// CmdShowcaseCloseRightDoor
//===========================================================================
DEF_STD_CMD(CmdShowcaseCloseRightDoor);

PlacementAction * closeRightDoorAction = NULL;

CmdShowcaseCloseRightDoor::CmdShowcaseCloseRightDoor()
  : Command("Close_Right_Door")
{
    sAppModule      = "ShowcaseMod";
    sGroup          = QT_TR_NOOP("ShowcaseMod");
    sMenuText       = QT_TR_NOOP("Closes the right door");
    sToolTipText    = QT_TR_NOOP("Animation of the right door when it's closing");
    sWhatsThis      = "Close_Right_Door";
    sStatusTip      = sToolTipText;
    sPixmap         = "Test6";
}

void CmdShowcaseCloseRightDoor::activated(int iMsg)
{
	App::Document* myDoc = App::GetApplication().getActiveDocument();
	PlacementAction * action = new PlacementAction();
	if(closeRightDoorAction != NULL)
	{
		closeRightDoorAction->stop();
		delete closeRightDoorAction;
		closeRightDoorAction = NULL;
	}

	float evolution = stopOpenRightDoorAction();

	closeRightDoorAction = action;
	Base::Placement rightDoorPlacementOrig(Base::Vector3d(800,0,400),Base::Rotation(Base::Vector3d(0,1,0),(-80.8)));
	Base::Placement rightDoorPlacementDest(Base::Vector3d(0,0,0),Base::Rotation(Base::Vector3d(0,1,0),(0)));
	App::DocumentObject * obj = myDoc->getObject("Peugeot_207001");
	App::GeoFeature * geo = (App::GeoFeature*) obj;
	geo->Placement.setValue(rightDoorPlacementOrig);
	action->setDuration(1);
	action->setTargetAndEndValueAndInitialEvolution(obj,rightDoorPlacementDest,evolution);
	action->update();
}

float stopCloseRightDoorAction() {
	float evolution = 0;
	if(closeRightDoorAction != NULL)
	{
		evolution = closeRightDoorAction->getOppositeEvolution();
		closeRightDoorAction->stop();
		delete closeRightDoorAction;
		closeRightDoorAction = NULL;
	}
	return evolution;
}

//===========================================================================
// CmdShowcaseOpenLeftDoor
//===========================================================================
DEF_STD_CMD(CmdShowcaseOpenLeftDoor);

PlacementAction * openLeftDoorAction = NULL;

CmdShowcaseOpenLeftDoor::CmdShowcaseOpenLeftDoor()
  : Command("Open_Left_Door")
{
    sAppModule      = "ShowcaseMod";
    sGroup          = QT_TR_NOOP("ShowcaseMod");
    sMenuText       = QT_TR_NOOP("Open the left door");
    sToolTipText    = QT_TR_NOOP("Animation of the left door when it's openning");
    sWhatsThis      = "Open_Left_Door";
    sStatusTip      = sToolTipText;
    sPixmap         = "Test4";
}

void CmdShowcaseOpenLeftDoor::activated(int iMsg)
{
App::Document* myDoc = App::GetApplication().getActiveDocument();
	PlacementAction * action = new PlacementAction();
	if(openLeftDoorAction != NULL)
	{
		openLeftDoorAction->stop();
		delete openLeftDoorAction;
		openLeftDoorAction = NULL;
	}

	float evolution = stopCloseLeftDoorAction();

	openLeftDoorAction = action;
	Base::Placement porteGauchePlacementOrig(Base::Vector3d(0,0,0),Base::Rotation(Base::Vector3d(0,1,0),(0)));
	Base::Placement porteGauchePlacementDest(Base::Vector3d(-100*8.75,0,100*5.6),Base::Rotation(Base::Vector3d(0,1,0),(101*0.8)));
	App::DocumentObject * obj = myDoc->getObject("Peugeot_207");
	App::GeoFeature * geo = (App::GeoFeature*) obj;
	geo->Placement.setValue(porteGauchePlacementOrig);
	action->setDuration(1);
	action->setTargetAndEndValueAndInitialEvolution(obj,porteGauchePlacementDest,evolution);
	action->update();
}

float stopOpenLeftDoorAction() {
	float evolution = 0;
	if(openLeftDoorAction != NULL)
	{
		evolution = openLeftDoorAction->getOppositeEvolution();
		openLeftDoorAction->stop();
		delete openLeftDoorAction;
		openLeftDoorAction = NULL;
	}
	return evolution;
}

//===========================================================================
// CmdShowcaseCloseLeftDoor
//===========================================================================
DEF_STD_CMD(CmdShowcaseCloseLeftDoor);

PlacementAction * closeLeftDoorAction = NULL;

CmdShowcaseCloseLeftDoor::CmdShowcaseCloseLeftDoor()
  : Command("Close_Left_Door")
{
    sAppModule      = "ShowcaseMod";
    sGroup          = QT_TR_NOOP("ShowcaseMod");
    sMenuText       = QT_TR_NOOP("Close the left door");
    sToolTipText    = QT_TR_NOOP("Animation of the left door when it's closing");
    sWhatsThis      = "Close_Left_Door";
    sStatusTip      = sToolTipText;
    sPixmap         = "Test7";
}

void CmdShowcaseCloseLeftDoor::activated(int iMsg)
{
	App::Document* myDoc = App::GetApplication().getActiveDocument();
	PlacementAction * action = new PlacementAction();
	if(closeLeftDoorAction != NULL)
	{
		closeLeftDoorAction->stop();
		delete closeLeftDoorAction;
		closeLeftDoorAction = NULL;
	}

	float evolution = stopOpenLeftDoorAction();
	
	closeLeftDoorAction = action;
	Base::Placement leftDoorPlacementOrig(Base::Vector3d(-875,0,560),Base::Rotation(Base::Vector3d(0,1,0),(80.8)));
	Base::Placement leftDoorPlacementDest(Base::Vector3d(0,0,0),Base::Rotation(Base::Vector3d(0,1,0),(0)));
	App::DocumentObject * obj = myDoc->getObject("Peugeot_207");
	App::GeoFeature * geo = (App::GeoFeature*) obj;
	geo->Placement.setValue(leftDoorPlacementOrig);
	action->setDuration(1);
	action->setTargetAndEndValueAndInitialEvolution(obj,leftDoorPlacementDest,evolution);
	action->update();
}

float stopCloseLeftDoorAction() {
	float evolution = 0;
	if(closeLeftDoorAction != NULL)
	{
		evolution = closeLeftDoorAction->getOppositeEvolution();
		closeLeftDoorAction->stop();
		delete closeLeftDoorAction;
		closeLeftDoorAction = NULL;
	}
	return evolution;
}

//===========================================================================
// CmdShowcaseOpenCarTrunk 
//===========================================================================
DEF_STD_CMD(CmdShowcaseOpenCarTrunk);

PlacementAction * openTrunkAction = NULL;

CmdShowcaseOpenCarTrunk::CmdShowcaseOpenCarTrunk()
  : Command("Open_Car_Trunk")
{
    sAppModule      = "ShowcaseMod";
    sGroup          = QT_TR_NOOP("ShowcaseMod");
    sMenuText       = QT_TR_NOOP("Open the car trunk");
    sToolTipText    = QT_TR_NOOP("Animation of the car trunk when it's opening");
    sWhatsThis      = "Open_Car_Trunk";
    sStatusTip      = sToolTipText;
    sPixmap         = "Test5";
}

void CmdShowcaseOpenCarTrunk::activated(int iMsg)
{
	App::Document* myDoc = App::GetApplication().getActiveDocument();
	PlacementAction * action = new PlacementAction();
	if(openTrunkAction != NULL)
	{
		openTrunkAction->stop();
		delete openTrunkAction;
		openTrunkAction = NULL;
	}
	float evolution = stopCloseTrunkAction();

	openTrunkAction = action;
	App::DocumentObject * obj = myDoc->getObject("Peugeot_207004");

	App::GeoFeature* geo1 = (App::GeoFeature*)obj;
	Base::Placement trunkPlacementOrig = geo1->Placement.getValue();
	Base::Placement trunkPlacementDest(Base::Vector3d(0,0,3300),Base::Rotation(Base::Vector3d(-1,0,0),(-80)));
	
	App::GeoFeature * geo = (App::GeoFeature*) obj;
	geo->Placement.setValue(trunkPlacementOrig);
	action->setDuration(1);
	action->setTargetAndEndValueAndInitialEvolution(obj,trunkPlacementDest, evolution);
	action->update();
}

float stopOpenTrunkAction() {
	float evolution = 0;
	if(openTrunkAction != NULL)
	{
		evolution = openTrunkAction->getOppositeEvolution();
		openTrunkAction->stop();
		delete openTrunkAction;
		openTrunkAction = NULL;
	}
	return evolution;
}

//===========================================================================
// CmdShowcaseCloseTrunk 
//===========================================================================
DEF_STD_CMD(CmdShowcaseCloseTrunk);

PlacementAction * closeTrunkAction = NULL;

CmdShowcaseCloseTrunk::CmdShowcaseCloseTrunk()
  : Command("Close_Trunk")
{
    sAppModule      = "ShowcaseMod";
    sGroup          = QT_TR_NOOP("ShowcaseMod");
    sMenuText       = QT_TR_NOOP("Close the car trunk");
    sToolTipText    = QT_TR_NOOP("Animation of the trunk when it's closing");
    sWhatsThis      = "Close_Trunk";
    sStatusTip      = sToolTipText;
    sPixmap         = "Test8";
}

void CmdShowcaseCloseTrunk::activated(int iMsg)
{
	App::Document* myDoc = App::GetApplication().getActiveDocument();
	PlacementAction * action = new PlacementAction();
	if(closeTrunkAction != NULL)
	{
		closeTrunkAction->stop();
		delete closeTrunkAction;
		closeTrunkAction = NULL;
	}
	float evolution = stopOpenTrunkAction();

	closeTrunkAction = action;
	App::DocumentObject * obj = myDoc->getObject("Peugeot_207004");

	App::GeoFeature* geo2 = (App::GeoFeature*)obj;
	Base::Placement trunkPlacementOrig = geo2->Placement.getValue();
	Base::Placement trunkPlacementDest(Base::Vector3d(0,0,0),Base::Rotation(Base::Vector3d(-1,0,0),(0)));
	
	App::GeoFeature * geo = (App::GeoFeature*) obj;
	geo->Placement.setValue(trunkPlacementOrig);
	action->setDuration(1);
	action->setTargetAndEndValueAndInitialEvolution(obj,trunkPlacementDest,evolution);
	action->update();
}

float stopCloseTrunkAction() {
	float evolution = 0;
	if(closeTrunkAction != NULL)
	{
		evolution = closeTrunkAction->getOppositeEvolution();
		closeTrunkAction->stop();
		delete closeTrunkAction;
		closeTrunkAction = NULL;
	}
	return evolution;
}

//===========================================================================
// CreateShowcaseModCommands 
//===========================================================================
void CreateShowcaseModCommands(void)
{
    Gui::CommandManager &rcCmdMgr = Gui::Application::Instance->commandManager();
    rcCmdMgr.addCommand(new CmdShowcaseModTest());
	rcCmdMgr.addCommand(new CmdShowcaseImportCar());
	rcCmdMgr.addCommand(new CmdShowcaseOpenRightDoor());
	rcCmdMgr.addCommand(new CmdShowcaseOpenLeftDoor());
	rcCmdMgr.addCommand(new CmdShowcaseOpenCarTrunk());
	rcCmdMgr.addCommand(new CmdShowcaseCloseRightDoor());
	rcCmdMgr.addCommand(new CmdShowcaseCloseLeftDoor());
	rcCmdMgr.addCommand(new CmdShowcaseCloseTrunk());
}