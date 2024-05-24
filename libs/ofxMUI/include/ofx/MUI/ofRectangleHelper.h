//
//  ofRectangleHelper.h
//  inouttest
//
//  Created by Roy Macdonald on 17-02-18.
//
//

#pragma once
#include "ofRectangle.h"
#include "ofLog.h"
#include "ofx/DOM/Element.h"
#include "ofMath.h"

namespace ofx{
namespace DOM{

#define PRINT_SWITCH_STRING(s) case s: return #s;

enum RectEdge{
	RECT_TOP = 0,
	RECT_RIGHT,
	RECT_BOTTOM,
	RECT_LEFT
};

enum SetEdgeResult
{
	SET_EDGE_NO_CHANGES = 0,
	SET_EDGE_MIN,
	SET_EDGE_CHANGED
};


class ofRectangleHelper{
public:
	//---------------------------------------------------------------------------------------------------------------------
	static inline DOM::Orientation getOrientationFromEdge(RectEdge edge)
	{
		if(edge == RECT_TOP || edge == RECT_BOTTOM)
		{
			return DOM::VERTICAL;
		}
		
		return DOM::HORIZONTAL;
		
	}
	
	
	
	
	static inline SetEdgeResult setEdge(Element* e, const float& val, RectEdge edge, bool clampAtMinSize = false, float minSize = 0){
		SetEdgeResult bRet = SET_EDGE_NO_CHANGES;
		if(e){
			auto r = e->getShape();
			
			if(edge == RECT_TOP)
			{
				bRet = setTop(r, val, clampAtMinSize, minSize);
			}
			else if(edge == RECT_RIGHT)
			{
				bRet = setRight(r, val, clampAtMinSize, minSize);
			}
			else if(edge == RECT_BOTTOM)
			{
				bRet = setBottom(r, val, clampAtMinSize, minSize);
			}
			else if(edge == RECT_LEFT)
			{
				bRet = setLeft(r, val, clampAtMinSize, minSize);
			}
			
			if(bRet != SET_EDGE_NO_CHANGES){
				e->setShape(r);
			}
		}
		return bRet;
	}
	
//	//---------------------------------------------------------------------------------------------------------------------
//	static inline bool setEdge(ofRectangle& r, const float& val, ofAlignVert edge){
//		switch(edge){
//			case OF_ALIGN_VERT_TOP :
//				return setTop(r,val);
//			case OF_ALIGN_VERT_BOTTOM :
//				return setBottom(r,val);
//			case OF_ALIGN_VERT_CENTER :
//			case OF_ALIGN_VERT_IGNORE :
//				return false;
//		}
//	}
//	//---------------------------------------------------------------------------------------------------------------------
//	static inline bool setEdge(ofRectangle& r, const float& val, ofAlignHorz edge){
//		switch(edge){
//			case OF_ALIGN_HORZ_LEFT :
//				return setLeft(r,val);
//			case OF_ALIGN_HORZ_RIGHT :
//				return setRight(r,val);
//			case OF_ALIGN_HORZ_CENTER :
//			case OF_ALIGN_HORZ_IGNORE :
//				return false;
//		}
//	}
	//---------------------------------------------------------------------------------------------------------------------
	//    static inline bool setEdge(ofRectangle& r, const float& val, const ofxTLHandleID& edge , bool bClampAtZero = false){
	//        if(edge == RECT_TOP){
	//            return setTop(r,val, bClampAtZero );
	//        }
	//        else if(edge == RECT_RIGHT){
	//            return setRight(r,val, bClampAtZero);
	//        }
	//        else if(edge == RECT_BOTTOM){
	//            return setBottom(r,val, bClampAtZero);
	//        }
	//        else if(edge == RECT_LEFT){
	//            return setLeft(r,val, bClampAtZero);
	//        }
	//        return false;
	//    }
	//---------------------------------------------------------------------------------------------------------------------
	static inline SetEdgeResult setTop(ofRectangle& r, const float& val, bool bClampAtMinHeight = false, float minHeight = 0){
		if(ofIsFloatEqual(r.getMinY(), val)) return SET_EDGE_NO_CHANGES;
		float mxY = r.getMaxY();
		
		r.y = val;
		r.height = mxY - val;
		
		if(bClampAtMinHeight && r.height < minHeight){
			r.y = mxY - minHeight;
			r.height = minHeight;
			return SET_EDGE_MIN;
		}
		return SET_EDGE_CHANGED;
	}
	//---------------------------------------------------------------------------------------------------------------------
	static inline SetEdgeResult setRight(ofRectangle& r, const float& val, bool bClampAtMinWidth = false, float minWidth = 0){
		if(ofIsFloatEqual(r.getMaxX(), val)) return SET_EDGE_NO_CHANGES;
		float mnX = r.getMinX();
		r.width = val - mnX;
		if(bClampAtMinWidth && r.width < minWidth){
			r.width = minWidth;
			return SET_EDGE_MIN;
		}
		return SET_EDGE_CHANGED;
	}
	//---------------------------------------------------------------------------------------------------------------------
	static inline SetEdgeResult setBottom(ofRectangle& r, const float& val, bool bClampAtMinHeight = false, float minHeight = 0){
		if(ofIsFloatEqual(r.getMaxY(), val)) return SET_EDGE_NO_CHANGES;
		float mnY = r.getMinY();

		r.height = val - mnY;
		
		if(bClampAtMinHeight && r.height < minHeight){
			r.height = minHeight;
			return SET_EDGE_MIN;
		}
		return SET_EDGE_CHANGED;
	}
	//---------------------------------------------------------------------------------------------------------------------
	static inline SetEdgeResult setLeft(ofRectangle& r, const float& val, bool bClampAtMinWidth = false, float minWidth = 0){
		if(ofIsFloatEqual(r.getMinX(), val)) return SET_EDGE_NO_CHANGES;
		float mxX = r.getMaxX();

		r.x = val;
		r.width = mxX - val;

		if(bClampAtMinWidth && r.width < minWidth){
			r.x = mxX - minWidth;
			r.width = minWidth;
			return SET_EDGE_MIN;
		}
		return SET_EDGE_CHANGED;
	}
	//---------------------------------------------------------------------------------------------------------------------
	//	static inline bool setDimension(Element* r, const float& val, int index, bool bSetMax, bool bClampAtZero = false){
	////		if(r == nullptr)return false;
	//		index
	//		return setEdge(r, val, bClampAtZero);
	//
	//	}
	//---------------------------------------------------------------------------------------------------------------------
	//    static inline bool setEdge(Element* r, const float& val, const RectEdge& edge, bool bClampAtZero = false, bool bGlobalPosition = false){
	//        if(r){
	//            auto temp= r->getShape();
	//            if(setEdge(temp, val, edge, bClampAtZero)){
	//                r->setShape(temp);
	//                return true;
	//            }
	//        }
	//        return false;
	//    }
	//    static inline bool setTop(std::shared_ptr<ofxTLNode> r, const float& val, bool bClampAtZero = false, bool bGlobalPosition = false){
	//        return setEdge (r, val, RECT_TOP, bClampAtZero, bGlobalPosition);
	//    }
	//    static inline bool setRight(std::shared_ptr<ofxTLNode> r, const float& val,bool bClampAtZero = false, bool bGlobalPosition = false){
	//        return setEdge (r, val, RECT_RIGHT, bClampAtZero, bGlobalPosition);
	//    }
	//    static inline bool setBottom(std::shared_ptr<ofxTLNode> r, const float& val,bool bClampAtZero = false, bool bGlobalPosition = false){
	//        return setEdge (r, val, RECT_BOTTOM, bClampAtZero, bGlobalPosition);
	//    }
	//    static inline bool setLeft(std::shared_ptr<ofxTLNode> r, const float& val, bool bClampAtZero = false, bool bGlobalPosition = false){
	//        return setEdge (r, val, RECT_LEFT, bClampAtZero, bGlobalPosition);
	//    }
	
	//---------------------------------------------------------------------------------------------------------------------
	static inline void addToEdge(ofRectangle& r, const float& val, RectEdge edge){
		if(edge == RECT_TOP){
			addToTop(r,val);
		}
		else if(edge == RECT_RIGHT){
			addToRight(r,val);
		}
		else if(edge == RECT_BOTTOM){
			addToBottom(r,val);
		}
		else if(edge == RECT_LEFT){
			addToLeft(r,val);
		}
	}
	//---------------------------------------------------------------------------------------------------------------------
	static inline void addToTop(ofRectangle& r, const float& val){
		float mxY = r.getMaxY();
		r.y += val;
		r.height = mxY - r.y;
	}
	//---------------------------------------------------------------------------------------------------------------------
	static inline void addToRight(ofRectangle& r, const float& val){
		r.width += val;
	}
	//---------------------------------------------------------------------------------------------------------------------
	static inline void addToBottom(ofRectangle& r, const float& val){
		r.height += val;
	}
	//---------------------------------------------------------------------------------------------------------------------
	static inline void addToLeft(ofRectangle& r, const float& val){
		float mxX = r.getMaxX();
		r.x += val;
		r.width = mxX - r.x;
	}
	//---------------------------------------------------------------------------------------------------------------------
	static inline ofAlignVert opposite(const ofAlignVert& a){
		switch(a) {
			case OF_ALIGN_VERT_IGNORE : return OF_ALIGN_VERT_IGNORE;
			case OF_ALIGN_VERT_TOP : return OF_ALIGN_VERT_BOTTOM;
			case OF_ALIGN_VERT_BOTTOM : return OF_ALIGN_VERT_TOP;
			case OF_ALIGN_VERT_CENTER : return OF_ALIGN_VERT_CENTER;
		}
	}
	//---------------------------------------------------------------------------------------------------------------------
	static inline ofAlignHorz opposite(const ofAlignHorz& a){
		switch(a) {
			case OF_ALIGN_HORZ_IGNORE : return OF_ALIGN_HORZ_IGNORE;
			case OF_ALIGN_HORZ_LEFT : return OF_ALIGN_HORZ_RIGHT;
			case OF_ALIGN_HORZ_RIGHT : return OF_ALIGN_HORZ_LEFT;
			case OF_ALIGN_HORZ_CENTER : return OF_ALIGN_HORZ_CENTER;
		}
	}
	//---------------------------------------------------------------------------------------------------------------------
	static inline bool keepInside(glm::vec2& p, const ofRectangle& target){
		
		bool bRet = false;
		auto mn = target.getMin();
		auto mx = target.getMax();
		for(int i = 0; i < 2; i++){
			if(p[i] < mn[i]){
				p[i] = mn[i];
				bRet |= true;
			}else if(p[i] > mx[i] ){
				p[i] = mx[i];
				bRet |= true;
			}
		}
		return bRet;
	}
	//---------------------------------------------------------------------------------------------------------------------
	static inline bool keepInsideX(ofRectangle& subject, const ofRectangle& target){
		if(subject.width > target.width){
			ofLogNotice("ofRectangleHelper::keepInsideX") << "failed. subject is wider than target!" << subject << "  -  " << target;
			return false;
		}
		subject.standardize();
		if(subject.x < target.getMinX()){
			subject.x = target.getMinX();
			return true;
		}
		else if(subject.getMaxX() > target.getMaxX()){
			subject.x = target.getMaxX() - subject.width;
			return true;
		}
		
		return false;
		
	}
	//---------------------------------------------------------------------------------------------------------------------
	//    static inline bool keepInsideX(std::shared_ptr<ofxTLNode> subject, const ofRectangle& target){
	//        if(subject){
	//            ofRectangle r = subject->getRect();
	//            bool b = keepInsideX(r, target);
	//            if(b){
	//                subject->setRect(r);
	//            }
	//            return b;
	//        }
	//        return false;
	//    }
	
	//---------------------------------------------------------------------------------------------------------------------
	static inline bool keepInsideY(ofRectangle& subject, const ofRectangle& target){
		if(subject.height > target.height){
			ofLogNotice("ofRectangleHelper::keepInsideY") << "failed. subject is taller than target! " << subject << "  -  " << target;
			return false;
		}
		
		subject.standardize();
		if(subject.y < target.getMinY()){
			subject.y = target.getMinY();
			return true;
		}
		else if(subject.getMaxY() > target.getMaxY()){
			subject.y = target.getMaxY() - subject.height;
			return true;
		}
		
		return false;
		
	}
	//    static inline bool keepInsideY(std::shared_ptr<ofxTLNode> subject, const ofRectangle& target){
	//        if(subject){
	//            ofRectangle r = subject->getRect();
	//            bool b = keepInsideY(r, target);
	//            if(b){
	//                subject->setRect(r);
	//            }
	//            return b;
	//        }
	//        return false;
	//    }
	
	
	//---------------------------------------------------------------------------------------------------------------------
	static inline bool keepInside(ofRectangle& subject, const ofRectangle& target){
		if(subject.width > target.width || subject.height > target.height){
			ofLogNotice("ofRectangleHelper::keepInside") << "failed. subject is larger than target!" << subject << "  -  " << target;
			return false;
		}
		bool bRet = keepInsideX(subject, target);
		bRet |= keepInsideY(subject, target);
		return bRet;
	}
	
	//---------------------------------------------------------------------------------------------------------------------
	static inline bool keepInside(Element* subject, const ofRectangle& target){
		auto r = subject->getShape();
		if(keepInside(r, target)){
			subject->setPosition(r.getPosition());
			return true;
		}
		
		return false;
	}
	//    static inline bool keepInside(std::shared_ptr<ofxTLNode> subject, const ofRectangle& target){
	//        if(subject){
	//            ofRectangle r = subject->getRect();
	//            bool b = keepInside(r, target);
	//            if(b){
	//                subject->setRect(r);
	//            }
	//            return b;
	//        }
	//        return false;
	//    }
	//---------------------------------------------------------------------------------------------------------------------
	static inline std::string toString (const ofAlignVert& a) {
		switch(a){
				PRINT_SWITCH_STRING(OF_ALIGN_VERT_IGNORE)
				PRINT_SWITCH_STRING(OF_ALIGN_VERT_TOP)
				PRINT_SWITCH_STRING(OF_ALIGN_VERT_BOTTOM)
				PRINT_SWITCH_STRING(OF_ALIGN_VERT_CENTER)
		}
	}
	//---------------------------------------------------------------------------------------------------------------------
	static inline std::string toString (const ofAlignHorz& a) {
		switch(a){
				PRINT_SWITCH_STRING(OF_ALIGN_HORZ_IGNORE)
				PRINT_SWITCH_STRING(OF_ALIGN_HORZ_LEFT)
				PRINT_SWITCH_STRING(OF_ALIGN_HORZ_RIGHT)
				PRINT_SWITCH_STRING(OF_ALIGN_HORZ_CENTER)
		}
	}
	
	static inline std::string toString (const RectEdge& e) {
		switch(e){
				PRINT_SWITCH_STRING(RECT_TOP)
				PRINT_SWITCH_STRING(RECT_RIGHT)
				PRINT_SWITCH_STRING(RECT_BOTTOM)
				PRINT_SWITCH_STRING(RECT_LEFT)
		}
	}
	
};

} } // namespace ofx/DOM
