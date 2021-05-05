CREATE OR REPLACE FUNCTION
array_to_min_max(anyarray)
RETURNS anyarray
AS 'MODULE_PATHNAME', 'array_to_min_max'
LANGUAGE c IMMUTABLE;

create aggregate min_to_max(anyarray)
(
    sfunc = array_to_min_max,
    stype = anyarray,
        initcond = '');


