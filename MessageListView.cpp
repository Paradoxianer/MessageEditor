#include <support/ClassInfo.h>
#include <string.h>

#include "MessageListView.h"
#include "StringItem.h"
#include "RectItem.h"
#include "FloatItem.h"
#include "BoolItem.h"
#include "MessageEditorDefs.h"

MessageListView::MessageListView(BMessage * forContainer):BOutlineListView(BRect(0,0,500,400),"MessageListView")
{
	container		= forContainer;
	baseEditMessage	= new BMessage(MESSAGE_VALUE_CHANGED);
}


void MessageListView::MouseDown(BPoint point)
{
	BOutlineListView::MouseDown(point);
}

void MessageListView::AttachedToWindow(void)
{
	ValueChanged();
}

void MessageListView::ValueChanged()
{
	MakeEmpty();
	AddMessage(container,NULL);
}

void MessageListView::SetContainer(BMessage *message){
	container = message;
	MakeEmpty();
	AddMessage(container,NULL);
}

void MessageListView::AddMessage(BMessage *message,BListItem* superItem)
{
	if (message==NULL)
		return;
	char		*name; 
	uint32		type; 
	int32		count;
	for (int32 i = 0; message->GetInfo(B_ANY_TYPE, i,(char **) &name, &type, &count) == B_OK; i++)
	{
		switch(type)
		{
			case B_MESSAGE_TYPE:
			{
				BMessage	*tmpMessage		= new BMessage();
				BMessage	*valueContainer	= new BMessage();
				if (message->FindMessage(name,count-1,tmpMessage)==B_OK)
				{
					BListItem	*newSuperItem=new BStringItem(name);
					LockLooper();
					if (superItem)
						AddUnder(newSuperItem,superItem);
					else
					{
						AddItem(newSuperItem);
						delete editMessage;
						editMessage		= new BMessage(*baseEditMessage);
					}
					//need to create a good Message to change the BMessage
					/*editMessage->FindString("_subgroup",valueContainer);
					editMessage->ReplaceMessage("valueContainer",valueContainer);*/
					AddMessage(tmpMessage,newSuperItem);
					UnlockLooper();
				}
				break;
			}
			case B_STRING_TYPE:
			{
				char		*string;
				message->FindString(name,count-1,(const char **)&string);
				StringItem *stringItem = new StringItem(name,string);
				if (superItem)
				{
					AddUnder(stringItem,superItem);
				}
				else
				{
					AddItem(stringItem);
					delete editMessage;
					editMessage		= new BMessage(*baseEditMessage);
				}
				BMessage *tmpMessage = new BMessage(*editMessage);
				stringItem->SetMessage(tmpMessage);
//				stringItem->SetTarget(doc);
				break;
			}
			case B_RECT_TYPE:
			{
				BRect	rect;
				message->FindRect(name,count-1,&rect);
				RectItem	*rectItem	= new RectItem(name,rect);
				if (superItem)
					AddUnder(rectItem,superItem);
				else
				{
					AddItem(rectItem);
					delete editMessage;
				//	editMessage		= new BMessage(*baseEditMessage);
				}
				BMessage *tmpMessage = new BMessage(*editMessage);
				rectItem->SetMessage(tmpMessage);
	//			rectItem->SetTarget(doc);
				break;
			}
			case B_FLOAT_TYPE:
			{
				float	value;
				message->FindFloat(name,count-1,&value);
				FloatItem *floatItem	= new FloatItem(name,value);
				if (superItem)
					AddUnder(floatItem,superItem);
				else
				{
					AddItem(floatItem);
					delete editMessage;
					editMessage		= new BMessage(*baseEditMessage);
				}
				BMessage *tmpMessage = new BMessage(*editMessage);
				floatItem->SetMessage(tmpMessage);
			//	floatItem->SetTarget(doc);
				break;
			}
			case B_BOOL_TYPE:
			{
				bool	value;
				message->FindBool(name,count-1,&value);
				BoolItem	*boolItem	= new BoolItem(name,value);
				if (superItem)
					AddUnder(boolItem,superItem);
				else
				{
					AddItem(boolItem);
					delete editMessage;
					editMessage		= new BMessage(*baseEditMessage);
				}
				BMessage *tmpMessage = new BMessage(*editMessage);
				boolItem->SetMessage(tmpMessage);
				//boolItem->SetTarget(doc);
				break;
			}
			case B_POINTER_TYPE:
			{
				void *pointer;
				message->FindPointer(name,count,(void **)&pointer);
				
				break;
			}
		}

	} 
}

void MessageListView::MessageReceived(BMessage *message)
{
	BaseListItem	*item;
	switch(message->what) 
	{
		case ITEM_CHANDED:
		{
			if ( (message->FindPointer("item",(void **)&item)==B_OK) && (item != NULL) )
				item->Invoke();
			break;
		}
		default:
			BOutlineListView::MessageReceived(message);
			break;
	}
}
