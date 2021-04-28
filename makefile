MODULES = min_to_max
EXTENSION = min_to_max
EXTENSION_VERSION = 0.0.1
DATA = min_to_max--0.0.1.sql
PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)

