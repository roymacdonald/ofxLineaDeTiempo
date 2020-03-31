//
//  BaseController.hpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/30/20.
//

#pragma once


#include "DOM/Node.h"
#include "DOM/Element.h"

#include "LineaDeTiempo/Controller/TimeControl.h"


namespace ofx {
namespace LineaDeTiempo {


class BaseHasViews{
public:
	virtual void generateView() = 0;
	virtual void destroyView() = 0;
};

template<typename ViewType>
class BaseController
: public DOM::Node
, public BaseHasViews
{
public:
	static_assert(std::is_base_of<DOM::Element, ViewType>::value,
				  "BaseController: Templated ViewType must be equal or derived from DOM::Element");
	
	
	BaseController(const std::string& id, DOM::Node* parent, TimeControl * timeControl);
	
	virtual ~BaseController() = default;
	
	
	TimeControl * getTimeControl();
	
	const TimeControl * getTimeControl() const;
	
	
	
	
	const ViewType * getView() const;

	ViewType * getView();

	void setView(ViewType * view);
	
	bool hasView() const;
	
	void destroyChildrenViews(DOM::Node * parent);
	
	void generateChildrenViews(DOM::Node * parent);
	
	
	typedef ViewType viewType;
	
	const std::string&  getDataTypeName() const;
	
	
protected:
	
	void _setTimeControl(TimeControl * timeControl);
	
	std::string _dataTypeName = "";
	
private:
	TimeControl * _timeControl = nullptr;
	
	ViewType* _view = nullptr;
		
	
};

}} //ofx::LineaDeTiempo
