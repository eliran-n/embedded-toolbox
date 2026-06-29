#include <iostream>

using namespace std;

/*
    Polymorphism - Meaning the same action but different behavior:
    All animal have the same action (method) - Making sound
    But each animal behave different - Making differnt sound 
*/

// Base class
class Animal 
{
  public:
    virtual void animal_sound()
    {
      cout << "The animal makes a sound \n";
    }
};

// Derived class
class Pig : public Animal 
{
  public:
    void animal_sound() override
    {
      cout << "The pig says: wee wee \n";
    }
};

// Derived class
class Dog : public Animal 
{
  public:
    void animal_sound() override
    {
      cout << "The dog says: bow wow \n";
    }
};

int main( void )
{
    Animal animal;
    animal.animal_sound();

    Pig pig;
    pig.animal_sound();

    Dog dog;
    dog.animal_sound();
    
    // With virtual - C++ point to the dog sound - derived class, instead of Animal sound - the base class
    // Since it's check the object type (the Dog class) instead of base on the pointer type we created which is Animal
    Animal* animal_ptr;
    animal_ptr = &dog;
    animal_ptr->animal_sound();

    return 0;
}