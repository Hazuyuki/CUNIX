The program uses pipes to perform inter-process communication. The father process first creates a child process for gathering the encoding results, then creates many child processes to encode the lines. They communicate with the father process with pipes. The mmap is used for decoding.

Run ./make, and output.bin is the encoded file and output.csv is the decoded file.