The program simulates the process of a COVID-19 monitor.
To simulate the process, firstly we need to input the information of buildings, including their geometry positions (double X, double Y), BuildingIDs (int BID), and UnitIDs (int UID).
Secondly we need to input the information of persons, including their IDs (int PID) and whether they are inflected (0/1).
Thirdly we need to input the place and time that one person goes, this simulated the process of recieving message from IoT terminal. We use BuildingID and UnitID to represent a place that the person goes.
After that we can change a person's status (inflected or not), or ask for one's trace in the last 14 days, or the number of inflected persons in 1km around a given geometry position.
Besides, we use linked list structure to store the data, so that a least amount of memory is needed.

A simple example:
        Input 1 to add building message;
        Input 2 to add person message;
        Input 3 to change one person's status;
        Input 4 to report the place a person goes;
        Input 5 to ask one's trace;
        Input 6 to ask the number of Inflected persons;
        Input -1 to quit.
Input the operation number: 1
Please input the geometry position X,Y of this building, and the BuildingID and UnitID:
1 1 1 1
Done.
Input the operation number: 1
Please input the geometry position X,Y of this building, and the BuildingID and UnitID:
1 2 1 2
Done.
Input the operation number: 1
Please input the geometry position X,Y of this building, and the BuildingID and UnitID:
2 1 2 1
Done.
Input the operation number: 1
Please input the geometry position X,Y of this building, and the BuildingID and UnitID:
2 2 2 2
Done.
Input the operation number: 2
Please input the person's ID, and a flag number for his status, 0 for not inflected and 1 for inflected:
123 1
Done.
Input the operation number: 2
Please input the person's ID, and a flag number for his status, 0 for not inflected and 1 for inflected:
234 1
Done.
Input the operation number: 4
Please input the person's ID, the date of today, and the BuildingID and the UnitID of the building he goes:
123 1 1 1
Done.
Input the operation number: 4
Please input the person's ID, the date of today, and the BuildingID and the UnitID of the building he goes:
123 1 1 2
Done.
Input the operation number: 4
Please input the person's ID, the date of today, and the BuildingID and the UnitID of the building he goes:
234 1 2 2
Done.
Input the operation number: 5
Please input the person's ID, and the date of today:
123 1
Day: 1, BuildingID: 1, UnitID: 2;
Day: 1, BuildingID: 1, UnitID: 1;
Input the operation number: 5
Please input the person's ID, and the date of today:
234 1
Day: 1, BuildingID: 2, UnitID: 2;
Input the operation number: 6
Please input the geometry position X,Y, and the date of today:
1 1 1
Inflected: 1
Input the operation number: 6 
Please input the geometry position X,Y, and the date of today:
1 2 1
Inflected: 2
Input the operation number: 6
Please input the geometry position X,Y, and the date of today:
2 2 1
Inflected: 2
Input the operation number: -1
