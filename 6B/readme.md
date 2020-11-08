A multi-thread version of 5B. The program splits the original file into small files by '\n' or '\r'. Small files are stored in ./temp, and will be processed by child processes. After all of them are done, the parent process will merge the output files together to form a final output.

The program takes input.csv as input, and output.bin is the binary encode result, output.csv is the decode result.