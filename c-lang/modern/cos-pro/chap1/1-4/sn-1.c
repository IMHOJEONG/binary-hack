

int main() {

    // 1
    int n = 42;
    char result[10];
    snprintf(result, sizeof(result), "%05d", n);
    
    // 2 
    int n = 10;
    char result[10];
    snprintf(result, sizeof(result), "%+d", n);
    
    // ------

    
}



