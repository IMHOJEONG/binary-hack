
int* solution(int arr[], int arr_len) {
    int left = 0, right = arr_len - 1;
    int idx = 0;
    int* answer = (int*)malloc(sizeof(int)*arr_len);
    while(left <= right){
        if(idx % 2 == 0){
            answer[idx] = arr[left];
            left += 1;
        }
        else{
            answer[idx] = arr[right];
            right -= 1;
        }
        idx += 1;
    }
    return answer;
}