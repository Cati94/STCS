#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Catarina Costa - Program to med and back to balance the temperture of 4 transmitors//

// Define hight and low temperature//

#define hightTemp 80.0000
#define lowTemp 60.0000

// Fuction of status of the system//

const char * get_status(double temp){
    if (temp>hightTemp){
        return "hight";
    } else if (temp <lowTemp){
        return "low";
    } else{
        return "normal";
    }
}

// Function define on/off heaters//

const char * determine_system_action(const char * tempStatus){
    if (tempStatus=="high"){
        return"off"; 
    }
    else if(tempStatus=="low"){
        return "on";
    }
    {else { return "set point ";
    }
}

// Classe Main Read tempetures and comunication Pipe //
int main(){
    double temp[4];
    int pipefd[2];
    pid_t pid; 

    // create a Pipe

    if (pipe(pipefd==1)){
        perror ("pipe");
        exit (exit_fail);
    }

    // fork//

    pid = fork ();
    if (pid == -1){
        perror("fork");
        exit(exit_fail)
    }
    if (pid==0){
        if (read(pipefd[0], temp, sizeof(temp))==-1){
        perror("read");
        exit (exit_fail);
    }
    
    }
    close (pipefd[1]);
}

// Analysing the tempeture and action system //

for (int i=0;i<4;i++){
    const char*tempStatus=get_status(temp[i]);
    const char* system_action = determine_system_action(tempStatus);
    printf("temperature: %.4f status: %s system action %s/n", temp[i], tempStatus, system_action); 
}
else{
    close(pipefd[0]);

    // write the tempetures in double on a pipe//

    if (write(pipefd[1],temp,sizeof(temp))==-1){
        perror("write");
        exit(exit_fail);
    }
    close(pipefd[1]);
    wait (NULL);
}
return 0; 
