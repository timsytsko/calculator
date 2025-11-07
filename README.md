to compile:
```
g++ -o <executable name> src/calc.cpp src/parser.hpp src/executer.hpp
```

to run (from file):
```
<executable name> <filename>
```
or without ```<filename>``` to input from console

```input.txt``` example:
```
((100 - 25 * 3) / (4 + 1) + (18 * 2 - 15 / 3) * (7 + 8 / 4)) / (12 * 3 - 20) / (5 + 2) + (45 - 5 * 7)
```