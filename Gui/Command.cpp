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
	// Base::Console().Message("Hello, World!\n");
   

	// FileOpen //
	App::Application &app = App::GetApplication();
	App::Document * myDoc = app.openDocument("C:/Users/tixie_000/Desktop/Projet_3DTRI_RenduEtape2_Groupe10/PeugeotAnimee.FCStd");
		
	//App::Document* myDoc = App::GetApplication().getActiveDocument();

	//Selection de la porte Gauche
	App::DocumentObject* porteGauche = myDoc->getObject("Peugeot_207");
	App::GeoFeature* geo = (App::GeoFeature*)myDoc->getObject("Peugeot_207");
	Base::Placement porteGauchePlacement = geo->Placement.getValue();

	//Selection de la porte Droite
	//App::DocumentObject* porteDroite = myDoc->getObject("Peugeot_207001");
	//App::PropertyPlacement porteDroitePlacement = porteDroite->placement();
	  

	
	
		//Base::Placement porteGauchePlacement(Base::Vector3d(0,0,0),Base::Rotation(Base::Vector3d(0,1,0),-(i*0.1)));
		//Base::Placement porteDroitePlacement(Base::Vector3(i*10,0,i*4),Base::Rotation(Base::Vector3(0,1,0),(i*0.6)));
		for(int i=0; i<101 ; i++)
		{
			geo->Placement.setValue(Base::Placement(Base::Vector3d(-i*10,0,i*4),Base::Rotation(Base::Vector3d(0,1,0),-(i*0.6))));
			//geo->Placement.setValue(Base::Placement(Base::Vector3d(20,0,8),Base::Rotation(Base::Vector3d(0,1,0),-(0.6))));
			geo->transformPlacement(porteGauchePlacement);
			
		}	
		
		//
		//porteDroite->transformPlacement(porteDroitePlacement);

		
		Gui::Application::Instance->updateActive();
		Sleep(10);

	

   

	//Base::Console().Message(myCar->getNameInDocument());
}





//===========================================================================
// CmdShowcaseOpenRightDoor
//===========================================================================
DEF_STD_CMD(CmdShowcaseOpenRightDoor);


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
	Base::Console().Message("VA CODER CETTE METHODE PLUS VITE QUE CA");
}

//===========================================================================
// CmdShowcaseOpenLeftDoor
//===========================================================================
DEF_STD_CMD(CmdShowcaseOpenLeftDoor);


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
	Base::Console().Message("ET CETTE METHODE LA ! TU L'AS OUBLIER AUSSI PEUT ETRE ?");	
}

//===========================================================================
// CmdShowcaseOpenCarTrunk 
//===========================================================================
DEF_STD_CMD(CmdShowcaseOpenCarTrunk);


CmdShowcaseOpenCarTrunk::CmdShowcaseOpenCarTrunk()
  : Command("Open_Car_Trunk")
{
    sAppModule      = "ShowcaseMod";
    sGroup          = QT_TR_NOOP("ShowcaseMod");
    sMenuText       = QT_TR_NOOP("Open the car trunk");
    sToolTipText    = QT_TR_NOOP("Animation of the car trunk when it's openning");
    sWhatsThis      = "Open_Car_Trunk";
    sStatusTip      = sToolTipText;
    sPixmap         = "Test5";
}

void CmdShowcaseOpenCarTrunk::activated(int iMsg)
{
	Base::Console().Message("WHHHHHAAAAAAAAAAAAAAAAAAAATTTT ENCORE UNE METHODE VIDE ! ");		
}

void CreateShowcaseModCommands(void)
{
    Gui::CommandManager &rcCmdMgr = Gui::Application::Instance->commandManager();
    rcCmdMgr.addCommand(new CmdShowcaseModTest());
	rcCmdMgr.addCommand(new CmdShowcaseImportCar());
	rcCmdMgr.addCommand(new CmdShowcaseOpenRightDoor());
	rcCmdMgr.addCommand(new CmdShowcaseOpenLeftDoor());
	rcCmdMgr.addCommand(new CmdShowcaseOpenCarTrunk());
}
