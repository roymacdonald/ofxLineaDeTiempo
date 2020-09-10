//
//  TimelineDocument.hpp
//  example-basic
//
//  Created by Roy Macdonald on 8/5/20.
//

#pragma once
#include "ofx/DOM/Document.h"
#include "MUI/Styles.h"
#include "LineaDeTiempo/View/ModalView.h"

namespace ofx {
namespace LineaDeTiempo {


class TimelineDocument: public DOM::Document
{
public:

		
	
	TimelineDocument(const DOM::DocumentSettings& settings);
	virtual ~TimelineDocument();
	
	
	ModalView* getModal();
	
	bool hasModal() const;
	
	virtual void onUpdate() override;
protected:
	
	ModalView* _modalView = nullptr;
	
	bool _bIgnoreChildReorder = false;

	ofEventListener _childReorderListener;
	
	void _childOrderChanged(DOM::ElementOrderEventArgs &);

};


} } // ofx::LineaDeTiempo

