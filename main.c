#include <stdio.h>
#include <stdlib.h> // Imported for "EXIT_FAILURE" and "EXIT_SUCCESS"
#include <string.h> // Imported for "strtok"
#include <math.h>

#define  LINE_MAX_SIZE 100
#define INPUT_DELIMS " \t\r\n"


int checkValid(int d) {
    /*
     * checks if the char is 0-9
     */
    if (d < 0) {
        return -1;
    }
    if (d > 9) {
        return -1;
    }
    return 1;
}

double stof(const char *s, int len, int commas) {
    /*
     * turn the string into a double
     */
    double rez = 0, sign = 1;
    int startWithZero=0;
    if (*s == '-') {
        return -1;
    };
    for (int point_seen = 0; *s; s++) {
        if (*s == '.') {
            /*
             * checks if there is more then one dot/or it suppose to be an natural number/start with a dot
             */
            if ((point_seen == len - 1) || (point_seen == 1) || (commas == 0)) {
                return -1;
            }
            point_seen = 1;
            continue;
        };
        int d = *s - '0';
        if(startWithZero<0&&point_seen==0){ return -1;}
        if(d==0){startWithZero=-1;}
        if (checkValid(d) < 0) { return -1; }
        if (d >= 0 && d <= 9) {
            if (point_seen) sign /= 10.0f;
            rez = rez * 10.0f + (double) d;
        };
    };
    return rez * sign;
}

double getLine(char *line) {
    if (fgets(line, LINE_MAX_SIZE, stdin) == NULL) {
        fprintf(stderr, "No input\n");
        return -1;
    }
    return 1;
}

double getdub(__size_t len, double flag, char *val, int commas) {
    /*
     * get the next double out of the char
     */
    if (len > 9 || (flag < 0)) {
        return -1;
    }
    double temp = stof(val, len, commas);
    if (temp < 0) {
        return -1;
    }
    return temp;
}

double parseLine(double *toReturn) {
    /*
     * get a line from the user parse it into an array of ints
     * varify legal input
     */
    char line[LINE_MAX_SIZE];
    char *value = NULL;
    double flag = getLine(line);
    value = strtok(line, INPUT_DELIMS);
    double temp;
    size_t length=0;
    int i = 0;
    while (value != NULL) {
        //todo 0.002 3
        length = strlen(value);
        temp = getdub(length, flag, value, 1);
        if (i > 99 || temp < 0) {
            return -1;
        }
        toReturn[i] = temp;
        i++;
        value = strtok(NULL, INPUT_DELIMS);
    }
    return i;
}
void copy_arr(double source[], double target[], int items)
/*
 * copy an double array
 */
{
    for (int counter = 0; counter < items; counter++) target[counter] = source[counter];
    return;
}

double getChar() {
    /*
     * get a single char and set it into a int
     */
    char *num[LINE_MAX_SIZE];
    double flag = getLine(num);
    double toReturn;
    char *val = NULL;
    int i = 0;
    val = strtok(num, INPUT_DELIMS);
    while (val != NULL) {
        size_t length = strlen(val);
        toReturn = getdub(length, flag, val, 0);
        if (i > 0 || toReturn < 0) {
            return -1;
        }
        i++;
        val = strtok(NULL, INPUT_DELIMS);
    }
    return toReturn;
}

void centralizedArray(double *array ,int numArgs) {
    if (numArgs==LINE_MAX_SIZE){
        return;
    }
    int zeros=LINE_MAX_SIZE-numArgs;
    double copy[LINE_MAX_SIZE];
    copy_arr(array,copy,LINE_MAX_SIZE);
    for (int i=0;i<LINE_MAX_SIZE;i++){
        if(i<floor(zeros/2))array[i]=0;
        if((i>=floor(zeros/2))&&(i<floor(zeros/2)+numArgs)){
            array[i]=copy[i-(int)floor(zeros/2)];
        }

    }
}

int main(int argc, const char *argv[]) {
    double h[LINE_MAX_SIZE] = {0};
    double g[LINE_MAX_SIZE] = {0};
    double len1 = parseLine(h);
    double len2 = parseLine(g);
    double rooms = getChar();
    centralizedArray(h,len1);
    for (int i = 0; i < 100; i++) {
        printf("%f ", h[i]);
    }
    if (len1 < 0 || len2 < 0) {
        return EXIT_FAILURE;
    }

}