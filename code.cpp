/* R/GA Code for Quokka problem */ 
/* Submission of Algorithm Engineer open position */
/* Philip Stathos */

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <cmath>

using namespace std;

int get_open( ifstream& file1 )
{
    const int MAXCHARS = 255; //max # of filename characters
    char name1[MAXCHARS];

    cout << "Please enter the name of the file you wish to open: ";
    cin >> name1; //user enters file name
    
    file1.open(name1); //opens first file
    
    if ( file1.fail() ) //check for successful open
    {
        cout << "\n One of the files was not successfully opened "
             << "\n Please check that the file currently exists." << endl;
        exit(1);
    }
    else
        return 0;
}

void load_file( ifstream& file1 )
{
    //read quokka data file created from seven day census
    
    int ch, id, d, Fp, H, S, i; //quokka id#, day#, Happiness score, and Selfie count
    double Fc; //Food prepared, Food consumed

    vector< int > Id, day, FP, Sc;
    vector< double > FC;
      
    while( (ch = file1.peek()) != EOF ) //check for end of file
    {
        while( file1 >> id >> d >> Fp >> Fc >> H >> S )
        {
            Id.push_back(id);
            day.push_back(d);
            FP.push_back(Fp);
            FC.push_back(Fc);
            Sc.push_back(S);
        }
    }
    
   
    //Below will be the loop calculating the highest target ratio, mentioned in the analysis, over the seven day census period.
    //Also will be collective ordered pairs for the Lagrange polynomial interpolation below. 
    
    double r, tr = 0; //tr: constraint ratio defined in analysis. tr short for target ratio. r: set as a dummy ratio.
    vector < double > fc;
    vector < int > sc;

    for( unsigned int i = 0; i < Id.size(); ++i ) //Loop for 50 quokka (id#'s)
    {
        if( ( ( ( FP[i] - FC[i] ) != 0 ) && ( FC[i] != 0 )  && ( Sc[i] != 0 ) ) )  //avoids division by zero below. Also avoids waisting time on no selfie score.
        {
            r = ( Sc[i] / ( ( FC[i] ) * ( FP[i] - FC[i] ) ) );  //ratio calculation. 
                                   
            if( r > tr )
                tr = r;
            
            fc.push_back( Id[i] * FC[i] );
            sc.push_back( Id[i] * Sc[i] ); //ordered pairs for lagrange polynomial. last element of all 3d vectors are set at 0 since only one measurment is made per day.
        }                                  //multiplying by quokkas id# as an identifier.
    }

    
    /* Now we have the Lagrange Polynomial interpolation, explained in the analysis. This is coupled together with the calculation for how much food to give each
       on a day do day basis for k number of days. */  

    cout << "How close to optimal (in terms of percent) would you like to achieve with today's feeding? " << endl;
    int acc;
    cin >> acc;
    cout << "Submit Quokka's ID# for today's feeding amount: " << endl;;
    int ID; 
    cin >> ID;
    cout << "How much food did Quokka #" << ID << " consume yesterday? (in kg) " << endl;
    double f; 
    cin >> f;
    cout << "How mush food was Quokka #" << ID << " fed yesterday? (in kg) " << endl;
    double pf;
    cin >> pf;
   
    double Self, sum = 0.0;

    do{
        for( unsigned int i = 0; i < sc.size(); ++i )
        {
            if( ( sc[i] % ID ) == 0 )
            {    
                double temp = 1.0;

                for( unsigned int j = 0; j < sc.size(); ++j )
                {
                    if( i != j )
                    {
                        temp = temp * ( f - ( fc[j] / ID ) ) / ( ( fc[i] / ID ) - ( fc[j] / ID ) );
                    }
                }
        
                Self = ( sc[i] / ID ) * temp; //diving by ID in this product and in the temp calculation above extract ordered pair values from specific id.  
            
                sum = sum + Self; //expected number of selfies dependent on food consumed.
            }  //Nested loop which calculates the predicted selfie using Lagrange polynomial interpolation 
        }        
        
        if( ( ( sum / ( f * ( pf - f ) ) ) > (acc/100) * ( tr ) ) &&  ( ( sum / ( f * ( pf - f ) ) ) < ( ( ( 1 - (acc/100) ) + 1 ) * ( tr ) ) ) )
        {
            cout << "Prepare the same amount of food for today. " << endl;
            break;
        }
        else
            f = f - 0.1;
   
    } while ( ( sum / ( f * ( pf - f ) ) ) < (acc/100) * tr );
    
    cout << "Food prepared for today shall be: " << f + 0.1 << "kg." << endl;
    cout << endl;
    cout << "Rounding to the nearest whole kg is up to the individual feeder. " << endl;
}
    
int main()
{
    ifstream infile_1;

    get_open(infile_1);

    load_file(infile_1);
}
