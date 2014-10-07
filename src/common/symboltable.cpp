#include <symboltable.hpp>
#include <format.hpp>
#include <parser.hpp>

std::ostream& operator<<(std::ostream& os, const SymbolTypeEnum e) {
	switch(e) {
		case SymbolTypeEnum::Undefined: os<<"Undefined"; break;
		case SymbolTypeEnum::Primative: os<<"Primative"; break;
		case SymbolTypeEnum::IdList: os<<"IdList"; break;
	}
	return os;
}

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

SymbolType::SymbolType() : type(SymbolTypeEnum::Undefined) {
}

std::ostream& operator<<(std::ostream& os, const SymbolType e) {
	os<<e.type<<" ";

	if(e.type == SymbolTypeEnum::Primative) {
		os<<e.primativeType;
	} else if(e.type == SymbolTypeEnum::IdList) {
		os<<e.follow.name;
	}
	
	return os;
}

SymbolTableEntry::SymbolTableEntry(const SymbolTableEntryType t) : type(t), 
		astEntry(nullptr)
{
}

SymbolTableEntry::SymbolTableEntry(const SymbolTableEntryType t,
		const Loc& l) : type(t), loc(l), astEntry(nullptr)
{
}

SymbolTableEntry::SymbolTableEntry(const SymbolTableEntryType t,
		const Loc& l, AstNode* n) : type(t), loc(l), 
		astEntry(n)
{
}

SymbolTableEntry::SymbolTableEntry(const SymbolTableEntryType t,
		AstNode* n) : type(t), astEntry(n)
{
}

bool SymbolTableEntry::operator<(const SymbolTableEntry o) const {
	return this->type < o.type;
}

bool SymbolTableEntry::operator==(const SymbolTableEntry o) const {
	return this->type == o.type;
}

std::ostream& operator<<(std::ostream& os, const SymbolTableEntry& e) {
	format(os, "%s:%s: ptr %p", e.type, e.loc, e.astEntry);
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

void SymbolTable::insert(const std::string& id, const SymbolTableEntryType t, 
		const Loc& l) {
	auto it(this->map.find(id));
	if(it == this->map.end()) {
		it = this->map.insert(std::make_pair(id, SymbolTableEntryVec())).first;
	}

	it->second.emplace_back(t, l);

	// get the last insert so getLast works
	this->lastEntry = &it->second.back();
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

bool SymbolTable::contains(const std::string& key, 
		const SymbolTableEntryType t) const {
	auto it(this->map.find(key));
	if(it == this->map.cend()) {
		if(this->parent) {
			return this->parent->contains(key, t);
		} else {
			return false;
		}
	} else {
		for(auto& jt : it->second) {
			if(jt.type == t) {
				return true;
			}
		}
		return false;
	}
}

void SymbolTable::toOstream(std::ostream& os, const size_t indent) const {
	for(size_t i = 0; i < indent; ++i) {
		os<<' ';
	}
	format(os, "%s\n", this->type);

	for(auto& it : this->map) {
		for(size_t i = 0; i < indent; ++i) {
			os<<' ';
		}
		format(os, "%s ", it.first);
		for(auto& jt : it.second) {
			format(os, "%s ", jt);
		}
		format(os, "\n");
	}

	//std::vector<SymbolTableEntry> entries(this->map.begin(), this->map.end());
	//std::sort(entries.begin(), entries.end());

	//for(auto& it : entries) {
	//	for(size_t i = 0; i < indent; ++i) {
	//		os<<' ';
	//	}
	//	format(os, "%s\n", it);
	//}

	for(auto& it : this->follow) {
		it->toOstream(os, indent+1);
	}
}

//SymbolTableEntry& SymbolTable::getLast();
