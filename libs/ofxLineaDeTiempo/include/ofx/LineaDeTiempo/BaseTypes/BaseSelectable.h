//
//  Header.h
//  tracksAndTimeTest
//
//  Created by Roy Macdonald on 3/23/20.
//

#pragma once

namespace ofx {
namespace LineaDeTiempo {

class BaseSelectable
{
public:
	
	
	virtual ~BaseSelectable() = default;
	
	virtual void setSelected(bool selected) = 0;
	
	
	virtual bool isSelected() const = 0;
	
	virtual void setSelectedNoEvents(bool selected) = 0;
	
};

} } // ofx::LineaDeTiempo
