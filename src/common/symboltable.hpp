#pragma once

#include <ostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <memory>

#include <ast.hpp>
#include <location.hpp>

class SymbolTable;

enum class SymbolTableEntryType {
	Variable,
	Constant,
	Function,
	Class,
	Struct
};

std::ostream& operator<<(std::ostream&, const SymbolTableEntryType);

struct SymbolTableEntry {
	SymbolTableEntryType type;
	Loc loc;
	AstNode* astEntry;

	explicit SymbolTableEntry(const SymbolTableEntryType);
	explicit SymbolTableEntry(const SymbolTableEntryType, const Loc&);
	explicit SymbolTableEntry(const SymbolTableEntryType, AstNode*);
	explicit SymbolTableEntry(const SymbolTableEntryType, const Loc&,AstNode*);

	bool operator<(const SymbolTableEntry) const;
	bool operator==(const SymbolTableEntry) const;
};

std::ostream& operator<<(std::ostream&, const SymbolTableEntry&);

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
typedef std::vector<SymbolTableEntry> SymbolTableEntryVec;
typedef std::unordered_map<std::string,SymbolTableEntryVec> SymbolTableEntryMap;

enum class SymbolTableType {
	Ordered,
	Unordered
};

std::ostream& operator<<(std::ostream&, const SymbolTableType);

class SymbolTable {
public:
	SymbolTable();
	SymbolTable(SymbolTable*,SymbolTableType = SymbolTableType::Ordered);

	void insert(const SymbolTableEntryType,const std::string&, const Loc&);

	SymbolTable* getParent();
	const SymbolTable* getParent() const;

	SymbolTableEntryMap& getMap();
	const SymbolTableEntryMap& getMap() const;

	void insertNewTable(SymbolTablePtr);
	const SymbolTableVec getFollow() const;
	SymbolTableVec getFollow();

	bool contains(const SymbolTableEntryType, const std::string&) const;
	SymbolTableType getType() const;

	void toOstream(std::ostream&, const size_t) const;

private:
	SymbolTableEntryMap map;
	SymbolTableVec follow;
	SymbolTable* parent;
	SymbolTableType type;
};
