int main() {
    double temps[4];  // Now reading 4 double temperatures
    int pipefd[2];  // Pipe for communication between parent and child
    pid_t pid;

    // Create a pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Fork a child process
    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {  // Child process: will read from pipe and process temperatures
        close(pipefd[1]);  // Close the write end of the pipe in the child process

        // Read 4 temperatures from the pipe
        if (read(pipefd[0], temps, sizeof(temps)) == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }

        close(pipefd[0]);  // Close the read end after reading

        // Process each temperature and determine the system's action
        for (int i = 0; i < 4; i++) {
            const char* temp_status = get_status(temps[i]);
            const char* system_action = determine_system_action(temp_status);
            printf("Temperature: %.4f Status: %s System Action: %s\n", temps[i], temp_status, system_action);
        }

    } else {  // Parent process: will write temperatures to the pipe
        close(pipefd[0]);  // Close the read end of the pipe in the parent process

        // Example temperatures to send via the pipe (as double, 4 decimal places)
        temps[0] = 72.5432;
        temps[1] = 85.3298;
        temps[2] = 50.9847;
        temps[3] = 65.1234;

        // Write the 4 temperatures (as double) to the pipe
        if (write(pipefd[1], temps, sizeof(temps)) == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }

        close(pipefd[1]);  // Close the write end after writing
        wait(NULL);  // Wait for the child process to finish
    }

    return 0;
}