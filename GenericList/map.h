//
//  map.h
//  GenericList
//
//  Created by Omar AlMadani on 18/11/2016.
//  Copyright © 2016 Omar AlMadani. All rights reserved.
//

#ifndef map_h
#define map_h
#include <stdio.h>
#include "List.h"
#include "status.h"

/** City structure
 */
typedef struct City {
    char name[100];
    int latitude;
    int longitude;
    int h ;
    int g;
    List* Neighbour;
    struct City * backpointer;
    
}City;

/** Neighbour structure
 */
typedef struct Neighbour {
    City* name;
    int dist;
}Neighbour;

/** Structure creation of a city.
 * @param cityname is the name of the newly created city
 * @return the new city
 */
City* createCity(char* cityname,int,int);
/** Structure creation of a Neighbour city.
 * @return the new neighbour city
 */
Neighbour* createNeighbour(City*,int);
/** display a list  of  distancess of the neighbour cities  .
 */
void displayCity (void * e);
/** display a list  of cities with thier latitude and longitude and the number of neighbours  .
 */
void displayNeighbours(void * e);
/** tests whether the list contains given element (O(N)).
 * @param l the list
 * @param name the searched element
 * @return 0 if element is not found in list
 * @return Null if element is at the head of the list (no predecessor)
 * @return (a pointer to) the predecessor of the search element otherwise
 */
City * checkCity(List * l,char name[20]);
/** Read the France.txt file and store the results into a :ist
 * @param filepath is the file that the user wants to read
 * the numbers of each line read is stored into the variable called line
 * if the line had 3 then that line variables cerate a new city if it contains 2 then creates a new neighbour.
 * @return the resulted list
 */
List* loadFile(char  filepath[200]);
/** Creates the shortest path between the two cities insreted in the parameters
 * @param city1 is the starting city
 * @param city2 is the goal city
 * @param filepath to be used for the previuos functionn to read for the file
 * we start from the city1 that was selected and we store this value in a List called Open and every time we move to the next city we take the value and store it in the Closed list until we reach the goal city. this will result with a the shortest list to be shown to the user.
 */
void createMap(char city1[20],char city2[20],char filepath[200]);
/** display the shortest path to get to the goal city from the begining but the path will be displayed in reverse.
 */
void displayPath (void * e);
/** Checks the avilabitity of the city incase the user enters a value that is not in the map we have.
 * @param filepath to load the file into a list to be checked
 * @param name name of the city that the user entered
 * @return int =0 if its not there otherwise returns 1
 */
int avilabitity (char filepath[100], char name[20]);


#endif /* map_h */
