#include <symboltable.hpp>

SymbolTableEntry::SymbolTableEntry(const std::string& i) :
		id(i), astEntry(nullptr)
{
}

SymbolTableEntry::SymbolTableEntry(const std::string& i, const Loc& l) :
		id(i), loc(l), astEntry(nullptr)
{
}

SymbolTableEntry::SymbolTableEntry(const std::string& i, const Loc& l,
		AstNode* n) : id(i), loc(l), astEntry(n)
{
}

SymbolTableEntry::SymbolTableEntry(const std::string& i, AstNode* n) : 
		id(i), astEntry(n)
{
}

bool SymbolTableEntry::operator<(const SymbolTableEntry o) const {
	return this->id < o.id;
}

bool SymbolTableEntry::operator==(const SymbolTableEntry o) const {
	return this->id == o.id;
}

SymbolTable::SymbolTable() : parent(nullptr), type(SymbolTableType::Ordered) {
}

SymbolTable::SymbolTable(SymbolTable* p, SymbolTableType t) : parent(p),
		type(t) 
{
}

void SymbolTable::insert(const std::string& id , const Loc& l) {
	this->map.emplace(id,l);
}

void SymbolTable::insertNewTable(SymbolTablePtr st) {
	this->follow.emplace_back(st);
}

SymbolTable* SymbolTable::getParent() {
	return this->parent;
}

const SymbolTable* SymbolTable::getParent() const {
	return this->parent;
}

SymbolTableEntryMap& SymbolTable::getMap() {
	return this->map;
}

const SymbolTableEntryMap& SymbolTable::getMap() const {
	return this->map;
}

const SymbolTableVec SymbolTable::getFollow() const {     	
	return this->follow;
}

SymbolTableVec SymbolTable::getFollow() {
	return this->follow;
}

bool SymbolTable::contains(const std::string& key) const {
	bool ret = static_cast<bool>(this->map.count(SymbolTableEntry(key)));
	if(ret) {
		return true;
	} else if(!ret && this->parent) {
		return this->parent->contains(key);
	} else {
		return false;
	}
}
