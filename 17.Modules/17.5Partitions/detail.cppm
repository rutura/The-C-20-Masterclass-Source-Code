// An INTERNAL partition: no `export` in front of `module`. Other files of the
// module may import it, but it is never visible to the importers of `forecast`.
module forecast:detail;

double square(double x) {
    return x * x;
}
