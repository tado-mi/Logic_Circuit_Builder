# Logic Circuit builder

Code written by [tado-mi](https://github.com/tado-mi) in 2017, initially for a course at the University of Rochester.

It is an implementation of a simple parser for logival expressions. The input is an expression in English (such as *x and not y*), the output is evaluation (up to) all the possible truth assignments. For now, the support is for up to 3 variables and all the (basic) logic gates: *or, and, not, nor, nand*.

# Description of the algorithm

* Convert the input into a [reverse Polish](https://en.wikipedia.org/wiki/Reverse_Polish_notation) (or postfix) notation, using the [Shanting-Yard algorithm](https://en.wikipedia.org/wiki/Shunting_yard_algorithm). The boolean operators are 'translated' into arithmetic operations (for the purposes of precedence values, and the desired binding of logic operations) as follows:

        +       or
        -       nor
        *       and
        /       nand
        !       not

The function of the operator is hardcoded.

* Construct the pre-circuit

The circuit constructed is the expression tree of the postfix, that comes to be with this [algorithm](https://stackoverflow.com/questions/423898/postfix-notation-to-expression-tree).

* Construct the circuit

each unique variable in the expression tree is linked to its instances. For example, if we have *not x or x*, the tree will end up looking like this:

                +
            /       \
           !         |
           |         |
           x         x      // instances of x
            \       /
                x           // the unique variable x

* Generate truth assignments

"Count" up to 2<sup>n</sup>, for `n = ` the number of unique variables. **Note:** for `n > 0` variables there exist 2<sup>n</sup> possible truth assignments, and each assignment can be represented by a binary number `m < n`. For example, if `n = 1, m = {0, 1}` and one-variable expression can have 2 possible assignments: `x = F` (represented by 0) or `x = T` (represented by 1). Similarly, if `n = 2, m = {0: 00, 1: 01, 2: 10, 3: 11}`, which correspond to all possible truth assignments of an expression with 2 variables.

* Assign values

We 'flip the switch from the assignment from 1 to 0, representing on/off or true/false. The value is past on to all the instances of the variable.

* Evaluation

Recursive evaluation from the root, down to the leaves.

# Source files

* **functions.c**: bunch of helping function, some of which (`string_legth`, `power`) can be achieved through lib inclusion, the rest are specific to current package.

* **stack.c**: a simple implementation of the [stack](https://en.wikipedia.org/wiki/Stack_%28abstract_data_types%29) data structure with its data type hardcoded as a string.

* **circuit_stack.c** a simple implementation of the [stack](https://en.wikipedia.org/wiki/Stack_%28abstract_data_types%29) data structure with its data type hardcoded as a circuit, where circuit is a data structure included in the package. *[adding in 2020: one could have just implemented a generic stack. One might go ahead and do that at some point :) ]*

* **postfix.c**: simple implementation of the Shanting-Yard algorithm. Comments added where non trivial modifications have been made.

## circuit.c

Implementation of a data structure suspiciously resembling a 'normal' [binary tree](https://en.wikipedia.org/wiki/Binary_tree), where logic gates are treated as internal nodes and variables are treated as leaves. Note that operation *not* takes only one argument: so, internal nodes corresponding to a *not* gate have only a right child.

**build(char\* post):** builds a circuit from a postfix of a logic expression much like an arithmetic expression tree would have been built from a postfix of an arithmetic expression.

**set_switch(circuit c, circuit\* input):** input is the assignment of values to the variables in the circuit c. The function recursively locates the variables and sets the switch on or off (ie: 0 or 1)

**create_switch(char\* assign, int n):** simply parses a string of form `x: T; y: F` to an array of one-node circuits with information of what the ith value should be, that will be later fed into set_switch() function

**eval_circ(circuit c):** recurisve evaluation of the circuit, starting at the root (or the last set gate), and tracing down to leaves, assining the switches that are already created and set

## main.c

for each provided case, main() calls the run(expression, assgn) function, which calculates the postfix of the given expression and either tests the assignment or loops through is all possible truth assignments.

**evaluate(char\* post, char\* assign):** simply builds the circuit from postfix and sets the variables to the given assignment.

**count(int i, int length, char\* var_names):** implicitly converts i to binary and returns the truth assignment corresponding to i. *length* and *var_name* are used to format answer in a human-friendly way.

# Compiling

There is an included makefile for convenience. To use it, hit on the terminal

	make
	make run
	make clean

equivalent to:

	gcc main.c -o main
	./main
	rm main

# Disclaimer

* I am using `==` and `!=` for string comparison, which is not exactly a good practice. However, it is working out for this particular task and keeps code lighter on the eye

* It is possible that your gcc compiler will throw a `seg fault` straight away. I would look to increase the allocated memories.
