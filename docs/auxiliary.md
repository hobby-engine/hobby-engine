# Auxiliary

These are just a bunch of random, helpful functions.

- `try(fn, ...)` - Executions a function if it's not `nil`.
- `matchType(var, type)` - Checks if a variable matches the passed type. Throws an error if it doesn't.
- `requireKeys(keys, table)` - Checks if `table` has all the keys in `keys`. Throws an error if it doesn't.
- `overrideKeys(dest, src)` - Takes the values from `src` and puts them in `dest`, with no regard for if `dest` already has that key.
- `injectKeys(dest, src)` - Takes the values from `src` and puts them in `dest`, if `dest` doesn't already have the key.
- `copyTable(deep)` - Copies a table. If `deep` is true, then it will recursively copy sub-tables as well.
- `swapRemove(index)` - Will remove a value at `index` in a table in a way that is faster. Only works if the order of elements doesn't matter.