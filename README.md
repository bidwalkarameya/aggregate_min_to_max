# aggregate_min_to_max

This Postgres extension provides function to find min and max value minimum and maximum values of that column.

Installing

This package installs like any Postgres extension. First say:

make && sudo make install

You will need to have pg_config in your path, but normally that is already the case. You can check with which pg_config.

Then in the database of your choice say:

CREATE EXTENSION min_to_max;

Function:-

T[] array_to_min_max(values T[])

Returns a tuple with the min in position 1 and the max in position 2.
