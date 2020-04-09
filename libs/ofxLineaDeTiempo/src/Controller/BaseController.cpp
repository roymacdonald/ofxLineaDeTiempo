//
//  BaseController.cpp
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/30/20.
//

#include "LineaDeTiempo/Controller/BaseController.h"
#include "LineaDeTiempo/Controller/TrackController.h"
#include "LineaDeTiempo/Controller/TrackGroupController.h"//
#include "LineaDeTiempo/Controller/TracksPanelController.h"
#include "LineaDeTiempo/Controller/RegionController.h"
#include "LineaDeTiempo/Controller/KeyframeController.h"

namespace ofx {
namespace LineaDeTiempo {

template<typename T>
BaseController<T>::BaseController(const std::string& id, Node* parent, TimeControl * timeControl)
: DOM::Node(id, parent)
, _timeControl(timeControl)
{
	
}


template<typename T>
const T * BaseController<T>::getView() const
{
	return _view;
}
template<typename T>
T * BaseController<T>::getView()
{
	return _view;
}
template<typename T>
void BaseController<T>::setView(T * view)
{
	_view = view;
}
template<typename T>
bool BaseController<T>::hasView() const
{
	return (_view != nullptr);
}
template<typename T>
void BaseController<T>::destroyChildrenViews(DOM::Node * parent)
{
	if(!parent) return;
	for(auto child : parent->children())
	{
		auto c = dynamic_cast<BaseHasViews*>(child);
		if(c) c->destroyView();
	}
}
template<typename T>
void BaseController<T>::generateChildrenViews(DOM::Node * parent)
{
	if(!parent) return;
	for(auto child : parent->children())
	{
		auto c = dynamic_cast<BaseHasViews*>(child);
		if(c) c->generateView();
	}
}


template<typename T>
void BaseController<T>::_setTimeControl(TimeControl * timeControl)
{
	_timeControl = timeControl;
}

template<typename T>
TimeControl * BaseController<T>::getTimeControl()
{
	return _timeControl;
}
template<typename T>
const TimeControl * BaseController<T>::getTimeControl() const
{
	return _timeControl;
}

template<typename T>
const std::string&  BaseController<T>::getDataTypeName() const
{
	return _dataTypeName;
}



template class BaseController<KeyframeView>;
template class BaseController<RegionView>;
template class BaseController<TrackView>;
template class BaseController<TrackGroupView>;
template class BaseController<KeyframeCollectionView>;

} } // ofx::LineaDeTiempo
