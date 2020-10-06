The program uses a function named ask to simulate the balance. It only tells which side is heavier, and outputs the result on the screen. The result shows that in our method, only when the 11# is different will lead to a four-step weighing. We can handle the other situations in three steps.


A simple example:


Please input the number of the different ball(0~11), and a flag -1 for lighter or 1 for heavier. Input -1 -1 to quit.

11 -1

weigh 1:

left side: 0 1 2 3 

right side: 4 5 6 7 

Two sides are same weighted.

weigh 2:

left side: 8 

right side: 9 

Two sides are same weighted.

weigh 3:

left side: 8 

right side: 10 

Two sides are same weighted.

weigh 4:

left side: 8 

right side: 11 

Left side is heavier.

#11, lighter


Please input the number of the different ball(0~11), and a flag -1 for lighter or 1 for heavier. Input -1 -1 to quit.

1 1

weigh 1:

left side: 0 1 2 3 

right side: 4 5 6 7 

Left side is heavier.

weigh 2:

left side: 0 5 6 7 

right side: 4 9 10 11 

Two sides are same weighted.

weigh 3:

left side: 1 

right side: 2 

Left side is heavier.

#1, heavier


Please input the number of the different ball(0~11), and a flag -1 for lighter or 1 for heavier. Input -1 -1 to quit.

-1 -1
