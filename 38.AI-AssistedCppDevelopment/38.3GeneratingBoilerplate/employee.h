#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>

// A class like this -- several fields, each with a getter and setter that
// does nothing interesting -- is exactly the kind of code worth generating
// rather than typing by hand. Prompting "add a getter and setter for each
// private member of this class" produces this reliably and fast, freeing
// you to spend your own attention on the parts of the class that actually
// need judgment (constructors, invariants, behavior).
class Employee
{
public:
	Employee(std::string name, std::string department, double salary)
		: m_name{std::move(name)}, m_department{std::move(department)}, m_salary{salary} {
	}

	const std::string& name() const { return m_name; }
	void set_name(const std::string& name) { m_name = name; }

	const std::string& department() const { return m_department; }
	void set_department(const std::string& department) { m_department = department; }

	double salary() const { return m_salary; }
	void set_salary(double salary) { m_salary = salary; }

private:
	std::string m_name;
	std::string m_department;
	double m_salary;
};

#endif // EMPLOYEE_H
