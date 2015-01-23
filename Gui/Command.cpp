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
   // Base::Console().Message("Hello, World!\n");
    
	App::Document* myDoc = App::GetApplication().getActiveDocument();

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

void CreateShowcaseModCommands(void)
{
    Gui::CommandManager &rcCmdMgr = Gui::Application::Instance->commandManager();
    rcCmdMgr.addCommand(new CmdShowcaseModTest());
}
