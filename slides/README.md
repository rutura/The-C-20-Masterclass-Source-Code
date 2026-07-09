# Lecture slides

Slides for every lecture are written as plain Markdown using
[Marp](https://marp.app/) and rendered to PDF with the official Marp CLI,
containerized the same way this repo already containerizes GCC and Clang in
[`../docker`](../docker).

Each lecture folder gets its own `slides.md` right next to its
`CMakeLists.txt`/`main.cpp`. Rendering produces `slides.pdf` in that same
folder.

## Build the image

Run once, from the repo root:

```sh
docker build -t masterclass-slides slides
```

## Render a lecture's slides

Mount the lecture folder as `/home/marp/app` (Marp CLI's default working
directory) and point it at `slides.md`. Also mount the shared theme so
`slides.md` can reference `theme: masterclass`.

```powershell
# Windows (PowerShell)
docker run --rm `
  -v "${PWD}\03.FirstSteps\3.2YourFirstProgram:/home/marp/app" `
  -v "${PWD}\slides\theme.css:/home/marp/app/theme.css" `
  masterclass-slides slides.md --pdf --allow-local-files -o slides.pdf
```

```sh
# Linux / macOS
docker run --rm \
  -v "$(pwd)/03.FirstSteps/3.2YourFirstProgram:/home/marp/app" \
  -v "$(pwd)/slides/theme.css:/home/marp/app/theme.css" \
  masterclass-slides slides.md --pdf --allow-local-files -o slides.pdf
```

Substitute any lecture folder that has a `slides.md`. `--allow-local-files`
lets a slide embed a local image (e.g. a screenshot saved next to
`slides.md`) if a lecture needs one.

## Writing slides.md

Front-matter goes at the top of every deck:

```markdown
---
marp: true
theme: masterclass
paginate: true
---
```

Slides are separated by a line containing only `---`. A fenced code block
renders with syntax highlighting:

````markdown
## Reading input

```cpp
std::string name;
std::getline(std::cin, name);
```
````

An image (must live next to `slides.md`, or be an absolute URL):

```markdown
![width:600px](screenshot.png)
```

The first slide of every deck in this course uses the `lead` class to
center the title:

```markdown
<!-- _class: lead -->
# 3.2 Your First Program
```

## Rendering every lecture in a chapter at once

There's no batch script by design - render one lecture at a time as you
finish drafting/editing its `slides.md`, the same way you build/run one
lecture at a time against the GCC/Clang images.
