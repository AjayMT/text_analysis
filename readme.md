
# text_analysis
An attempt to replicate [this](https://github.com/jasonxia17/TextAnalyzer) in C.

## Compiling
If you're on macOS or linux you probably already have GNU make installed. Open up your terminal and type in the following:

```sh
git clone http://github.com/ajaymt/text_analysis.git
cd text_analysis
make zipf
```

This will produce a binary file called `./zipf` in the `text_analysis` directory.

I have no idea how C compilation works on Windows.

## Running
The compilation step should have produced a binary file called `zipf`. You can run this program from your terminal.

```sh
./zipf
```

If `zipf` receives no arguments or "help" as its first argument it will print a help message.

To read the first 10000 bytes of a file called `harry-potter.txt` and print out the resulting frequency map, you would do the following:
```sh
./zipf 10000 < harry-potter.txt
```

To run `zipf` on the test data (`test-data/sherlock.txt`):
```sh
make example
```

This will write the output to a file called `out.txt`.

To run tests:
```sh
make test
```

TODO windows instructions
