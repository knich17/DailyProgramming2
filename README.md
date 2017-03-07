# Day 2 - Horse Race Sorting
[Found at /r/dailyprogrammer](https://www.reddit.com/r/dailyprogrammer/comments/5j6ggm/20161219_challenge_296_easy_the_twelve_days_of/)

## Problem Description
This challenge is inspired by the well-known horse racing puzzle. In that puzzle, you need to find the fastest 3 horses out of a group of 25. You do not have a stopwatch and you can only race 5 of them at the same time. In this challenge, you need to sort a list of numeric values. However, you can only directly compare values during a "race" in which you take a set of 5 values and sort them. Based on the outcomes of these races, you need to be able to sort the entire list.

## Solution
Currently a failed/incomplete solution.

A quicksort algorithm was implemented to sort a given array of length 5, of type "Horse", a custom class containing the horses time as well as vectors containing pointers to slower or faster horses.

The next issue was deciding which horses to race (max of 5). The idea is that you would want to race the 5 horses that you would gain the most information from. I originally considered the horses possible information gain only individually which lead the program into an infinite loop when each horse has a lot of potential information but the 5 horses together gain none.

In the end I picked a starting horse with the highest potential, then kept adding the horse that best increased the group potential.

The end result is that it, as expected, cycles through enough races that every horse has raced each other at one some point.

The next step, that would hopefully drastically reduce required races, would be to consider that if A is smaller than B and another race shows that B is smaller than C, you also know that A is smaller than C. An attempt to do just this was unsucessfully implemented as it makes no difference to the number of races required to order the list.

## Notes
This problem is more difficult than I first assumed, with the hard part being deciding which horses to race against each other.

## Issues
Just a basic solution, requires lots of races, code also desperatly requires refactoring and better comments.