#include <stdio.h>
#include <stdlib.h> // Imported for "EXIT_FAILURE" and "EXIT_SUCCESS"
#include <string.h> // Imported for "strtok"
#include <math.h>


#define  LINE_MAX_SIZE 100
#define INPUT_DELIMS " \t\r\n"
#define errorm "‫‪ERROR\n‬‬"
#define maxStars 20

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

double gendub(double len,double flag, char *val, int commas) {
    /*
     * get the next double out of the char
     */
    if (len > 9 || flag < 0) {
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
        temp = gendub(length, flag, value, 1);
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
    char num[LINE_MAX_SIZE];
    double flag = getLine(num);
    double toReturn;
    char *val = NULL;
    int i = 0;
    val = strtok(num, INPUT_DELIMS);
    while (val != NULL) {
        size_t length = strlen(val);
        toReturn = gendub(length, flag, val, 0);
        if (i > 0 || toReturn < 0) {
            return -1;
        }
        i++;
        val = strtok(NULL, INPUT_DELIMS);
    }
    return toReturn;
}

double sumArray(double * array){
    /*
     * return the sum of an array at len of a Max Line
     */
    double sum =0 ;
    for (int i=0;i<=LINE_MAX_SIZE;i++){
        sum+=array[i];
    }
    return sum;
}
void normArray(double *array){
    double  sum = sumArray(array);
    for (int i=0;i<LINE_MAX_SIZE;i++){
        array[i]=array[i]/sum;
    }
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
    normArray(array);

}

int phi(int t ,int len){
    return t+floor(len/2);
}

double convoltionArg(double *h, double * g, int cord , int lenh,int leng){
    int start=-ceil(leng/2);
    int end=floor(leng/2);
    double sum=0;
    for (start;start<end;start++){
        if (!(phi(cord-start,lenh)<=0 || phi(start,leng)<=0 ||phi(cord-start,lenh)>=lenh||phi(start,leng)>=leng)){
            sum+=h[phi(cord-start,lenh)]*g[phi(start,leng)];
        }
    }
    return sum;
}

int convoltion(double *h, double *g, double *output,int lenh,int leng ){
    int start=-ceil(lenh/2)-1;
    int end=floor(lenh/2)-1;
    for (int i=0;start<end;start++){
        output[i]=convoltionArg(h,g,start,lenh,leng);
        i++;
    }
}


//double conArg(double* h,double* g,int cord){
//    double sum=0;
//    for (int i=0;i<=cord;i++){
//        sum+=h[i]*g[cord-i];
//    }
//    return sum;
//}
//
//
//void conv(double* h, double* g,double* output){
//    for (int i=0;i<LINE_MAX_SIZE;i++){
//        output[i]=conArg(h,g,i);
//    }
//}
double findMax(double * array ,int len){
    double output=0;
    for (int i=0 ;i<len ;i++){
        if (array[i]>output);
        output=array[i];
    }
    return output;
}

//double getStars(double max ,double arg){
//    double s =arg/max;
//    return floor(s);
//}


//double  rou(double arg){
//    return round(arg*1000)/1000;
//}

int main(int argc, const char *argv[]) {
    double h[LINE_MAX_SIZE] = {0};
    double g[LINE_MAX_SIZE] = {0};
    double len1 = parseLine(h);
    if(len1<0){
        fprintf(stdout, "%s", errorm);
        return EXIT_FAILURE;
    }
    double len2 = parseLine(g);
    if(len2<0){
        fprintf(stdout, "%s", errorm);
        return EXIT_FAILURE;
    }
    if(len1<len2){
        fprintf(stdout, "%s", errorm);
        return EXIT_FAILURE;
    }
    double rooms = getChar();
    if (rooms<0){
        fprintf(stdout, "%s", errorm);
        return EXIT_FAILURE;
    }
    centralizedArray(h,len1);
    centralizedArray(g,len2);
    double output[LINE_MAX_SIZE]={0};
    for (int i=0;i<rooms;i++){
        convoltion(g,h,output,LINE_MAX_SIZE,LINE_MAX_SIZE);
        centralizedArray(output,LINE_MAX_SIZE);
//        copy_arr(output,g,LINE_MAX_SIZE);
    }
//    double max=findMax(output,LINE_MAX_SIZE);
    for (int i = 0; i < 100; i++) {
        printf("%0.3f\n", output[i]);
    }

}