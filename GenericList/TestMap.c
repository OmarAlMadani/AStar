//
//  TestMap.c
//  GenericList
//
//  Created by Omar AlMadani on 18/11/2016.
//  Copyright © 2016 Omar AlMadani. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "map.h"




int main() {
    
    int option =0;
    char str[20];
    char str2[20];
    char str3[100];
    
  printf( "Welcome to the application\n");
  printf( "Main Menu :\n");
  printf( "1.find a specific path \n");
  printf( "2.exit \n");  
  printf( "please enter your choice : ");
  scanf("%d",&option);

    
    switch(option) {
            
        case 1  :
            printf( "Enter the starting city :");
            scanf("%s",str);
            
            printf( "Enter the targeted city :");
            scanf("%s",str2);
            
            printf( "Enter your file path :");
            scanf("%s",str3);
            
            if (avilabitity (str3, str)== 0 ||avilabitity (str3, str2)== 0 ) {
                printf( "City doesn't exist") ;
            }
            else{
                createMap(str,str2,str3);
            }
            break;
        case 2 :
            exit(1);
            
        default :
            printf( "not a valid choice") ;

        return 0 ;
    }
}

