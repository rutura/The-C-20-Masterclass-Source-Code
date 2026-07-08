#ifndef NAME_TAG_H
#define NAME_TAG_H

#include <string>
#include <cctype>

// Suppose a prompt for "a small class holding someone's display name"
// returned something close to this. It compiles. Whether it's actually
// good code is a separate question -- and answering that question is the
// entire point of this final lecture. A short review checklist, applied
// to concrete code:
//
//  1. Ownership: does every resource have a clear, single owner? (Chapter
//     15, SmartPointers / Chapter 17, MoveSemantics)
//  2. Const-correctness: are members and parameters marked const where
//     nothing needs to change them? (Chapter 13, Classes)
//  3. Lifetime: could any reference/pointer here outlive what it refers
//     to? (Chapter 13's DanglingPointersAndReferences)
//  4. Idiom: is this how the language expresses the idea today, or an
//     older pattern that still compiles? (33.6, this chapter)
//  5. Tests: if this shipped with a generated test suite, does it cover
//     the case that actually matters? (Chapter 31, Testing)
//
// This class passes some of that checklist and fails others -- see the
// comments on each member for which is which.
class NameTag
{
public:
	NameTag(std::string name) : m_name{name} {
	}

	// (1) and (3): returning a reference into the class is fine as long as
	// the NameTag outlives the reference -- true here, since main() below
	// keeps the NameTag alive for as long as it uses display_name(). This
	// would fail the checklist if display_name() ever returned a reference
	// to something temporary instead of a member.
	const std::string& display_name() const {
		return m_name;
	}

	// (2): missing const. This method doesn't need to modify anything, but
	// nothing stops it from being called on a non-const NameTag and
	// accidentally mutating m_name later as the class grows -- an easy
	// thing to miss when skimming code that "looks fine."
	std::string shout_name(){
		std::string result = m_name;
		for (char& c : result)
			c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
		return result;
	}

private:
	std::string m_name;
};

#endif // NAME_TAG_H
