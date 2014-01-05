#include <location.hpp>
#include <format.hpp>

Loc::Loc() : line(0), column(0) {}

Loc::Loc(unsigned l, unsigned c) : line(l), column(c) {
	
}

Loc::Loc(std::string f, unsigned l, unsigned c) : file(f), line(l), 
		column(c) {

}

std::string Loc::toString() const {
	std::stringstream ss;
	ss<<(*this);
	return ss.str();
}

std::ostream& operator<<(std::ostream& os, const Loc& l) {
	if(l.file.size() == 0u) {	
		format(os, "%u:%u",l.line,l.column);
	} else {
		format(os, "%s:%u:%u",l.file,l.line,l.column);
	}
	return os;
}
