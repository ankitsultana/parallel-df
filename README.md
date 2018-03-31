# parallel-df

An OpenMP based solution for computing K-most frequent words in a corpus.

### Dependencies

* C++11 or higher
* OpenMP

### Usage

* Build the project

```
make
```

* Add path to the corpus to a file (see `exp.txt`). In case you want to try
this on multiple corpus, add each of their top level paths in a different line
in `exp.txt`

* The executable is `bin/exec`, which you can run like so:

```
time bin/exec -config exp.txt -k 2 -nt 2
```

### License

GNU GPL v3
