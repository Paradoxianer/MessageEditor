/*
 * Copyright 2015 Your Name <your@email.address>
 * All rights reserved. Distributed under the terms of the MIT license.
 */

#include <Catalog.h>
#include <LayoutBuilder.h>
#include <Application.h>

#include "MessageEditorWindow.h"
#include "MessageEditorDefs.h"

#undef B_TRANSLATION_CONTEXT
#define B_TRANSLATION_CONTEXT "MessageEditorWindow"


MessageEditorWindow::MessageEditorWindow(float left, float top, float right, float bottom)
	: 
	BWindow(BRect(left,top,right,bottom), "MessageEditor", B_TITLED_WINDOW, B_ASYNCHRONOUS_CONTROLS)
{
	fCurrentMessage = NULL;
	mListView = new MessageListView(fCurrentMessage);

	
	fTopMenuBar = new BMenuBar("topmenubar");
	fMessageFileTextControl = new BTextControl(B_TRANSLATE("Message File"), "", 
											new BMessage(FILE_OPEN));

	fChooseMessageFileButton = new BButton(B_TRANSLATE("Choose Message File"),
											new BMessage(MENU_FILE_OPEN));
											
	fOpenFilePanel = new BFilePanel();
	
	
	
	//define menu layout
	BLayoutBuilder::Menu<>(fTopMenuBar)
		.AddMenu(B_TRANSLATE("File"))
			.AddItem(B_TRANSLATE("Quit"), B_QUIT_REQUESTED, 'Q')
		.End()
		.AddMenu(B_TRANSLATE("Help"))
			.AddItem(B_TRANSLATE("About"), MENU_APP_ABOUT)
		.End()
	.End();

	//define main layout
	BLayoutBuilder::Group<>(this, B_VERTICAL,0)
		.SetInsets(0)
		.Add(fTopMenuBar)
		.AddGroup(B_HORIZONTAL)
			.SetInsets(5,5,5,5)
			.Add(fMessageFileTextControl)
			.Add(fChooseMessageFileButton)
		.End()
		.AddGroup(B_HORIZONTAL)
			.SetInsets(5,3,3,3)
			.Add(mListView,20)
		//.AddGlue()
	.Layout();
}


MessageEditorWindow::~MessageEditorWindow() {
	delete fCurrentMessage;
	delete fOpenFilePanel;	
}


void
MessageEditorWindow::MessageReceived(BMessage *msg) {
	switch(msg->what) {
		case MENU_APP_ABOUT: {
			be_app->PostMessage(B_ABOUT_REQUESTED);
			break;
		}
		
		case MENU_FILE_OPEN: {
			fOpenFilePanel->Show();
			break;
		}		
		default: {
			BWindow::MessageReceived(msg);
			break;
		}

	}
}

void MessageEditorWindow::SetMessage(BMessage *newMessage){
	mListView->SetContainer(newMessage);
};

bool MessageEditorWindow::QuitRequested(){
	return true;
};

