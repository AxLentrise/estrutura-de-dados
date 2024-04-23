#include <stdio.h>
#include <string.h>
#define PRODUCTS 1
#define MAX 50

struct reg {
    int iCode;
    char cDesc[MAX];
    char cType;
    double dPrice;
};

struct reg readReg(void){

    struct reg product;

    printf("Enter the product code: ");
    fflush(stdin);
    scanf("%d", &product.iCode);
    printf("\nEnter the product desc: ");
    if(fgets(product.cDesc, sizeof product.cDesc, stdin) != NULL){
        product.cDesc[strlen(product.cDesc)-1] = '\0';
    }
    printf("\nEnter the product type: ");
    fflush(stdin);
    scanf("%c", &product.cType);
    printf("\nEnter the product price: ");
    fflush(stdin);
    scanf("%f", product.dPrice);

    return product;
}


int main(int argc, char **argv){

    struct reg products[PRODUCTS];
    
    for(int i = 0; i < PRODUCTS; i++){
        products[i] = readReg();
    }
    
    

    return 0;
}