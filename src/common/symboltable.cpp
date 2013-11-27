#include <symboltable.hpp>

SymbolTableEntry::SymbolTableEntry(const std::string& i, const Loc& l) :
	id(i), loc(l) 
{
}

bool SymbolTableEntry::operator<(const SymbolTableEntry o) const {
	return this->id < o.id;
}

bool SymbolTableEntry::operator==(const SymbolTableEntry o) const {
	return this->id == o.id;
}

SymbolTable::SymbolTable() : parent(nullptr) {
}

SymbolTable::SymbolTable(SymbolTablePtr p) : parent(p) {
}

void SymbolTable::insert(const std::string& id , const Loc& l) {
	this->map.emplace(id,l);
}

SymbolTablePtr SymbolTable::getParent() {
	return this->parent;
}

SymbolTableConstPtr SymbolTable::getParent() const {
	return this->parent;
}

/*void SymbolTable::insertNewTable(SymbolTable* t) {
	this->follow.push_back(t);
}

const SymbolTableVec SymbolTable::getFollow() const {
	return this->follow;
}

SymbolTableVec SymbolTable::getFollow() {
	return this->follow;
}*/
