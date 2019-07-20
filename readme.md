## Compile
`make`

### Running
`./sudoku-solver input.txt`

#### input.txt
Keep in mind, this can be called whatever you want. I've included a few example files in the `input/` directory. 

The file is a plain text list of up to 81 comma separated values. Values should be 0-9 or, ? to represent an unknown value. To convert a normal puzzle to this format, you simply read it in, left-to-right, top-to-bottom. If there are consecutive ?s this can be condensed by prepending the ? with the number of consecutive recurrances.

For example, if we wanted to put the following puzzzle into the program.

![alt text](https://i.imgur.com/PgALkPQ.png "Example sudoku.")

This is the resulting list
`5,3,2?,7,4?,6,2?,1,9,5,4?,9,8,4?,6,?,8,3?,6,3?,3,4,2?,8,?,3,2?,1,7,3?,2,3?,6,?,6,4?,2,8,4?,4,1,9,2?,5,4?,8,2?,7,9`

If your submitted file doesn't contain a valid sudoku, the application will abort and display the cause of the problem. Newlines and other whitespace will be ignored, so feel free to use it as you see fit.
