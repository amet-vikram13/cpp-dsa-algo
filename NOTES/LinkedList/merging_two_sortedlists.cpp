/*
  Merge two sorted lists A and B as one linked list
  Node is defined as 
  struct Node
  {
     int data;
     struct Node *next;
  }
*/
Node* MergeLists(Node *headA, Node* headB)
{
    
    struct Node * newhead;
    if(headA==NULL && headB==NULL)
        return headA;
    else
    {
        
        if(headA==NULL || headB==NULL)
            return ((headA!=NULL) ? (headA) : (headB));
        else
        {
            struct Node * list; struct Node * lnxt;
            
            // Initializing final sorted LinkedList
            if(headA->data==headB->data)
            {
                list = new struct Node;
                list->data = headA->data;
                lnxt = NULL;
                list->next = NULL; 
                newhead = list;
            }
            else
            {
                list = new struct Node; lnxt = new struct Node;
                list->data = ((headA->data < headB->data) ? (headA->data) : (headB->data));
                lnxt->data = ((headA->data > headB->data) ? (headA->data) : (headB->data));
                list->next = lnxt; lnxt->next = NULL;
                newhead = list;
            }

            // Traversing the two given sorted linkedlist
            while(headA->next!=NULL && headB->next!=NULL)
            {
                headA = headA->next;
                headB = headB->next;
                
                
                
                // If values from both list are equal then only one new node
                if(headA->data==headB->data)
                {
                  struct Node * lnew1 = new struct Node;
                  lnew1->data = headA->data;

                  
                  if(lnxt!=NULL)
                  {
                    if(lnxt->data < lnew1->data)
                    {
                      
                      lnew1->next = NULL;
                      lnxt->next = lnew1;
                      list = lnxt;
                      lnxt = lnew1;

                    }
                    else if(lnxt->data > lnew1->data)
                    {
                      if(list->data < headA->data)
                      {
                        
                        lnew1->next = lnxt;
                        list->next = lnew1;
                        list = lnew1; 
                      }
                    }
                  }
                  else
                  {
                    if(list->data < lnew1->data)
                    {
                      
                      lnew1->next = NULL;
                      lnxt = lnew1;
                      list->next = lnxt;
                    }
                  }
                }
                // If values from both list are different then two new nodes
                else
                {
                  struct Node * lnew1 = new struct Node;
                  struct Node * lnew2 = new struct Node;
                  lnew1->data = ((headA->data < headB->data) ? (headA->data) : (headB->data));;
                  lnew2->data = ((headA->data > headB->data) ? (headA->data) : (headB->data));;
                  
                  
                  if(lnxt!=NULL)
                  {
                    if(lnxt->data < lnew1->data)
                    {
                      lnew1->next = NULL;
                      lnxt->next = lnew1;
                      list = lnxt;
                      lnxt = lnew1;

                    }
                    else if(lnxt->data > headA->data)
                    {
                      if(list->data < headA->data)
                      {
                        lnew1->next = lnxt;
                        list->next = lnew1;
                        list = lnew1;
                      }
                    }

                    if(lnxt->data < lnew2->data)
                    {
                      lnew2->next = NULL;
                      lnxt->next = lnew2;
                      list = lnxt;
                      lnxt = lnew2;

                    }
                    else if(lnxt->data > lnew2->data)
                    {
                      lnew2->next = lnxt;
                      list->next = lnew2;
                      list = lnew2;
                    }
                  }
                  else
                  {
                    if(list->data < lnew1->data)
                    {
                      lnew1->next = NULL;
                      lnxt = lnew1;
                      list->next = lnxt;
                    }    
                  }
               }
            }

            // Taking rest of elements
            while(headA->next!=NULL)
            {
              headA = headA->next;
              struct Node * lnew1 = new struct Node;
              lnew1->data = headA->data;
              
              if(lnxt->data < lnew1->data)
              {
                lnew1->next = NULL;
                lnxt->next = lnew1;
                list = lnxt;
                lnxt = lnew1;

              }
              else if(lnxt->data > lnew1->data)
              {
                if(list->data < headA->data)
                {
                  
                  lnew1->next = lnxt;
                  list->next = lnew1;
                  list = lnew1; 
                }
              }
            }

            // Taking rest of elemets
            while(headB->next!=NULL)
            {
              headB = headB->next;
              struct Node * lnew1 = new struct Node;
              lnew1->data = headB->data;
              
              if(lnxt->data < lnew1->data)
              {
                lnew1->next = NULL;
                lnxt->next = lnew1;
                list = lnxt;
                lnxt = lnew1;

              }
              else if(lnxt->data > lnew1->data)
              {
                if(list->data < headA->data)
                {
                  
                  lnew1->next = lnxt;
                  list->next = lnew1;
                  list = lnew1; 
                }
              }
            }
        }
    }
    return newhead;
}



                
          
      
  


