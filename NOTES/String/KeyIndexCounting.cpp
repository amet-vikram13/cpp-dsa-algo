 #include <bits/stdc++.h>
using namespace std;

/*

String: Sequence of characters (immutable).

Length: Number of characters.
Indexing: Get the ith character.
Substring extraction: Get a contiguous subsequence of characters.
String concatenation: Append one character to end of another string.

Proposition: Key-indexed counting uses ~ 11N + 4R array accesses to 
             sort N items whose keys are integers between 0 and R-1

            : Key-indexed counting uses extra space proportional to N+R

            : Key-indexed counting is stable.

            : Also known as Counting sort

Points to be noted:
1. Counting sort is efficient if the range of input data is not significantly greater than the number of 
   objects to be sorted. Consider the situation where the input sequence is between range 1 to 10K and 
   the data is 10, 5, 10K, 5K.
2. It is not a comparison based sorting. It running time complexity is O(n) with space proportional to 
   the range of data.
3. It is often used as a sub-routine to another sorting algorithm like radix sort.
4. Counting sort uses a partial hashing to count the occurrence of the data object in O(1).
5. Counting sort can be extended to work for negative inputs also.
*/

struct KeyValue
{
	int key;
	string value;
};


class KeyIndexCounting
{
	private:
		int N;
		int R;
		int* count;
		KeyValue* aux;

	public:
		KeyIndexCounting(int r,KeyValue a[],int n)
		{
			N = n;
			
			// VIP
			// R is the number of space of charaters allowed.
			// If value of characters range from 1...R ,
			// we need count array from 1...R+1 i.e C array of lenght R+2. 
			R = r; 
			
			count = new int[R+2];
			aux = new KeyValue[N];

			for(int i=0;i<R+2;i++)
				count[i] = 0;

			for(int i=0;i<N;i++)
				count[a[i].key+1]++;    // How many values with a particular Key are there.
			                            // VIP Step we are increasing the count value for key+1 and
			                            // NOT key itself.

			for(int i=0;i<R+1;i++)
				count[i+1] += count[i];  // Now count[i] represents number of keys 
			                             // less than key i or the start index for 
										 // key i in aux array.
										 // <as count[i] initially stored count of key+1 and NOT key.>

			for(int i=0;i<N;i++)
				aux[count[a[i].key]++] = a[i];  // Now placing a[i] items at their appropriate positions
			                                    // with increasing count[a[i].key] after every placement.

			for(int i=0;i<N;i++)
				a[i] = aux[i];

			delete[] aux;

			for(int i=0;i<N;i++)
				cout << a[i].value << " " << a[i].key << endl;
		}
};


int main()
{
	KeyValue a[] = {{2,"Anderson"},{3,"Brown"},{3,"Davis"},{4,"Garcia"},{1,"Harris"},{3,"Jackson"},{4,"Johnson"},
	                {3,"Jones"},{1,"Martin"},{2,"Martinez"},{2,"Miller"},{1,"Moore"},{2,"Robinson"},{4,"Smith"},
	                {3,"Taylor"},{4,"Thomas"},{4,"Thompson"},{2,"White"},{3,"Williams"},{4,"Wilson"}};

	KeyIndexCounting kis(4,a,20);

	return 0;

}