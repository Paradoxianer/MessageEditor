/*
 * Copyright 2015 Your Name <your@email.address>
 * All rights reserved. Distributed under the terms of the MIT license.
 */
#ifndef MESSAGE_EDITOR_WINDOW_H
#define MESSAGE_EDITOR_WINDOW_H

#include <Window.h>
#include <SupportDefs.h>
#include <FilePanel.h>

#include "MessageListView.h"


class MessageEditorWindow: public BWindow {
public:
	MessageEditorWindow(float left, float top, float right, float bottom);
	~MessageEditorWindow();
	void MessageReceived(BMessage *msg);
	void SetMessage(BMessage *newMessage);
	BMessage Message(){return fCurrentMessage;);
	bool QuitRequested();

private:
		
	MessageListView	*mListView;
	BMessage		*fCurrentMessage;
	BFilePanel		*fOpenFilePanel;

	
};


#endif // _H
