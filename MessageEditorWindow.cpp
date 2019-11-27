/*
 * Copyright 2015 Your Name <your@email.address>
 * All rights reserved. Distributed under the terms of the MIT license.
 */


#include "MessageEditorWindow.h"

MessageEditorWindow::MessageEditorWindow(float left, float top, float right, float bottom)
	: 
	BWindow(BRect(left,top,right,bottom), "MessageEditor", B_TITLED_WINDOW, B_ASYNCHRONOUS_CONTROLS)
{
	fCurrentMessage = NULL
	mListView = new MessageEditor(fCurrentMessage);

	
	fTopMenuBar = new BMenuBar("topmenubar");
	fMessageFileTextControl = new BTextControl(B_TRANSLATE("Message File"), "", 
											new BMessage(MENU_FILE_OPEN));

	fChooseMessageFileButton = new BButton(B_TRANSLATE("Choose Message File"),
											new BMessage(MW_BUTTON_CHOOSEMESSAGEFILE));
											
	fOpenFilePanel = new BFilePanel(B_OPEN_PANEL, 
									new BMessenger(this), 
									NULL,
									B_FILE_NODE,
									false,
									new BMessage(MW_REF_MESSAGEFILE));
	
	
	
	//define menu layout
	BLayoutBuilder::Menu<>(fTopMenuBar)
		.AddMenu(B_TRANSLATE("File"))
			.AddItem(B_TRANSLATE("Quit"), B_QUIT_REQUESTED, 'Q')
		.End()
		.AddMenu(B_TRANSLATE("Help"))
			.AddItem(B_TRANSLATE("About"), MW_MENU_ABOUT)
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
		case MENU_ABOUT: {
			be_app->PostMessage(B_ABOUT_REQUESTED);
			break;
		}
		
		case MENU_OPEN: {
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
};

