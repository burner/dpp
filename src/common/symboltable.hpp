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

template <class T>
inline void hashCombine(std::size_t& seed, const T& v) {
    std::hash<T> hasher;
    seed ^= hasher(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
}

namespace std {
	template<>
	struct hash<SymbolTableEntry> {
		size_t operator()(const SymbolTableEntry& s) const {
			size_t hash(std::hash<size_t>()(static_cast<size_t>(s.type)));
			hashCombine(hash, s.loc.file);
			hashCombine(hash, s.loc.line);
			hashCombine(hash, s.loc.column);
			return hash;
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

	void insert(const std::string&, const SymbolTableEntryType, const Loc&);

	SymbolTable* getParent();
	const SymbolTable* getParent() const;

	SymbolTableEntryMap& getMap();
	const SymbolTableEntryMap& getMap() const;

	void insertNewTable(SymbolTablePtr);
	const SymbolTableVec getFollow() const;
	SymbolTableVec getFollow();

	bool contains(const std::string&, const SymbolTableEntryType) const;
	SymbolTableType getType() const;

	void toOstream(std::ostream&, const size_t = 0) const;

	SymbolTableEntry& getLast();

private:
	SymbolTableEntryMap map;
	SymbolTableVec follow;
	SymbolTable* parent;
	SymbolTableType type;
	SymbolTableEntry* lastEntry;
};
