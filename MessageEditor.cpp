/*
 * Copyright 2015 Your Name <your@email.address>
 * All rights reserved. Distributed under the terms of the MIT license.
 */



#include <storage/Directory.h>
#include <storage/File.h>
#include <storage/FindDirectory.h>
#include <storage/Path.h>
#include <translation/TranslationUtils.h>

#include <string.h>
#include <stdio.h>

#include "MessageEditor.h"


MessageEditor::MessageEditor():BApplication(APP_SIGNATURE) {
	//RegisterMime();
	mWindow= new MessageEditorWindow(100.0,100.0,600.0,500.0);
	mWindow->CenterOnScreen();
}

MessageEditor::~MessageEditor() {
	delete mWindow;
}

void MessageEditor::ReadyToRun() {
	//create settingsfolder
	BPath		settings;
	status_t	err				= B_OK;
	BDirectory	*settingsDir	= NULL;
	find_directory(B_USER_SETTINGS_DIRECTORY, &settings, true);
	settingsDir = new BDirectory(settings.Path());
	err = settingsDir->CreateDirectory("MessageEditor", NULL);
	err = settingsDir->SetTo(settingsDir, "MessageEditor");
}

/**
 * @todo request the Quit .. don´t simply quit all without asking (so that there is chance to save or abort because the document has changed)
 */
bool MessageEditor::QuitRequested() {
	delete mWindow;
	return true;
}

void MessageEditor::MessageReceived(BMessage *message) {
	switch(message->what) {
/*		case MENU_FILE_OPEN: {
			break;
		}
		case MENU_FILE_NEW: {
			break;
		}*/
		default:
			BApplication::MessageReceived(message);
			break;
	}
}

void MessageEditor::RefsReceived(BMessage *msg) {
	uint32 		type;
	int32 		count;
	entry_ref	ref;

	msg->GetInfo("refs", &type, &count);

	// not a entry_ref?
	if (type != B_REF_TYPE) {
		return;
	}

	if (msg->FindRef("refs", 0, &ref) == B_OK){
			BFile *messageFile = new BFile(&ref, B_READ_WRITE);
			if (messageFile->InitCheck()==B_OK){
				BMessage *toLoad = new BMessage();
				if (toLoad->Unflatten(messageFile) == B_OK){
					mWindow->SetMessage(toLoad);
				}
				else
					printf("could not parse BMessage");
			}
			else
				printf("ERROR initilizing File\n");
			delete messageFile;	
		}
}

void MessageEditor::AboutRequested() {
	//**ToDo implement a about Window
}

void MessageEditor::ArgvReceived(int32 argc, char **argv) {
	if (argc>1) {
		BEntry ref(argv[1]);
		if (ref.Exists()){
				/** try to load the Message
				}
				else
					printf("Error creating the document");*/
		}
		else
			printf("Could not load %s. File dosent exist",argv[1]);
	}
}

int main()
{

	new MessageEditor();
	be_app->Run();
	delete be_app;
	return 0;
}
