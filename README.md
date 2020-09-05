# philosophers-problem-deadlock
Five philosophers want to eat in a circular table.
Next to each of them there are two sticks which are shared to the next diner - guest in the table.
To demonstrate:
  Philo1 <->stick1<-> Philo2 <-> stick2 <-> Philo3...
As you can see, when philo2 wants to eat he must pick up stick1, stick2.
But if he picks up stick1 and at right after this, context switch occured and philo3 picks up stick2,
then a deadlock might happened and no one can eat.
There must be an order!! Any solution ???
