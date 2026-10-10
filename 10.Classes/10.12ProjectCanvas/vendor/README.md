# Vendored third-party code

`stb_image_write.h` - single-header image writer by Sean Barrett.

- Source:  https://github.com/nothings/stb
- Version: v1.16
- Commit:  2c980bb59875b0d32144a71867fbdebb2f77cd20
- License: public domain / MIT (see `LICENSE`)

"Vendored" means the file is committed straight into this repo. Nothing
is downloaded at build time; the header is compiled from source along
with our own code, so there is no prebuilt binary and no ABI mismatch to
worry about.

Exactly one `.cpp` in the project defines `STB_IMAGE_WRITE_IMPLEMENTATION`
before including this header - that is the translation unit where the
function bodies get compiled. Every other file just includes the header
for the declarations.
