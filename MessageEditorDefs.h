#ifndef MESSAGE_EDITOR_DEFS_H
#define MESSAGE_EDITOR_DEFS_H
/*
 * @author Paradoxon powered by Jesus Christ
 * @version 0.01
 * @date 2005/10/04
 */

#include <app/AppDefs.h>
#include <support/TypeConstants.h>
#include <support/Debug.h>


//main type for Translation

#define	APP_SIGNATURE			"application/x-vnd.MessageEditor"

const uint32	B_CLEAR							= 'clea';


// Messages for menu commands
const uint32	MENU_APP_ABOUT					= B_ABOUT_REQUESTED;
/*const uint32	MENU_APP_SETTINGS				= 'MEse';
const uint32	MENU_APP_HELP					= 'MEhe';*/
const uint32	MENU_APP_QUIT					= B_QUIT_REQUESTED;

const uint32	FILE_OPEN						= 'Flop';

const uint32	MENU_FILE_OPEN					= 'MFop';
const uint32	MENU_FILE_CLOSE					= 'MFcl';
const uint32	MENU_FILE_SAVE					= 'MFsv';
const uint32	MENU_FILE_SAVEAS				= 'MFsa';
const uint32	MENU_FILE_PRINT					= 'MFpr';
const uint32	MENU_FILE_QUIT					= 'MFqu';

const uint32	MENU_SEARCH_FIND				= 'MSfi';
const uint32	MENU_SEARCH_FIND_NEXT			= 'MSfn';
const uint32	MENU_SEARCH_REPLACE				= 'MSre';
const uint32	MENU_SEARCH_REPLACE_AND_FIND	= 'MSrf';
const uint32	MENU_SEARCH_REPLACE_ALL			= 'MSra';

const uint32	MENU_HELP_ABOUT					= 'MHab';


extern const int32		M_E_VERSION;//						= "0.01";


#endif

