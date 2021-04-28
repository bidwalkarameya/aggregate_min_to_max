CREATE OR REPLACE FUNCTION 
min_max_val(anyarray)
RETURNS anyarray
AS 'min_to_max', 'min_to_max'
LANGUAGE c IMMUTABLE;

create aggregate min_to_max()
(
    sfunc = min_max_value,
    stype = anyarray
);
