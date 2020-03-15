//
//  BaseHasHeader.h
//  timedDataTest
//
//  Created by Roy Macdonald on 3/10/20.
//

#pragma once

namespace ofx {
namespace LineaDeTiempo {



template<typename HeaderType>
class BaseHasHeader
{
public:
	BaseHasHeader()
	{
		
	}
	BaseHasHeader(HeaderType* header)
	{
		_header = header;
	}

	virtual ~BaseHasHeader() = default;
	
	void setHeader(HeaderType* header)
	{
		_header = header;
	}
	
	HeaderType* getHeader()
	{
		return _header;
	}

	const HeaderType* getHeader() const
	{
		return _header;
	}
	
	typedef HeaderType headerType;
	
protected:
	HeaderType* _header = nullptr;
	
};


}}  //ofx::LineaDeTiempo
