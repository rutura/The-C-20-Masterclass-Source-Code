module weather:detail;

// Internal: used by the other partitions, invisible to importers.
const char* label_for(double celsius) {
    return celsius >= 25.0 ? "warm" : (celsius >= 15.0 ? "mild" : "cold");
}
