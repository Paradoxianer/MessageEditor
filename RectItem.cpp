#include "RectItem.h"
#include <stdio.h>
#include <stdlib.h>
#include <interface/InterfaceDefs.h>
#include <Catalog.h>

#undef B_TRANSLATION_CONTEXT
#define B_TRANSLATION_CONTEXT "RectItem"
/*
 * @author Paradoxon
 */


RectItem::RectItem(char *newLabel,
		BRect newRect,
		uint32 level,
		bool expanded)
	: BaseListItem(B_RECT_TYPE, level, expanded)
{
	sleft			= new char[24];
	stop			= new char[24];
	sright			= new char[24];
	sbottom			= new char[24];
	sprintf(sleft,"%.2f",newRect.left);
	sprintf(stop,"%.2f",newRect.top);
	sprintf(sright,"%.2f",newRect.right);
	sprintf(sbottom,"%.2f",newRect.bottom);

	BMessage		*inputChanged = new BMessage(ITEM_CHANDED);
	inputChanged->AddPointer("item",this);

	left			= new BTextControl(BRect(0,0,100,10),"left","left",sleft,inputChanged);
	top				= new BTextControl(BRect(0,0,100,10),"top","top",stop,inputChanged);
	right			= new BTextControl(BRect(0,0,100,10),"right","right",sright,inputChanged);
	bottom			= new BTextControl(BRect(0,0,100,10),"bottom","bottom",sbottom,inputChanged);
	left->SetDivider(40);
	top->SetDivider(40);
	right->SetDivider(40);
	bottom->SetDivider(40);
	label			= newLabel;
	rect			= newRect;
	background		= ui_color(B_CONTROL_BACKGROUND_COLOR);
	backgroundHi	= ui_color(B_CONTROL_HIGHLIGHT_COLOR);
	foreground		= ui_color(B_CONTROL_TEXT_COLOR);
}



void RectItem::Update(BView *newOwner, const BFont *font)
{
	BListItem::Update(newOwner,font);
	owner = newOwner;
	float	widht;
	left->GetPreferredSize(&widht,&textControlHeight);
	SetHeight(textControlHeight*4+3);
	font_height	fontHeight;
	font->GetHeight(&fontHeight);
	textLine=((textControlHeight+3)-fontHeight.ascent)/2;
	
	
}

void RectItem::DrawItem(BView *owner, BRect bounds, bool complete)
{
	BRect	newBounds=bounds;
	newBounds.InsetBy(1,1);
	owner->SetDrawingMode(B_OP_OVER);
	owner->MovePenTo(newBounds.left+4, newBounds.bottom-2);
	rgb_color color;
	if (IsSelected())
		color = backgroundHi;
	else
		color = background;
	owner->SetHighColor(color);
	left->SetViewColor(color);
	top->SetViewColor(color);
	right->SetViewColor(color);
	bottom->SetViewColor(color);
	owner->FillRoundRect(bounds,3,3);
	if (IsEnabled())
		owner->SetHighColor(foreground);	
	else
		owner->SetHighColor(tint_color(foreground,B_DISABLED_LABEL_TINT));
	owner->MovePenTo(newBounds.left+4, newBounds.bottom-(textControlHeight*3)-textLine); 
	owner->DrawString(label);
	if (IsSelected())
	{
		if (left->Parent() == NULL)
		{
			owner->AddChild(left);
			owner->AddChild(top);
			owner->AddChild(right);
			owner->AddChild(bottom);
			left->ResizeTo(newBounds.Width()-SEPERATOR-3,textControlHeight);
			top->ResizeTo(newBounds.Width()-SEPERATOR-3,textControlHeight);
			right->ResizeTo(newBounds.Width()-SEPERATOR-3,textControlHeight);
			bottom->ResizeTo(newBounds.Width()-SEPERATOR-3,textControlHeight);
			left->SetTarget(owner);
			top->SetTarget(owner);
			right->SetTarget(owner);
			bottom->SetTarget(owner);
		}
	    left->MoveTo(newBounds.right-SEPERATOR+1,newBounds.top+2);
	    top->MoveTo(newBounds.right-SEPERATOR+1,left->Frame().bottom);
	    right->MoveTo(newBounds.right-SEPERATOR+1,top->Frame().bottom);
   	    bottom->MoveTo(newBounds.right-SEPERATOR+1,right->Frame().bottom);
	}
	else
	{
		if (left->Parent() != NULL)
		{
			sleft	= (char *)left->Text();
			stop	= (char *)top->Text();
			sright	= (char *)left->Text();
			sbottom	= (char *)top->Text();
			owner->RemoveChild(left);
			owner->RemoveChild(top);
			owner->RemoveChild(right);
			owner->RemoveChild(bottom);
		}
		owner->MovePenTo(newBounds.right-SEPERATOR+3, newBounds.bottom-(textControlHeight*3)-textLine);
		owner->DrawString(B_TRANSLATE("left")); 
		owner->MovePenTo(newBounds.right-SEPERATOR+52, newBounds.bottom-(textControlHeight*3)-textLine);
		owner->DrawString(left->Text());
		owner->MovePenTo(newBounds.right-SEPERATOR+3, newBounds.bottom-(textControlHeight*2)-textLine);
		owner->DrawString(B_TRANSLATE("top")); 
		owner->MovePenTo(newBounds.right-SEPERATOR+52, newBounds.bottom-(textControlHeight*2)-textLine);
		owner->DrawString(top->Text());
		owner->MovePenTo(newBounds.right-SEPERATOR+3, newBounds.bottom-(textControlHeight)-textLine);
		owner->DrawString(B_TRANSLATE("right")); 
		owner->MovePenTo(newBounds.right-SEPERATOR+52, newBounds.bottom-(textControlHeight)-textLine);
		owner->DrawString(right->Text());
		owner->MovePenTo(newBounds.right-SEPERATOR+3, newBounds.bottom-textLine);
		owner->DrawString(B_TRANSLATE("bottom")); 
		owner->MovePenTo(newBounds.right-SEPERATOR+52, newBounds.bottom-textLine);
		owner->DrawString(bottom->Text());

	}
	owner->SetHighColor(205,205,205,255);
//	owner->StrokeRoundRect(newBounds,3,3);
	owner->StrokeLine(BPoint(newBounds.right-SEPERATOR,newBounds.top),BPoint(newBounds.right-SEPERATOR,newBounds.bottom));
	owner->SetHighColor(foreground);	
}

void RectItem::Select(void)
{
}
void RectItem::Deselect(void)
{
}

void RectItem::SetExpanded(bool expande)
{
}

BRect RectItem::GetRect(void)
{
	float rleft		= atof(left->Text());
	float rtop		= atof(top->Text());
	float rright	= atof(right->Text());
	float rbottom	= atof(bottom->Text());
	return BRect(rleft,rtop,rright,rbottom);
}

status_t RectItem::Invoke(BMessage *message)
{
	BMessage	*sendMessage	= NULL;
	BMessage	*valueContainer	= new BMessage();
	if (message==NULL)
		sendMessage = new BMessage(*Message());
	else
		sendMessage = new BMessage(*message);
	if (sendMessage != NULL)	
	{
		sendMessage->FindMessage("valueContainer",valueContainer);
		valueContainer->AddInt32("type",B_RECT_TYPE);
		valueContainer->AddString("name",label);
		valueContainer->AddRect("newValue", GetRect()); 
		sendMessage->ReplaceMessage("valueContainer",valueContainer);
		BInvoker::Invoke(sendMessage);
	}
	else
		return B_ERROR;
}
