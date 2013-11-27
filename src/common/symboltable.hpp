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

	SymbolTableEntry(const std::string&,const Loc&);

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
typedef std::vector<SymbolTable*> SymbolTableVec;
typedef std::unordered_set<SymbolTableEntry> SymbolTableMap;

class SymbolTable {
public:
	SymbolTable();
	SymbolTable(SymbolTablePtr);

	void insert(const std::string&, const Loc&);

	SymbolTablePtr getParent();
	SymbolTableConstPtr getParent() const;

	void insertNewTable(SymbolTable*);
	const SymbolTableVec getFollow() const;
	SymbolTableVec getFollow();

private:
	SymbolTableMap map;
	SymbolTablePtr parent;
};
