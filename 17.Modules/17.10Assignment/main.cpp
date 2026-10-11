#include <print>
#include <string>
#include <vector>

/*
    Chapter 17 assignment - Modules

    Eight small jobs for the weather station. This assignment is different from
    the earlier ones: most exercises ask you to WRITE NEW FILES (module files)
    and then use them from main(). Work like this for each exercise:

      1. write the module file(s) in this folder (the solution/ folder has the
         answers, look only after you tried)
      2. add the file(s) to the FILE_SET in CMakeLists.txt, and any
         implementation unit (.cpp) to the add_executable line
      3. add `import name;` below, and the lines in main() under the heading

    Rules:
      - Use std::print / std::println. Never std::cout, never std::endl.
      - Brace-initialize every variable: int n{0};  double x{1.5};
      - Qualify everything with std:: - no `using namespace std;`
      - Every module unit includes the standard headers IT uses.
      - Put the #includes before the `import` lines in this file.
*/

// Add your `import ...;` lines here, after the #includes above.


int main() {

    /*
        Exercise 1 - a first module (17.3)

        Write module `units` (units.cppm) exporting two functions:
            double to_fahrenheit(double celsius)      c * 9 / 5 + 32
            double to_kelvin(double celsius)          c + the offset
        The number 273.15 lives in a function `kelvin_offset()` that is NOT
        exported. Print 21.5 C in both.

        Sample output:
            21.5 C = 70.7 F = 294.65 K
    */
    std::println("--- Exercise 1: a first module ---");
    // TODO


    /*
        Exercise 2 - a struct and a constant (17.3)

        Write module `limits` exporting struct Range {double low; double high;},
        a constexpr Range `comfortable` {18, 26}, and a constexpr function
        within(const Range&, double). Define the two numbers 18 and 26 as MACROS
        inside the module (#define) and use them to build `comfortable`: the
        macros must not be visible in main().

        Sample output:
            comfortable range: 18 to 26
            22 is comfortable: true   30 is comfortable: false
    */
    std::println("\n--- Exercise 2: a struct and a constant ---");
    // TODO


    /*
        Exercise 3 - interface and implementation (17.4)

        Write module `statistics`: an interface file statistics.cppm that declares
            double mean_of(const std::vector<double>&)
            double largest_of(const std::vector<double>&)
        (its global module fragment includes <vector>) and an implementation
        unit statistics.cpp (`module statistics;`) that defines them, with its
        own global module fragment including <algorithm>, <numeric> and <vector>.
        Both return 0 for an empty vector. Use {18.5, 24.0, 21.5, 12.0}.

        Sample output:
            mean 19.00, largest 24
    */
    std::println("\n--- Exercise 3: interface and implementation ---");
    // TODO


    /*
        Exercise 4 - a template in a module (17.4)

        Write module `clamp` exporting the template
            template <typename T> T clamped(T value, T low, T high)
        Where must the body be, and why?

        Sample output:
            clamped(35, 0, 30) = 30   clamped(-4.5, 0.0, 30.0) = 0
    */
    std::println("\n--- Exercise 4: a template in a module ---");
    // TODO


    /*
        Exercise 5 - partitions (17.5)

        Write module `weather` with three partitions:
            weather:model    exports struct Reading {int hour; double celsius;}
            weather:detail   an INTERNAL partition with const char* label_for(double):
                             "warm" from 25 up, "mild" from 15 up, otherwise "cold"
            weather:format   exports std::string describe(const Reading&), declared
                             in the partition and DEFINED in an implementation unit
                             weather.cpp, the only place that imports :detail
        and the primary interface weather.cppm that re-exports :model and :format.
        describe() gives "<hour>h: <celsius> C, <label>" (use std::format). Describe
        the readings {6, 11.5}, {12, 26.0}, {18, 19.0}.

        Sample output:
            6h: 11.5 C, cold
            12h: 26 C, warm
            18h: 19 C, mild
    */
    std::println("\n--- Exercise 5: partitions ---");
    // TODO


    /*
        Exercise 6 - import std (17.6)

        This one is a separate program, because a file that says `import std;`
        should not also #include standard headers. Write main_std.cpp that
        starts with `import std;` and has NO #include, plus a module `summary`
        (summary.cppm, also `import std;`) exporting
            std::string summary_of(const std::vector<double>&)
        which gives "lowest <min>, highest <max>, mean <mean with 2 decimals>".
        Add a second executable to CMakeLists.txt and call target_use_import_std()
        on it (see the end of the file for the pattern in the solution).

        Sample output (from that second program):
            lowest 12, highest 24, mean 19.00
    */
    std::println("\n--- Exercise 6: import std (in a second program) ---");


    /*
        Exercise 7 - wrapping a legacy header (17.7)

        legacy_alarm.h and legacy_alarm.cpp are provided: an old header with a
        macro ALARM_LEVELS, a struct Alarm, make_alarm() and describe_level().
        Do not change them. Write module `alarms` (alarms.cppm) that includes the
        header in its global module fragment and exports the three names with
        export using ::name;, plus a constexpr int `alarm_levels` built from the
        macro. legacy_alarm.cpp goes on the add_executable line as an ordinary
        source, and the folder needs to be on the include path
        (target_include_directories). Make an alarm of level 2, "battery low".

        Sample output:
            warning: battery low (levels go up to 3)
    */
    std::println("\n--- Exercise 7: wrapping a legacy header ---");
    // TODO


    /*
        Exercise 8 - read the build (17.8)

        Build your program, then change files and rebuild, and write down in the
        comments below which files were rebuilt each time (the output of
        `cmake --build` lists them). Predict first, then check.

            a. change only main.cpp:
            b. change the BODY of a function in statistics.cpp:
            c. change a body inside units.cppm (a module interface):
            d. add a new exported function to limits.cppm:

        Expected (for the files of this assignment):
            a. only main.cpp
            b. only statistics.cpp
            c. units.cppm and every file that imports units, here main.cpp
            d. limits.cppm and every file that imports limits, here main.cpp
    */
    std::println("\n--- Exercise 8: read the build ---");
    std::println("(a written exercise: see the comment above)");

    return 0;
}
