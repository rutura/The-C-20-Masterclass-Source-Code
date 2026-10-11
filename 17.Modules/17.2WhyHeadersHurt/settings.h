#pragma once

// A settings header from "somewhere in the project". It means well, but a
// macro does not respect scope, namespaces or the file it was written in:
// from the next line on, EVERY line of every file that includes this header
// sees the word WARM as the number 25.
#define WARM 25
#define COLD 5
