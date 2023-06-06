# Etude 08 - Rational Thinking

## Integer

We chose to represent the Integers by an array of ints - one int per digit.
The arrays start with the lowest-valued digit, i.e., the array represents the number "backwards".
This is to make sure that the int at index x always represents the value (int * 10^x).

The Integers also has a boolean value, stating whether the number is positive or not.

The arithmetic operators are pretty much implemented by the methods you learn in primary school, except for multiplication, where we used Karatsuba's algorithm, as shown in this video: https://www.youtube.com/watch?v=yWI2K4jOjFQ.

For division, we made our own algorithm to perform the "smaller divisions", called slowDivision().

## Rational

The Rationals holds three Integers: The numerator, the denominator, and one for the "whole ones".

It also holds a boolean of its own, indicating whether it is positive or not.

The arithmetics in this class also correspond with primary school mathematics, and lean heavily on the already implemented operations of Integers.

We added some helping methods for scaling fractions, and moving the "whole ones" into/out of the fraction, 
since these are operations that is performed in almost every arithmetic operation with rationals.