#ifndef INTEGER_H
#define INTEGER_H

class Integer
{
public:
  explicit Integer(int value);
  Integer() { fmt::println("Default constructor for Integer called"); }
  ~Integer();

  int get_value() const { return inner_int; }

  void set_value(int new_val) { inner_int = new_val; }

private:
  int inner_int{};
};

#endif// INTEGER_H
