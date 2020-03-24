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
	BaseSelectable()
	{
		
	}
	
	virtual ~BaseSelectable() = default;
	
	virtual void setSelected(bool selected) = 0;
	
	bool isSelected() const
	{
		return _isSelected;
	}
	
	
	bool _isSelected = false;
};

} } // ofx::LineaDeTiempo
