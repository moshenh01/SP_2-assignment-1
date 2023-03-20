#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AdptArray.h"



typedef struct AdptArray_ 
{
    int ArrSize;
    
    PElement* pElemArr;//array of pointers to elements
    DEL_FUNC delFunc;
    COPY_FUNC copyFunc;
    PRINT_FUNC printFunc;
}AdptArray;


PAdptArray CreateAdptArray(COPY_FUNC cf, DEL_FUNC df ,PRINT_FUNC pf){

    PAdptArray parr = (PAdptArray)malloc(sizeof(AdptArray));//allocate memory for the array struct .
    if(parr == NULL)//the allocation failed.
        return NULL;

    parr->ArrSize = 0;//initialize the array size to 0.
    parr->pElemArr = (PElement*)malloc(sizeof(PElement));//allocate memory for the array of pointers to elements.
    if(parr->pElemArr == NULL)//the allocation failed.
    {
        free(parr);//free the memory allocated for the array struct.
        return NULL;
    }
    parr->pElemArr = NULL;//initialize the first element of the array of pointers to elements to NULL.
    parr->delFunc = df;//initialize the delete function.
    parr->copyFunc = cf;//initialize the copy function.
    parr->printFunc = pf;//initialize the print function.
    return parr;
}

void DeleteAdptArray(PAdptArray parr){
    int i;
    if(parr == NULL)//the array is empty.
        return;
    for(i = 0; i < parr->ArrSize; i++)//loop over the array of pointers to elements.
    {
        if(parr->pElemArr[i] != NULL)
            parr->delFunc(parr->pElemArr[i]);//delete the element pointed by the current pointer.
    }
    free(parr->pElemArr);//free the memory allocated for the array of pointers to elements.
    free(parr);//free the memory allocated for the array struct.
}

Result SetAdptArrayAt(PAdptArray parr, int indx, PElement elem){

    if(parr == NULL)//the array is empty.
        return FAIL;
    if(indx < 0){//the index is negative.
        printf("The index is negative");
        return FAIL;
    }
    if(indx >= parr->ArrSize)//the index is out of bounds.
    {
        PElement* temp = (PElement*)realloc(parr->pElemArr, (indx+1)*sizeof(PElement));//allocate memory for the array of pointers to elements.
        if(temp == NULL)//the allocation failed.
            return FAIL;
        parr->pElemArr = temp;//update the array of pointers to elements.
        parr->pElemArr[indx] = parr->copyFunc(elem);//copy the element to the array.
        parr->ArrSize = indx+1;//update the array size.
        return SUCCESS;
    }
    parr->delFunc(parr->pElemArr[indx]);//delete the element pointed by the pointer at the given index.
    parr->pElemArr[indx] = parr->copyFunc(elem);//copy the new element to the array.
    return SUCCESS;

}

PElement GetAdptArrayAt(PAdptArray parr, int indx){
    if(parr == NULL)//the array is empty.
        return NULL;
    if(indx < 0)//the index is negative.
        return NULL;
    if(indx >= parr->ArrSize)//the index is out of bounds.
        return NULL;
    if(parr->pElemArr[indx] == NULL)//the element is empty.
        return NULL;
    return parr->copyFunc(parr->pElemArr[indx]);//return the element pointed by the pointer at the given index.
}
int GetAdptArraySize(PAdptArray parr){
    if(parr == NULL)//the array is empty.
        return -1;
    return parr->ArrSize;//return the array size.
}
void PrintDB(PAdptArray parr){
    int i;
    if(parr == NULL){//the array is empty.
        printf("The array is empty\n");
        return;
    }
    // printf("start printing the array\n");
    // printf("the array size is %d\n", parr->ArrSize);
    for(i = 0; i < parr->ArrSize; i++)//loop over the array of pointers to elements.
    {
        if(parr->pElemArr[i] != NULL)//the element is empty.
            parr->printFunc(parr->pElemArr[i]);//print the element pointed by the current pointer.
    }
        
        
}

