#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <memory>

#include <ast.hpp>
#include <location.hpp>

class SymbolTable;

struct SymbolTableEntry {
	std::string id;
	Loc loc;

	explicit SymbolTableEntry(const std::string&);
	explicit SymbolTableEntry(const std::string&,const Loc&);

	bool operator<(const SymbolTableEntry) const;
	bool operator==(const SymbolTableEntry) const;
};

namespace std {
	template<>
	struct hash<SymbolTableEntry> {
		size_t operator()(const SymbolTableEntry& s) const {
			return std::hash<string>()(s.id);
		}
	};
}

//typedef std::unordered_map<std::string,AstNode*> SymbolTableMap;
typedef std::shared_ptr<SymbolTable> SymbolTablePtr;
typedef std::shared_ptr<const SymbolTable> SymbolTableConstPtr;
typedef std::vector<SymbolTablePtr> SymbolTableVec;
typedef std::unordered_set<SymbolTableEntry> SymbolTableEntryMap;

class SymbolTable {
public:
	SymbolTable();
	SymbolTable(SymbolTable*);

	void insert(const std::string&, const Loc&);

	SymbolTable* getParent();
	const SymbolTable* getParent() const;

	SymbolTableEntryMap& getMap();
	const SymbolTableEntryMap& getMap() const;

	void insertNewTable(SymbolTablePtr);
	const SymbolTableVec getFollow() const;
	SymbolTableVec getFollow();

	bool contains(const std::string&) const;

private:
	SymbolTableEntryMap map;
	SymbolTableVec follow;
	SymbolTable* parent;
};
