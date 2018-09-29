
# text_analysis
An attempt to replicate [this](https://github.com/jasonxia17/TextAnalyzer) in C.

## Compiling
If you're on macOS or linux you probably already have GNU make installed. Open up your terminal and type in the following:

```sh
git clone http://github.com/ajaymt/text_analysis.git
cd text_analysis
make zipf
```

Run `make test` instead of `make zipf` if you want to compile the test file.

I have no idea how C compilation works on Windows.

## Running
The compilation step should have produced a binary file called `zipf` (`test` if you compiled the test program). You can run this program from your terminal.

```sh
./zipf
```

To read the first 10000 bytes of a file called `harry-potter.txt` and print out the resulting frequency map, you would do the following:

```sh
./zipf 10000 < harry-potter.txt
```

To run tests:
```sh
./test
```

I'm sorry Windows users -- you'll have to figure this one out on your own as well.
