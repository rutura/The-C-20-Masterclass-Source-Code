// A module in ONE file, with its implementation hidden below a private module
// fragment. Everything after `module :private;` is invisible to importers and
// does not make them rebuild when it changes.
export module single;

export int twice(int x);

module :private;

int twice(int x) {
    return x * 2;
}
