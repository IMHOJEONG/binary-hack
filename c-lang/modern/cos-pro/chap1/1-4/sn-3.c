// 6
char v[32] = "123456789";
int one, two, three;

sscanf(v, "%d%d%d", one, two, three)

char result[32];
snprintf(result, sizeof(result),
    "%d,%d,%d",
    one, two, three
);

// 7
int v = 255; 
char result[32];

snprintf(
    result, sizeof(result),
    "dec:%d hex:%x oct:%o",
    v, v, v 
);

// 8 
double v = 3.141592
char result[32];
snprintf(result, 
    sizeof(result),
    "%2f",
    v
);

