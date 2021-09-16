#include <iostream>
#include <climits>
using namespace std;

class MinHeap
{
	private:
		int * harr;    // Heap starts at index 0
		int capacity;  // maximum size
		int heap_size; // current count (N)

		void exch(int i,int j)
		{
			int temp = harr[i];
			harr[i]  = harr[j];
			harr[j]  = temp;
		}

	public:
		//Constructor
		MinHeap(int * arr,int capacity);

		// to heapify a subtree with root at
		// given index (sink operation)
		void heapify(int i);

		int parent(int i)
		{ return (i-1)/2; }

		int left(int i)
		{	return (2*i+1); }

		int right(int i)
		{	return (2*i+2); }

		// to extract the root which is the
		// minimum element
		int extractMin();
		
		// Return the min key (key at root)
		// from min heap
		int getMin()
		{	return harr[0]; }

		int getSize()
		{	return heap_size; }

		void insertKey(int k);
};

MinHeap::MinHeap(int arr[],int n)
{
	heap_size = n;
	capacity  = n;
	harr = new int[n];

	for(int i=0;i<n;i++)
		harr[i] = arr[i];

	// building the heap from first non leaf
	// node by calling max heapify fuction
	for(int i=n/2-1;i>-1;i--)
		heapify(i);
}

void MinHeap::insertKey(int k)
{
	heap_size++;
	int i = heap_size-1;
	harr[i] = k;

	//Fix the minheap property if it is violated(swim op)
	while(i>0 && harr[parent(i)]>harr[i])
	{
		exch(i,parent(i));
		i = parent(i);
	}
}

// method to remove minimum element
// (or root) from min heap
int MinHeap::extractMin()
{
	if (heap_size<=0)
		return INT_MAX;
	if (heap_size==1)
	{
		heap_size--;
		return harr[0];
	}

	int min = harr[0];
	harr[0] = harr[heap_size--];
	heapify(0);
	return min;
}

void MinHeap::heapify(int i)
{
	int l = left(i);
	int r = right(i);
	int smallest = i;

	if (l < heap_size && harr[l] < harr[i])
		smallest = l;

	if(r < heap_size && harr[r] < harr[smallest])
		smallest = r;

	if(smallest!=i)
	{
		exch(i,smallest);
		heapify(smallest);
	}
}

// Returns count of steps needed to make 
// all elements greater than or equal to
// k by adding elements
int countMinOps(int arr[],int n,int k)
{
	// Build a minheap of array elements
	MinHeap h(arr,n);

	long int res = 0;

	while(h.getMin() < k)
	{
		if(h.getSize()==1)
			return -1;

		// Extract two minimum elements
		// and insert their sum
		int first  = h.extractMin();
		int second = h.extractMin();
		h.insertKey(first+second);
		res++; 
	}

	return res;
}

int main()
{
	int arr[] = {1,10,12,9,2,3};
	int n = sizeof(arr)/sizeof(arr[0]);
	int k = 6;
	cout<<countMinOps(arr,n,k)<<endl;
	return 0;
}