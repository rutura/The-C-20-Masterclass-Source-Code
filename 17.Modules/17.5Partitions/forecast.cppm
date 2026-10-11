// The PRIMARY MODULE INTERFACE: the one file with no colon in its name. It
// decides what the module offers by re-exporting its partitions.
export module forecast;

export import :model;              // exports everything that partition exports
export import :stats;
// detail is NOT re-exported: it is for the module's own files only.
