

int merge(int arr[], int l,
          int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temp arrays
    int L[n1], R[n2];

    // Copy data to temp arrays
    // L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Merge the temp arrays back
    // into arr[l..r]
    // Initial index of first subarray
    i = 0;

    // Initial index of second subarray
    j = 0;

    // Initial index of merged subarray
    k = l;
    int cnt = 0;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            cnt += n1 - i;
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements
    // of L[], if there are any
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of
    // R[], if there are any
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
    return cnt;
}

// l is for left index and r is
// right index of the sub-array
// of arr to be sorted
int mergeSort(int arr[],
              int l, int r)
{
    int cnt = 0;
    if (l < r)
    {

        // Same as (l+r)/2, but avoids
        // overflow for large l and h
        int m = l + (r - l) / 2;

        // Sort first and second halves
        cnt += mergeSort(arr, l, m);
        cnt += mergeSort(arr, m + 1, r);

        cnt += merge(arr, l, m, r);
    }
    return cnt;
}

int solution(int A[], int N)
{
    // Implement your solution here
    int cnt = 0;
    cnt = mergeSort(A, 0, N - 1);
    return cnt;
}