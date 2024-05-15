#ifndef BULL_DOG_H
#define BULL_DOG_H
#include "dog.h"
class BullDog : public Dog
{
public:
  BullDog();
  virtual ~BullDog();


  // Will throw a compiler error
  /*
 virtual void run() const override{
     fmt::println( "Bulldog::run() called" );
 }
 */
};

#endif// BULL_DOG_H
