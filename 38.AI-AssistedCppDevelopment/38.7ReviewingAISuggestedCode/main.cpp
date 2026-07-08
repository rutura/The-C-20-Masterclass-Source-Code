#include <print>
#include "name_tag.h"

void print_tag(const NameTag& tag){
	std::println("{}", tag.display_name());
}

int main(){

	NameTag tag("Grace Hopper");

	print_tag(tag);
	std::println("{}", tag.shout_name());

	// Applying item (2) from the checklist in name_tag.h: shout_name()
	// should be const, since it doesn't (and shouldn't need to) modify the
	// NameTag. Try marking it const in name_tag.h and rebuilding -- it
	// still compiles and behaves identically, because it was already only
	// reading m_name. That's the review process in one small example: the
	// suggested code worked, but reading it against a checklist caught a
	// real, fixable gap before it became a habit repeated across a whole
	// codebase.

	return 0;
}
