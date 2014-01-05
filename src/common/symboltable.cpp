#include <symboltable.hpp>
#include <format.hpp>

std::ostream& operator<<(std::ostream& os, const SymbolTableEntryType e) {
	switch(e) {
		case SymbolTableEntryType::Variable: os<<"Variable"; break;
		case SymbolTableEntryType::Constant: os<<"Constant"; break;
		case SymbolTableEntryType::Function: os<<"Function"; break;
		case SymbolTableEntryType::Class: os<<"Class"; break;
		case SymbolTableEntryType::Struct: os<<"Struct"; break;
	};
	return os;
}

SymbolTableEntry::SymbolTableEntry(const SymbolTableEntryType t ,
		const std::string& i) : type(t), id(i), astEntry(nullptr)
{
}

SymbolTableEntry::SymbolTableEntry(const SymbolTableEntryType t,
		const std::string& i, const Loc& l) : type(t), id(i), loc(l), astEntry(nullptr)
{
}

SymbolTableEntry::SymbolTableEntry(const SymbolTableEntryType t,
		const std::string& i, const Loc& l, AstNode* n) : type(t), id(i), loc(l), 
		astEntry(n)
{
}

SymbolTableEntry::SymbolTableEntry(const SymbolTableEntryType t,
		const std::string& i, AstNode* n) : type(t), id(i), astEntry(n)
{
}

bool SymbolTableEntry::operator<(const SymbolTableEntry o) const {
	return this->id < o.id;
}

bool SymbolTableEntry::operator==(const SymbolTableEntry o) const {
	return this->id == o.id;
}

std::ostream& operator<<(std::ostream& os, const SymbolTableEntry& e) {
	format(os, "%s:%s:%s", e.id, e.type, e.loc);
	return os;
}

std::ostream& operator<<(std::ostream& os, const SymbolTableType t) {
	switch(t) {
		case SymbolTableType::Ordered: os<<"Ordered"; break;
		case SymbolTableType::Unordered: os<<"Unordered"; break;
	}
	return os;
}

SymbolTable::SymbolTable() : parent(nullptr), type(SymbolTableType::Unordered) {
}

SymbolTable::SymbolTable(SymbolTable* p, SymbolTableType t) : parent(p),
		type(t) 
{
}

void SymbolTable::insert(const SymbolTableEntryType t, const std::string& id , const Loc& l) {
	this->map.emplace(t,id,l);
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

bool SymbolTable::contains(const SymbolTableEntryType t, const std::string& key) const {
	bool ret = static_cast<bool>(this->map.count(SymbolTableEntry(t, key)));
	if(ret) {
		return true;
	} else if(!ret && this->parent) {
		return this->parent->contains(t, key);
	} else {
		return false;
	}
}

void SymbolTable::toOstream(std::ostream& os, const size_t indent) const {
	for(size_t i = 0; i < indent; ++i) {
		os<<' ';
	}
	format(os, "%s\n", this->type);

	std::vector<SymbolTableEntry> entries(this->map.begin(), this->map.end());
	std::sort(entries.begin(), entries.end());

	for(auto& it : entries) {
		for(size_t i = 0; i < indent; ++i) {
			os<<' ';
		}
		format(os, "%s\n", it);
	}

	for(auto& it : this->follow) {
		it->toOstream(os, indent+1);
	}
}
