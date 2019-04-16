# Speller

A program that spell-checks a file. A dictionary and sample text files to be spell-checked are provided.


## Compiling

* `make` or `make speller` to compile.
* `make clean` to delete `speller` and any `core` or `.o` files


## Running

* To execute: `speller [dictionary] text`
  * `dictionary` is a text file containg a list of lower-case words.
    * If the `dictionary` argument is omitted `speller` will use the default dictionary: `dictionaries/large`. Therefore, `./speller text` is equivalent to `./speller dictionaries/large text`
  * `text` is the file to be spell-checked.
* Examples:
  * `./speller texts/shakespeare.txt`
  * `./speller dictionaries/large texts/shakespeare.txt`