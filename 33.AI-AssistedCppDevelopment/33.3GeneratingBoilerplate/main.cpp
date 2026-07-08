#include <print>
#include "employee.h"

int main(){

	Employee employee("Ada Lovelace", "Engineering", 95000.0);

	std::println("{} works in {}, earning {}",
		employee.name(), employee.department(), employee.salary());

	employee.set_salary(102000.0);
	std::println("After a raise: {}", employee.salary());

	return 0;
}
