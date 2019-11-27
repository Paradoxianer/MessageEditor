/*
 * Copyright 2015 Your Name <your@email.address>
 * All rights reserved. Distributed under the terms of the MIT license.
 */


#include "MessageEditor.h"

#include <app/Roster.h>
#include <interface/Alert.h>
#include <interface/Rect.h>

#include <storage/Directory.h>
#include <storage/Entry.h>
#include <storage/FindDirectory.h>
#include <storage/Path.h>
#include <translation/TranslationUtils.h>

#include <string.h>


ProjektConceptor::ProjektConceptor():BApplication(APP_SIGNATURE) {
	//RegisterMime();
	mWindow= new MessageEditorWindow();
}

ProjektConceptor::~ProjektConceptor() {
	TRACE();
	delete mWindow;
}

void ProjektConceptor::ReadyToRun() {
	TRACE();
	//creat settingsfolder
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
bool ProjektConceptor::QuitRequested() {
	TRACE();
	delete
	return true;
}

void ProjektConceptor::MessageReceived(BMessage *message) {
	TRACE();
	switch(message->what) {
		case MENU_FILE_OPEN: {
//			openPanel->Show();		// Show the file panel
			break;
		}
		case MENU_FILE_NEW: {
			break;
		}
		default:
			BApplication::MessageReceived(message);
			break;
	}
}

void ProjektConceptor::RefsReceived(BMessage *msg) {
	TRACE();
	uint32 		type;
	int32 		count;
	BEntry		*entry=new BEntry();
	entry_ref	ref;

	msg->GetInfo("refs", &type, &count);

	// not a entry_ref?
	if (type != B_REF_TYPE) {
		delete entry;
		return;
	}

	if (msg->FindRef("refs", 0, &ref) == B_OK)
		if (entry->SetTo(&ref,true)==B_OK) {
			PDocument *doc=documentManager->PDocumentAt(0);
			doc->SetEntry(&ref);
			doc->Load();
		}
	delete entry;
}

void ProjektConceptor::AboutRequested() {
	TRACE();
	//**ToDo implement a about Window
}

void ProjektConceptor::ArgvReceived(int32 argc, char **argv) {
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
