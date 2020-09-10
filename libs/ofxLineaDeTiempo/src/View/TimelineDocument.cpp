//
//  TimelineDocument.cpp
//  example-basic
//
//  Created by Roy Macdonald on 8/5/20.
//

#include "View/TimelineDocument.h"



namespace ofx {
namespace LineaDeTiempo {

TimelineDocument::TimelineDocument(const DOM::DocumentSettings& settings)
: DOM::Document(settings)
{

	_childReorderListener = childReordered.newListener(this, &TimelineDocument::_childOrderChanged);
	
}


TimelineDocument::~TimelineDocument()
{
}


void TimelineDocument::_childOrderChanged(DOM::ElementOrderEventArgs & args)
{
	
	
	if(!_bIgnoreChildReorder)
	{
		if(_modalView)
		{
			_bIgnoreChildReorder = true;
	
//			std::cout << "TimelineDocument::_childOrderChanged  " << args.element()->getId() << "\n";
//			std::cout << "    oldIndex: " << args.oldIndex() << "\n";
//			std::cout << "    newIndex: " << args.newIndex() << "\n";
//			std::cout << "    wasMovedForward: " << std::boolalpha << args.wasMovedForward() << "\n";
//			std::cout << "    wasMovedBackward: " << std::boolalpha << args.wasMovedBackward() << "\n";
//			std::cout << "    isAtFront: " << std::boolalpha << args.isAtFront() << "\n";
//			std::cout << "    isAtBack: " << std::boolalpha << args.isAtBack() << "\n";
//			
			
			_modalView->moveToFront();
		
			_bIgnoreChildReorder = false;
		}
	}
}

bool TimelineDocument::hasModal() const
{
	return _modalView != nullptr;
	
}

ModalView* TimelineDocument::getModal()
{
	if(_modalView == nullptr)
	{
		_modalView = addChild<ModalView>("Timeline ModalView", ofRectangle(0,0,getWidth(), getHeight()), this);
	}
	return _modalView;
}

void TimelineDocument::onUpdate()
{
	if(_modalView && _modalView->shouldBeDestroyed())
	{
		_modalView->removeAllChildren();
		removeChild(_modalView);
		_modalView = nullptr;
	}
}


} } // ofx::LineaDeTiempo

