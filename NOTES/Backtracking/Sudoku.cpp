bool findUnAssigned(vector<vector<char> > A,int& row,int& col)
{
    for(row=0;row<A.size();row++)
        for(col=0;col<A.size();col++)
            if(A[row][col]=='.')
                return true;
    return false;
}

bool checkGrid(vector<vector<char> > A,int row,int col,char num)
{
    for(int j=0;j<A.size();j++)
        if(A[row][j]==num)
            return false;
    
    for(int i=0;i<A.size();i++)
        if(A[i][col]==num)
            return false;
    
    row = row - row%3;
    col = col - col%3;
    
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            if(A[row+i][col+j]==num)
                return false;
    
    return true;
}

bool _solveSudoku(vector<vector<char> > &A)
{
    int row,col;
    
    if(!findUnAssigned(A,row,col))
        return true;
    
    for(int num=1;num<=9;num++)
    {
        if (checkGrid(A,row,col,'0'+num))
        {
            A[row][col] = '0'+num;
            
            if(_solveSudoku(A))
                return true;
            
            A[row][col] = '.';
        }
    }
    
    return false;
}

void Solution::solveSudoku(vector<vector<char> > &A) {
    // Do not write main() function.
    // Do not read input, instead use the arguments to the function.
    // Do not print the output, instead return values as specified
    // Still have a doubt. Checkout www.interviewbit.com/pages/sample_codes/ for more details
   _solveSudoku(A);
}
