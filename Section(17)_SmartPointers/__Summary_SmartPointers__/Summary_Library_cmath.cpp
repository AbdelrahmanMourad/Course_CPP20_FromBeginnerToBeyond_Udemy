/*
========================================================================================================
<cmath> - Most Important and Commonly Used Functions (with Examples)
========================================================================================================
| <cmath> provides mathematical functions for floating-point and integer math.
| Useful for scientific, engineering, and graphics applications.
--------------------------------------------------------------------------------
| 1. sqrt
|    - Square root.
|    - Example: double r = sqrt(16.0); // r = 4.0
|
| 2. pow
|    - Power function.
|    - Example: double p = pow(2.0, 3.0); // p = 8.0
|
| 3. abs / fabs
|    - Absolute value (int/double).
|    - Example: int a = abs(-5); double b = fabs(-3.2);
|
| 4. sin, cos, tan
|    - Trigonometric functions (input in radians).
|    - Example: double s = sin(M_PI/2); // s = 1.0
|
| 5. asin, acos, atan, atan2
|    - Inverse trigonometric functions.
|    - Example: double a = asin(1.0); // a = pi/2
|
| 6. exp, log, log10
|    - Exponential and logarithmic functions.
|    - Example: double e = exp(1.0); // e = 2.718...
|    - Example: double l = log(10.0); // natural log
|    - Example: double l10 = log10(100.0); // l10 = 2.0
|
| 7. ceil, floor, round, trunc
|    - Rounding functions.
|    - Example: ceil(2.3) = 3.0, floor(2.7) = 2.0, round(2.5) = 3.0, trunc(2.9) = 2.0
|
| 8. fmod
|    - Floating-point remainder.
|    - Example: double r = fmod(7.5, 2.0); // r = 1.5
|
| 9. hypot
|    - Euclidean distance (sqrt(x*x + y*y)).
|    - Example: double h = hypot(3.0, 4.0); // h = 5.0
|
| 10. min, max (C++11 and later)
|    - Minimum/maximum of two values.
|    - Example: double m = std::min(3.2, 4.5);
========================================================================================================
*/