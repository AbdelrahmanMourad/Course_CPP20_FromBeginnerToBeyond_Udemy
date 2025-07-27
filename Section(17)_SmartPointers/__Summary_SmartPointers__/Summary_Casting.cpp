/*
========================================================================================================
C++ Casting Summary: static_cast, dynamic_cast, reinterpret_cast, const_cast, C-style, and Smart Pointer Casts
========================================================================================================
| 1. static_cast<T>(expr)
|   - Compile-time cast for related types (e.g., int to double, base* to derived* if safe).
|   - No runtime type check; unsafe for downcasting unless you are sure.
|   - Example:
|       int i = 42;
|       double d = static_cast<double>(i); // int to double
|       Base* b = new Derived();
|       Derived* d = static_cast<Derived*>(b); // OK if b actually points to Derived

--------------------------------------------------------------------------------
| 2. dynamic_cast<T>(expr)
|   - Safe runtime-checked cast for polymorphic types (must have at least one virtual function).
|   - Used for downcasting (base* to derived*).
|   - Returns nullptr (for pointers) or throws std::bad_cast (for references) if cast fails.
|   - Example:
|       class Base { virtual void foo() {} };
|       class Derived : public Base {};
|       Base* b = new Derived();
|       Derived* d = dynamic_cast<Derived*>(b); // OK, d != nullptr
|       Base* b2 = new Base();
|       Derived* d2 = dynamic_cast<Derived*>(b2); // d2 == nullptr

--------------------------------------------------------------------------------
| 3. reinterpret_cast<T>(expr)
|   - Low-level, bitwise cast. Used for casting between unrelated pointer types or integer/pointer.
|   - Dangerous! Use only when you know what you are doing.
|   - Example:
|       int i = 0x12345678;
|       char* p = reinterpret_cast<char*>(&i);

--------------------------------------------------------------------------------
| 4. const_cast<T>(expr)
|   - Adds or removes const/volatile qualifier.
|   - Only use to remove constness when you are sure the object is not actually const.
|   - Example:
|       const int x = 10;
|       int* px = const_cast<int*>(&x);

--------------------------------------------------------------------------------
| 5. C-style cast (T)expr or T(expr)
|   - Tries static_cast, then const_cast, then reinterpret_cast (in that order).
|   - Not recommended: less explicit, can hide bugs.
|   - Example:
|       int i = (int)3.14; // C-style cast

--------------------------------------------------------------------------------
| 6. std::dynamic_pointer_cast<T>(shared_ptr<U>)
|   - For std::shared_ptr only.
|   - Safe downcast with runtime check (like dynamic_cast for raw pointers).
|   - Returns std::shared_ptr<T> (may be nullptr if cast fails).
|   - Example:
|       std::shared_ptr<Base> b = std::make_shared<Derived>();
|       std::shared_ptr<Derived> d = std::dynamic_pointer_cast<Derived>(b);

--------------------------------------------------------------------------------
| 7. std::static_pointer_cast<T>(shared_ptr<U>)
|   - For std::shared_ptr only.
|   - Compile-time cast (like static_cast for raw pointers).
|   - No runtime check; unsafe if types are not related.
|   - Example:
|       std::shared_ptr<Base> b = std::make_shared<Derived>();
|       std::shared_ptr<Derived> d = std::static_pointer_cast<Derived>(b);

--------------------------------------------------------------------------------
| 8. std::const_pointer_cast<T>(shared_ptr<U>)
|   - For std::shared_ptr only.
|   - Adds or removes constness from the pointed-to type.
|   - Example:
|       std::shared_ptr<const int> c = std::make_shared<int>(42);
|       std::shared_ptr<int> nc = std::const_pointer_cast<int>(c);

--------------------------------------------------------------------------------
| 9. Smart Pointer Notes:
|   - std::unique_ptr does NOT have dynamic_pointer_cast/static_pointer_cast helpers.
|   - For unique_ptr, use raw pointer casts and reconstruct unique_ptr if needed:
|       std::unique_ptr<Base> b = std::make_unique<Derived>();
|       Derived* d = dynamic_cast<Derived*>(b.get());
|       if (d) 
|       { 
|           // safe to use d   
|       }                           
|
--------------------------------------------------------------------------------
| 10. When to Use Which Cast?
|   - static_cast: Safe, related types, no runtime check.
|   - dynamic_cast: Polymorphic types, safe downcasting, runtime check.
|   - reinterpret_cast: Low-level, bitwise, avoid unless necessary.
|   - const_cast: Change constness, use with care.
|   - C-style: Avoid in C++, prefer explicit casts.
|   - dynamic_pointer_cast/static_pointer_cast: For shared_ptr, same rules as dynamic_cast/static_cast.

--------------------------------------------------------------------------------
| 11. Example Table:
|
|   |---------------------------------------------------------------------------------------------------------|
|   | Cast Type                | Use Case                  | Runtime Check | Works with Smart Ptr?            |
|   |------------------------- |-------------------------- |---------------|----------------------------------|
|   | static_cast              | Related types             | No            | static_pointer_cast              |
|   | dynamic_cast             | Polymorphic downcast      | Yes           | dynamic_pointer_cast             |
|   | reinterpret_cast         | Unrelated types, bitwise  | No            | reinterpret_pointer_cast (C++20) |
|   | const_cast               | Add/remove const/volatile | No            | const_pointer_cast               |
|   | C-style                  | Anything                  | No            | Not recommended                  |
|   |---------------------------------------------------------------------------------------------------------|

--------------------------------------------------------------------------------
| 12. Best Practices:
|   - Prefer static_cast for upcasting and safe conversions.
|   - Use dynamic_cast for downcasting in polymorphic hierarchies.
|   - Avoid reinterpret_cast unless absolutely necessary.
|   - Use const_cast only when you are sure the object is not actually const.
|   - Avoid C-style casts in C++ code.
|   - For shared_ptr, use dynamic_pointer_cast/static_pointer_cast as needed.
|   - For unique_ptr, cast the raw pointer and reconstruct unique_ptr if needed.

========================================================================================================
*/