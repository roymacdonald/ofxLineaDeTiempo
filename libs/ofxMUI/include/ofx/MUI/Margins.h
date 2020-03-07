//
//  Margins.h
//  tracksTest
//
//  Created by Roy Macdonald on 2/20/20.
//

#pragma once
namespace ofx {
namespace MUI {

class Margins{
public:
	float top = 0;
	float bottom = 0;
	float left = 0;
	float right = 0;
	
	void reset()
	{
		top = 0;
		bottom = 0;
		left = 0;
		right = 0;		
	}
};

} } // ofx::MUI
