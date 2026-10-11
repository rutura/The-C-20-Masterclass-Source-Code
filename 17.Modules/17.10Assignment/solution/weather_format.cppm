module;

#include <string>

export module weather:format;

import :model;

export std::string describe(const Reading& reading);
