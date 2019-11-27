/**
 * @class MessageEditor
 * @brief Main Application Class
 *
 *
 * @author Paradoxon
 * @version 0.01
 * @date 2018/10/04
 *
 * @todo Register MimeType and MimeType for the Dokumentenst also register supported mimetypes
 */

#ifndef MESSAGE_EDITOR_H_
#define MESSAGE_EDITOR_H_

#include <Application.h>
#include "MessageEditorWindow.h"

#define	APP_SIGNATURE			"application/x-vnd.MessageEditor"

class MessageEditor : public BApplication {
    public:
									MessageEditor();
									~MessageEditor();

	virtual	void					ReadyToRun(void);
	virtual	bool					QuitRequested(void);
	virtual	void					MessageReceived(BMessage *message);
	virtual	void					RefsReceived(BMessage *message);
	virtual	void					AboutRequested(void);
	virtual	void					ArgvReceived(int32 argc, char **argv);
//	virtual	void					RegisterMime(void);
    private:
    	MessageEditorWindow			*mWindow;
    
};
#endif
