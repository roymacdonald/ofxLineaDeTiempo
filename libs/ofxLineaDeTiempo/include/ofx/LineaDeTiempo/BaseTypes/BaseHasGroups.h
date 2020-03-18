////
////  BaseHasGroups.h
////  GroupsAndTimeTest
////
////  Created by Roy Macdonald on 3/11/20.
////
//
//#pragma once
//
//#include "LineaDeTiempo/BaseTypes/NamedConstPointerCollection.h"
//
//
//namespace ofx {
//namespace LineaDeTiempo {
//
//template<typename GroupType>
//class BaseHasGroups
//{
//public:
//
//	virtual ~BaseHasGroups() = default;
//	
//	virtual bool removeGroup(GroupType* group) = 0 ;
//	
//	 bool removeGroup(const std::string& name)
//	 {
//	 	return _groupsCollection.remove(name);
//	 }
//
//	 bool removeGroup(const size_t& index)
//	 {
//	 	 return _groupsCollection.remove(index);
//	 }
//
//	 GroupType* getGroup(const std::string& name)
//	 {
//	 	 return _groupsCollection.at(name);
//	 }
//
//	 const GroupType* getGroup(const std::string& name) const
//	 {
//	 	 return _groupsCollection.at(name);
//	 }
//
//	 GroupType* getGroup(const size_t& index)
//	 {
//	 	 return _groupsCollection.at(index);
//	 }
//
//	 const GroupType* getGroup(const size_t& index)const
//	 {
//		 return _groupsCollection.at(index);
//	 }
//
//	 const std::vector<GroupType*>& getGroups()
//	 {
//	 	return _groupsCollection.getCollection();
//	 }
//
//	 const std::vector<const GroupType*>& getGroups() const
//	 {
//		 return _groupsCollection.getCollection();
//	 }
//
//	 size_t getNumGroups() const
//	 {
//		 return _groupsCollection.size();
//	 }
//
//
//	
//	typedef GroupType groupType;
//	
//		
//	protected:
//		
//		NamedConstPointerCollection<GroupType> _groupsCollection;
//
//
//
//
//};
//
//}} //ofx::LineaDeTiempo
