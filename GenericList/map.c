//
//  map.c
//  GenericList
//
//  Created by Omar AlMadani on 18/11/2016.
//  Copyright © 2016 Omar AlMadani. All rights reserved.
//

#include "map.h"
#include "status.h"
#include "List.h"
#include <string.h>


/** Calculates the cost of distance from the beginnig and the distance to goal of a specific city.
 * @param c is of type City
 * @return the value of h + the value of g
 */
int cost(City * c){
    return c->h + c->g;
}
/** Calculates the distance between two neighbours
 * @param n1 is the first neighbour city
 * @param n2 is the second neighbour city
 * @return the resulted substraction of city 2 from city 1
 */
int compDistance(void * n1, void * n2){
    return ((Neighbour*)n1)->dist - ((Neighbour*)n2)->dist;
}
/** Calculates the remaining distance between two cities
 * @param c1 is the first city
 * @param c2 is the second city
 * @return the resulted substraction of city 2 from city 1
 */
int compRemDistance(void * c1, void * c2){
    return (((City *)c1)->h - ((City *)c2)->h);
}
/** Function to compare two elements (strings) : based on strcmp
* @param s1 the first string to compare
* @param s2 the second string to compare
* @return <0 if s1 is less than s2
* @return 0 if s1 equals s2
* @return >0 otherwise
 */
int compString (void * s1, void * s2) {
    return (int)strcmp(((City *)s1)->name, ((City *)s2)->name);
}
/** Calculates the cost of two difrient cities.
 * @param c1 is a City
 * @param c2 is another City
 * @return the resulted substraction of the cost of city 2 from city 1
 */
int compCity (void * c1, void * c2) {
    City * n1 = (City *)c1;
    City * n2= (City *)c2;
    return cost(n1)-cost(n2);
}
/** Structure creation of a city.
 * @param cityname is the name of the newly created city
 * @param latitude is the latitude value of this city
 * @param longitude is the longitude value of this city
 * @return the new city
 */
City* createCity(char* cityname,int latitude,int longitude){
    
    City* ct = (City*)malloc(sizeof(City));
    if (!ct) return 0;
    strcpy(ct->name, cityname);
    ct->latitude=latitude;
    ct->longitude=longitude;
    ct->h=9999;
    ct->Neighbour = newList(compDistance, displayCity);
    ct->Neighbour->comp=compDistance;
    
    return ct ;
    
}
/** Structure creation of a Neighbour city.
 * @param city is the name of the city related to the created neighbour
 * @param distance is the distance from the neighbour to this city
 * @return the new neighbour city
 */
Neighbour* createNeighbour(City* city,int distance){
    
    Neighbour * n = (Neighbour *) malloc(sizeof(Neighbour));
    n->name = city;
    n->dist = distance;
    return n;

}
/** display a list  of cities with thier latitude and longitude and the number of neighbours  .
 */
void displayCity (void * e){
    City * c = (City *)e;
    printf("%s %d %d %d\n", c->name, c->latitude,c->longitude,c->Neighbour->nelts);
    forEach(c->Neighbour, displayNeighbours);
}
/** display a list  of  distancess of the neighbour cities  .
 */
void displayNeighbours(void * e){
    Neighbour * n = (Neighbour *)e;
    printf("%d\n",n->dist);
}
/** tests whether the list contains given element (O(N)).
 * @param l the list
 * @param name the searched element
 * @return 0 if element is not found in list
 * @return Null if element is at the head of the list (no predecessor)
 * @return (a pointer to) the predecessor of the search element otherwise
 */
City * checkCity(List * l,char name[20]){
    if(!l->head) return NULL;
    Node * current = l->head;
    while(current){
        
        if(strcmp(((City *)(current->val))->name, name) == 0){
            return current->val;
        }
        current=current->next;
    }
    return 0;
}
/** Read the France.txt file and store the results into a :ist
 * @param filepath is the file that the user wants to read
 * the numbers of each line read is stored into the variable called line
 * if the line had 3 then that line variables cerate a new city if it contains 2 then creates a new neighbour.
 * @return the resulted list
 */
List* loadFile(char filepath[200]) {
    
    FILE * myFile;
    myFile = fopen(filepath, "r");
    if (myFile== NULL)
    {
        printf("can not open file \n");
        return NULL;
    }
    char ch[20];
    int ch1;
    int ch2;
    City * ct = (City *)malloc(sizeof(City));
    List * cities = newList(compString, displayCity);
    rewind(myFile);
    int line =0;

    while(!feof(myFile)){
        
        line = fscanf(myFile,"%s %d %d\n", ch, &ch1, &ch2);
        City * existingCity = checkCity(cities, ch);
        
        if (line == 3){
            if(existingCity == 0){
                ct = createCity(ch, ch1, ch2);
                addList(cities, ct);
            }else{
                ct = existingCity;
                ct->latitude = ch2;
                ct->longitude = ch2;
            }
        }
        
        else if (line == 2){
            Neighbour * nt = (Neighbour *)malloc(sizeof(Neighbour));
            if (existingCity==0){
                City * neighbourcity = createCity(ch, -1, -1);
                addList(cities, neighbourcity);
                nt = createNeighbour(neighbourcity,ch1);
                addList(ct->Neighbour, nt);
                
            }else{
                nt=createNeighbour(existingCity, ch1);
                addList(ct->Neighbour, nt);
            }
        }
    }
    
    fclose(myFile);
    
    return cities;
    
   }
/** Creates the shortest path between the two cities insreted in the parameters
 * @param city1 is the starting city
 * @param city2 is the goal city
 * @param fliepath to be used for the previuos functionn to read for the file
 * we start from the city1 that was selected and we store this value in a List called Open and every time we move to the next city we take the value and store it in the Closed list until we reach the goal city. this will result with a the shortest list to be shown to the user.
 */
void createMap(char city1[20],char city2[20],char filepath[200]){
    
    List * cities = loadFile(filepath);
    List * OPEN = newList(compCity, displayCity);
    List * CLOSED = newList(compString, displayCity);
    City * start = checkCity(cities, city1);
    City * goal = checkCity(cities, city2);
    Node * tmp = NULL;
    
    addList(OPEN, start);
    start->h = 0;
    start->g=compRemDistance(start, goal);
    
    while(OPEN->head){
        void * e;
        remFromListAt(OPEN, 1, &e);
        addList(CLOSED, e);
        City * n = (City *) e;
        
        if(n == goal){
             printf(" -- please note that the path is in reversed order ( from the distation back to the goal) --");
            printf("\n");
            while(n){
               
                displayPath(n);
                n = n ->backpointer;
            }
            printf("\n");
            
        }
        
        tmp = n->Neighbour->head;
        
        while(tmp){
            
            City * succ = ((Neighbour *)tmp->val)->name;
            int distance =((Neighbour *)tmp->val)->dist;
            int distance_so_far = n->h + distance;
            
            if((isInList(OPEN, succ)!=0) ||
               ((isInList(CLOSED, succ)!=0) &&
                (distance_so_far > succ->h)))
            {
                tmp = tmp->next;
            }
            else{
                if(isInList(OPEN, succ)!=0){
                    remFromList(OPEN, succ);
                }
                if(isInList(CLOSED, succ)!=0){
                    remFromList(CLOSED, succ);
                }
                succ->h = distance_so_far;
                succ->backpointer = n;
                addList(OPEN, succ);
                tmp = tmp->next;
            }
            
        }
        
    }
    
    printf("load failed");
   

}
/** display the shortest path to get to the goal city from the begining but the path will be displayed in reverse.
 */
void displayPath (void * e){
    City * c = (City *)e ;

    printf("%s \n",c->name);
}
/** Checks the avilabitity of the city incase the user enters a value that is not in the map we have.
 * @param filepath to load the file into a list to be checked
 * @param name name of the city that the user entered
 * @return int =0 if its not there otherwise returns 1
 */
int avilabitity (char filepath[100], char name[20]){
    int available =0;
    List * l = loadFile(filepath);
    if (checkCity(l, name)==NULL){
       return available;
    }
return available = 1 ;
}







