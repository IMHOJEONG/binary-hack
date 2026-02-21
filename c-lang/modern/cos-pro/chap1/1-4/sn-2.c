

int main() {

    // 3 
    char data[32] = "2026 2 5";
    
    int year, month, day;
    
    sscanf(data, "%d %d %d", &year, &month, &day);
    
    char result[32];
    snprintf(result, sizeof(data), 
        "%04d-%02d-%02d",
        year,
        month,
        day
    );
    
    // 4 
    int total = 3661;
    int hour = (total / 3600);
    int minute = (total / 3600 / 60);
    int second = (total / 3600 % 60);
    char result[32];
    snprintf(result, sizeof(result),
        "%02d:%02d:%02d", 
        hour,
        minute,
        second
    );
    
    
    // 5 
    int x = -3, y = 10;
    char result[32];
    snprintf(result, sizeof(result), 
        "\"( %+d , %+d )\"",
        x, y
    );


}    
